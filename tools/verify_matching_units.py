#!/usr/bin/env python3
"""Compile reviewed units and compare their text directly with the retail ROM."""

from __future__ import annotations

import argparse
import hashlib
import re
import shlex
import struct
import subprocess
import tomllib
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
MANIFEST = ROOT / "config/us/matching_units.tsv"
KMC_MANIFEST = ROOT / "config/us/matching_kmc_units.tsv"
ASM_MANIFEST = ROOT / "config/us/matching_asm_units.tsv"


def elf32_be_section(path: Path, wanted: str) -> bytes:
    data = path.read_bytes()
    if data[:6] != b"\x7fELF\x01\x02":
        raise ValueError(f"{path}: expected ELF32 big-endian object")
    if struct.unpack_from(">H", data, 18)[0] != 8:
        raise ValueError(f"{path}: expected MIPS object")
    shoff = struct.unpack_from(">I", data, 32)[0]
    shentsize, shnum, shstrndx = struct.unpack_from(">HHH", data, 46)
    headers = [struct.unpack_from(">IIIIIIIIII", data, shoff + i * shentsize) for i in range(shnum)]
    strings_header = headers[shstrndx]
    strings = data[strings_header[4] : strings_header[4] + strings_header[5]]
    for header in headers:
        name_start = header[0]
        name_end = strings.find(b"\0", name_start)
        name = strings[name_start:name_end].decode("ascii")
        if name == wanted:
            return data[header[4] : header[4] + header[5]]
    raise ValueError(f"{path}: no {wanted} section")


def symbol_addresses() -> dict[str, int]:
    catalogue = tomllib.loads((ROOT / "config/us/recomp_function_boundaries.toml").read_text())
    return {function["name"]: function["vram"] for function in catalogue["section"][0]["functions"]}


def inferred_symbol_address(name: str, known: dict[str, int]) -> int:
    if name in known:
        return known[name]
    match = re.fullmatch(r"(?:D|func)_([0-9A-Fa-f]{8})", name)
    if match:
        return int(match.group(1), 16)
    raise ValueError(f"no retail address known for relocation symbol {name}")


def relocate_elf32_be_section(
    path: Path, wanted: str, known: dict[str, int], section_bases: dict[str, int] | None = None
) -> bytes:
    """Apply the small subset of MIPS REL relocations emitted by matching C units."""
    data = path.read_bytes()
    shoff = struct.unpack_from(">I", data, 32)[0]
    shentsize, shnum, shstrndx = struct.unpack_from(">HHH", data, 46)
    headers = [struct.unpack_from(">IIIIIIIIII", data, shoff + i * shentsize) for i in range(shnum)]
    strings_header = headers[shstrndx]
    section_names = data[strings_header[4] : strings_header[4] + strings_header[5]]

    def section_name(header: tuple[int, ...]) -> str:
        end = section_names.find(b"\0", header[0])
        return section_names[header[0] : end].decode("ascii")

    section_bases = section_bases or {}
    target_index = next(i for i, header in enumerate(headers) if section_name(header) == wanted)
    target = bytearray(elf32_be_section(path, wanted))
    pending_hi: dict[int, list[tuple[int, int]]] = {}

    for rel_header in headers:
        if rel_header[1] != 9 or rel_header[7] != target_index:  # SHT_REL, sh_info target
            continue
        sym_header = headers[rel_header[6]]
        str_header = headers[sym_header[6]]
        symbol_names = data[str_header[4] : str_header[4] + str_header[5]]
        symbols = []
        for offset in range(sym_header[4], sym_header[4] + sym_header[5], sym_header[9]):
            name_offset, value = struct.unpack_from(">II", data, offset)
            section_index = struct.unpack_from(">H", data, offset + 14)[0]
            end = symbol_names.find(b"\0", name_offset)
            symbols.append((symbol_names[name_offset:end].decode("ascii"), value, section_index))

        for offset in range(rel_header[4], rel_header[4] + rel_header[5], rel_header[9]):
            location, info = struct.unpack_from(">II", data, offset)
            symbol_index, kind = info >> 8, info & 0xFF
            name, symbol_value, section_index = symbols[symbol_index]
            if name == "":
                base = section_bases.get(section_name(headers[section_index]), 0)
                address = base + symbol_value
            else:
                address = inferred_symbol_address(name, known)
            word = struct.unpack_from(">I", target, location)[0]
            if kind == 2:  # R_MIPS_32
                struct.pack_into(">I", target, location, (word + address) & 0xFFFFFFFF)
            elif kind == 4:  # R_MIPS_26
                word = (word & 0xFC000000) | (((word & 0x03FFFFFF) + (address >> 2)) & 0x03FFFFFF)
                struct.pack_into(">I", target, location, word)
            elif kind == 5:  # R_MIPS_HI16; completed when its LO16 arrives
                pending_hi.setdefault(symbol_index, []).append((location, word))
            elif kind == 6:  # R_MIPS_LO16
                low_addend = struct.unpack(">h", struct.pack(">H", word & 0xFFFF))[0]
                full_value = address + low_addend
                struct.pack_into(">I", target, location, (word & 0xFFFF0000) | (full_value & 0xFFFF))
                for hi_location, hi_word in pending_hi.pop(symbol_index, []):
                    hi_addend = (hi_word & 0xFFFF) << 16
                    value = address + hi_addend + low_addend
                    patched = (hi_word & 0xFFFF0000) | (((value + 0x8000) >> 16) & 0xFFFF)
                    struct.pack_into(">I", target, hi_location, patched)
            else:
                raise ValueError(f"{path}: unsupported MIPS relocation type {kind}")
    if pending_hi:
        raise ValueError(f"{path}: unmatched R_MIPS_HI16 relocation")
    return bytes(target)


