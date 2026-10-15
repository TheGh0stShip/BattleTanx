#!/usr/bin/env python3
"""Parse and validate the BattleTanx (USA Rev 0) ROM ranges covered by this ledger.

Usage: classify_regions.py <repo> <outdir>
Writes ledger.tsv, pack_entries.tsv, recordings.tsv, unknown_2c19b0.tsv and
extracts payloads under <outdir>/out/.  Every check raises on mismatch.
"""
import hashlib
import math
import os
import struct
import sys

ROM_SHA1 = "535860d941738ac1210c20a9b80114fea0e0ff17"
REPO, OUTDIR = sys.argv[1], sys.argv[2]
sys.path.insert(0, os.path.join(REPO, "tools"))
import lzari  # noqa: E402

rom = open(os.path.join(REPO, "baseroms/us/baserom.z64"), "rb").read()
if hashlib.sha1(rom).hexdigest() != ROM_SHA1 or len(rom) != 0x800000:
    sys.exit("base ROM SHA-1 mismatch")

u32 = lambda a: struct.unpack_from(">I", rom, a)[0]
ledger = []  # (start, end, kind, name, format, evidence)


def check(cond, msg):
    if not cond:
        raise SystemExit("CHECK FAILED: " + msg)


def add(start, end, kind, name, fmt, evidence):
    check(start < end, f"empty interval {name}")
    ledger.append((start, end, kind, name, fmt, evidence))


def dump(name, data):
    os.makedirs(os.path.join(OUTDIR, "out"), exist_ok=True)
    with open(os.path.join(OUTDIR, "out", name), "wb") as fh:
        fh.write(data)


# ---------------------------------------------------------------- (4) header + IPL3
def cic6102_crc(r):
    mask = 0xFFFFFFFF
    seed = 0xF8CA4DDC
    t1 = t2 = t3 = t4 = t5 = t6 = seed
    for i in range(0x1000, 0x101000, 4):
        d = struct.unpack_from(">I", r, i)[0]
        if (t6 + d) & mask < t6:
            t4 = (t4 + 1) & mask
        t6 = (t6 + d) & mask
        t3 ^= d
        rot = d & 0x1F
        rv = ((d << rot) | (d >> (32 - rot))) & mask if rot else d
        t5 = (t5 + rv) & mask
        t2 = t2 ^ rv if t2 > d else t2 ^ (t6 ^ d)
        t1 = (t1 + (t5 ^ d)) & mask
    return (t6 ^ t4 ^ t3) & mask, (t5 ^ t2 ^ t1) & mask


crc1, crc2 = cic6102_crc(rom)
check((crc1, crc2) == (u32(0x10), u32(0x14)), "header CRC (CIC-6102 algorithm) mismatch")
check(u32(0x8) == 0x80071000, "header entry point")
check(rom[0x20:0x34] == b"BATTLETANX          ", "header title")
add(0x0, 0x40, "rom_metadata", "cartridge_header",
    "N64 cartridge header: PI config 0x80371240, clock 0x0F, entry 0x80071000, CRC 0x6AA4DDE7/0xE3E2F4E7, "
    "title 'BATTLETANX', game code NBXE rev 0",
    "CRC pair recomputed over ROM 0x1000..0x101000 with the CIC-6102 algorithm matches header words 0x10/0x14")
ipl3_md5 = hashlib.md5(rom[0x40:0x1000]).hexdigest()
check(ipl3_md5 == "e24dd796b2fa16511521139d28c8356b", "IPL3 digest")
add(0x40, 0x1000, "rom_metadata", "ipl3_bootcode",
    f"RSP/CPU boot code (IPL3), md5 {ipl3_md5}",
    "CIC-6102 checksum algorithm validates the header CRC; IPL3 copies ROM 0x1000..0x101000 to 0x80071000 (entry)")

# ---------------------------------------------------------------- (4) 0xD7040..0x101000
# entrypoint (src/boot/entry.s) zeroes 0x80147040..0x803C8880 before calling main, so
# the IPL3 copy of ROM 0xD7040..0x101000 (VRAM 0x80147040..0x80171000) is discarded.
check(u32(0x1000) == 0x3C1D8015 and u32(0x1008) == 0x3C088014 and u32(0x100C) == 0x25087040,
      "entrypoint BSS clear start 0x80147040")
