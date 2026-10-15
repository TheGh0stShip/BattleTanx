#!/usr/bin/env python3
"""Merge the per-format inventories into one canonical ROM interval ledger.

Usage: rom_ledger.py REPO RUN_DIR OUT_DIR
RUN_DIR holds the outputs of audio_banks.py, tile_pools.py, rom_regions.py,
level_sections.py and bundle_entries.py (one sub-directory each).  The ledger
covers ROM 0x0..0x800000 with non-overlapping intervals; the initialized
program image (ROM 0x1000..0xD7040) is a single row whose bytes are accounted
for by data_ledger.py.  Exits non-zero on any gap or overlap.
"""
import csv, hashlib, struct, sys
from collections import defaultdict
from pathlib import Path

ROM_SHA1 = "535860d941738ac1210c20a9b80114fea0e0ff17"
repo, run, out = Path(sys.argv[1]), Path(sys.argv[2]), Path(sys.argv[3])
rom = (repo / "baseroms/us/baserom.z64").read_bytes()
if hashlib.sha1(rom).hexdigest() != ROM_SHA1:
    sys.exit("ROM SHA-1 mismatch")
sys.path.insert(0, str(repo / "tools"))
import battletanx_assets as assets  # noqa: E402

ROWS = []


def add(a, b, cls, category, kind, name, evidence):
    if b > a:
        ROWS.append((a, b, cls, category, kind, name, evidence))


def tsv(path):
    return list(csv.DictReader(open(path), delimiter="\t"))


def num(text):
    return int(text, 16) if text.lower().startswith("0x") or any(c in text.lower() for c in "abcdef") else int(text)


def fill_gaps(a, b, rows, name, evidence):
    """Classify bytes between consecutive owned rows: zero/0xFF fill is padding."""
    rows = sorted(rows)
    cur = a
    for s, e, *rest in rows:
        if s > cur:
            gap = rom[cur:s]
            cls = "padding" if set(gap) <= {0} else "unknown"
            add(cur, s, cls, "-", "fill" if cls == "padding" else "gap", f"{name}_gap_{cur:06X}", evidence)
        add(s, e, *rest)
        cur = max(cur, e)
    if cur < b:
        gap = rom[cur:b]
        add(cur, b, "padding" if set(gap) <= {0} else "unknown", "-", "fill", f"{name}_gap_{cur:06X}", evidence)


# program image and the boot/main-segment tail (rom_regions.py)
add(0x1000, 0xD7040, "program_image", "-", "initialized_image", "main_initialized_image",
    "IPL3 copies ROM 0x1000.. to 0x80071000; .text/.rodata/.data ledger in initialized_data_ledger.tsv")
CAT_REGION = {"cartridge_header": "-", "ipl3_bootcode": "-", "segment1_static_gfx": "models"}
packs = defaultdict(list)
for r in tsv(run / "rom_regions/pack_entries.tsv"):
    packs[r["pack"]].append(r)
for r in tsv(run / "rom_regions/ledger.tsv"):
    a, b = num(r["rom_start"]), num(r["rom_end"])
    if a >= 0x100000 and a < 0x101000:
        continue  # sample table head: covered by audio_banks.py
    if r["name"] in packs:
        entries = sorted((num(e["rom_start"]), num(e["rom_end"]), e) for e in packs[r["name"]])
        add(a, entries[0][0], "container", "images", "pack_header", r["name"] + "_header",
            "u32 count; u32 offset[count]; u32 0; padded to 8")
        owned = [(s, e, "payload", "images", ent["format"], f"{r['name']}_{int(ent['index'], 0):02d}",
                  f"{ent['dims']} {ent['dims_evidence']}") for s, e, ent in entries]
        fill_gaps(entries[0][0], b, owned, r["name"], "pack entry alignment")
        continue
    category = CAT_REGION.get(r["name"], "animations" if r["name"].startswith("demo_recording") else "-")
    if r["kind"] == "unknown":
        cls = "unused"  # parsed structure, no reference anywhere in code or data
    else:
        cls = r["kind"]
    add(a, b, cls, category if cls == "payload" else "-", r["format"][:60], r["name"], r["evidence"][:200])

# audio (audio_banks.py)
for r in tsv(run / "audio_banks/ledger.tsv"):
    a, b = num(r["rom_start"]), num(r["rom_end"])
    group, kind = r["group"], r["kind"]
    category = "sound_effects" if group.startswith("sfx") else "music"
    cls = "padding" if kind == "padding" else ("container" if group.endswith("ctl") else "payload")
    add(a, b, cls, "-" if cls == "padding" else category, kind, f"{group}_{a:06X}", r["detail"][:200])

# fonts (battletanx_assets.font_sets)
for font in assets.font_sets(rom):
    base = font["rom_start"]
    first = font["entries"][0]["start"]
    add(base, base + first, "container", "fonts", "font_set_header", font["name"] + "_header",
        "u32 count; u32 offset[count]; load_texture_draw_font 0x801053B0")
    for i, e in enumerate(font["entries"]):
        add(base + e["start"], base + e["end"], "payload", "fonts", "ia8_glyph_atlas",
            f"{font['name']}_{i:02d}", f"{e['glyphs']} glyphs, IA8 {e['width']}x{e['rows']}")

# resource bundles: each compressed stream is one ROM interval; entries live in decoded space
bundle_cats = defaultdict(set)
for r in tsv(run / "bundle_entries/bundle_entries.tsv"):
    bundle_cats[r["bundle"]].add(r["category"])
