#!/usr/bin/env python3
"""Classify every entry of every BattleTanx (USA Rev 0) resource bundle.

Bundle layout (as consumed by the game):
    u32 count; u32 offset[count]; u32 0;  (padded to 8)
offset[i] is relative to the start of the decoded bundle (NOT to the
payload).  Entry i spans [offset[i], offset[i+1]) and the last entry runs to
the end of the decoded data.  Consumers fetch entry i as
    base + *(u32 *)(base + 4 + 4*i)
(`lw rX, (4+4i)(base); addu rX, rX, base`).

Consumer evidence is recovered from retail assembly (asm/us/functions) by
bundle_consumers.py (constant/entry-offset propagation up to each draw call), then size
arithmetic is checked against the decoded bytes.

Usage: parse_bundle_entries.py [--repo PATH] [--out DIR] [--extract]
"""
import argparse
import hashlib
import struct
import sys
from collections import defaultdict
from pathlib import Path

HERE = Path(__file__).resolve().parent
ROM_SHA1 = "535860d941738ac1210c20a9b80114fea0e0ff17"

# Consumer function -> bundle resident in the screen buffer (mode 1 / current)
# while it draws.  Evidence for the pairing is in report.md.
SCREEN = {
    "func_800CAA04": "bundle_49C740", "func_800CC4E4": "bundle_4B39B0", "func_800C83D4": "bundle_3DC430",
    "func_800DAE30": "bundle_4AC150", "func_800CE554": "bundle_4B1300", "func_800CFEB0": "bundle_4B1300",
    "func_800D455C": "bundle_4AD7E0", "func_800D9134": "bundle_3DFD10", "func_800C5C60": "bundle_3D6940",
    "func_800D6BC0": "bundle_3D16D0", "func_800C5580": "bundle_49DCD0", "func_800D0DAC": "bundle_4B3280",
    "func_800C4090": "bundle_596EA0",
    # story slides: func_800B1520 switch on D_803276E0; func_800AC2E0 loads per chapter
    "func_800AD340": "bundle_4B4B00", "func_800AD5A0": "bundle_4B4B00", "func_800AD828": "bundle_4B4B00",
    "func_800ADD70": "bundle_4C1930", "func_800AE2B8": "bundle_4C1930", "func_800AE800": "bundle_4C1930",
    "func_800AEA50": "bundle_4C1930", "func_800AEF98": "bundle_4E46E0", "func_800AF534": "bundle_4E46E0",
    "func_800AFB08": "bundle_4E46E0", "func_800B0210": "bundle_4E46E0", "func_800B0440": "bundle_50D930",
    "func_800B098C": "bundle_50D930", "func_800B0D1C": "bundle_50D930", "func_800B1264": "bundle_50D930",
    # story slides: func_800BB69C / func_800BE99C / func_800C224C
    "func_800BA764": "bundle_533870", "func_800BA960": "bundle_533870", "func_800BAB5C": "bundle_533870",
    "func_800BAD58": "bundle_533870", "func_800BB254": "bundle_533870", "func_800BB450": "bundle_533870",
    "func_800BD994": "bundle_554D00", "func_800BDEF8": "bundle_554D00", "func_800BE45C": "bundle_554D00",
    "func_800C0EDC": "bundle_56FDB0", "func_800C10D8": "bundle_56FDB0", "func_800C12D4": "bundle_56FDB0",
    "func_800C17D0": "bundle_56FDB0", "func_800C1B54": "bundle_58AE00", "func_800C2050": "bundle_58AE00",
}
STORY = {b for f, b in SCREEN.items() if f < "func_800C3000" and f > "func_800AD000"}
STRIPS = [f"bundle_strip_{i}" for i in range(10)]
STRIP_WIDTH = (130, 145, 175, 139, 127, 172, 134, 128, 163, 149)  # D_80134030, ROM 0xC4030

