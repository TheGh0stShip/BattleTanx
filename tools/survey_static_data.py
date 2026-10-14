#!/usr/bin/env python3
"""Classify every byte of the loaded BattleTanx program image.

The supported ROM is verified before reading.  Output is written only to
``build/us/static_data/`` as JSON and Markdown.  Classification is
heuristic for unreconstructed ranges and exact for ranges claimed by the
matching code/data manifests; only manifest-backed ranges count as matched.
"""

from __future__ import annotations

import argparse
import hashlib
import json
import struct
import tomllib
from dataclasses import dataclass
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
CATALOGUE = ROOT / "config/us/recomp_function_boundaries.toml"
CODE_MANIFESTS = (
    ROOT / "config/us/matching_units.tsv",
    ROOT / "config/us/matching_kmc_units.tsv",
    ROOT / "config/us/matching_asm_units.tsv",
)
DATA_MANIFEST = ROOT / "config/us/matching_data_units.tsv"
EXPECTED_SHA256 = "c5b7cf3523de025e3f18e2c8df2deb0eced5613e7c46cb8c6c5a4f22644ead3f"
DEFAULT_OUTPUT = ROOT / "build/us/static_data"

RDRAM_POINTER = (0x80000000, 0x80800000)
CART_POINTER = (0xB0000000, 0xB0800000)


@dataclass(frozen=True)
class Region:
    start: int  # ROM offset
    end: int
    kind: str
    detail: str = ""


def read_rom(path: Path) -> bytes:
    data = path.read_bytes()
    digest = hashlib.sha256(data).hexdigest()
    if digest != EXPECTED_SHA256:
        raise SystemExit(f"{path}: unsupported ROM (SHA-256 {digest})")
    return data


def be32(data: bytes, offset: int) -> int:
    return struct.unpack_from(">I", data, offset)[0]


def manifest_ranges(paths) -> list[tuple[int, int, str]]:
    ranges = []
    for path in paths:
        for line in path.read_text().splitlines():
            if not line or line.startswith("#"):
                continue
            fields = line.split("\t")
            start, size = int(fields[0], 0), int(fields[1], 0)
            ranges.append((start, start + size, fields[2]))
    return sorted(ranges)


def function_ranges(section: dict) -> list[tuple[int, int, str]]:
    delta = section["vram"] - section["rom"]
    occupied = 0
    result = []
    for function in sorted(section["functions"], key=lambda f: (f["vram"], -f["size"])):
        start = function["vram"] - delta
        if start < occupied:
            continue
        result.append((start, start + function["size"], function["name"]))
        occupied = start + function["size"]
    return result


def is_float(word: int) -> bool:
    exponent = (word >> 23) & 0xFF
    return word == 0 or (0x60 <= exponent <= 0x9E and (word & 0x7FFFFF) % 0x10 == 0)


def classify_words(rom: bytes, start: int, end: int, text_span: tuple[int, int], delta: int) -> list[Region]:
    """Split an unclaimed range into padding, strings, pointer tables and unknown words."""
    regions: list[Region] = []
    offset = start
    while offset < end:
        # zero runs
        run = offset
        while run < end and rom[run] == 0:
            run += 1
        if run - offset >= 4:
            regions.append(Region(offset, run, "zero"))
            offset = run
            continue
        # NUL-terminated printable strings
        run = offset
        while run < end and 0x20 <= rom[run] < 0x7F:
            run += 1
        if run - offset >= 4 and run < end and rom[run] == 0:
            stop = run + 1
            while stop < end and stop % 4 and rom[stop] == 0:
                stop += 1
            regions.append(Region(offset, stop, "string", rom[offset:run].decode("ascii")))
            offset = stop
            continue
        if offset % 4 or offset + 4 > end:
            regions.append(Region(offset, offset + 1, "byte"))
            offset += 1
            continue
        word = be32(rom, offset)
        if text_span[0] <= word < text_span[1] and word % 4 == 0:
            kind = "code_pointer"
        elif RDRAM_POINTER[0] <= word < RDRAM_POINTER[1]:
            kind = "rdram_pointer"
        elif CART_POINTER[0] <= word < CART_POINTER[1]:
            kind = "cart_pointer"
        elif is_float(word):
            kind = "float"
        else:
            kind = "word"
        regions.append(Region(offset, offset + 4, kind))
        offset += 4
    # merge adjacent regions of the same kind (strings stay separate)
    merged: list[Region] = []
    for region in regions:
        if merged and merged[-1].kind == region.kind and merged[-1].end == region.start and region.kind != "string":
            merged[-1] = Region(merged[-1].start, region.end, region.kind)
        else:
            merged.append(region)
    return merged


