from __future__ import annotations

import sys
import tempfile
import tomllib
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))

from generate_splat_config import canonical_functions
from verify_rom import EXPECTED_SHA1, EXPECTED_SHA256, EXPECTED_SIZE, verify


class ProjectTests(unittest.TestCase):
    def setUp(self) -> None:
        self.catalogue = tomllib.loads((ROOT / "config/us/recomp_function_boundaries.toml").read_text())

    def test_catalogue_shape_and_ranges(self) -> None:
        section = self.catalogue["section"][0]
        self.assertEqual(section["rom"], 0x1000)
        self.assertEqual(section["vram"], 0x80071000)
        self.assertEqual(section["size"], 0x100000)
        self.assertEqual(len(section["functions"]), 1692)
        canonical = canonical_functions(section)
        # 101 catalogue entries are internal aliases or overlapping hypotheses;
        # they remain documented but cannot be independent linker segments.
        self.assertEqual(len(canonical), 1591)
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
        self.assertEqual(len(rows), 46)
        self.assertEqual(sum(int(row[1], 0) for row in rows), 7216)
        for _start, _size, source, _flags, digest in rows:
            self.assertTrue((ROOT / source).is_file())
            self.assertEqual(len(digest), 64)

        kmc_rows = [line.split("\t") for line in (ROOT / "config/us/matching_kmc_units.tsv").read_text().splitlines() if line and not line.startswith("#")]
        self.assertEqual(len(kmc_rows), 102)
        self.assertEqual(sum(int(row[1], 0) for row in kmc_rows), 4760)
        for _start, _size, source, _flags, digest in kmc_rows:
            self.assertTrue((ROOT / source).is_file())
            self.assertEqual(len(digest), 64)

        asm_rows = [line.split("\t") for line in (ROOT / "config/us/matching_asm_units.tsv").read_text().splitlines() if line and not line.startswith("#")]
        self.assertEqual(len(asm_rows), 14)
        self.assertEqual(sum(int(row[1], 0) for row in asm_rows), 1212)
        for _start, _size, source, digest in asm_rows:
            self.assertTrue((ROOT / source).is_file())
            self.assertEqual(len(digest), 64)


if __name__ == "__main__":
    unittest.main()
