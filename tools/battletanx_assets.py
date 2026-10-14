#!/usr/bin/env python3
"""Declarative BattleTanx (USA Rev 0) resource layouts and extraction.

Layouts are derived from recovered game code (see each record's
``evidence``) and validated against the supported ROM before use.  The
supported ROM's SHA-256 is checked before any read.  Extraction writes only
to ignored ``build/`` paths; no ROM-derived bytes belong in the repository.
"""

from __future__ import annotations

import argparse
import hashlib
import json
import struct
from dataclasses import asdict, dataclass
from pathlib import Path

import lzari

ROOT = Path(__file__).resolve().parents[1]
SUPPORTED_SHA256 = "c5b7cf3523de025e3f18e2c8df2deb0eced5613e7c46cb8c6c5a4f22644ead3f"
MAIN_VRAM = 0x80071000
MAIN_ROM = 0x1000
PI_CART_BASE = 0xB0000000
DEFAULT_OUTPUT = ROOT / "build/us/assets"


class AssetError(ValueError):
    pass


def load_rom(path: Path) -> bytes:
    data = path.read_bytes()
    digest = hashlib.sha256(data).hexdigest()
    if digest != SUPPORTED_SHA256:
        raise AssetError(f"{path}: unsupported ROM (SHA-256 {digest})")
    return data


def be_u32(data: bytes, offset: int) -> int:
    """Read one big-endian unsigned 32-bit word."""
    if offset < 0 or offset + 4 > len(data):
        raise AssetError(f"u32 read at 0x{offset:X} is out of bounds")
    return struct.unpack_from(">I", data, offset)[0]


def be_u32_array(data: bytes, offset: int, count: int) -> tuple[int, ...]:
    if offset < 0 or offset + 4 * count > len(data):
        raise AssetError(f"u32[{count}] read at 0x{offset:X} is out of bounds")
    return struct.unpack_from(f">{count}I", data, offset)


def vram_to_rom(vram: int) -> int:
    return vram - MAIN_VRAM + MAIN_ROM


def pi_to_rom(address: int) -> int:
    """Cartridge PI addresses (0xB0000000 + ROM offset) as used by rom_dma_read."""
    if not PI_CART_BASE <= address < PI_CART_BASE + 0x800000:
        raise AssetError(f"0x{address:08X} is not a cartridge PI address")
    return address - PI_CART_BASE


# ---------------------------------------------------------------------------
# Record layouts


LZARI_HEADER = struct.Struct(">I")  # expanded size; arithmetic-coded bits follow
BUNDLE_HEADER = struct.Struct(">II")  # entry count, payload offset


@dataclass(frozen=True)
class Bundle:
    """Decompressed resource bundle.

    ``u32 count; u32 payload_offset; u32 boundary[count];`` padded to 8
    bytes.  ``boundary[0..count-2]`` are ascending entry boundaries relative
    to ``payload_offset``; ``boundary[count-1]`` is zero.  Entry ``i`` spans
    from the previous boundary (0 for the first) to ``boundary[i]``, and the
    last entry runs to the end of the payload.
    """

    count: int
    payload_offset: int
    entries: tuple[tuple[int, int], ...]  # (start, end) relative to the bundle


def bundle_header_size(count: int) -> int:
    return (BUNDLE_HEADER.size + 4 * count + 7) & ~7


def parse_bundle(data: bytes) -> Bundle:
    count, payload = BUNDLE_HEADER.unpack_from(data, 0)
    if count == 0 or count > 0x400:
        raise AssetError(f"implausible bundle entry count {count}")
    if payload != bundle_header_size(count):
        raise AssetError(f"payload offset 0x{payload:X} != aligned header 0x{bundle_header_size(count):X}")
    boundaries = be_u32_array(data, BUNDLE_HEADER.size, count)
    if boundaries[-1] != 0:
        raise AssetError("bundle boundary table is not zero-terminated")
    cuts = list(boundaries[:-1])
    if cuts != sorted(cuts) or (cuts and cuts[0] == 0):
        raise AssetError("bundle boundaries are not strictly ascending")
    edges = [0, *cuts, len(data) - payload]
    if edges[-2] > edges[-1]:
        raise AssetError("bundle boundary exceeds payload")
    entries = tuple((payload + left, payload + right) for left, right in zip(edges, edges[1:]))
    return Bundle(count, payload, entries)


@dataclass(frozen=True)
class Resource:
    name: str
    rom_start: int
    rom_end: int
    encoding: str  # "lzari" or "raw"
    capacity: int  # destination bytes passed by the loader
    loader: str  # recovered C function (evidence)


