#!/usr/bin/env python3
"""Generate an objdiff v2 progress report for decomp.dev."""

from __future__ import annotations

import argparse
import json
import tomllib
from pathlib import Path

from generate_splat_config import canonical_functions

ROOT = Path(__file__).resolve().parents[1]
CATALOGUE = ROOT / "config/us/recomp_function_boundaries.toml"
MANIFESTS = (
    ROOT / "config/us/matching_units.tsv",
    ROOT / "config/us/matching_kmc_units.tsv",
    ROOT / "config/us/matching_asm_units.tsv",
)
DEFAULT_OUTPUT = ROOT / "build/report.json"
MATCHING_DATA = ROOT / "config/us/matching_data_units.tsv"
ASSET_PROGRESS = ROOT / "config/us/asset_progress.toml"
LIBULTRA_START = 0x80110480
# The entry point (0x80071000) zeroes .bss from 0x80147040 to 0x803C8880, so
# initialized program data ends here; the rest of the 1 MiB main copy is not
# reconstructable static data and must not inflate decomp.dev data totals.
INITIALIZED_DATA_END = 0x80147040


def asset_progress() -> tuple[int, int]:
    manifest = tomllib.loads(ASSET_PROGRESS.read_text())
    region = manifest["region"]
    start, end = region["rom_start"], region["rom_end"]
    if start < 0 or end <= start:
        raise ValueError(f"{ASSET_PROGRESS}: invalid asset region")

    ranges: list[tuple[int, int]] = []
    names: set[str] = set()
    for entry in manifest.get("range", []):
        name = entry["name"]
        left, right = entry["rom_start"], entry["rom_end"]
        if name in names:
            raise ValueError(f"{ASSET_PROGRESS}: duplicate range name {name!r}")
        if not start <= left < right <= end:
            raise ValueError(f"{ASSET_PROGRESS}: {name!r} lies outside the asset region")
        names.add(name)
        ranges.append((left, right))

    ranges.sort()
    for previous, current in zip(ranges, ranges[1:]):
        if current[0] < previous[1]:
            raise ValueError(f"{ASSET_PROGRESS}: overlapping asset ranges")
    return end - start, sum(right - left for left, right in ranges)


ASSET_CATEGORIES = (
    ("assets_textures", "Textures and palettes", ("texture", "palette")),
    ("assets_images", "Images, sprites and fonts", ("image", "sprite", "font")),
    ("assets_models", "Models and display lists", ("model", "display_list")),
    ("assets_levels", "Levels and world data", ("level", "world")),
    ("assets_music", "Music", ("music",)),
    ("assets_sound", "Sound effects and sample banks", ("sample_bank", "sound_effect")),
    ("assets_scripts", "Scripts and tables", ("script", "table")),
    ("assets_containers", "Verified resource containers", ("resource_bundle",)),
)


def asset_kind_totals() -> dict[str, int]:
    manifest = tomllib.loads(ASSET_PROGRESS.read_text())
    totals = {category_id: 0 for category_id, _name, _kinds in ASSET_CATEGORIES}
    for entry in manifest.get("range", []):
        for category_id, _name, kinds in ASSET_CATEGORIES:
            if entry.get("kind") in kinds:
                totals[category_id] += entry["rom_end"] - entry["rom_start"]
                break
        else:
            raise ValueError(f"{ASSET_PROGRESS}: unclassified asset kind {entry.get('kind')!r}")
    return totals


def manifest_ranges() -> list[tuple[int, int, str]]:
    ranges: list[tuple[int, int, str]] = []
    for manifest in MANIFESTS:
        for line in manifest.read_text().splitlines():
            if not line or line.startswith("#"):
                continue
            fields = line.split("\t")
            start, size = int(fields[0], 0), int(fields[1], 0)
            ranges.append((start, start + size, fields[2]))
    return ranges


def data_ranges() -> list[tuple[int, int]]:
    ranges = []
    for line in MATCHING_DATA.read_text().splitlines():
        if not line or line.startswith("#"):
            continue
        fields = line.split("\t")
        # START SIZE SOURCE [SECTION] SHA256; SECTION defaults to .rodata.
        if len(fields) not in (4, 5):
            raise ValueError(f"{MATCHING_DATA}: data row needs 4 or 5 fields: {line!r}")
        start, size = int(fields[0], 0), int(fields[1], 0)
        ranges.append((start, start + size))
    return ranges


def range_bytes(start: int, end: int, ranges: list[tuple[int, int]]) -> int:
    spans = sorted((max(start, left), min(end, right)) for left, right in ranges
                   if left < end and right > start)
    total = 0
    cursor = start
    for left, right in spans:
        if right <= cursor:
            continue
        left = max(left, cursor)
        total += right - left
        cursor = right
    return total


def covered_bytes(start: int, end: int, ranges: list[tuple[int, int, str]]) -> int:
    spans = sorted((max(start, left), min(end, right)) for left, right, _ in ranges if left < end and right > start)
    total = 0
    cursor = start
    for left, right in spans:
        if right <= cursor:
            continue
        left = max(left, cursor)
        total += right - left
        cursor = right
    return total