check(u32(0x1010) == 0x3C09803D and u32(0x1014) == 0x25298880, "entrypoint BSS clear end 0x803C8880")
seg = rom[0xD7040:0xD7360]
vps = [struct.unpack_from(">8h", seg, i * 16) for i in range(8)]
check(all(v[2] == 0x1FF and v[6] == 0x1FF for v in vps), "Vp scale/translate z = 0x1FF")
for off in range(0x80, 0x320, 8):  # every word pair must be an F3D/RDP command
    check(seg[off] in (0x03, 0xB6, 0xB7, 0xB8, 0xB9, 0xBA, 0xBB, 0xBC, 0xE7, 0xEA, 0xEB, 0xEC, 0xED, 0xEE,
                       0xF2, 0xF5, 0xF7, 0xF8, 0xF9, 0xFA, 0xFB, 0xFC), f"F3D opcode at seg+0x{off:X}")
check(seg[0x318] == 0xB8, "segment block ends with G_ENDDL")
dump("seg1_static_D7040.bin", seg)
add(0xD7040, 0xD7360, "payload", "segment1_static_gfx",
    "8 Vp viewports (0x80 B, 16 B each: scale/translate s16x4) + F3D display lists 0x80..0x320 "
    "(render-mode setup, 8 viewport/scissor lists, tile clears) ending in G_ENDDL",
    "initialize_runtime_buffers (func_8007D4E8) rom_dma_read(D_B00D7040, 0x803C8880, D_B00D7360-D_B00D7040); "
    "build_runtime_display_list emits G_MOVEWORD segment (0xBC000406) with that base")
tail = rom[0xD7360:0x100000]
zero_runs = []
i = 0
while i < len(tail):
    if tail[i] == 0:
        j = i
        while j < len(tail) and tail[j] == 0:
            j += 1
        if j - i >= 0x100:
            zero_runs.append((0xD7360 + i, 0xD7360 + j))
        i = j
    else:
        i += 1
add(0xD7360, 0x100000, "unused", "boot_copy_residue",
    f"0x{len(tail):X} bytes of non-uniform data (fragments of UTF-16LE strings such as 'READDATA'); "
    f"long zero runs: {', '.join(f'0x{a:X}-0x{b:X}' for a, b in zero_runs)}",
    "no PI reference (only D_B00D7040/D_B00D7360 exist in this range); IPL3 copies it to 0x80147360..0x80170000 "
    "but entrypoint clears 0x80147040..0x803C8880 before main, so the bytes are never observable")

# audio wave table head
ctl = rom[0x215620:0x217EC0]
check(ctl[:2] == b"B1", "sound effect ALBankFile magic")
waves = set()
for b in range(struct.unpack_from(">h", ctl, 2)[0]):
    bo = struct.unpack_from(">I", ctl, 4 + 4 * b)[0]
    n = struct.unpack_from(">h", ctl, bo)[0]
    insts = list(struct.unpack_from(f">{n}I", ctl, bo + 12)) + [struct.unpack_from(">I", ctl, bo + 8)[0]]
    for ins in filter(None, insts):
        for s in range(struct.unpack_from(">h", ctl, ins + 14)[0]):
            snd = struct.unpack_from(">I", ctl, ins + 16 + 4 * s)[0]
            w = struct.unpack_from(">I", ctl, snd + 8)[0]
            waves.add(struct.unpack_from(">II", ctl, w))
lowest = min(waves)
check(lowest[0] == 0, "first sound-effect wave starts at table offset 0")
covered = sorted(waves)
add(0x100000, 0x101000, "payload", "sound_effect_wave_table_head",
    f"VADPCM wave data, start of the sound-effect .tbl (0x100000..0x215620); wave at tbl+0 length 0x{lowest[1]:X}",
    "load_audio_banks (func_8007A004) passes D_B0100000 as the .tbl base to alBnkfNew; ctl at 0x215620 "
    "has a wave at offset 0 (asset_progress credits the same table from 0x101000)")

