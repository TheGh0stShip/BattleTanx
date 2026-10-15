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
import n64_texture

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

    ``u32 count; u32 offset[count]; u32 0;`` padded to 8 bytes.  Each
    ``offset[i]`` is relative to the start of the bundle (consumers fetch entry
    ``i`` as ``base + *(u32 *)(base + 4 + 4 * i)``); ``offset[0]`` equals the
    aligned header size.  Entry ``i`` spans ``offset[i]`` to ``offset[i + 1]``
    and the last entry runs to the end of the bundle.
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
    offsets = be_u32_array(data, 4, count)
    if be_u32(data, 4 + 4 * count) != 0:
        raise AssetError("bundle offset table is not zero-terminated")
    edges = [*offsets, len(data)]
    if any(left >= right for left, right in zip(edges, edges[1:])):
        raise AssetError("bundle offsets are not strictly ascending within the bundle")
    entries = tuple(zip(edges, edges[1:]))
    return Bundle(count, payload, entries)


@dataclass(frozen=True)
class Resource:
    name: str
    rom_start: int
    rom_end: int
    encoding: str  # "lzari" or "raw"
    capacity: int  # destination bytes passed by the loader
    loader: str  # recovered C function (evidence)


RESOURCE_BUNDLES = (
    Resource("bundle_49C740", 0x49C740, 0x49DCD0, "raw", 0x3A980, "load_raw_resource_bundle_49C740 (0x800CA980)"),
    Resource("bundle_49DCD0", 0x49DCD0, 0x4AC150, "lzari", 0x25800, "load_resource_bundle_49DCD0 (0x800C54F0)"),
    Resource("bundle_4AC150", 0x4AC150, 0x4AD7E0, "lzari", 0x25800, "load_resource_bundle_4AC150 (0x800DADBC)"),
    Resource("bundle_4AD7E0", 0x4AD7E0, 0x4B1300, "lzari", 0x25800, "load_resource_bundle_4AD7E0 (0x800D44CC)"),
    Resource("bundle_4B1300", 0x4B1300, 0x4B3280, "lzari", 0x25800, "load_resource_bundle_4B1300 (0x800CE4B0)"),
    Resource("bundle_4B3280", 0x4B3280, 0x4B39B0, "lzari", 0x25800, "load_resource_bundle_4B3280 (0x800D0D30)"),
    Resource("bundle_4B39B0", 0x4B39B0, 0x4B4B00, "lzari", 0x25800, "load_resource_bundle_4B39B0 (0x800CC470)"),
    Resource("bundle_3D6940", 0x3D6940, 0x3DC430, "lzari", 0x25800, "load_resource_bundle_3D6940 (0x800C5B90)"),
    Resource("bundle_3DFD10", 0x3DFD10, 0x3EA970, "lzari", 0x25800, "load_resource_bundle_3DFD10 (0x800D9080)"),
    Resource("bundle_2D2790", 0x2D2790, 0x2E2CD0, "lzari", 0x25800, "init_audio_mode_state (0x800AB690)"),
    Resource("bundle_3D16D0", 0x3D16D0, 0x3D6940, "lzari", 0x25800, "load_resource_bundle_3D16D0 (0x800D6908)"),
    Resource("bundle_3DC430", 0x3DC430, 0x3DFD10, "lzari", 0x25800,
             "load_splash_and_random_strip_bundles (0x800C8218)"),
    Resource("bundle_4B4B00", 0x4B4B00, 0x4C1930, "lzari", 0x3A980, "level bundle loader (0x800AC2E0)"),
    Resource("bundle_4C1930", 0x4C1930, 0x4E46E0, "lzari", 0x3A980, "level bundle loader (0x800AC2E0)"),
    Resource("bundle_4E46E0", 0x4E46E0, 0x50D930, "lzari", 0x493E0, "level bundle loader (0x800AC2E0)"),
    Resource("bundle_50D930", 0x50D930, 0x533870, "lzari", 0x3A980, "level bundle loader (0x800AC2E0)"),
    Resource("bundle_533870", 0x533870, 0x554D00, "lzari", 0x3A980, "bundle loader (0x800B9C9C)"),
    Resource("bundle_554D00", 0x554D00, 0x56FDB0, "lzari", 0x25800, "bundle loader (0x800BD20C)"),
    Resource("bundle_56FDB0", 0x56FDB0, 0x58AE00, "lzari", 0x3A980, "bundle loader (0x800C0898)"),
    Resource("bundle_58AE00", 0x58AE00, 0x596EA0, "lzari", 0x3A980, "bundle loader (0x800C0898)"),
    Resource("bundle_596EA0", 0x596EA0, 0x5A1110, "lzari", 0x25800, "run_sequence_d_loop (0x800C4AE0)"),
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


RESOURCE_BUNDLE_STRIP_TABLE = PiAddressTable(
    "bundle_strip", 0x80134B88, 0x80134BB0, 10, 0xBC00, "load_strip_bundle (0x800CA8C0)"
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


# ---------------------------------------------------------------------------
# Audio: libaudio ALBankFile banks and type-0 MIDI sequences.  Ranges come from
# load_audio_banks (0x8007A004) and the sequence offset table it scans.


@dataclass(frozen=True)
class AudioBank:
    name: str
    ctl_start: int
    ctl_end: int
    tbl_start: int
    tbl_end: int


AUDIO_BANKS = (
    AudioBank("sound_effects", 0x215620, 0x217EC0, 0x100000, 0x215620),
    AudioBank("music_instruments", 0x298D60, 0x29A710, 0x217EC0, 0x298D60),
)
SEQUENCE_TABLE_VRAM = 0x80125714  # 20 PI addresses: 19 sequence starts and the end
SEQUENCE_COUNT = 19


def parse_audio_bank(rom: bytes, bank: AudioBank) -> dict:
    ctl = rom[bank.ctl_start:bank.ctl_end]
    if ctl[:2] != b"B1":
        raise AssetError(f"{bank.name}: missing ALBankFile magic")
    count = struct.unpack_from(">h", ctl, 2)[0]
    waves = set()
    instruments = sounds = 0
    for index in range(count):
        offset = be_u32(ctl, 4 + 4 * index)
        inst_count = struct.unpack_from(">h", ctl, offset)[0]
        percussion = be_u32(ctl, offset + 8)
        inst_offsets = list(be_u32_array(ctl, offset + 12, inst_count)) + ([percussion] if percussion else [])
        for inst in inst_offsets:
            if not inst:
                continue
            instruments += 1
            for sound_index in range(struct.unpack_from(">h", ctl, inst + 14)[0]):
                sound = be_u32(ctl, inst + 16 + 4 * sound_index)
                sounds += 1
                wave = be_u32(ctl, sound + 8)
                base, length = be_u32_array(ctl, wave, 2)
                if ctl[wave + 8] != 0:
                    raise AssetError(f"{bank.name}: non-ADPCM wave at 0x{wave:X}")
                waves.add((base, length))
    end = max(base + length for base, length in waves)
    if bank.tbl_start + end > bank.tbl_end:
        raise AssetError(f"{bank.name}: wave data exceeds its table range")
    return {"name": bank.name, "ctl_start": bank.ctl_start, "ctl_end": bank.ctl_end,
            "tbl_start": bank.tbl_start, "tbl_end": bank.tbl_end, "banks": count,
            "instruments": instruments, "sounds": sounds, "waves": len(waves),
            "ctl_sha256": hashlib.sha256(ctl).hexdigest(),
            "tbl_sha256": hashlib.sha256(rom[bank.tbl_start:bank.tbl_end]).hexdigest()}


def sequence_ranges(rom: bytes) -> list[tuple[int, int]]:
    addresses = be_u32_array(rom, vram_to_rom(SEQUENCE_TABLE_VRAM), SEQUENCE_COUNT + 1)
    return [(pi_to_rom(left), pi_to_rom(right)) for left, right in zip(addresses, addresses[1:])]


def parse_sequence(data: bytes, name: str) -> dict:
    if data[:4] != b"MThd":
        raise AssetError(f"{name}: missing MThd header")
    header_size = be_u32(data, 4)
    file_format, tracks, division = struct.unpack_from(">HHH", data, 8)
    offset = 8 + header_size
    seen = 0
    while offset < len(data) and data[offset:offset + 4] == b"MTrk":
        offset += 8 + be_u32(data, offset + 4)
        seen += 1
    if seen != tracks or offset > len(data) or any(data[offset:]):
        raise AssetError(f"{name}: MIDI chunks do not account for the range")
    return {"name": name, "format": file_format, "tracks": tracks, "division": division,
            "midi_size": offset}


def audio_inventory(rom: bytes) -> dict:
    sequences = []
    for index, (left, right) in enumerate(sequence_ranges(rom)):
        row = parse_sequence(rom[left:right], f"sequence_{index:02d}")
        row.update(rom_start=left, rom_end=right, sha256=hashlib.sha256(rom[left:right]).hexdigest())
        sequences.append(row)
    return {"banks": [parse_audio_bank(rom, bank) for bank in AUDIO_BANKS], "sequences": sequences}


# ---------------------------------------------------------------------------
# I4 texture banks in program data (src/code/render/texture_bank_data.c).

TEXTURE_KIND_TABLE_VRAM = 0x80132278
TEXTURE_BANK_COUNT_VRAMS = (0x80132298, 0x801322F0, 0x801322CC, 0x801322BC)  # kinds 0..3


def texture_banks(rom: bytes) -> list[dict]:
    rows = []
    for kind, count_vram in enumerate(TEXTURE_BANK_COUNT_VRAMS):
        entry = vram_to_rom(TEXTURE_KIND_TABLE_VRAM + 8 * kind)
        if be_u32(rom, entry) != kind:
            raise AssetError(f"texture kind table entry {kind} is out of order")
        fmt = vram_to_rom(be_u32(rom, entry + 4))
        image_format, image_size, width, height = struct.unpack_from(">HHHH", rom, fmt)
        count = struct.unpack_from(">H", rom, vram_to_rom(count_vram))[0]
        for index, vram in enumerate(be_u32_array(rom, vram_to_rom(count_vram) + 4, count)):
            start = vram_to_rom(vram)
            size = width * height // 2
            rows.append({"name": f"texture_kind{kind}_{index:02d}", "vram": vram, "rom_start": start,
                         "rom_end": start + size, "format": image_format, "size": image_size,
                         "width": width, "height": height,
                         "sha256": hashlib.sha256(rom[start:start + size]).hexdigest()})
    return rows


# ---------------------------------------------------------------------------
# Font sets: raw blocks DMAed by load_texture_draw_font (0x801053B0).  Layout:
# ``u32 count; u32 offset[count]`` (offsets from the block start, 0x40-aligned;
# the last entry runs to the block end).  Each entry starts with
# ``u32 glyph_count, glyph_height, zero, texture_width, texture_rows,
# texture_offset``, a 128-byte character-to-glyph map (0xFF = no glyph),
# ``glyph_count`` 4-byte records {s, t, width, unused}, and an IA8 texture.


@dataclass(frozen=True)
class FontSet:
    name: str
    rom_start: int
    rom_end: int


FONT_SETS = (
    FontSet("font_set_0", 0x2C3E50, 0x2CB230),
    FontSet("font_set_1", 0x2CB230, 0x2D2790),
)
FONT_ENTRY_HEADER = struct.Struct(">6I")
FONT_MAP_OFFSET = 0x18
FONT_MAP_SIZE = 0x80
FONT_GLYPH_OFFSET = FONT_MAP_OFFSET + FONT_MAP_SIZE


def parse_font_set(block: bytes) -> list[dict]:
    count = be_u32(block, 0)
    if not 1 <= count <= 64:
        raise AssetError(f"implausible font entry count {count}")
    offsets = list(be_u32_array(block, 4, count))
    edges = [*offsets, len(block)]
    if offsets[0] < 4 + 4 * count or any(offset % 0x40 for offset in offsets):
        raise AssetError("font entry offsets are not 0x40-aligned after the table")
    if any(left >= right for left, right in zip(edges, edges[1:])):
        raise AssetError("font entry offsets are not ascending")
    entries = []
    for index, (left, right) in enumerate(zip(edges, edges[1:])):
        entry = block[left:right]
        glyphs, height, _zero, width, rows, texture = FONT_ENTRY_HEADER.unpack_from(entry, 0)
        glyph_end = FONT_GLYPH_OFFSET + 4 * glyphs
        if not glyph_end <= texture < glyph_end + 0x40 or texture % 8:
            raise AssetError(f"font entry {index}: texture offset 0x{texture:X} does not follow its glyphs")
        if not 0 < width <= 0x400 or texture + width * rows > len(entry) or len(entry) - texture - width * rows >= 0x40:
            raise AssetError(f"font entry {index}: IA8 texture {width}x{rows} does not fill the entry")
        glyph_map = entry[FONT_MAP_OFFSET:FONT_GLYPH_OFFSET]
        if any(value != 0xFF and value > glyphs for value in glyph_map):
            raise AssetError(f"font entry {index}: character map refers past glyph {glyphs}")
        for glyph in range(glyphs):
            s, t, glyph_width, _unused = entry[FONT_GLYPH_OFFSET + 4 * glyph:FONT_GLYPH_OFFSET + 4 * glyph + 4]
            if s + glyph_width > width + 1 or t + height > rows + 1:
                raise AssetError(f"font entry {index} glyph {glyph} lies outside its texture")
        entries.append({"start": left, "end": right, "glyphs": glyphs, "height": height, "width": width,
                        "rows": rows, "texture_offset": texture,
                        "mapped": sum(1 for value in glyph_map if value != 0xFF)})
    return entries


def font_sets(rom: bytes) -> list[dict]:
    return [{"name": font.name, "rom_start": font.rom_start, "rom_end": font.rom_end,
             "entries": parse_font_set(rom[font.rom_start:font.rom_end])} for font in FONT_SETS]


# ---------------------------------------------------------------------------
# Raw colour-indexed images.  func_800F5960 DMAs a stream straight into the
# draw buffer; func_800F5B6C draws briefing images as CI8 with a 256-colour
# TLUT at the stream start, and func_801009E8 draws level maps as CI4 with a
# 16-colour TLUT.  Records are {u32 pi_start, pi_end; s32 width, height}.


@dataclass(frozen=True)
class ImageTable:
    name: str
    vram: int
    count: int
    stride: int
    size_id: int  # 0 = CI4, 1 = CI8


IMAGE_TABLES = (
    ImageTable("briefing", 0x80141768, 17, 0x10, 1),
    ImageTable("level_map", 0x80141308, 15, 0x28, 0),
)
# Briefing rows 4 and 7 are never selected by the level-to-image list at
# 0x801416F8; their table sizes (155x30, 168x30) do not fit the streams, which
# decode exactly at the sizes below.
IMAGE_SIZE_OVERRIDES = {("briefing", 4): (199, 80), ("briefing", 7): (210, 80)}
IMAGE_RECORD = struct.Struct(">IIii")


def image_streams(rom: bytes) -> list[dict]:
    rows = []
    for table in IMAGE_TABLES:
        for index in range(table.count):
            start, end, width, height = IMAGE_RECORD.unpack_from(rom, vram_to_rom(table.vram) + index * table.stride)
            if start == 0 or end - start <= 1:
                continue  # empty slot or terminator
            start, end = pi_to_rom(start), pi_to_rom(end)
            width, height = IMAGE_SIZE_OVERRIDES.get((table.name, index), (width, height))
            colours = 256 if table.size_id else 16
            pixels = width * height if table.size_id else (width * height + 1) // 2
            used = 2 * colours + pixels
            if not 0 <= (end - start) - used < 0x40:
                raise AssetError(f"{table.name}[{index}]: {width}x{height} does not fit 0x{end - start:X} bytes")
            rows.append({"name": f"{table.name}_{index:02d}", "rom_start": start, "rom_end": end,
                         "data_size": used, "format": 2, "size": table.size_id,
                         "width": width, "height": height})
    return rows


# ---------------------------------------------------------------------------
# Level streams.  func_800865E0 (called from initialize_runtime_state) fills a
# 28-record table at 0x80125A68 with {world_start, world_end, nav_start,
# nav_end} cartridge addresses.  The level loader func_80088CF0 decodes the
# world stream and relocates its nine section offsets (the 16-byte records of
# section 7 are counted as (offset[8] - offset[7]) / 16); func_800DDA08 decodes
# the navigation stream for the AI and relocates the size word and the section
# offsets at 0x0C..0x1C.  Records 18..23 are unused.

LEVEL_STREAMS = (
    (0, (0x738900, 0x73B2ED), None),
    (1, (0x73B2F0, 0x742D4E), (0x6F9C40, 0x6FEE7B)),
    (2, (0x742D50, 0x7472BF), (0x6FEE80, 0x7017CF)),
    (3, (0x7472C0, 0x74F0F3), (0x7017D0, 0x70510B)),
    (4, (0x74F0F8, 0x754EEE), (0x705110, 0x709533)),
    (5, (0x754EF0, 0x756FA0), (0x709538, 0x709BFE)),
    (6, (0x756FA0, 0x75EC8F), (0x709C00, 0x70D997)),
    (7, (0x75EC90, 0x767ED4), (0x70D998, 0x711DCF)),
    (8, (0x767ED8, 0x76FE3E), (0x711DD0, 0x716B2E)),
    (9, (0x76FE40, 0x771EA8), (0x716B30, 0x7175C6)),
    (10, (0x771EA8, 0x77A36E), (0x7175C8, 0x71B3DA)),
    (11, (0x77A370, 0x783327), (0x71B3E0, 0x722A4D)),
    (12, (0x783328, 0x78A974), (0x722A50, 0x726272)),
    (13, (0x78A978, 0x7909F2), (0x726278, 0x727F76)),
    (14, (0x7909F8, 0x79731D), (0x727F78, 0x72D02C)),
    (15, (0x797320, 0x79EB33), (0x72D030, 0x730C8C)),
    (16, (0x79EB38, 0x7A6187), (0x731460, 0x73789B)),
    (17, (0x7A6188, 0x7A8868), (0x730C90, 0x731460)),
    (24, (0x7A8868, 0x7ADEE6), (0x7378A0, 0x7388F5)),
    (25, (0x7ADEE8, 0x7B0F3F), None),
    (26, (0x7B0F40, 0x7B4508), None),
    (27, (0x7B4508, 0x7B69A0), None),
)
WORLD_SECTIONS = 9
WORLD_RECORD_SIZE = 0x10
NAV_HEADER = struct.Struct(">IIHHIIIII")  # size, size, two counts, five section offsets
NAV_HEADER_SIZE = 0x28  # the header is followed by two more words before section 0


def decode_stream(rom: bytes, start: int, end: int) -> bytes:
    result = lzari.decompress_with_info(rom[start:end])
    if result.consumed_bytes > end - start or len(result.data) != LZARI_HEADER.unpack_from(rom, start)[0]:
        raise AssetError(f"0x{start:X}: LZARI stream does not fit its range")
    return result.data


def parse_world_stream(data: bytes) -> dict:
    offsets = be_u32_array(data, 0, WORLD_SECTIONS)
    if offsets[0] != 4 * WORLD_SECTIONS or list(offsets) != sorted(offsets) or offsets[-1] != len(data):
        raise AssetError("world stream section offsets are not an ascending table ending at the stream size")
    if (offsets[8] - offsets[7]) % WORLD_RECORD_SIZE:
        raise AssetError("world stream record section is not a whole number of 16-byte records")
    return {"size": len(data), "sections": list(offsets), "records": (offsets[8] - offsets[7]) // WORLD_RECORD_SIZE}


def parse_nav_stream(data: bytes) -> dict:
    size, size_again, count_a, count_b, *offsets = NAV_HEADER.unpack_from(data, 0)
    if size != len(data) or size_again != len(data):
        raise AssetError("navigation stream size words do not match the stream")
    if offsets[0] != NAV_HEADER_SIZE or list(offsets) != sorted(offsets) or offsets[-1] > len(data):
        raise AssetError("navigation stream section offsets are not ascending within the stream")
    return {"size": len(data), "counts": [count_a, count_b], "sections": offsets}


def level_streams(rom: bytes) -> list[dict]:
    rows = []
    for index, world, nav in LEVEL_STREAMS:
        row = {"index": index, "world": None, "nav": None}
        if world:
            row["world"] = {"rom_start": world[0], "rom_end": world[1],
                            **parse_world_stream(decode_stream(rom, *world))}
        if nav:
            row["nav"] = {"rom_start": nav[0], "rom_end": nav[1], **parse_nav_stream(decode_stream(rom, *nav))}
        rows.append(row)
    return rows


def catalogue(rom: bytes) -> list[dict]:
    rows = []
    for resource in (*RESOURCE_BUNDLES, *read_pi_table(rom, RESOURCE_BUNDLE_STRIP_TABLE)):
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
    audio = audio_inventory(rom)
    textures = texture_banks(rom)
    (args.output / "audio.json").write_text(json.dumps(audio, indent=1) + "\n")
    (args.output / "textures.json").write_text(json.dumps(textures, indent=1) + "\n")
    fonts = font_sets(rom)
    images = image_streams(rom)
    (args.output / "fonts.json").write_text(json.dumps(fonts, indent=1) + "\n")
    (args.output / "images.json").write_text(json.dumps(images, indent=1) + "\n")
    levels = level_streams(rom)
    (args.output / "levels.json").write_text(json.dumps(levels, indent=1) + "\n")
    if args.command == "extract":
        for row in rows:
            resource = Resource(**{k: row[k] for k in Resource.__dataclass_fields__})
            data = decode_resource(rom, resource)
            folder = args.output / row["name"]
            folder.mkdir(parents=True, exist_ok=True)
            for index, entry in enumerate(row["entries"]):
                (folder / f"entry_{index:02d}.bin").write_bytes(data[entry["start"]:entry["end"]])
        audio_folder = args.output / "audio"
        audio_folder.mkdir(parents=True, exist_ok=True)
        for bank in audio["banks"]:
            (audio_folder / f"{bank['name']}.ctl").write_bytes(rom[bank["ctl_start"]:bank["ctl_end"]])
            (audio_folder / f"{bank['name']}.tbl").write_bytes(rom[bank["tbl_start"]:bank["tbl_end"]])
        for sequence in audio["sequences"]:
            midi = rom[sequence["rom_start"]:sequence["rom_start"] + sequence["midi_size"]]
            (audio_folder / f"{sequence['name']}.mid").write_bytes(midi)
        texture_folder = args.output / "textures"
        texture_folder.mkdir(parents=True, exist_ok=True)
        for texture in textures:
            pixels = n64_texture.decode_texture(rom[texture["rom_start"]:texture["rom_end"]], texture["format"],
                                                texture["size"], texture["width"], texture["height"])
            png = n64_texture.encode_png_rgba(texture["width"], texture["height"], pixels)
            (texture_folder / f"{texture['name']}.png").write_bytes(png)
        font_folder = args.output / "fonts"
        font_folder.mkdir(parents=True, exist_ok=True)
        for font in fonts:
            block = rom[font["rom_start"]:font["rom_end"]]
            for index, entry in enumerate(font["entries"]):
                texture = entry["start"] + entry["texture_offset"]
                pixels = n64_texture.decode_texture(block[texture:texture + entry["width"] * entry["rows"]], 3, 1,
                                                    entry["width"], entry["rows"])
                png = n64_texture.encode_png_rgba(entry["width"], entry["rows"], pixels)
                (font_folder / f"{font['name']}_{index:02d}.png").write_bytes(png)
        image_folder = args.output / "images"
        image_folder.mkdir(parents=True, exist_ok=True)
        for image in images:
            data = rom[image["rom_start"]:image["rom_start"] + image["data_size"]]
            pixels = n64_texture.decode_texture(data, image["format"],
                                                image["size"], image["width"], image["height"])
            png = n64_texture.encode_png_rgba(image["width"], image["height"], pixels)
            (image_folder / f"{image['name']}.png").write_bytes(png)
        level_folder = args.output / "levels"
        level_folder.mkdir(parents=True, exist_ok=True)
        for level in levels:
            for part in ("world", "nav"):
                if level[part]:
                    data = decode_stream(rom, level[part]["rom_start"], level[part]["rom_end"])
                    (level_folder / f"level_{level['index']:02d}_{part}.bin").write_bytes(data)
    for row in rows:
        print(f"{row['name']:16} ROM 0x{row['rom_start']:06X}-0x{row['rom_end']:06X} "
              f"{row['encoding']:5} 0x{row['expanded_size']:05X} bytes, {len(row['entries'])} entries")


if __name__ == "__main__":
    main()
