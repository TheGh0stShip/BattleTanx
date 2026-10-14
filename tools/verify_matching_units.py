#!/usr/bin/env python3
"""Compile reviewed units and compare their text directly with the retail ROM."""

from __future__ import annotations

import argparse
import hashlib
import shlex
import struct
import subprocess
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
    matched = 0
    for pipeline, start, size, source, flags, expected_digest in rows():
        output = output_dir / f"{source.stem}.o"
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
        compiled_text = elf32_be_section(output, ".text")
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
