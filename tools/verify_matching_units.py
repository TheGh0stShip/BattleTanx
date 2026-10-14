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


def rows() -> list[tuple[int, int, Path, list[str], str]]:
    result = []
    for line in MANIFEST.read_text().splitlines():
        if not line or line.startswith("#"):
            continue
        start, size, source, flags, digest = line.split("\t")
        result.append((int(start, 0), int(size, 0), ROOT / source, shlex.split(flags), digest))
    return result


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("--rom", type=Path, default=ROOT / "baseroms/us/baserom.z64")
    args = parser.parse_args()
    rom = args.rom.read_bytes()
    compiler = ROOT / ".toolchain/ido5.3/cc"
    if not compiler.is_file():
        raise SystemExit("missing pinned compiler; run tools/bootstrap_ido.sh")
    output_dir = ROOT / "build/us/matching"
    output_dir.mkdir(parents=True, exist_ok=True)
    matched = 0
    for start, size, source, flags, expected_digest in rows():
        output = output_dir / f"{source.stem}.o"
        subprocess.run([str(compiler), "-c", *flags, "-Iinclude", "-o", str(output), str(source)], check=True, cwd=ROOT)
        text = elf32_be_section(output, ".text")
        digest = hashlib.sha256(text).hexdigest()
        if len(text) != size:
            raise SystemExit(f"{source}: text size 0x{len(text):X}, expected 0x{size:X}")
        if digest != expected_digest:
            raise SystemExit(f"{source}: text SHA-256 {digest}, expected {expected_digest}")
        retail = rom[start : start + size]
        if text != retail:
            first = next(i for i, (left, right) in enumerate(zip(text, retail)) if left != right)
            raise SystemExit(f"{source}: mismatch at ROM 0x{start + first:X}")
        matched += size
        print(f"MATCH {source.relative_to(ROOT)}: ROM 0x{start:X}-0x{start + size:X} ({size} bytes)")
    print(f"Verified {len(rows())} matching source unit(s), {matched} bytes")


if __name__ == "__main__":
    main()