# ---------------------------------------------------------------- (2) 0x2C19B0..0x2C3E50
check(u32(0x80125760 - 0x80070000) == 0xB02C19B0, "sequence table end sentinel")
base = 0x2C19B0
count = u32(base)
rel = [u32(base + 4 + 4 * i) for i in range(count)]
check(count == 4 and rel[0] == 4 * count, "2C19B0 table: offsets relative to the table at +4")
edges = [base + 4 + o for o in rel] + [0x2C3E50]
check(all(a < b for a, b in zip(edges, edges[1:])), "2C19B0 offsets ascending")
unk_rows = []
for k, (a, b) in enumerate(zip(edges, edges[1:])):
    halves = struct.unpack_from(f">{(b - a) // 2}H", rom, a)
    opaque = sum(h & 1 for h in halves) / len(halves)
    unk_rows.append((k, a, b, b - a, f"{opaque:.3f}"))
    dump(f"unknown_2C19B0_entry{k}.bin", rom[a:b])
add(0x2C19B0, 0x2C3E50, "unknown", "unreferenced_offset_table_2C19B0",
    "u32 count=4; u32 offset[4] relative to the table (+4); entries 0x850/0x2E0/0x2E0/0x167C bytes whose "
    "16-bit words have the low bit set at the rates listed in unknown_2c19b0.tsv (RGBA5551-like); dimensions unknown",
    "no consumer: no PI constant or %hi/%lo pair in 0xB02C19B0..0xB02C3E4F, the only data hit is the "
    "music sequence table end sentinel at 0x80125760; font loader starts at D_B02C3E50. Needed: a loader or "
    "a computed address into this range")

# ---------------------------------------------------------------- (1) image packs
PACKS = [
    ("pack_308290", 0x308290, 0x30BFE0, "CI4", "D_8037AD78 (0x5000)",
     "func_800F5960 rom_dma_read when 1<=D_80134E58<=2"),
    ("pack_30BFE0", 0x30BFE0, 0x3102D0, "CI8", "D_80382D80 (0x5000)",
     "func_800F5B6C rom_dma_read when 1<=D_80134E58<=2"),
    ("pack_3102D0", 0x3102D0, 0x312D90, "CI4", "D_8037AD78 (0x5000)",
     "func_800F5960 rom_dma_read when 3<=D_80134E58<=4"),
    ("pack_312D90", 0x312D90, 0x316C60, "CI8", "D_80382D80 (0x5000)",
     "func_800F5B6C rom_dma_read when 3<=D_80134E58<=4"),
    ("pack_316C60", 0x316C60, 0x319B30, "MIXED", "D_8037FD80 (0x3000)",
     "func_800F5960 rom_dma_read (always)"),
]
CI8_SITES = {  # (w,h): draw sites passing these dimensions to func_800F3D40 with a 256-entry TLUT
    (264, 4): "func_80102050", (4, 150): "func_80102050", (4, 87): "func_80102050",
    (100, 38): "func_800F6934", (134, 38): "func_800F6934/func_800F8120", (90, 25): "func_800F9F34/func_800FC674",
    (4, 92): "func_80102A30", (134, 4): "func_80102A30", (9, 9): "func_8010316C/func_80103E50/func_8010435C",
    (134, 76): "func_800FFF78",
}
CI4_SITES = {(32, 32): "func_800F6934/func_800F9F34 (LoadBlock 0x70FF400, tile 0x7C07C, slots 12+k)",
             (64, 64): "func_800F6934 (slot e3, LoadBlock 0x73FF200, tile 0xFC0FC)"}