def rows() -> list[tuple[str, int, int, Path, list[str], str]]:
    result = []
    for pipeline, manifest in (("ido", MANIFEST), ("kmc", KMC_MANIFEST)):
        for line in manifest.read_text().splitlines():
            if not line or line.startswith("#"):
                continue
            start, size, source, flags, digest = line.split("\t")
            result.append((pipeline, int(start, 0), int(size, 0), ROOT / source, shlex.split(flags), digest))
    for line in ASM_MANIFEST.read_text().splitlines():
        if not line or line.startswith("#"):
            continue
        start, size, source, digest = line.split("\t")
        result.append(("asm", int(start, 0), int(size, 0), ROOT / source, [], digest))
    result.sort(key=lambda row: row[1])
    return result


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("--rom", type=Path, default=ROOT / "baseroms/us/baserom.z64")
    args = parser.parse_args()
    rom = args.rom.read_bytes()
    compiler = ROOT / ".toolchain/ido5.3/cc"
    if not compiler.is_file():
        raise SystemExit("missing pinned compiler; run tools/bootstrap_ido.sh")
    kmc_root = ROOT / ".toolchain/kmc-gcc-2.7.2"
    if not (kmc_root / "gcc").is_file() or not (kmc_root / "as").is_file():
        raise SystemExit("missing pinned KMC compiler; run tools/bootstrap_kmc_gcc.sh")
    output_dir = ROOT / "build/us/matching"
    output_dir.mkdir(parents=True, exist_ok=True)
    known_symbols = symbol_addresses()
    matched = 0
    for pipeline, start, size, source, flags, expected_digest in rows():
        output = output_dir / f"{source.stem}.o"
        section_bases = {".text": 0x80070000 + start}
        compiler_flags = []
        for flag in flags:
            if flag.startswith("--section-base="):
                section, address = flag.removeprefix("--section-base=").split(":", 1)
                section_bases[section] = int(address, 0)
            else:
                compiler_flags.append(flag)
        flags = compiler_flags
        if pipeline == "ido":
            subprocess.run([str(compiler), "-c", *flags, "-Iinclude", "-o", str(output), str(source)], check=True, cwd=ROOT)
        elif pipeline == "kmc":
            legacy_normalizer = "--normalizer-legacy" in flags
            flags = [flag for flag in flags if flag != "--normalizer-legacy"]
            raw = output.with_suffix(".raw.s")
            normalized = output.with_suffix(".s")
            subprocess.run([str(kmc_root / "gcc"), f"-B{kmc_root}/", "-S", *flags, "-Iinclude", "-o", str(raw), str(source)], check=True, cwd=ROOT)
            normalize_command = [str(ROOT / "tools/normalize_kmc_gcc_asm.py")]
            if legacy_normalizer:
                normalize_command.append("--legacy")
            subprocess.run([*normalize_command, str(raw), str(normalized)], check=True, cwd=ROOT)
            subprocess.run([str(kmc_root / "as"), "-mips3", "-G0", "-o", str(output), str(normalized)], check=True, cwd=ROOT)
        else:
            subprocess.run([str(kmc_root / "as"), "-mips3", "-G0", "-o", str(output), str(source)], check=True, cwd=ROOT)
        compiled_text = relocate_elf32_be_section(output, ".text", known_symbols, section_bases)
        if len(compiled_text) < size:
            raise SystemExit(f"{source}: text size 0x{len(compiled_text):X}, expected at least 0x{size:X}")
        if any(compiled_text[size:]):
            raise SystemExit(f"{source}: nonzero compiler padding after expected 0x{size:X}-byte text")
        text = compiled_text[:size]
        digest = hashlib.sha256(text).hexdigest()
        if digest != expected_digest:
            raise SystemExit(f"{source}: text SHA-256 {digest}, expected {expected_digest}")
        retail = rom[start : start + size]
        if text != retail:
            first = next(i for i, (left, right) in enumerate(zip(text, retail)) if left != right)
            raise SystemExit(f"{source}: mismatch at ROM 0x{start + first:X}")
        matched += size
        print(f"MATCH [{pipeline.upper()}] {source.relative_to(ROOT)}: ROM 0x{start:X}-0x{start + size:X} ({size} bytes)")
    print(f"Verified {len(rows())} matching source unit(s), {matched} bytes")


if __name__ == "__main__":
    main()
