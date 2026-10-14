#!/usr/bin/env python3
"""Generate a deterministic splat config from the reviewed function catalogue."""

from __future__ import annotations

import tomllib
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
CATALOGUE = ROOT / "config/us/recomp_function_boundaries.toml"
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
    cursor = rom_start
    for function in functions:
        offset = rom_start + function["vram"] - vram_start
        if offset > cursor:
            lines.append(f"      - [0x{cursor:X}, bin, gaps/gap_{cursor:06X}]")
        lines.append(f"      - [0x{offset:X}, asm, functions/{function['name']}]")
        cursor = offset + function["size"]
    if cursor < rom_end:
        lines.append(f"      - [0x{cursor:X}, bin, gaps/gap_{cursor:06X}]")
    lines.extend([f"  - [0x{rom_end:X}, bin, assets]", "  - [0x800000]", ""])
    OUTPUT.write_text("\n".join(lines))
    print(f"Wrote {OUTPUT.relative_to(ROOT)} with {len(functions)} canonical function segments")


if __name__ == "__main__":
    main()
