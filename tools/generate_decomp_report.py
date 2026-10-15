#!/usr/bin/env python3
"""Generate the objdiff v2 progress report consumed by recomp.fyi."""

from __future__ import annotations

import argparse
import json
import tomllib
from pathlib import Path

from decompkit.config import load_config
from decompkit.tables import parse_address_ranges, read_tsv
from generate_splat_config import canonical_functions

ROOT = Path(__file__).resolve().parents[1]
DEFAULT_CONFIG = ROOT / "config/decompkit.toml"
ASSET_PROGRESS = ROOT / "config/us/asset_progress.toml"
DATA_PROGRESS = ROOT / "config/us/data_progress.toml"
LIBULTRA_START = 0x80110480
# The entry point (0x80071000) zeroes .bss from 0x80147040 to 0x803C8880, so
# initialized program data ends here; the rest of the 1 MiB main copy is not
# reconstructable static data and must not inflate reported data totals.
INITIALIZED_DATA_END = 0x80147040


ASSET_CLASSES = ("payload", "container", "padding", "unused", "unknown")


def asset_ledger() -> tuple[int, int, list[tuple[int, int, str, str]]]:
    manifest = tomllib.loads(ASSET_PROGRESS.read_text())
    region = manifest["region"]
    start, end = region["rom_start"], region["rom_end"]
    if start < 0 or end <= start:
        raise ValueError(f"{ASSET_PROGRESS}: invalid asset region")
    path = ROOT / manifest["ledger"]["path"]
    runs = []
    cursor = start
    for line in path.read_text().splitlines():
        if not line or line.startswith("#") or line.startswith("rom_start"):
            continue
        left, right, kind, category = line.split("\t")
        left, right = int(left, 16), int(right, 16)
        if left != cursor or right <= left:
            raise ValueError(f"{path}: gap or overlap at 0x{min(left, cursor):X}")
        if kind not in ASSET_CLASSES:
            raise ValueError(f"{path}: unknown class {kind!r}")
        runs.append((left, right, kind, category))
        cursor = right
    if cursor != end:
        raise ValueError(f"{path}: ledger ends at 0x{cursor:X}, region ends at 0x{end:X}")
    return start, end, runs


def asset_progress() -> tuple[int, int]:
    start, end, runs = asset_ledger()
    return end - start, sum(right - left for left, right, kind, _ in runs if kind != "unknown")


ASSET_CATEGORIES = (
    ("assets_textures", "Textures and palettes", ("textures",)),
    ("assets_images", "Images, sprites and screens", ("images",)),
    ("assets_fonts", "Fonts and text", ("fonts",)),
    ("assets_models", "Models and display lists", ("models",)),
    ("assets_animations", "Animations and recordings", ("animations",)),
    ("assets_levels", "Levels and world data", ("levels",)),
    ("assets_navigation", "Navigation", ("navigation",)),
    ("assets_scripts", "Scripts and data tables", ("scripts",)),
    ("assets_music", "Music", ("music",)),
    ("assets_sound", "Sound effects and sample banks", ("sound_effects",)),
)


def asset_kind_totals() -> dict[str, int]:
    totals = {category_id: 0 for category_id, _name, _kinds in ASSET_CATEGORIES}
    for left, right, kind, category in asset_ledger()[2]:
        if kind not in ("payload", "container"):
            continue
        for category_id, _name, categories in ASSET_CATEGORIES:
            if category in categories:
                totals[category_id] += right - left
                break
        else:
            raise ValueError(f"{ASSET_PROGRESS}: unclassified asset category {category!r}")
    return totals


def manifest_ranges(config) -> list[tuple[int, int, str]]:
    parsed = parse_address_ranges(
        [path for path, _pipeline in config.unit_manifests], allow_empty=True
    )
    return [(item["start"], item["end"], item["row"]["SOURCE"]) for item in parsed]


def data_ranges(config) -> list[tuple[int, int]]:
    return [
        (int(row["ROM_START"], 0), int(row["ROM_START"], 0) + int(row["SIZE"], 0))
        for row in read_tsv(config.data_manifest)
    ]


def initialized_data_progress(matched_ranges: list[tuple[int, int]]) -> tuple[int, int]:
    """Return audited initialized-data totals and validate the manifest."""
    progress = tomllib.loads(DATA_PROGRESS.read_text())["initialized_data"]
    matched = progress["matched"]
    unmatched = progress["unmatched"]
    manifest_bytes = sum(end - start for start, end in matched_ranges)
    if manifest_bytes != matched:
        raise ValueError(
            f"{DATA_PROGRESS}: matched={matched}, but the data manifest covers "
            f"{manifest_bytes} bytes"
        )
    return matched + unmatched, matched


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


def build_report(config_path: Path = DEFAULT_CONFIG) -> dict:
    config = load_config(config_path)
    section = tomllib.loads(config.functions.read_text())["section"][0]
    functions = canonical_functions(section)
    ranges = manifest_ranges(config)
    matched_data_ranges = data_ranges(config)
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
    category_rom_spans = {
        "game": (section["rom"], LIBULTRA_START - rom_delta),
        "libultra": (LIBULTRA_START - rom_delta, image_end - rom_delta),
    }
    total_functions = len(functions)
    matched_functions = sum(values[3] for values in category_totals.values())
    categories = []
    for category_id, name in (("game", "Game code"), ("libultra", "libultra")):
        total, matched, count, complete = category_totals[category_id]
        data_start, data_end = category_rom_spans[category_id]
        matched_data = range_bytes(data_start, data_end, matched_data_ranges)
        categories.append({
            "id": category_id,
            "name": name,
            "measures": measures(total, matched, count, complete, count, complete,
                                 total_data=matched_data, matched_data=matched_data),
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
    total_data, matched_data = initialized_data_progress(matched_data_ranges)
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
    parser.add_argument("--config", type=Path, default=DEFAULT_CONFIG)
    parser.add_argument("--output", type=Path)
    args = parser.parse_args()
    config = load_config(args.config)
    output = args.output or config.report_output
    report = build_report(args.config)
    output.parent.mkdir(parents=True, exist_ok=True)
    output.write_text(json.dumps(report, indent=2) + "\n")
    print(f"wrote {output}: {report['measures']['matched_code']} / "
          f"{report['measures']['total_code']} code bytes")


if __name__ == "__main__":
    main()