for res in (*assets.RESOURCE_BUNDLES, *assets.read_pi_table(rom, assets.RESOURCE_BUNDLE_STRIP_TABLE)):
    cats = bundle_cats.get(res.name, set())
    add(res.rom_start, res.rom_end, "payload", "images", f"{res.encoding}_bundle",
        res.name, f"{res.loader}; decoded entries in bundle_entries.tsv ({', '.join(sorted(cats))})")

# tile pools (tile_pools.py)
MCAT = {"geometry_display_list": ("payload", "models"), "geometry_vertices": ("payload", "models"),
        "texture_display_list": ("payload", "textures"), "texture_palette": ("payload", "textures"),
        "texture_texture": ("payload", "textures"), "texture_palette_trailer": ("unused", "-"),
        "texture_dead_dl_commands": ("unused", "-"), "unknown_unreferenced_geometry": ("unused", "-"),
        "padding(0x00)": ("padding", "-")}
for r in tsv(run / "tile_pools/ledger.tsv"):
    cls, cat = MCAT[r["kind"]]
    add(num(r["rom_start"]), num(r["rom_end"]), cls, cat, r["kind"], f"{r['kind']}_{num(r['rom_start']):06X}",
        r["evidence"][:200])

# level streams (battletanx_assets.LEVEL_STREAMS); gaps between streams are padding or listed residues
level_rows = []
for index, world, nav in assets.LEVEL_STREAMS:
    if world:
        level_rows.append((*world, "payload", "levels", "lzari_world_stream", f"level_{index:02d}_world",
                           "func_80088CF0 nine-section world stream"))
    if nav:
        level_rows.append((*nav, "payload", "navigation", "lzari_nav_stream", f"level_{index:02d}_nav",
                           "func_800DDA08 navigation stream"))
residues = {(num(r["rom_start"]), num(r["rom_end"])) for r in tsv(run / "rom_regions/ledger.tsv")}
for s, e, *rest in sorted(level_rows):
    add(s, e, *rest)
cur_rows = sorted(level_rows)
for (s0, e0, *_), (s1, e1, *_) in zip(cur_rows, cur_rows[1:]):
    if s1 > e0 and (e0, s1) not in residues:
        add(e0, s1, "padding" if set(rom[e0:s1]) <= {0} else "unknown", "-", "fill", f"level_gap_{e0:06X}",
            "alignment between level streams")

# briefing and level-map images (battletanx_assets.image_streams)
for img in assets.image_streams(rom):
    used = img["rom_start"] + img["data_size"]
    add(img["rom_start"], used, "payload", "images", f"ci{4 if img['size'] == 0 else 8}",
        img["name"], f"{img['width']}x{img['height']} CI, palette at stream start")
    add(used, img["rom_end"], "padding" if set(rom[used:img["rom_end"]]) <= {0} else "unused", "-",
        "fill", img["name"] + "_tail", "stream tail after palette + pixels")

# check and fill: every remaining hole must be explained
ROWS.sort()
final, cur = [], 0
for row in ROWS:
    a, b = row[0], row[1]
    if a < cur:
        sys.exit(f"overlap at 0x{a:X} ({row[5]})")
    if a > cur:
        hole = rom[cur:a]
        final.append((cur, a, "padding" if set(hole) <= {0} else "unknown", "-", "fill",
                      f"hole_{cur:06X}", "not owned by any parser"))
    final.append(row)
    cur = b
if cur != 0x800000:
    sys.exit(f"ledger ends at 0x{cur:X}")
out.mkdir(parents=True, exist_ok=True)
with open(out / "rom_interval_ledger.tsv", "w") as f:
    f.write("rom_start\trom_end\tsize\tclass\tcategory\tkind\tname\tevidence\n")
    for a, b, cls, cat, kind, name, ev in final:
        f.write(f"0x{a:06X}\t0x{b:06X}\t{b - a}\t{cls}\t{cat}\t{kind}\t{name}\t{ev}\n")
totals_cls, totals_cat = defaultdict(int), defaultdict(int)
for a, b, cls, cat, *_ in final:
    totals_cls[cls] += b - a
    if cls in ("payload", "container"):
        totals_cat[cat] += b - a
with open(out / "unknown_intervals.tsv", "w") as f:
    f.write("rom_start\trom_end\tsize\tname\tevidence_needed\n")
    for a, b, cls, cat, kind, name, ev in final:
        if cls == "unknown":
            f.write(f"0x{a:06X}\t0x{b:06X}\t{b - a}\t{name}\t{ev}\n")
for k in sorted(totals_cls):
    print(f"class {k:14} {totals_cls[k]:9}")
for k in sorted(totals_cat):
    print(f"category {k:14} {totals_cat[k]:9}")
print("rows", len(final), "unknown", totals_cls.get("unknown", 0))

# compact asset ledger for progress reporting: maximal runs of (class, category) over the asset region
REGION = (0x101000, 0x800000)
runs = []
for a, b, cls, cat, *_ in final:
    a, b = max(a, REGION[0]), min(b, REGION[1])
    if b <= a:
        continue
    key = (cls, cat if cls in ("payload", "container") else "-")
    if runs and runs[-1][2] == key and runs[-1][1] == a:
        runs[-1][1] = b
    else:
        runs.append([a, b, key])
with open(out / "asset_ledger.tsv", "w") as f:
    f.write("# Asset region ledger: every byte of ROM 0x101000..0x800000 in exactly one run.\n")
    f.write("# Generated by tools/asset_inventory/rom_ledger.py; classes: payload, container, padding, unused, unknown.\n")
    f.write("rom_start\trom_end\tclass\tcategory\n")
    for a, b, (cls, cat) in runs:
        f.write(f"0x{a:06X}\t0x{b:06X}\t{cls}\t{cat}\n")
print("asset ledger runs", len(runs))