SCREEN_RESOURCES = (
    Resource("screen_49C740", 0x49C740, 0x49DCD0, "raw", 0x3A980, "load_raw_screen_image_49C740 (0x800CA980)"),
    Resource("screen_49DCD0", 0x49DCD0, 0x4AC150, "lzari", 0x25800, "load_screen_image_49DCD0 (0x800C54F0)"),
    Resource("screen_4AC150", 0x4AC150, 0x4AD7E0, "lzari", 0x25800, "load_screen_image_4AC150 (0x800DADBC)"),
    Resource("screen_4AD7E0", 0x4AD7E0, 0x4B1300, "lzari", 0x25800, "load_screen_image_4AD7E0 (0x800D44CC)"),
    Resource("screen_4B1300", 0x4B1300, 0x4B3280, "lzari", 0x25800, "load_screen_image_4B1300 (0x800CE4B0)"),
    Resource("screen_4B3280", 0x4B3280, 0x4B39B0, "lzari", 0x25800, "load_screen_image_4B3280 (0x800D0D30)"),
    Resource("screen_4B39B0", 0x4B39B0, 0x4B4B00, "lzari", 0x25800, "load_screen_image_4B39B0 (0x800CC470)"),
    Resource("screen_3D6940", 0x3D6940, 0x3DC430, "lzari", 0x25800, "load_screen_image_3D6940 (0x800C5B90)"),
    Resource("screen_3DFD10", 0x3DFD10, 0x3EA970, "lzari", 0x25800, "load_screen_image_3DFD10 (0x800D9080)"),
)


@dataclass(frozen=True)
class PiAddressTable:
    """Parallel start/end tables of cartridge PI addresses in program data."""

    name: str
    start_vram: int
    end_vram: int
    count: int
    capacity: int
    loader: str


SCREEN_STRIP_TABLE = PiAddressTable(
    "screen_strip", 0x80134B88, 0x80134BB0, 10, 0xBC00, "load_screen_strip (0x800CA8C0)"
)


def read_pi_table(rom: bytes, table: PiAddressTable) -> list[Resource]:
    starts = be_u32_array(rom, vram_to_rom(table.start_vram), table.count)
    ends = be_u32_array(rom, vram_to_rom(table.end_vram), table.count)
    resources = []
    for index, (start, end) in enumerate(zip(starts, ends)):
        left, right = pi_to_rom(start), pi_to_rom(end)
        if right <= left:
            raise AssetError(f"{table.name}[{index}] has an empty or reversed range")
        resources.append(Resource(f"{table.name}_{index}", left, right, "lzari", table.capacity, table.loader))
    return resources


def decode_resource(rom: bytes, resource: Resource) -> bytes:
    payload = rom[resource.rom_start:resource.rom_end]
    if resource.encoding == "raw":
        if len(payload) > resource.capacity:
            raise AssetError(f"{resource.name} exceeds its loader capacity")
        return payload
    expanded = LZARI_HEADER.unpack_from(payload, 0)[0]
    if expanded == 0 or expanded > resource.capacity:
        raise AssetError(f"{resource.name}: expanded size 0x{expanded:X} exceeds capacity 0x{resource.capacity:X}")
    data = lzari.decompress(payload, max_output=resource.capacity)
    if len(data) != expanded:
        raise AssetError(f"{resource.name}: decoded 0x{len(data):X} bytes, header says 0x{expanded:X}")
    return data


def catalogue(rom: bytes) -> list[dict]:
    rows = []
    for resource in (*SCREEN_RESOURCES, *read_pi_table(rom, SCREEN_STRIP_TABLE)):
        data = decode_resource(rom, resource)
        bundle = parse_bundle(data)
        row = asdict(resource)
        row.update(
            expanded_size=len(data),
            sha256=hashlib.sha256(data).hexdigest(),
            entries=[{"start": s, "end": e} for s, e in bundle.entries],
        )
        rows.append(row)
    return rows


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("command", choices=("catalogue", "extract"))
    parser.add_argument("--rom", type=Path, default=ROOT / "baseroms/us/baserom.z64")
    parser.add_argument("--output", type=Path, default=DEFAULT_OUTPUT)
    args = parser.parse_args()
    rom = load_rom(args.rom)
    rows = catalogue(rom)
    args.output.mkdir(parents=True, exist_ok=True)
    (args.output / "resources.json").write_text(json.dumps(rows, indent=1) + "\n")
    if args.command == "extract":
        for row in rows:
            resource = Resource(**{k: row[k] for k in Resource.__dataclass_fields__})
            data = decode_resource(rom, resource)
            folder = args.output / row["name"]
            folder.mkdir(parents=True, exist_ok=True)
            for index, entry in enumerate(row["entries"]):
                (folder / f"entry_{index:02d}.bin").write_bytes(data[entry["start"]:entry["end"]])
    for row in rows:
        print(f"{row['name']:16} ROM 0x{row['rom_start']:06X}-0x{row['rom_end']:06X} "
              f"{row['encoding']:5} 0x{row['expanded_size']:05X} bytes, {len(row['entries'])} entries")


if __name__ == "__main__":
    main()