pack_rows = []
# Direct references to the offset word of entry i (buffer + 4 + 4*i) and what the site does with it.
SLOT_SITES = {
    ("D_8037AD78", 2): "D_8037AD84: func_800F6934 (texture setup before func_800F4DFC)",
    ("D_8037AD78", 3): "D_8037AD88: func_800F6934/func_800F8120 64x64 CI4 load (LoadBlock 0x73FF200, tile 0xFC0FC)",
    ("D_8037AD78", 4): "D_8037AD8C: func_800FFB58",
    ("D_8037AD78", 7): "D_8037AD98: func_800F6934; also texel base +0x20 for computed slots 12+k (32x32 CI4)",
    ("D_8037AD78", 9): "D_8037ADA0: func_800F6934",
    ("D_8037AD78", 14): "D_8037ADB4: func_800F9F34/func_800FC674",
    ("D_8037AD78", 16): "D_8037ADBC: func_800F9F34/func_800FC674",
    ("D_8037AD78", 17): "D_8037ADC0: func_800F6934/func_800F8120/func_800F9F34/func_800FC674",
    ("D_8037AD78", 20): "D_8037ADCC: func_800F6934/func_800F8120/func_800D1BA0",
    ("D_80382D80", 1): "D_80382D88: func_80102050 draws 4x150",
    ("D_80382D80", 2): "D_80382D8C: func_80102050 draws 4x87",
    ("D_80382D80", 3): "D_80382D90: func_80102050 draws 4x150",
    ("D_80382D80", 4): "D_80382D94: func_80102050 draws 4x87",
    ("D_80382D80", 5): "D_80382D98: func_80102050 draws 264x4",
    ("D_80382D80", 6): "D_80382D9C: func_800F6934 draws 100x38; func_800F8120 134x38; "
                       "func_800F9F34/func_800FC674 loop D9C..DAC drawing 90x25",
    ("D_80382D80", 7): "D_80382DA0: func_800F6934 draws 134x38",
    ("D_80382D80", 8): "D_80382DA4: func_80102A30 draws 4x92",
    ("D_80382D80", 10): "D_80382DAC: func_80102A30 draws 134x4",
    ("D_8037FD80", 0): "D_8037FD84: func_8010316C/func_8010435C draw 9x9",
    ("D_8037FD80", 1): "D_8037FD88: func_800F5B6C/func_8010316C/func_8010435C draw 9x9",
    ("D_8037FD80", 2): "D_8037FD8C: func_800FFF78 draws 134x76",
    ("D_8037FD80", 3): "D_8037FD90: func_80100550 G_SETTIMG + G_LOADTILE",
}
for name, a, b, fmt, buf, loader in PACKS:
    n = u32(a)
    offs = [u32(a + 4 + 4 * i) for i in range(n)]
    hdr = (4 + 4 * n + 4 + 7) & ~7
    check(u32(a + 4 + 4 * n) == 0, f"{name} zero terminator")
    check(offs[0] == hdr and rom[a + 8 + 4 * n:a + hdr] == bytes(hdr - 8 - 4 * n), f"{name} header pad")
    check(b - a <= 0x5000 and (name != "pack_316C60" or b - a <= 0x3000), f"{name} fits buffer")
    ends = offs[1:] + [b - a]
    check(all(x < y for x, y in zip(offs, ends)), f"{name} offsets ascending")
    for i, (s, e) in enumerate(zip(offs, ends)):
        size = e - s
        efmt = fmt if fmt != "MIXED" else ("CI8" if i < 3 else "TEX")
        pal = {"CI4": 0x20, "CI8": 0x200, "TEX": 0}[efmt]
        sites = {"CI4": CI4_SITES, "CI8": CI8_SITES, "TEX": {}}[efmt]
        match = []
        for (w, h), where in sites.items():
            px = (w * h + 1) // 2 if efmt == "CI4" else w * h
            if 0 <= size - pal - px < 0x40:
                match.append((size - pal - px, w, h, where))
        match.sort()
        slot = SLOT_SITES.get((buf[:10], i), "")
        if match and match[0][0] <= 8:
            slack, w, h, where = match[0]
            dims = f"{w}x{h}"
            tail = rom[a + e - slack:a + e]
            note = f"trailing {slack} B" + (" zero" if tail == bytes(slack) else f" non-zero {tail.hex()}")
        elif match:
            slack, w, h, where = match[0]
            dims = "unpinned"
            note = (f"pixel bytes 0x{size - pal:X}; nearest consumer size {w}x{h} ({where}) leaves 0x{slack:X} B")
        else:
            dims, where = "unpinned", ""
            note = f"pixel bytes 0x{size - pal:X}; no consumer dimension fits"
        if efmt == "TEX":
            dims, where, note = "unpinned", "", "0x40-byte texture block loaded with G_LOADTILE"
        where = f"size fit: {where}" if where else ""
        pack_rows.append((name, i, a + s, a + e, size, efmt, pal // 2, dims, where, slot or "none found", note))
        dump(f"{name}_e{i:02d}.bin", rom[a + s:a + e])
    add(a, b, "container", name,
        f"raw (not LZARI) image pack: u32 count={n}; u32 offset[count] from pack start; u32 0; zero pad to 8; "
        f"entries = {'16-colour RGBA5551 TLUT (0x20 B) + CI4 texels' if fmt == 'CI4' else '256-colour RGBA5551 TLUT (0x200 B) + CI8 texels' if fmt == 'CI8' else 'CI8 TLUT+texels (e0..e2) and a 0x40-byte texture (e3)'}",
        f"{loader} into {buf}; entries addressed as buffer+offset[i] (TLUT) and +0x20/+0x200 (texels)")

# ---------------------------------------------------------------- (1) demo recordings
# func_800EC410: jump table jtbl_800749B0 indexed by D_80137904 (0..11, default = case 0).
jt = [u32(0x49B0 + 4 * i) for i in range(12)]
check(jt[3] == jt[11] == 0x800EC4D8 and jt[0] == 0x800EC4E8, "recording jump table")
REC = [0x319B30, 0x334630, 0x348DB0, 0x364100, 0x3747F0, 0x380670, 0x383CC0, 0x38BBE0, 0x3A0820,
       0x3B9630, 0x3C1550, 0x3D16D0]
CASES = {0x319B30: "0 (and >=12)", 0x334630: "1", 0x348DB0: "2", 0x364100: "3, 11", 0x3747F0: "4",
         0x380670: "5", 0x383CC0: "6", 0x38BBE0: "7", 0x3A0820: "8", 0x3B9630: "9", 0x3C1550: "10"}
rec_rows = []
for a, b in zip(REC, REC[1:]):
    h = struct.unpack_from(">6I", rom, a)
    stride = 12 * h[1] + 0x30
    total = 0x18 + h[0] * stride + 12 * h[3]
    pad = b - a - total
    check(0 <= pad < 16 and (a + total + 15) & ~15 == b and rom[a + total:b] == bytes(pad), f"rec 0x{a:X} size")
    for f in range(h[0]):  # every frame starts with a finite 4x3 f32 matrix
        m = struct.unpack_from(">12f", rom, a + 0x18 + f * stride)
        check(all(math.isfinite(x) for x in m), f"rec 0x{a:X} frame {f} matrix")
    rec_rows.append((a, a + total, b, CASES[a], *h, stride))
    dump(f"recording_{a:06X}.bin", rom[a:a + total])
    add(a, a + total, "payload", f"demo_recording_{a:06X}",
        f"raw demo recording: header u32[6]={list(h)}; {h[0]} frames x 0x{stride:X} B (4x3 f32 camera matrix + "
        f"{h[1]} x 12 B) + {h[3]} x 12 B trailer",
        f"func_800EC410 case {CASES[a]} of D_80137904: rom_dma_read 0x18-byte header to D_8033B600, allocates "
        f"frames*(12*h1+0x30)+12*h3, DMAs the body from ROM+0x18; read by load_recorded_frame_matrix (func_800EC7A8)")
    if pad:
        add(a + total, b, "padding", f"demo_recording_{a:06X}_pad", "0x00 fill to 16-byte alignment",
            "outside the size computed by func_800EC410; all zero")

# ---------------------------------------------------------------- (3) residues
r = lzari.decompress_with_info(rom[0x7378A0:0x7388F5])
check(r.consumed_bytes <= 0x7388F5 - 0x7378A0, "nav stream 24 fits")
check(u32(0x16AD0) == 0x3C02B074 and u32(0x16AD4) == 0x244288F5 and u32(0x165E0) == 0x3C02B074 and
      u32(0x165E4) == 0x24428900, "func_800865E0 stores 0xB07388F5 / 0xB0738900")
add(0x7388F5, 0x738900, "unused", "level_stream_alignment_gap_7388F5",
    f"11 non-zero bytes {rom[0x7388F5:0x738900].hex()} between nav stream 24 and world stream 0",
    "func_800865E0 (fills the level stream table 0x80125A68) stores nav stream 24 end 0xB07388F5 (0x80086AD0) (LZARI decode consumes "
    f"0x{r.consumed_bytes:X} of 0x{0x7388F5 - 0x7378A0:X} bytes) and world stream 0 start 0xB0738900 (0x800865E0); no other reference")
text = rom[0x7E3210:0x7E3250]
check(text.startswith(b"rob zydbel, tod frye, and alex werner are all key players!\0") and
      text[0x3A:] == bytes(6), "credit string")
check(u32(0x80141768 - 0x80070000 + 16 * 16 + 4) == 0xB07E3210, "briefing table last end = 0x7E3210")
check(u32(0x80141308 - 0x80070000 + 8 * 40) == 0xB07E3250, "level map 8 starts at 0x7E3250")
add(0x7E3210, 0x7E3250, "unused", "orphan_ascii_string_7E3210",
    "ASCII 'rob zydbel, tod frye, and alex werner are all key players!' + NUL, zero pad to 0x7E3250",
    "lies between briefing image 16 (ends 0xB07E3210, table 0x80141768) and level map 8 (starts 0xB07E3250, "
    "table 0x80141308); no PI constant or pointer refers to it")
ptrs = {u32(0x80141308 - 0x80070000 + 40 * i) for i in range(15)} | \
       {u32(0x80141308 - 0x80070000 + 40 * i + 4) for i in range(15)}
check(0xB07E76D0 in ptrs and 0xB07E7C50 in ptrs, "map table bounds around the gap")
check(not any(0xB07E76D0 <= p < 0xB07E7C50 for p in ptrs if p != 0xB07E76D0), "gap not referenced")
check(sorted(set(struct.unpack_from(">28i", rom, 0x80141560 - 0x80070000))) == list(range(15)), "map index list (28 levels) selects records 0..14")
add(0x7E76D0, 0x7E7C50, "unused", "unreferenced_map_slot_7E76D0",
    "0x580 bytes; begins like the level-map records (16-colour RGBA5551 TLUT, 0x20 B) + 0x560 B (CI4 area of "
    "e.g. 2752 texels); width/height unknown",
    "level map table 0x80141308 (15 records, all selected via 0x80141560 indices 0..14) skips it: record 9 ends at "
    "0xB07E76D0 and record 10 starts at 0xB07E7C50; no other reference")
check(set(rom[0x7EA060:]) == {0xFF}, "0xFF fill")
add(0x7EA060, 0x800000, "padding", "rom_tail_fill", "0xFF fill to the 8 MiB ROM end",
    "last level map ends at 0xB07EA060; every byte to 0x800000 is 0xFF")

# ---------------------------------------------------------------- outputs
ledger.sort()
for x, y in zip(ledger, ledger[1:]):
    check(x[1] <= y[0], f"overlap {x[3]} / {y[3]}")
TARGETS = [(0x0, 0x1000), (0xD7040, 0x101000), (0x2C19B0, 0x2C3E50), (0x308290, 0x3D16D0),
           (0x7388F5, 0x738900), (0x7E3210, 0x7E3250), (0x7E76D0, 0x7E7C50), (0x7EA060, 0x800000)]
for ts, te in TARGETS:
    pos = ts
    for s, e, *_ in ledger:
        if ts <= s < te:
            check(s == pos, f"gap at 0x{pos:X}")
            pos = e
    check(pos == te, f"target 0x{ts:X} not covered (stops 0x{pos:X})")


def tsv(name, header, rows):
    with open(os.path.join(OUTDIR, name), "w") as fh:
        fh.write("\t".join(header) + "\n")
        for row in rows:
            fh.write("\t".join(f"0x{v:X}" if isinstance(v, int) and not isinstance(v, bool) and v > 9 else str(v)
                               for v in row) + "\n")


tsv("ledger.tsv", ["rom_start", "rom_end", "size", "kind", "name", "format", "evidence"],
    [(s, e, e - s, k, n, f, ev) for s, e, k, n, f, ev in ledger])
tsv("pack_entries.tsv", ["pack", "index", "rom_start", "rom_end", "size", "format", "tlut_colours", "dims",
                         "dims_evidence", "slot_symbol_references", "note"], pack_rows)
tsv("recordings.tsv", ["rom_start", "data_end", "rom_end", "case", "frames", "h1_records_per_frame", "h2",
                       "h3_trailer_records", "h4", "h5", "frame_stride"], rec_rows)
tsv("unknown_2c19b0.tsv", ["index", "rom_start", "rom_end", "size", "low_bit_set_ratio"], unk_rows)
totals = {}
for s, e, k, *_ in ledger:
    totals[k] = totals.get(k, 0) + e - s
print("ok", {k: hex(v) for k, v in sorted(totals.items())}, "rows", len(ledger))