# Entries whose index is chosen at run time from a word table in program data
# (table value v selects entry v-1).  (bundle, entries, fmt, w, h, consumer evidence)
DYNAMIC = [
    ("bundle_3D6940", (1, 17, 18, 19, 20, 21, 22, 24, 27, 29), "CI8", 23, 23,
     "func_800C5C60@0x800C6508/0x800C6644 word index from D_80134A28[strip]/D_80134A50[strip]"),
    ("bundle_3DC430", (1, 9, 10, 11, 12, 13, 14, 16, 17, 19), "CI8", 23, 23,
     "func_800C83D4@0x800C91A8/0x800C92D4 word index from D_80134AD4[strip]/D_80134AFC[strip]"),
    ("bundle_3DFD10", (4, 5, 6, 7, 8), "CI8", 64, 64,
     "func_800D9134@0x800D9CA0 word index from D_8013555C[0..4] = 8,5,7,9,6"),
    ("bundle_4AD7E0", (15, 18, 21), "CI8", 65, 18,
     "func_800D455C@0x800D5150 word index from D_80134FF0[1..3] = 16,19,22"),
    ("bundle_4AD7E0", (14, 17, 20), "CI8", 5, 131,
     "func_800D455C@0x800D529C word index from D_80135000[1..3] = 15,18,21"),
    ("bundle_4AD7E0", (13, 16, 19), "CI8", 65, 5,
     "func_800D455C@0x800D53EC word index from D_80135010[1..3] = 14,17,20"),
]
# Size-arithmetic hints for entries with no consumer found.
UNKNOWN_HINT = {
    ("bundle_3D6940", 10): "size 0xAA0 = 0x200+276*8 (CI8 276x8 shape); no reader of offset word +0x2C found",
    ("bundle_3D6940", 23): "size 0x418 = 0x200+23*23+7; not selected by D_80134A28/D_80134A50",
    ("bundle_3DC430", 15): "size 0x418 = 0x200+23*23+7; not selected by D_80134AD4/D_80134AFC",
    ("bundle_4B39B0", 1): "size 0x268 = 0x200+8*13 (same shape as entry 0); no reader of offset word +0x8 found",
    ("bundle_4AD7E0", 24): "size 0x1A50 (0x200 + 0x1850); no reader of offset word +0x64 found",
}
for _i in range(9):
    UNKNOWN_HINT[("bundle_4AD7E0", _i)] = ("size 0x258 = 0x200+9*9+7 (CI8 9x9 shape); func_800D455C has a "
                                           "dynamic 9x9 draw at 0x800D5728 whose index source (D_80135020) is unresolved")
for _s in STRIPS:
    UNKNOWN_HINT[(_s, 3)] = "ASCII text, CRLF lines, NUL padded (faction description); no reader of offset word +0x10 found"
    UNKNOWN_HINT[(_s, 4)] = "ASCII text, CRLF lines, NUL terminated (unit roster); no reader of offset word +0x14 found"

BPP = {"CI8": 1.0, "CI4": 0.5, "IA8": 1.0}


def decode_all(repo: Path):
    sys.path.insert(0, str(repo / "tools"))
    import battletanx_assets as b  # noqa: E402
    rom_path = repo / "baseroms/us/baserom.z64"
    raw = rom_path.read_bytes()
    if hashlib.sha1(raw).hexdigest() != ROM_SHA1:
        raise SystemExit("unsupported ROM (SHA-1 mismatch)")
    rom = b.load_rom(rom_path)
    out = {}
    for r in (*b.RESOURCE_BUNDLES, *b.read_pi_table(rom, b.RESOURCE_BUNDLE_STRIP_TABLE)):
        d = b.decode_resource(rom, r)
        n = struct.unpack_from(">I", d)[0]
        offs = list(struct.unpack_from(f">{n}I", d, 4))
        assert struct.unpack_from(">I", d, 4 + 4 * n)[0] == 0, r.name
        assert offs[0] == (8 + 4 * n + 7) & ~7, r.name
        assert offs == sorted(offs) and offs[-1] <= len(d), r.name
        out[r.name] = (r, d, list(zip(offs, offs[1:] + [len(d)])))
    return out


def observations(repo: Path):
    sys.path.insert(0, str(HERE))
    import bundle_consumers as track
    track.ASM = str(repo / "asm/us/functions")
    fmt = track.fmt
    obs = defaultdict(list)
    for f, bundle in SCREEN.items():
        for o in fmt(f):
            addr, mode, kind = o[0], o[1], o[2]
            if kind not in ("draw3D40", "draw41C0") or not o[3] or o[3][0] != "E":
                continue
            idx = (o[3][1] - 4) // 4
            targets = [bundle] if mode in ("S", 1) else ["bundle_2D2790"] if mode == 0 else STRIPS if mode == 4 else []
            for t in targets:
                obs[(t, idx)].append((f, addr, kind, o[3][2], o[4], o[5], o[6], o[7] if len(o) > 7 else None))
    return obs


