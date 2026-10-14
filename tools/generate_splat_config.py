#!/usr/bin/env python3
"""Generate a deterministic splat config from the reviewed function catalogue."""

from __future__ import annotations

import tomllib
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
CATALOGUE = ROOT / "config/us/recomp_function_boundaries.toml"
MATCHING = ROOT / "config/us/matching_units.tsv"
MATCHING_KMC = ROOT / "config/us/matching_kmc_units.tsv"
MATCHING_ASM = ROOT / "config/us/matching_asm_units.tsv"
OUTPUT = ROOT / "config/us/splat.yaml"


def canonical_functions(section: dict) -> list[dict]:
    start = section["vram"]
    end = start + section["size"]
    functions = sorted(section["functions"], key=lambda f: (f["vram"], -f["size"], f["name"]))
    result: list[dict] = []
    occupied_until = start
    for function in functions:
        address = function["vram"]
        size = function["size"]
        if address % 4 or size <= 0 or size % 4:
            raise ValueError(f"unaligned function: {function}")
        if address < start or address + size > end:
            raise ValueError(f"out-of-range function: {function}")
        # The recomp catalogue deliberately retains a few internal aliases.
        if address < occupied_until:
            continue
        result.append(function)
        occupied_until = address + size
    return result


def main() -> None:
    data = tomllib.loads(CATALOGUE.read_text())
    section = data["section"][0]
    functions = canonical_functions(section)
    rom_start = section["rom"]
    vram_start = section["vram"]
    rom_end = rom_start + section["size"]
    lines = [
        "name: BattleTanx (USA)",
        "sha1: 535860d941738ac1210c20a9b80114fea0e0ff17",
        "",
        "options:",
        "  base_path: ../..",
        "  target_path: baseroms/us/baserom.z64",
        "  platform: n64",
        "  compiler: IDO",
        "  basename: battletanx",
        "  build_path: build/us",
        "  asm_path: asm/us",
        "  src_path: src",
        "  cache_path: .splache/us",
        "  subalign: 4",
        "  create_asm_dependencies: true",
        "  disassemble_all: false",
        "",
        "segments:",
        "  - name: header",
        "    type: header",
        "    start: 0x0",
        "  - name: ipl3",
        "    type: bin",
        "    start: 0x40",
        "  - name: main",
        "    type: code",
        f"    start: 0x{rom_start:X}",
        f"    vram: 0x{vram_start:X}",
        "    subsegments:",
    ]
    matching = []
    for manifest in (MATCHING, MATCHING_KMC):
        for line in manifest.read_text().splitlines():
            if not line or line.startswith("#"):
                continue
            offset, size, source, _flags, _digest = line.split("\t")
            matching.append((int(offset, 0), int(offset, 0) + int(size, 0), source.removeprefix("src/").removesuffix(".c"), "c"))
    for line in MATCHING_ASM.read_text().splitlines():
        if not line or line.startswith("#"):
            continue
        offset, size, source, _digest = line.split("\t")
        matching.append((int(offset, 0), int(offset, 0) + int(size, 0), source.removeprefix("src/").removesuffix(".s"), "hasm"))
    matching.sort()
    for left, right in zip(matching, matching[1:]):
        if left[1] > right[0]:
            raise ValueError(f"overlapping matching units: {left} and {right}")
    segments = [(rom_start + f["vram"] - vram_start, rom_start + f["vram"] - vram_start + f["size"], "asm", f"functions/{f['name']}") for f in functions]
    segments = [segment for segment in segments if not any(segment[0] < end and segment[1] > start for start, end, _source, _kind in matching)]
    segments.extend((start, end, kind, source) for start, end, source, kind in matching)
    segments.sort()
    cursor = rom_start
    for offset, end, kind, name in segments:
        if offset > cursor:
            lines.append(f"      - [0x{cursor:X}, bin, gaps/gap_{cursor:06X}]")
        lines.append(f"      - [0x{offset:X}, {kind}, {name}]")
        cursor = end
    if cursor < rom_end:
        lines.append(f"      - [0x{cursor:X}, bin, gaps/gap_{cursor:06X}]")
    lines.extend([f"  - [0x{rom_end:X}, bin, assets]", "  - [0x800000]", ""])
    OUTPUT.write_text("\n".join(lines))
    print(f"Wrote {OUTPUT.relative_to(ROOT)} with {len(functions)} canonical functions and {len(matching)} matching source unit(s)")


if __name__ == "__main__":
    main()
