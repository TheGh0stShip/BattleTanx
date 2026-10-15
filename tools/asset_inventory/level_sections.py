#!/usr/bin/env python3
"""Parse and validate the BattleTanx (N64 USA Rev 0) world and navigation level streams.

Usage: level_sections.py REPO_ROOT OUT_DIR
Writes OUT_DIR/world_sections.tsv and OUT_DIR/navigation_sections.tsv; exits non-zero on any failed check.
"""
import hashlib, struct, sys
from pathlib import Path

ROM_SHA1 = "535860d941738ac1210c20a9b80114fea0e0ff17"
repo, out = Path(sys.argv[1]), Path(sys.argv[2])
sys.path.insert(0, str(repo / "tools"))
import battletanx_assets as bta  # noqa: E402

rom = (repo / "baseroms/us/baserom.z64").read_bytes()
if hashlib.sha1(rom).hexdigest() != ROM_SHA1:
    sys.exit("base ROM SHA-1 mismatch")

failures = []
def check(cond, msg):
    if not cond:
        failures.append(msg)
    return cond

u8 = lambda d, o: d[o]
u16 = lambda d, o: struct.unpack_from(">H", d, o)[0]
s16 = lambda d, o: struct.unpack_from(">h", d, o)[0]
u32 = lambda d, o: struct.unpack_from(">I", d, o)[0]
s32 = lambda d, o: struct.unpack_from(">i", d, o)[0]

# (struct field, record type, record size, consumer evidence)
WORLD = [
    ("+0x00", "WorldHeader", 0x2E0, "func_80088CF0: reads +0x20 flags bit0, copies +0x00..+0x1F, +0x24..+0x27B blocks, +0x27C section1 count, +0x280 (-1 sentinel), +0x2DC index base"),
    ("+0x04", "WorldGroup", 0x14, "func_80088CF0 @0x8008937C: stride fp*5*4; u8 count@+0x0 (lhu), u16 first@+0x2 into section2, 4 words @+0x4..+0x13"),
    ("+0x08", "WorldGroupItem", 0x1C, "func_80088CF0 @0x8008946C: stride idx*7*4; u8 flags@+0x0, u8 @+0x1, u8 @+0x3 (bit7), u32 @+0x8, f32 @+0xC/+0x10, u16 @+0x14, s16 @+0x16 (-1 none), s16 @+0x18 index into section3"),
    ("+0x0C", "WorldShape", 0x0C, "func_80088CF0 @0x800895EC..0x8008A27C: stride idx*3*4; s16 fields @+0x4,+0x6,+0x8,+0xA; copy loop of 0x1C2 records step 0xC"),
    ("+0x10", "WorldSlotA", 0x04, "func_80088CF0 @0x80089300: stride fp*4; u8 @+0x0, u16 @+0x2 (scaled by 8 into a table)"),
    ("+0x14", "WorldSlotB", 0x04, "func_80088CF0 @0x8008A824: stride fp*4; u8 @+0x0, u16 @+0x2"),
    ("+0x18", "WorldLink", 0x10, "func_80088CF0 @0x8008A894: stride fp<<4; u32 key @+0x0, u16 packed @+0x4 (0x7FF/0xF800 split), u32 key @+0x8"),
    ("+0x1C", "WorldRecord16", 0x10, "func_80088CF0 @0x80088EA0: count=(off8-off7)>>4 stored at +0x20; loop @0x8008906C"),
]

NAV = [  # header offset, name, record type, size, evidence
    (0x0C, "vertices", "NavVertex", 8, "func_800E0A84/800E05A4/800E1648/800E0B00: header->vertices[i] f32 x@+0,y@+4, i < u16 @+0x08, 0 invalid"),
    (0x10, "corners", "NavCorner", 4, "func_800E1818/800E18B0/800E0E84/800E09F4: corners[i] u16 vertex@+0, u16 adjacent corner@+2; aliases section +0x14"),
    (0x14, "triangles", "NavTriangle", 12, "func_800E09B0: links + id*0xC, id < u16 @+0x0A; func_800E0870 adjacent/3 via func_800E19DC"),
    (0x18, "triangle_kinds", "u8", 1, "func_800E19DC/800DF214: kinds[id] (u8) indexes enabled table"),
    (0x1C, "kind_enabled", "u8", 1, "func_800E19DC/800DF214: enabled[kind] (u8); func_800DDBCC clears +0x9..+0xE"),
]