def lui_addiu(rom: bytes, offset: int) -> int:
    """Decode a ``lui rt, hi`` / ``addiu rt, rt, lo`` pair."""
    hi, lo = be32(rom, offset), be32(rom, offset + 4)
    if hi >> 26 != 0x0F or lo >> 26 != 0x09:
        raise ValueError(f"no lui/addiu pair at ROM 0x{offset:X}")
    return ((hi & 0xFFFF) << 16) + struct.unpack(">h", struct.pack(">H", lo & 0xFFFF))[0] & 0xFFFFFFFF


def bss_bounds(rom: bytes, entry_rom: int) -> tuple[int, int]:
    """The entry point zeroes [bss_start, bss_end) with $t0/$t1 before main."""
    return lui_addiu(rom, entry_rom + 8), lui_addiu(rom, entry_rom + 16)


def survey(rom: bytes) -> dict:
    section = tomllib.loads(CATALOGUE.read_text())["section"][0]
    delta = section["vram"] - section["rom"]
    start = section["rom"]
    bss_start, bss_end = bss_bounds(rom, start)
    image_end = section["rom"] + section["size"]
    end = bss_start - delta
    functions = function_ranges(section)
    text_span = (functions[0][0] + delta, functions[-1][1] + delta)
    code = manifest_ranges(CODE_MANIFESTS)
    data = manifest_ranges([DATA_MANIFEST])
    claimed: list[Region] = []
    for left, right, name in functions:
        claimed.append(Region(left, right, "code", name))
    for left, right, source in data:
        claimed.append(Region(left, right, "matched_data", source))
    claimed.sort(key=lambda r: (r.start, r.end))
    regions: list[Region] = []
    cursor = start
    for region in claimed:
        if region.start < cursor:
            continue
        if region.start > cursor:
            regions.extend(classify_words(rom, cursor, region.start, text_span, delta))
        regions.append(region)
        cursor = region.end
    if cursor < end:
        regions.extend(classify_words(rom, cursor, end, text_span, delta))
    if end < image_end:
        regions.append(Region(end, image_end, "outside_initialized_image",
                              f"bss VRAM 0x{bss_start:08X}-0x{bss_end:08X}"))
    totals: dict[str, int] = {}
    for region in regions:
        totals[region.kind] = totals.get(region.kind, 0) + region.end - region.start
    matched_code = 0
    for left, right, _ in code:
        matched_code += max(0, min(right, end) - max(left, start))
    return {
        "rom_start": start,
        "rom_end": end,
        "vram_start": section["vram"],
        "bss_start": bss_start,
        "bss_end": bss_end,
        "totals": totals,
        "matched_code_bytes": matched_code,
        "regions": [region.__dict__ for region in regions],
    }


def write_markdown(report: dict, path: Path) -> None:
    lines = ["# BattleTanx program-image data survey", "",
             f"ROM 0x{report['rom_start']:X}-0x{report['rom_end']:X}", "", "| kind | bytes |", "| --- | ---: |"]
    for kind, size in sorted(report["totals"].items(), key=lambda kv: -kv[1]):
        lines.append(f"| {kind} | {size} |")
    lines += ["", "| ROM start | ROM end | VRAM | kind | detail |", "| --- | --- | --- | --- | --- |"]
    delta = report["vram_start"] - report["rom_start"]
    for region in report["regions"]:
        if region["kind"] == "code":
            continue
        lines.append(f"| 0x{region['start']:X} | 0x{region['end']:X} | 0x{region['start'] + delta:08X} | "
                     f"{region['kind']} | {region['detail'][:48]} |")
    path.write_text("\n".join(lines) + "\n")


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--rom", type=Path, default=ROOT / "baseroms/us/baserom.z64")
    parser.add_argument("--output", type=Path, default=DEFAULT_OUTPUT)
    args = parser.parse_args()
    rom = read_rom(args.rom)
    report = survey(rom)
    args.output.mkdir(parents=True, exist_ok=True)
    (args.output / "data_map.json").write_text(json.dumps(report, indent=1) + "\n")
    write_markdown(report, args.output / "data_map.md")
    for kind, size in sorted(report["totals"].items(), key=lambda kv: -kv[1]):
        print(f"{kind:14} {size:8d}")


if __name__ == "__main__":
    main()
