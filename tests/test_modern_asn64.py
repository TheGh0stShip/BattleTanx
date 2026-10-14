import os
from pathlib import Path
import subprocess
import sys
import tempfile
import unittest


ROOT = Path(__file__).resolve().parents[1]
TOOL = ROOT / "tools" / "modern_asn64.py"


class ModernAsn64Tests(unittest.TestCase):
    def preprocess(self, body: str, disabled: str = "") -> str:
        with tempfile.TemporaryDirectory() as directory:
            source = Path(directory) / "fixture.s"
            output = Path(directory) / "expanded.s"
            source.write_text("\t.text\n" + body, encoding="ascii")
            env = dict(os.environ)
            env["MODERN_ASN64_DUMP"] = str(output)
            env["MODERN_ASN64_DISABLE"] = disabled
            subprocess.run(
                [sys.executable, str(TOOL), "/bin/true", str(source)],
                check=True,
                cwd=ROOT,
                env=env,
            )
            return output.read_text(encoding="ascii")

    def test_symbol_plus_base_load_uses_at(self) -> None:
        text = self.preprocess("\tlw\t$2,D_801144A0($3)\n")
        self.assertIn("lui $at,%hi(D_801144A0)", text)
        self.assertIn("addu $at,$at,$3", text)
        self.assertIn("lw $2,%lo(D_801144A0)($at)", text)

    def test_large_offset_add_order_is_retail_order(self) -> None:
        text = self.preprocess("\tsw\t$2,49152($4)\n")
        self.assertIn("lui $at,0x1", text)
        self.assertIn("addu $at,$4,$at", text)
        self.assertIn("sw $2,-16384($at)", text)

    def test_float_compare_label_hazard_gets_nop(self) -> None:
        text = self.preprocess(
            "\tc.lt.s\t$f2,$f0\n.L17:\n\tbc1f\t.L18\n\tmove\t$2,$0\n.L18:\n"
        )
        self.assertIn(".L17:\n\tnop\n\tbc1f", text)

    def test_remu_expands_to_divu_and_mfhi(self) -> None:
        text = self.preprocess("\tremu\t$3,$2,$4\n")
        self.assertIn("divu $0,$2,$4", text)
        self.assertIn("break 0x7", text)
        self.assertIn("mfhi $3", text)

    def test_multu_observes_hilo_hazard(self) -> None:
        text = self.preprocess(
            "\tmultu\t$2,$3\n\tmfhi\t$4\n\taddu\t$2,$2,$17\n\tmultu\t$2,$3\n"
        )
        self.assertIn("addu\t$2,$2,$17\n\tnop\n\tmultu", text)

    def test_hoisted_float_multiply_gets_spacing_nop(self) -> None:
        text = self.preprocess(
            "\tmul.s\t$f0,$f20,$f0\n"
            "\t.set\tnoreorder\n"
            "\tj\t.L1\n"
            "\tmul.s\t$f0,$f0,$f2\n"
            ".L1:\n"
        )
        self.assertIn(
            "mul.s\t$f0,$f20,$f0\n\tnop\n\tmul.s\t$f0,$f0,$f2\n\tj\t.L1\n\tnop",
            text,
        )

    def test_disabled_rule_leaves_symbol_load_for_gas(self) -> None:
        text = self.preprocess(
            "\tlw\t$2,D_801144A0($3)\n", disabled="MEM-SYM-BASE"
        )
        self.assertIn("lw\t$2,D_801144A0($3)", text)
        self.assertNotIn("%hi(D_801144A0)", text)


if __name__ == "__main__":
    unittest.main()