wrows, nrows = [], []
NAVSTATS = {}
for index, world, nav in bta.LEVEL_STREAMS:
    d = bta.decode_stream(rom, *world)
    offs = [u32(d, 4 * k) for k in range(9)]
    check(offs[0] == 0x24 and offs == sorted(offs) and offs[8] == len(d), f"L{index} world offset table")
    sizes = [offs[k + 1] - offs[k] for k in range(8)]
    counts = []
    for k, (field, rtype, rsize, ev) in enumerate(WORLD):
        check(sizes[k] % rsize == 0, f"L{index} world section {k} size 0x{sizes[k]:X} % 0x{rsize:X}")
        counts.append(sizes[k] // rsize)
    check(sizes[0] == 0x2E0, f"L{index} header size")
    h = offs[0]
    ngroups = s32(d, h + 0x27C); first = s32(d, h + 0x280)
    check(counts[1] == ngroups + (1 if first != -1 else 0), f"L{index} section1 count {counts[1]} vs header 0x27C={ngroups} 0x280={first}")
    # group -> item spans
    end = 0
    for g in range(counts[1]):
        r = offs[1] + 20 * g
        n, f0 = u16(d, r), u16(d, r + 2)
        check(f0 + n <= counts[2], f"L{index} group {g} items {f0}+{n} > {counts[2]}")
        end = max(end, f0 + n)
    check(end == counts[2], f"L{index} groups cover {end} of {counts[2]} items")
    for i in range(counts[2]):
        r = offs[2] + 28 * i
        if not (d[r] & 1):
            check(0 <= s16(d, r + 0x18) < counts[3], f"L{index} item {i} shape {s16(d, r + 0x18)} >= {counts[3]}")
    check(counts[7] == 0, f"L{index} section7 non-empty")
    for k, (field, rtype, rsize, ev) in enumerate(WORLD):
        wrows.append([index, k, field, f"0x{offs[k]:X}", f"0x{offs[k+1]:X}", rtype, f"0x{rsize:X}", counts[k], ev])
    if not nav:
        continue
    d = bta.decode_stream(rom, *nav)
    size, size2, nv, nt = struct.unpack_from(">IIHH", d, 0)
    no = [u32(d, o) for o in (0x0C, 0x10, 0x14, 0x18, 0x1C)]
    check(size == size2 == len(d), f"N{index} size words")
    check(no[0] == 0x28 and d[0x20:0x28] == bytes.fromhex("0200000000000000"), f"N{index} header tail")
    check(no[1] == no[2], f"N{index} corners alias triangles")
    vend = no[0] + 8 * nv; tend = no[2] + 12 * nt; kend = no[3] + nt
    check(vend == no[1], f"N{index} vertex section size")
    check(d[tend:no[3]] == bytes(no[3] - tend) and no[3] - tend < 8 and no[3] % 8 == 0, f"N{index} triangle padding")
    check(d[kend:no[4]] == bytes(no[4] - kend) and no[4] - kend < 8, f"N{index} kind padding")
    check(len(d) - no[4] == 0x100, f"N{index} enabled table size")
    check(d[0:8 + 0] and d[no[0]:no[0] + 8] == bytes(8) and d[no[2]:no[2] + 12] == bytes(12), f"N{index} null records")
    cv = lambda c: u16(d, no[2] + 4 * c)
    nx = lambda c: c - c % 3 + (c % 3 + 1) % 3
    degenerate = {t for t in range(1, nt) if len({cv(3 * t + k) for k in range(3)}) < 3}
    nontwin = 0
    for c in range(3 * nt):
        v, adj = cv(c), u16(d, no[2] + 4 * c + 2)
        check(c < 3 or 0 < v < nv, f"N{index} corner {c} vertex {v}")
        if adj:
            check(3 <= adj < 3 * nt, f"N{index} corner {c} adjacency {adj} out of range")
            if not (cv(adj) == cv(nx(c)) and cv(nx(adj)) == v):
                nontwin += 1
                check(c // 3 in degenerate, f"N{index} corner {c} adjacency {adj} is not the reversed edge")
    check(nontwin == len(degenerate), f"N{index} non-twin edges {nontwin} != degenerate triangles {len(degenerate)}")
    NAVSTATS[index] = (nv, nt, len(degenerate))
    check(max(d[no[3]:kend]) < 0x100, "kinds")
    spans = [(0x0C, no[0], vend, nv, 8), (0x10, no[1], no[1], 3 * nt, 4), (0x14, no[2], tend, nt, 12),
             (0x18, no[3], kend, nt, 1), (0x1C, no[4], len(d), 0x100, 1)]
    for (ho, name, rtype, rsize, ev), (_, s, e, n, _) in zip(NAV, spans):
        if ho == 0x10:
            e = tend
        nrows.append([index, f"+0x{ho:02X}", name, f"0x{s:X}", f"0x{e:X}", rtype, rsize, n, ev])
    nrows.append([index, "pad", "triangle_pad", f"0x{tend:X}", f"0x{no[3]:X}", "zero fill 0x00", 1, no[3] - tend, "alignment to 8 before +0x18"])
    nrows.append([index, "pad", "kind_pad", f"0x{kend:X}", f"0x{no[4]:X}", "zero fill 0x00", 1, no[4] - kend, "fill before +0x1C"])

hdr_w = ["level", "section", "struct_field", "start", "end", "record_type", "record_size", "count", "consumer_evidence"]
hdr_n = ["level", "header_field", "section", "start", "end", "record_type", "record_size", "count", "consumer_evidence"]
out.mkdir(parents=True, exist_ok=True)
(out / "world_sections.tsv").write_text("\n".join("\t".join(map(str, r)) for r in [hdr_w] + wrows) + "\n")
(out / "navigation_sections.tsv").write_text("\n".join("\t".join(map(str, r)) for r in [hdr_n] + nrows) + "\n")
print(f"{len(wrows)} world rows, {len(nrows)} navigation rows, {len(failures)} failures")
for f in failures[:40]:
    print("FAIL", f)
sys.exit(1 if failures else 0)