def classify(B, obs):
    rows = []
    dyn = {}
    for bundle, idxs, f_, w, h, ev in DYNAMIC:
        for i in idxs:
            dyn[(bundle, i)] = (f_, w, h, ev)
    for name, (r, d, ents) in B.items():
        strip = name.startswith("bundle_strip")
        for i, (s, e) in enumerate(ents):
            size = e - s
            key = (name, i)
            fmt_, w, h, tex, consumers, ev, cat, note = None, None, None, 0, [], [], "unknown", ""
            o = obs.get(key, [])
            if strip and i == 2:
                fmt_, w, h, tex = "CI4", 130, 51, 0xA0
                consumers = ["func_800C5C60", "func_800C83D4"]
                ev = ["func_800C5C60@0x800C63A4 func_800F41C0(texels=entry+0xA0, w=130, h=51) TLUT 16 colours "
                      "(G_LOADTLUT 0x0703C000) from entry+0 (mode 4 buffer)",
                      "func_800C83D4@0x800C907C texels via slot base+0xA000+i*0xBC00, word +0xC; palette "
                      "entry+(D_80134B24[..]<<5)"]
                note = "5 x 16-colour RGBA5551 palettes at +0x00..+0xA0"
                cat = "image"
            elif strip and i == 5:
                k = int(name.rsplit("_", 1)[1])
                fmt_, w, h, tex = "CI8", STRIP_WIDTH[k], 21, 0x200
                consumers = ["func_800C5C60"]
                ev = [f"func_800C5C60@0x800C76F8 draw_paletted_image(entry+0x200, CI 8b, w=D_80134030[{k}]={w}, h=21) mode 4"]
                cat = "image"
            elif name == "bundle_4AC150" and i == 7:
                fmt_, w, h, tex = "IA8", 24, 21, 0
                consumers = ["func_800DAE30"]
                ev = ["func_800DAE30@0x800DBCB0 draw_paletted_image(entry+0, fmt=3 IA, siz=1 8b, load 24x24, "
                      "drawn 21x21); bytes = 24*21"]
                note = "texture load requests 24 rows; only 21 rows (504 bytes) are in the entry"
                cat = "image"
            elif o:
                vals = sorted({(x[3], x[4], x[5], x[6], x[7]) for x in o if isinstance(x[6], int)})
                add, f1, f2, w, h = vals[0]
                if f1 == 2 and f2 == 1 and add == 0x200:
                    fmt_, tex = "CI8", 0x200
                consumers = sorted({x[0] for x in o})
                ev = [f"{x[0]}@{x[1].upper().replace('0X', '0x')} draw_paletted_image(entry+0x{x[3]:X}, fmt={x[4]}, "
                      f"siz={x[5]}, {x[6]}x{x[7]})" for x in sorted(o)[:3]]
                if len(o) > 3:
                    ev.append(f"+{len(o) - 3} more draw sites")
                if name == "bundle_2D2790" and i in (14, 15):
                    h = 185
                    note = "drawn with height 183; data holds 185 rows"
                cat = "image"
            elif key in dyn:
                fmt_, w, h, ev1 = dyn[key]
                tex = 0x200
                consumers = [ev1.split("@")[0]]
                ev = [ev1]
                cat = "image"
            if fmt_:
                need = tex + int(w * h * BPP[fmt_] + 0.5)
                tail = size - need
                if tail < 0:
                    raise SystemExit(f"{name}[{i}] too small for {fmt_} {w}x{h}")
                fill = set(d[s + need:e])
                if tail:
                    note = (note + "; " if note else "") + f"0x{tail:X} trailing bytes" + (
                        " (fill 0x00)" if fill == {0} else " (non-zero)")
                if tail >= 8 and not (strip and i == 2) and not (name == "bundle_2D2790" and i in (14, 15)):
                    note += "; tail >= 8"
                cat = "story_image" if name in STORY else "ui_image"
                dims = f"{w}x{h}"
                fdesc = {"CI8": "CI8 (pal 0x200 @+0, texels @+0x200)", "CI4": "CI4 (texels @+0xA0)",
                         "IA8": "IA8"}[fmt_]
                label = f"{name[7:]}_{i:02d}_{cat}_{dims}"
            else:
                fdesc, dims = "unknown", ""
                hint = UNKNOWN_HINT.get(key, "no consumer found")
                ev = ["needs: a reader of offset word +0x%X of this bundle" % (4 + 4 * i), hint]
                label = f"{name[7:]}_{i:02d}_unknown"
            rows.append(dict(bundle=name, rom=f"0x{r.rom_start:06X}-0x{r.rom_end:06X}", index=i,
                             start=f"0x{s:05X}", end=f"0x{e:05X}", size=f"0x{size:X}", format=fdesc, dims=dims,
                             consumer=",".join(c.replace("func_", "") for c in consumers) or "-",
                             category=cat, name=label, evidence=" | ".join(ev + ([note] if note else [])),
                             sha1=hashlib.sha1(d[s:e]).hexdigest()[:12], _size=size, _data=d[s:e]))
    return rows


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--repo", type=Path, required=True)
    ap.add_argument("--out", type=Path, required=True)
    ap.add_argument("--extract", action="store_true", help="write raw entry payloads to OUT/out/")
    a = ap.parse_args()
    B = decode_all(a.repo)
    rows = classify(B, observations(a.repo))
    cols = ["bundle", "rom", "index", "start", "end", "size", "format", "dims", "consumer", "category", "name",
            "sha1", "evidence"]
    with open(a.out / "bundle_entries.tsv", "w") as fh:
        fh.write("\t".join(cols) + "\n")
        for r in rows:
            fh.write("\t".join(str(r[c]) for c in cols) + "\n")
    tot = defaultdict(int)
    for r in rows:
        tot[r["category"]] += r["_size"]
        if a.extract:
            p = a.out / "out" / r["bundle"]
            p.mkdir(parents=True, exist_ok=True)
            (p / f"{r['index']:02d}.bin").write_bytes(r["_data"])
    hdr = sum(ents[0][0] for _, _, ents in B.values())
    print(f"bundles={len(B)} entries={len(rows)} header_bytes=0x{hdr:X}")
    for k, v in sorted(tot.items()):
        print(f"{k:14s} {sum(1 for r in rows if r['category'] == k):4d} entries 0x{v:06X} bytes")


if __name__ == "__main__":
    main()
