from __future__ import annotations

import json
import sys
import tempfile
import tomllib
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))

from generate_splat_config import canonical_functions
from generate_decomp_report import build_report
from decompkit.config import load_config
from decompkit.adapters import CommandBuildAdapter, ImageReference
from decompkit.tables import parse_address_ranges, read_tsv
from verify_rom import EXPECTED_SHA1, EXPECTED_SHA256, EXPECTED_SIZE, verify


class ProjectTests(unittest.TestCase):
    def setUp(self) -> None:
        self.catalogue = tomllib.loads((ROOT / "config/us/recomp_function_boundaries.toml").read_text())

    def test_catalogue_shape_and_ranges(self) -> None:
        section = self.catalogue["section"][0]
        self.assertEqual(section["rom"], 0x1000)
        self.assertEqual(section["vram"], 0x80071000)
        self.assertEqual(section["size"], 0x100000)
        self.assertEqual(len(section["functions"]), 1738)
        canonical = canonical_functions(section)
        # 26 catalogue entries are internal aliases or overlapping hypotheses;
        # they remain documented but cannot be independent linker segments.
        self.assertEqual(len(canonical), 1738)
        for left, right in zip(canonical, canonical[1:]):
            self.assertLessEqual(left["vram"] + left["size"], right["vram"])

    def test_rom_contract(self) -> None:
        self.assertEqual(EXPECTED_SIZE, 8 * 1024 * 1024)
        self.assertEqual(EXPECTED_SHA1, "535860d941738ac1210c20a9b80114fea0e0ff17")
        self.assertEqual(EXPECTED_SHA256, "c5b7cf3523de025e3f18e2c8df2deb0eced5613e7c46cb8c6c5a4f22644ead3f")

    def test_rejects_non_rom(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            path = Path(directory) / "bad.z64"
            path.write_bytes(b"not a rom")
            with self.assertRaises(SystemExit):
                verify(path)

    def test_vita_architecture_is_durable(self) -> None:
        text = (ROOT / "docs/ARCHITECTURE.md").read_text()
        for required in ("ARMv7-A", "ILP32", "not AArch64", "floating-point ABI", "LP64", "LLP64"):
            self.assertIn(required, text)

    def test_matching_unit_is_a_c_segment(self) -> None:
        splat = (ROOT / "config/us/splat.yaml").read_text()
        self.assertIn("[0xA31A0, c, libultra/ll]", splat)
        for name in ("__ull_rem", "__ull_div", "__ll_div", "__ll_mul"):
            self.assertNotIn(f"asm, functions/{name}]", splat)

    def test_matching_manifest(self) -> None:
        rows = [line.split("\t") for line in (ROOT / "config/us/matching_units.tsv").read_text().splitlines() if line and not line.startswith("#")]
        self.assertEqual(len(rows), 155)
        self.assertEqual(sum(int(row[1], 0) for row in rows), 78356)
        for _start, _size, source, _flags, digest in rows:
            self.assertTrue((ROOT / source).is_file())
            self.assertEqual(len(digest), 64)

        kmc_rows = [line.split("\t") for line in (ROOT / "config/us/matching_kmc_units.tsv").read_text().splitlines() if line and not line.startswith("#")]
        self.assertEqual(len(kmc_rows), 1344)
        self.assertEqual(sum(int(row[1], 0) for row in kmc_rows), 450120)
        for _start, _size, source, _flags, digest in kmc_rows:
            self.assertTrue((ROOT / source).is_file())
            self.assertEqual(len(digest), 64)

        sn_rows = [line.split("\t") for line in (ROOT / "config/us/matching_sn_units.tsv").read_text().splitlines() if line and not line.startswith("#")]
        self.assertEqual(len(sn_rows), 3)
        self.assertEqual(sum(int(row[1], 0) for row in sn_rows), 4328)
        for _start, _size, source, _flags, digest in sn_rows:
            self.assertTrue((ROOT / source).is_file())
            self.assertEqual(len(digest), 64)

        asm_rows = [line.split("\t") for line in (ROOT / "config/us/matching_asm_units.tsv").read_text().splitlines() if line and not line.startswith("#")]
        self.assertEqual(len(asm_rows), 17)
        self.assertEqual(sum(int(row[1], 0) for row in asm_rows), 1348)
        for _start, _size, source, digest in asm_rows:
            self.assertTrue((ROOT / source).is_file())
            self.assertEqual(len(digest), 64)

        data_rows = [line.split("\t") for line in (ROOT / "config/us/matching_data_units.tsv").read_text().splitlines() if line and not line.startswith("#")]
        self.assertEqual(len(data_rows), 197)
        self.assertEqual(sum(int(row[1], 0) for row in data_rows), 153924)
        for _start, _size, source, section, digest in data_rows:
            self.assertTrue((ROOT / source).is_file())
            self.assertIn(section, {".rodata", ".rdata", ".data"})
            self.assertEqual(len(digest), 64)

    def test_recomp_fyi_manifest(self) -> None:
        manifest = json.loads((ROOT / ".recomp.json").read_text())
        self.assertEqual(manifest["$schema"], "https://recomp.fyi/schema/v1.json")
        self.assertEqual(manifest["game"], "BattleTanx")
        self.assertEqual(manifest["system"], "N64")
        self.assertEqual(manifest["type"], "decomp")
        self.assertEqual(manifest["status"], "in-progress")
        self.assertEqual(manifest["original"]["region"], "USA")
        self.assertEqual(manifest["original"]["revision"], "Rev 0")
        self.assertEqual(manifest["original"]["serial"], "NBXE")
        self.assertEqual(manifest["original"]["sha1"], EXPECTED_SHA1)
        self.assertEqual(manifest["project"], "BattleTanx (N64) matching decompilation")

    def test_recomp_fyi_report(self) -> None:
        report = build_report()
        self.assertEqual(report["version"], 2)
        self.assertEqual(len(report["units"]), 1738)
        self.assertEqual(report["measures"]["total_functions"], 1738)
        self.assertGreater(report["measures"]["matched_functions"], 0)
        self.assertEqual(int(report["measures"]["total_data"]), 153924)
        self.assertEqual(report["measures"]["matched_data"], "153924")
        self.assertEqual(report["measures"]["matched_data_percent"], 100.0)
        self.assertEqual({category["id"] for category in report["categories"]},
                         {"game", "libultra", "assets", "assets_textures", "assets_images",
                          "assets_fonts", "assets_models", "assets_animations", "assets_levels",
                          "assets_navigation", "assets_scripts", "assets_music", "assets_sound"})
        by_id = {category["id"]: category for category in report["categories"]}
        expected = {"assets_textures": 1399768, "assets_images": 1671170,
                    "assets_fonts": 59712, "assets_models": 725520,
                    "assets_animations": 752496, "assets_levels": 516211,
                    "assets_navigation": 257151, "assets_scripts": 0,
                    "assets_music": 694320, "assets_sound": 1141682}
        for category_id, size in expected.items():
            self.assertEqual(by_id[category_id]["measures"]["matched_data"], str(size))
        assets = next(category for category in report["categories"] if category["id"] == "assets")
        self.assertEqual(assets["measures"]["matched_data"], "7335936")
        self.assertEqual(assets["measures"]["total_data"], "7335936")
        # The report must remain JSON serializable with protobuf-compatible
        # string encoding for every uint64 field.
        encoded = json.dumps(report)
        self.assertIn('"version": 2', encoded)
        for unit in report["units"]:
            self.assertIsInstance(unit["functions"][0]["size"], str)
            self.assertIsInstance(unit["functions"][0]["address"], str)

    def test_decompkit_configuration_and_manifests(self) -> None:
        config = load_config(ROOT / "config/decompkit.toml")
        self.assertEqual(config.root, ROOT)
        self.assertEqual(config.report_output, ROOT / "build/report.json")
        self.assertEqual([pipeline for _path, pipeline in config.unit_manifests],
                         ["ido", "kmc", "sn", "assembly"])
        ranges = parse_address_ranges(
            [path for path, _pipeline in config.unit_manifests], allow_empty=True
        )
        self.assertEqual(len(ranges), 1519)
        self.assertEqual(sum(int(row["SIZE"], 0)
                             for row in read_tsv(config.data_manifest)), 153924)

    def test_decompkit_adapter_protocol(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            directory = Path(directory)
            source = directory / "unit.c"
            source.write_text("void unit(void) {}\n")
            adapter_script = directory / "adapter.py"
            adapter_script.write_text(
                "import json,sys\n"
                "request=json.load(open(sys.argv[1]))\n"
                "json.dump({'format':'decompkit-build-response-v1',"
                "'text_hex':'54455854','text_size':4,'rodata_hex':'44415441',"
                "'rodata_vram':'0x1008'},open(sys.argv[2],'w'))\n"
            )
            adapter = CommandBuildAdapter(
                [sys.executable, str(adapter_script), "{request}", "{response}"]
            )
            built = adapter(str(source), 0x1000, pipeline="test")
            self.assertEqual((built["text"], built["rodata"]), (b"TEXT", b"DATA"))
            image = directory / "image.bin"
            image.write_bytes(b"TEXT----DATA")
            reference = ImageReference(image, lambda address: address - 0x1000)
            self.assertEqual(reference(0x1008, 4), b"DATA")


if __name__ == "__main__":
    unittest.main()
