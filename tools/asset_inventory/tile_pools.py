#!/usr/bin/env python3
"""Parse and validate the BattleTanx (USA Rev 0) world tile pools.

Pools:
  geometry pool  ROM 0x3EA970..0x49C740  (base symbol D_B03EA970)
  texture pool   ROM 0x5A1110..0x6F9C40  (base symbol D_B05A1110)

Index: section 6 of each decoded world stream (func_80088CF0 stores
stream+offset[6] at model+0x18) is an array of 16-byte tile records
  u32 tex_off; u16 flags; u16 tex_size; u32 geo_off; u32 geo_size
func_8008716C builds per-level unique lists keyed on tex_off / geo_off;
func_80088CF0 DMAs tex_off+D_B05A1110 / geo_off+D_B03EA970 (func_80077930)
and relocates: func_800852E0 adds the buffer address to every G_SETTIMG (0xFD)
word, func_80085290 (and copy_model_leaf func_800880B4) to every G_VTX (0x04)
word; both stop at G_ENDDL 0xB8000000.

Writes models.tsv, textures.tsv, ledger.tsv into the output directory.
"""
import hashlib
import struct
import sys
from pathlib import Path

REPO = Path(__file__).resolve().parents[0]
ROM_SHA1 = "535860d941738ac1210c20a9b80114fea0e0ff17"
GEO_BASE, GEO_END = 0x3EA970, 0x49C740
TEX_BASE, TEX_END = 0x5A1110, 0x6F9C40
RECORD = struct.Struct(">IHHII")

# Commands that are accepted and carry no external data (F3DEX 1.x opcodes).
PLAIN = {0xB1, 0xB6, 0xB7, 0xB9, 0xBA, 0xBB, 0xBF, 0xE6, 0xE7, 0xE8, 0xF2,
         0xF5, 0xF7, 0xF8, 0xFA, 0xFB, 0xFC, 0xF3, 0xF0}
SIZ_BITS = {0: 4, 1: 8, 2: 16, 3: 32}
FMT = {0: "RGBA", 1: "YUV", 2: "CI", 3: "IA", 4: "I"}


class ParseError(Exception):
    pass


def walk_dl(blob):
    """Return (dl_end, commands) for a display list at blob offset 0."""
    cmds = []
    for pos in range(0, len(blob) - 7, 8):
        w0, w1 = struct.unpack_from(">II", blob, pos)
        op = w0 >> 24
        cmds.append((pos, op, w0, w1))
        if op == 0xB8:
            if w1 != 0 or w0 != 0xB8000000:
                raise ParseError(f"bad G_ENDDL at 0x{pos:X}")
            return pos + 8, cmds
        if op not in PLAIN and op not in (0x04, 0xFD):
            raise ParseError(f"unexpected opcode 0x{op:02X} at 0x{pos:X}")
    raise ParseError("no G_ENDDL")