def source_for(start: int, end: int, ranges: list[tuple[int, int, str]]) -> str | None:
    for left, right, source in ranges:
        if left <= start and end <= right:
            return source
    return None


def measures(total_code: int, matched_code: int, total_functions: int, matched_functions: int,
             total_units: int, complete_units: int, total_data: int = 0,
             matched_data: int = 0) -> dict:
    code_percent = matched_code * 100.0 / total_code if total_code else 0.0
    data_percent = matched_data * 100.0 / total_data if total_data else 0.0
    function_percent = matched_functions * 100.0 / total_functions if total_functions else 0.0
    return {
        "fuzzy_match_percent": code_percent,
        "total_code": str(total_code),
        "matched_code": str(matched_code),
        "matched_code_percent": code_percent,
        "total_data": str(total_data),
        "matched_data": str(matched_data),
        "matched_data_percent": data_percent,
        "total_functions": total_functions,
        "matched_functions": matched_functions,
        "matched_functions_percent": function_percent,
        "complete_code": str(matched_code),
        "complete_code_percent": code_percent,
        "complete_data": str(matched_data),
        "complete_data_percent": data_percent,
        "total_units": total_units,
        "complete_units": complete_units,
    }


def build_report() -> dict:
    section = tomllib.loads(CATALOGUE.read_text())["section"][0]
    functions = canonical_functions(section)
    ranges = manifest_ranges()
    matched_data_ranges = data_ranges()
    rom_delta = section["vram"] - section["rom"]
    units = []
    category_totals = {"game": [0, 0, 0, 0], "libultra": [0, 0, 0, 0]}

    for function in functions:
        vram = function["vram"]
        size = function["size"]
        rom_start = vram - rom_delta
        rom_end = rom_start + size
        matched = covered_bytes(rom_start, rom_end, ranges)
        is_complete = matched == size
        category = "libultra" if vram >= LIBULTRA_START else "game"
        source = source_for(rom_start, rom_end, ranges)
        unit_measures = measures(size, matched, 1, int(is_complete), 1, int(is_complete))
        units.append({
            "name": function["name"],
            "measures": unit_measures,
            "functions": [{
                "name": function["name"],
                "size": str(size),
                "fuzzy_match_percent": unit_measures["fuzzy_match_percent"],
                "address": str(vram),
                "metadata": {"virtual_address": str(vram)},
            }],
            "metadata": {
                "complete": is_complete,
                "source_path": source or f"asm/us/functions/{function['name']}.s",
                "progress_categories": [category],
                "auto_generated": source is None,
            },
        })
        totals = category_totals[category]
        totals[0] += size
        totals[1] += matched
        totals[2] += 1
        totals[3] += int(is_complete)

    total_code = sum(values[0] for values in category_totals.values())
    matched_code = sum(values[1] for values in category_totals.values())
    image_end = min(section["vram"] + section["size"], INITIALIZED_DATA_END)
    category_spans = {
        "game": LIBULTRA_START - section["vram"],
        "libultra": image_end - LIBULTRA_START,
    }
    category_rom_spans = {
        "game": (section["rom"], LIBULTRA_START - rom_delta),
        "libultra": (LIBULTRA_START - rom_delta, image_end - rom_delta),
    }
    total_functions = len(functions)
    matched_functions = sum(values[3] for values in category_totals.values())
    categories = []
    for category_id, name in (("game", "Game code"), ("libultra", "libultra")):
        total, matched, count, complete = category_totals[category_id]
        total_data = category_spans[category_id] - total
        data_start, data_end = category_rom_spans[category_id]
        matched_data = range_bytes(data_start, data_end, matched_data_ranges)
        categories.append({
            "id": category_id,
            "name": name,
            "measures": measures(total, matched, count, complete, count, complete,
                                 total_data=total_data, matched_data=matched_data),
        })
    total_assets, identified_assets = asset_progress()
    categories.append({
        "id": "assets",
        "name": "Asset identification",
        "measures": measures(0, 0, 0, 0, 0, 0,
                             total_data=total_assets, matched_data=identified_assets),
    })
    kind_totals = asset_kind_totals()
    for category_id, name, _kinds in ASSET_CATEGORIES:
        categories.append({
            "id": category_id,
            "name": name,
            "measures": measures(0, 0, 0, 0, 0, 0,
                                 total_data=total_assets, matched_data=kind_totals[category_id]),
        })
    total_data = image_end - section["vram"] - total_code
    matched_data = sum(range_bytes(start, end, matched_data_ranges)
                       for start, end in category_rom_spans.values())
    return {
        "measures": measures(total_code, matched_code, total_functions, matched_functions,
                             total_functions, matched_functions, total_data=total_data,
                             matched_data=matched_data),
        "units": units,
        "version": 2,
        "categories": categories,
    }


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("--output", type=Path, default=DEFAULT_OUTPUT)
    args = parser.parse_args()
    report = build_report()
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(json.dumps(report, indent=2) + "\n")
    print(f"wrote {args.output}: {report['measures']['matched_code']} / "
          f"{report['measures']['total_code']} code bytes")


if __name__ == "__main__":
    main()
