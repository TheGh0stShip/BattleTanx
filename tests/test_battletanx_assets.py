"""Layout, codec and report-accounting tests for BattleTanx asset tooling."""

from __future__ import annotations

import struct
import sys
import tempfile
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))

import battletanx_assets as assets  # noqa: E402
import generate_decomp_report as report  # noqa: E402
import lzari  # noqa: E402
import verify_matching_units as verifier  # noqa: E402

ROM = ROOT / "baseroms/us/baserom.z64"


def synthetic_bundle(entries: list[bytes]) -> bytes:
    count = len(entries)
    header = struct.pack(">II", count, assets.bundle_header_size(count))
    boundaries, cursor = [], 0
    for entry in entries[:-1]:
        cursor += len(entry)
        boundaries.append(cursor)
    header += struct.pack(f">{count}I", *boundaries, 0)
    header += b"\0" * (assets.bundle_header_size(count) - len(header))
    return header + b"".join(entries)


class EndianTests(unittest.TestCase):
    def test_big_endian_words(self) -> None:
        data = bytes.fromhex("B02FC650 00000010")
        self.assertEqual(assets.be_u32(data, 0), 0xB02FC650)
        self.assertEqual(assets.be_u32_array(data, 0, 2), (0xB02FC650, 0x10))
        with self.assertRaises(assets.AssetError):
            assets.be_u32(data, 6)

    def test_address_conversions(self) -> None:
        self.assertEqual(assets.pi_to_rom(0xB02FC650), 0x2FC650)
        self.assertEqual(assets.vram_to_rom(0x80134B88), 0xC4B88)
        with self.assertRaises(assets.AssetError):
            assets.pi_to_rom(0x80134B88)


class LayoutTests(unittest.TestCase):
    def test_record_sizes(self) -> None:
        self.assertEqual(assets.LZARI_HEADER.size, 4)
        self.assertEqual(assets.BUNDLE_HEADER.size, 8)
        self.assertEqual([assets.bundle_header_size(n) for n in (1, 4, 5, 9, 25, 30)],
                         [0x10, 0x18, 0x20, 0x30, 0x70, 0x80])
        table = assets.RESOURCE_BUNDLE_STRIP_TABLE
        self.assertEqual(table.end_vram - table.start_vram, 4 * table.count)

    def test_bundle_round_trip(self) -> None:
        entries = [b"A" * 8, b"BB" * 6, b"C" * 3]
        bundle = assets.parse_bundle(synthetic_bundle(entries))
        data = synthetic_bundle(entries)
        self.assertEqual(bundle.count, 3)
        self.assertEqual([data[s:e] for s, e in bundle.entries], entries)

    def test_bundle_rejects_bad_headers(self) -> None:
        good = bytearray(synthetic_bundle([b"x" * 4, b"y" * 4]))
        bad = bytearray(good)
        struct.pack_into(">I", bad, 4, 0x40)
        with self.assertRaises(assets.AssetError):
            assets.parse_bundle(bytes(bad))
        bad = bytearray(good)
        struct.pack_into(">I", bad, 12, 7)
        with self.assertRaises(assets.AssetError):
            assets.parse_bundle(bytes(bad))


class LzariTests(unittest.TestCase):
    def test_round_trip_and_header(self) -> None:
        source = synthetic_bundle([bytes(range(256)) * 3, b"tank" * 300])
        stream = lzari.compress(source)
        self.assertEqual(struct.unpack_from(">I", stream)[0], len(source))
        self.assertEqual(lzari.decompress(stream), source)

    def test_empty_stream(self) -> None:
        self.assertEqual(lzari.decompress(struct.pack(">I", 0)), b"")


class ManifestAccountingTests(unittest.TestCase):
    def test_asset_progress_inventory(self) -> None:
        total, identified = report.asset_progress()
        self.assertEqual(total, 0x800000 - 0x101000)
        self.assertEqual(identified, 0x20EA80)

    def test_data_rows_accept_optional_section(self) -> None:
        four = "0x5EA0\t0x100\tsrc/libultra/xprintf.c\t" + "0" * 64
        five = "0xD6FC0\t0x50\tsrc/libultra/xprintf.c\t.data\t" + "0" * 64
        self.assertEqual(verifier.parse_data_row(four)[3], ".rodata")
        self.assertEqual(verifier.parse_data_row(five)[:4], (0xD6FC0, 0x50, "src/libultra/xprintf.c", ".data"))
        with self.assertRaises(ValueError):
            verifier.parse_data_row("0x0\t0x4\tsrc/x.c\t.bss\t" + "0" * 64)

    def test_report_counts_only_initialized_data(self) -> None:
        built = report.build_report()
        measures = built["measures"]
        section_vram = 0x80071000
        self.assertEqual(int(measures["total_data"]),
                         report.INITIALIZED_DATA_END - section_vram - int(measures["total_code"]))
        categories = {c["id"]: int(c["measures"]["total_data"]) for c in built["categories"]}
        self.assertEqual(categories["game"] + categories["libultra"], int(measures["total_data"]))
        self.assertEqual(categories["assets"], 0x800000 - 0x101000)


@unittest.skipUnless(ROM.is_file(), "requires the supported ROM")
class RomTests(unittest.TestCase):
    def test_entry_point_bss_bounds(self) -> None:
        import survey_static_data as survey
        rom = survey.read_rom(ROM)
        self.assertEqual(survey.bss_bounds(rom, 0x1000), (report.INITIALIZED_DATA_END, 0x803C8880))

    def test_strip_table_is_a_contiguous_chain(self) -> None:
        rom = assets.load_rom(ROM)
        strips = assets.read_pi_table(rom, assets.RESOURCE_BUNDLE_STRIP_TABLE)
        spans = sorted((r.rom_start, r.rom_end) for r in strips)
        for (_, end), (start, _) in zip(spans, spans[1:]):
            self.assertEqual(end, start)

    def test_catalogue_decodes_every_resource(self) -> None:
        rom = assets.load_rom(ROM)
        rows = assets.catalogue(rom)
        self.assertEqual(len(rows), len(assets.RESOURCE_BUNDLES) + assets.RESOURCE_BUNDLE_STRIP_TABLE.count)
        for row in rows:
            self.assertLessEqual(row["expanded_size"], row["capacity"])
            self.assertEqual(row["entries"][-1]["end"], row["expanded_size"])


if __name__ == "__main__":
    unittest.main()
