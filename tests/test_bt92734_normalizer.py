import os
from pathlib import Path
import subprocess
import sys
import tempfile
import unittest


ROOT = Path(__file__).resolve().parents[1]
TOOL = ROOT / "tools" / "modern_asn64.py"
KMC = ROOT / ".toolchain" / "kmc-gcc-2.7.2"
SOURCE = ROOT / "src" / "code" / "effects" / "update_effect_kind_5.c"
RULE = "BT92734-UPDATE-KIND5"


class UpdateEffectKind5NormalizerTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls) -> None:
        cls.temporary = tempfile.TemporaryDirectory(dir=ROOT / "build")
        cls.directory = Path(cls.temporary.name)
        cls.raw = cls.directory / "raw.s"
        subprocess.run(
            [
                str(KMC / "gcc"),
                f"-B{KMC}/",
                "-S",
                "-O2",
                "-G0",
                "-mips3",
                "-mgp32",
                "-mfp32",
                "-Iinclude",
                "-o",
                str(cls.raw),
                str(SOURCE),
            ],
            check=True,
            cwd=ROOT,
        )

    @classmethod
    def tearDownClass(cls) -> None:
        cls.temporary.cleanup()

    def invoke(self, text: str, disabled: str = ""):
        source = self.directory / "fixture.s"
        output = self.directory / "expanded.s"
        fires = self.directory / "fires.tsv"
        source.write_text(text, encoding="ascii")
        output.unlink(missing_ok=True)
        fires.unlink(missing_ok=True)
        env = dict(os.environ)
        env["MODERN_ASN64_DUMP"] = str(output)
        env["MODERN_ASN64_FIRES"] = str(fires)
        env["MODERN_ASN64_DISABLE"] = disabled
        result = subprocess.run(
            [sys.executable, str(TOOL), "/bin/true", str(source)],
            cwd=ROOT,
            env=env,
            text=True,
            capture_output=True,
        )
        return result, output, fires

    def test_rule_fires_exactly_once_and_can_be_disabled(self) -> None:
        raw = self.raw.read_text(encoding="ascii")
        result, output, fires = self.invoke(raw)
        self.assertEqual(result.returncode, 0, result.stderr)
        self.assertTrue(output.is_file())
        self.assertEqual(fires.read_text(encoding="ascii").count(f"{RULE}\t1\n"), 1)

        disabled, disabled_output, disabled_fires = self.invoke(raw, RULE)
        self.assertEqual(disabled.returncode, 0, disabled.stderr)
        self.assertTrue(disabled_output.is_file())
        self.assertNotIn(RULE, disabled_fires.read_text(encoding="ascii"))

    def test_rule_rejects_source_drift_duplicate_and_second_application(self) -> None:
        raw = self.raw.read_text(encoding="ascii")
        marker = "\tl.d\t$f22,D_80071EA8\n"
        self.assertEqual(raw.count(marker), 1)
        drifted, _, _ = self.invoke(raw.replace(marker, "\tl.d\t$f20,D_80071EA8\n", 1))
        self.assertNotEqual(drifted.returncode, 0)

        duplicated, _, _ = self.invoke(raw + raw)
        self.assertNotEqual(duplicated.returncode, 0)

        first, normalized, _ = self.invoke(raw)
        self.assertEqual(first.returncode, 0, first.stderr)
        second, _, _ = self.invoke(normalized.read_text(encoding="ascii"))
        self.assertNotEqual(second.returncode, 0)

    def test_unrelated_function_is_unchanged(self) -> None:
        unrelated = "\t.text\nfixture_unrelated:\n\tjr\t$31\n\tnop\n\t.end\tfixture_unrelated\n"
        result, output, fires = self.invoke(unrelated)
        self.assertEqual(result.returncode, 0, result.stderr)
        enabled_text = output.read_text(encoding="ascii")
        disabled, disabled_output, _ = self.invoke(unrelated, RULE)
        self.assertEqual(disabled.returncode, 0, disabled.stderr)
        self.assertEqual(enabled_text, disabled_output.read_text(encoding="ascii"))
        self.assertNotIn(RULE, fires.read_text(encoding="ascii"))


if __name__ == "__main__":
    unittest.main()