def parse_geometry(blob):
    """Geometry blob: display list + vertex arrays referenced by G_VTX."""
    end, cmds = walk_dl(blob)
    spans = [(0, end, "display_list")]
    vtx = set()
    loaded = 0
    verts = 0
    for pos, op, w0, w1 in cmds:
        if op == 0x04:
            n = (w0 >> 10) & 0x3F
            length = (w0 & 0x3FF) + 1
            v0 = ((w0 >> 16) & 0xFF) // 2
            if length != n * 16 or w1 % 8 or w1 + length > len(blob) or w1 < end:
                raise ParseError(f"bad G_VTX at 0x{pos:X}")
            vtx.add((w1, w1 + length))
            loaded = v0 + n
        elif op == 0xBF:
            idx = [(w1 >> s) & 0xFF for s in (16, 8, 0)]
            if any(i % 2 or i // 2 >= loaded for i in idx):
                raise ParseError(f"triangle index beyond loaded vertices at 0x{pos:X}")
        elif op == 0xFD:
            raise ParseError("G_SETTIMG inside geometry blob")
    for s, e in merge(vtx):
        spans.append((s, e, "vertices"))
        verts += (e - s) // 16
    return {"dl_cmds": len(cmds), "vtx_cmds": len(vtx), "vertices": verts,
            "tris": sum(1 for c in cmds if c[1] == 0xBF), "spans": spans}


def parse_texture(blob):
    """Texture blob: display list + image/TLUT data referenced by G_SETTIMG."""
    end, cmds = walk_dl(blob)
    spans = [(0, end, "display_list")]
    timg = None
    tiles = {}
    images, palettes = [], []
    for pos, op, w0, w1 in cmds:
        if op == 0xFD:
            timg = ((w0 >> 21) & 7, (w0 >> 19) & 3, (w0 & 0xFFF) + 1, w1)
        elif op == 0xF5:
            tiles[(w1 >> 24) & 7] = {"fmt": (w0 >> 21) & 7, "siz": (w0 >> 19) & 3,
                                     "tmem": w0 & 0x1FF, "pal": (w1 >> 20) & 0xF}
        elif op == 0xF3:  # G_LOADBLOCK
            texels = ((w1 >> 12) & 0xFFF) + 1
            nbytes = texels * SIZ_BITS[timg[1]] // 8
            images.append({"addr": timg[3], "bytes": nbytes, "load_fmt": timg[0], "load_siz": timg[1]})
        elif op == 0xF0:  # G_LOADTLUT
            count = ((w1 >> 14) & 0x3FF) + 1
            palettes.append({"addr": timg[3], "bytes": count * 2, "colours": count})
        elif op == 0xF2:
            t = (w1 >> 24) & 7
            if t in tiles and images:
                tiles[t]["w"] = ((((w1 >> 12) & 0xFFF) - ((w0 >> 12) & 0xFFF)) >> 2) + 1
                tiles[t]["h"] = (((w1 & 0xFFF) - (w0 & 0xFFF)) >> 2) + 1
    if not images and not palettes and timg is None:
        return {"dl_cmds": len(cmds), "image": None, "palettes": [], "spans": spans}
    rt = tiles.get(0)
    if rt is None or len(images) != 1:
        raise ParseError(f"expected one LOADBLOCK and render tile 0, got {len(images)}")
    img = images[0]
    img.update(fmt=FMT[rt["fmt"]], siz=SIZ_BITS[rt["siz"]], w=rt["w"], h=rt["h"])
    if img["w"] * img["h"] * img["siz"] // 8 != img["bytes"]:
        raise ParseError("render tile dimensions do not match the loaded bytes")
    if (rt["fmt"] == 2) != bool(palettes):
        raise ParseError("palette presence does not match the render format")
    for item, kind in [(img, "texture")] + [(p, "palette") for p in palettes]:
        a = item["addr"]
        if a < end or a + item["bytes"] > len(blob) or a % 8:
            raise ParseError(f"{kind} at 0x{a:X} outside blob or misaligned")
        spans.append((a, a + item["bytes"], kind))
    return {"dl_cmds": len(cmds), "image": img, "palettes": palettes, "spans": spans}


def merge(ivs):
    out = []
    for s, e in sorted(ivs):
        if out and s <= out[-1][1]:
            out[-1] = (out[-1][0], max(out[-1][1], e))
        else:
            out.append((s, e))
    return out


def fill_spans(blob, spans, base):
    """Order spans, fill holes as padding (if all one byte) or unknown."""
    spans = sorted(spans)
    out, cur = [], 0
    for s, e, k in spans:
        if s < cur:
            raise ParseError(f"overlap at 0x{base + s:X}")
        if s > cur:
            out.append((cur, s, hole_kind(blob[cur:s], out[-1][2] if out else None)))
        out.append((s, e, k))
        cur = e
    if cur < len(blob):
        out.append((cur, len(blob), hole_kind(blob[cur:], out[-1][2] if out else None)))
    return out


GBI_OPS = PLAIN | {0x04, 0xFD, 0xB8}


def hole_kind(b, prev=None):
    if prev == "palette" and b == bytes.fromhex("0000000000000010"):
        return "palette_trailer"  # 8 bytes after each 16-entry TLUT; outside the LOADTLUT count
    if prev == "display_list" and len(b) % 8 == 0 and len(set(b)) > 1 and \
            all(b[i] in GBI_OPS for i in range(0, len(b), 8)):
        return "dead_dl_commands"  # GBI words after G_ENDDL; never executed or relocated
    return f"padding(0x{b[0]:02X})" if len(set(b)) == 1 else "unknown"


def main():
    out_dir = Path(sys.argv[2])
    repo = Path(sys.argv[1])
    sys.path.insert(0, str(repo / "tools"))
    import battletanx_assets as A

    rom = (repo / "baseroms/us/baserom.z64").read_bytes()
    if hashlib.sha1(rom).hexdigest() != ROM_SHA1:
        raise SystemExit("ROM SHA-1 mismatch")

    geo, tex = {}, {}
    for level, world, _nav in A.LEVEL_STREAMS:
        data = A.decode_stream(rom, *world)
        off = A.be_u32_array(data, 0, 9)
        for i in range(off[6], off[7], 16):
            t, flags, tsize, g, gsize = RECORD.unpack_from(data, i)
            if not (t or tsize or g or gsize):
                continue
            for d, key, size in ((tex, t, tsize), (geo, g, gsize)):
                ent = d.setdefault(key, {"size": size, "levels": set(), "pairs": set()})
                if ent["size"] != size:
                    raise ParseError(f"offset 0x{key:X} referenced with two sizes")
                ent["levels"].add(level)
            geo[g]["pairs"].add(t)
            tex[t]["pairs"].add(g)

    ledger, models, textures = [], [], []

    def pool(entries, base, end, parser, label):
        cur = base
        for off in sorted(entries):
            e = entries[off]
            s, stop = base + off, base + off + e["size"]
            if s < cur:
                raise ParseError(f"{label} blob 0x{s:X} overlaps")
            if s > cur:
                gap(cur, s)
            blob = rom[s:stop]
            info = parser(blob)
            e["info"] = info
            for a, b, k in fill_spans(blob, info["spans"], s):
                ledger.append((s + a, s + b, f"{label}_{k}",
                               f"{label} tile blob +0x{off:X} (levels {sorted(e['levels'])})"))
            cur = stop
        if cur < end:
            gap(cur, end)

    def gap(a, b):
        blob = rom[a:b]
        if len(set(blob)) == 1:
            ledger.append((a, b, f"padding(0x{blob[0]:02X})", "no tile record references these bytes"))
            return
        # Structural probe only: chain geometry-shaped blobs; no consumer record exists.
        pos = a
        while pos < b:
            try:
                end, _ = walk_dl(rom[pos:b])
                info = parse_geometry(rom[pos:b])
                last = max(e for _, e, _ in info["spans"])
            except ParseError:
                ledger.append((pos, b, "unknown", "unreferenced; does not parse as a geometry blob"))
                return
            ledger.append((pos, pos + last, "unknown_unreferenced_geometry",
                           f"parses as DL+{info['vertices']} vertices but no world tile record references it"))
            pos += last

    pool(geo, GEO_BASE, GEO_END, parse_geometry, "geometry")
    pool(tex, TEX_BASE, TEX_END, parse_texture, "texture")

    # Completeness / non-overlap check across both ranges.
    ledger.sort()
    for (a, b, *_), (c, *_r) in zip(ledger, ledger[1:]):
        if b != c and not (b == GEO_END and c == TEX_BASE):
            raise ParseError(f"ledger discontinuity at 0x{b:X}")
    assert ledger[0][0] == GEO_BASE and ledger[-1][1] == TEX_END

    for off in sorted(geo):
        e = geo[off]
        i = e["info"]
        models.append((f"geo_{off:06X}", f"0x{GEO_BASE + off:06X}", f"0x{GEO_BASE + off + e['size']:06X}",
                       i["dl_cmds"], i["vtx_cmds"], i["vertices"], i["tris"],
                       ",".join(f"tex_{t:06X}" for t in sorted(e["pairs"])),
                       ",".join(map(str, sorted(e["levels"])))))
    for off in sorted(tex):
        e = tex[off]
        im = e["info"]["image"]
        pal = e["info"]["palettes"]
        s = TEX_BASE + off
        if im is None:
            textures.append((f"tex_{off:06X}", f"0x{s:06X}", f"0x{s + e['size']:06X}", "-", "-",
                             "none(prim colour DL)", 0, "-", "-", ",".join(map(str, sorted(e["levels"])))))
            continue
        textures.append((f"tex_{off:06X}", f"0x{s:06X}", f"0x{s + e['size']:06X}",
                         f"0x{s + im['addr']:06X}", f"0x{s + im['addr'] + im['bytes']:06X}",
                         f"{im['fmt']}{im['siz']}", im["bytes"], f"{im['w']}x{im['h']}",
                         ",".join(f"0x{s + p['addr']:06X}-0x{s + p['addr'] + p['bytes']:06X}({p['colours']})"
                                  for p in pal) or "-",
                         ",".join(map(str, sorted(e["levels"])))))

    def write(name, header, rows):
        with open(out_dir / name, "w") as f:
            f.write("\t".join(header) + "\n")
            for r in rows:
                f.write("\t".join(str(x) for x in r) + "\n")

    write("models.tsv", ["model_id", "rom_start", "rom_end", "dl_commands", "vtx_loads", "vertices",
                         "triangles", "textures_paired", "levels"], models)
    write("textures.tsv", ["texture_id", "blob_start", "blob_end", "image_start", "image_end", "format",
                           "image_bytes", "dims", "palette", "levels"], textures)
    write("ledger.tsv", ["rom_start", "rom_end", "size", "kind", "evidence"],
          [(f"0x{a:06X}", f"0x{b:06X}", b - a, k, ev) for a, b, k, ev in ledger])

    totals = {}
    for a, b, k, _ in ledger:
        totals[k] = totals.get(k, 0) + b - a
    for k in sorted(totals):
        print(f"{k}\t{totals[k]}")
    print("geometry blobs", len(models), "texture blobs", len(textures))


if __name__ == "__main__":
    main()
