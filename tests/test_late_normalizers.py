import os
from pathlib import Path
import subprocess
import sys
import tempfile
import unittest


ROOT = Path(__file__).resolve().parents[1]
TOOL = ROOT / "tools" / "modern_asn64.py"
KMC = ROOT / ".toolchain" / "kmc-gcc-2.7.2"
CASES = (
    (
        "BT10874-SEGMENT-HIT",
        ROOT / "src/code/math/find_segment_hit.c",
        "\tl.s\t$f0,0($11)\n",
    ),
    (
        "BT106010-TEXT-CHAR",
        ROOT / "src/code/render/draw_text_char.c",
        "\tor\t$2,$7,$6\n",
    ),
    (
        "BT10647C-TEXT-CHAR-FIXED",
        ROOT / "src/code/render/draw_text_char_fixed.c",
        "\tlbu\t$18,153($2)\n",
    ),
    (
        "BT9A354-PUSH-FP-ALLOC",
        ROOT / "src/code/gameplay/update_tank_drive.c",
        "\tl.s\t$f10,912($17)\n",
    ),
    (
        "BTD455C-CONTROLS-ALLOC",
        ROOT / "src/code/frontend/draw_controls_help_screen.c",
        "\tmove\t$7,$16\n",
    ),
)


class LateFunctionNormalizerTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls) -> None:
        cls.temporary = tempfile.TemporaryDirectory(dir=ROOT / "build")
        cls.directory = Path(cls.temporary.name)
        cls.raw = {}
        for rule, source, _ in CASES:
            output = cls.directory / f"{rule}.s"
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
                    str(output),
                    str(source),
                ],
                check=True,
                cwd=ROOT,
            )
            cls.raw[rule] = output.read_text(encoding="ascii")

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

    def test_rules_fire_once_and_disable_cleanly(self) -> None:
        for rule, _, _ in CASES:
            with self.subTest(rule=rule):
                result, output, fires = self.invoke(self.raw[rule])
                self.assertEqual(result.returncode, 0, result.stderr)
                self.assertTrue(output.is_file())
                self.assertEqual(fires.read_text(encoding="ascii").count(f"{rule}\t1\n"), 1)

                disabled, disabled_output, disabled_fires = self.invoke(self.raw[rule], rule)
                self.assertEqual(disabled.returncode, 0, disabled.stderr)
                self.assertTrue(disabled_output.is_file())
                self.assertNotIn(rule, disabled_fires.read_text(encoding="ascii"))

    def test_rules_reject_drift_duplicate_and_second_application(self) -> None:
        for rule, _, marker in CASES:
            with self.subTest(rule=rule):
                raw = self.raw[rule]
                self.assertEqual(raw.count(marker), 1)
                drifted, _, _ = self.invoke(raw.replace(marker, "\tnop\n", 1))
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
        disabled, disabled_output, _ = self.invoke(
            unrelated, ",".join(rule for rule, _, _ in CASES)
        )
        self.assertEqual(disabled.returncode, 0, disabled.stderr)
        self.assertEqual(enabled_text, disabled_output.read_text(encoding="ascii"))
        fire_text = fires.read_text(encoding="ascii")
        for rule, _, _ in CASES:
            self.assertNotIn(rule, fire_text)


if __name__ == "__main__":
    unittest.main()
