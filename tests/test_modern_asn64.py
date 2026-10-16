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

    def test_multiword_positive_offset_uses_at(self) -> None:
        text = self.preprocess("\tlw\t$16,72008($19)\n")
        self.assertIn("lui $at,0x1", text)
        self.assertIn("addu $at,$19,$at", text)
        self.assertIn("lw $16,6472($at)", text)

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

    def test_full_width_li_counts_as_two_hazard_instructions(self) -> None:
        text = self.preprocess(
            "\tmult\t$4,$22\n\tmfhi\t$8\n"
            "\tli\t$2,-1431655765\n\tmultu\t$3,$2\n"
        )
        self.assertNotIn("li\t$2,-1431655765\n\tnop\n\tmultu", text)

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

    def test_inlined_intersection_uses_retail_likely_branch(self) -> None:
        text = self.preprocess(
            "func_800E1118:\n"
            "\tsub.s\t$f4,$f10,$f6\n"
            "\tmtc1\t$0,$f2\n"
            "\t#nop\n"
            "\tc.eq.s\t$f4,$f2\n"
            "\t#nop\n"
            "\t.set\tnoreorder\n"
            "\t.set\tnomacro\n"
            "\tbc1t\t.L61\n"
            "\tmul.s\t$f0,$f10,$f2\n"
            "\t.set\tmacro\n"
            "\t.set\treorder\n"
            ".L61:\n"
        )
        self.assertIn(
            "mul.s\t$f0,$f10,$f2\n"
            "\t.set\tnomacro\n"
            "\tbc1tl\t.L61\n"
            "\tnop\n",
            text,
        )

    def test_morph_model_address_uses_retail_operand_order(self) -> None:
        body = (
            "func_8009201C:\n"
            "\tlbu\t$2,14($20)\n"
            "\tsll\t$3,$3,2\n"
            "\taddu\t$3,$3,$5\n"
            "\tlhu\t$3,2($3)\n"
        )
        text = self.preprocess(body)
        self.assertIn("addu\t$3,$5,$3", text)

        disabled = self.preprocess(body, disabled="MORPH-MODEL-ADDRESS-ORDER")
        self.assertIn("addu\t$3,$3,$5", disabled)

    def test_attached_camera_uses_retail_floating_registers(self) -> None:
        body = (
            "func_80077E94:\n"
            "\tadd.s\t$f20,$f2,$f0\n"
            "\ts.s\t$f20,8($18)\n"
            "\tsub.s\t$f20,$f0,$f20\n"
            "\tsqrt.s\t$f2,$f12\n"
            "\tc.eq.s\t$f2,$f2\n"
            "\tdiv.s\t$f22,$f22,$f2\n"
            "\tmov.s\t$f2,$f0\n"
            "\tdiv.s\t$f22,$f22,$f2\n"
            "\tdiv.s\t$f20,$f20,$f2\n"
            "\tsub.s\t$f20,$f0,$f20\n"
            "\tneg.s\t$f20,$f20\n"
            "\tmul.s\t$f20,$f20,$f0\n"
            "\ts.s\t$f20,0($19)\n"
            "\tmul.s\t$f0,$f0,$f22\n"
        )
        text = self.preprocess(body)
        self.assertIn("add.s\t$f12,$f2,$f0", text)
        self.assertEqual(text.count("sub.s\t$f20,$f0,$f12"), 2)
        self.assertIn("sqrt.s\t$f4,$f12", text)
        self.assertIn("neg.s\t$f2,$f20\n\tmul.s\t$f2,$f2,$f0", text)
        self.assertIn("mul.s\t$f0,$f22,$f0", text)

        disabled = self.preprocess(body, disabled="ATTACHED-CAMERA-FPRS")
        self.assertIn("add.s\t$f20,$f2,$f0", disabled)
        self.assertIn("sqrt.s\t$f2,$f12", disabled)

    def test_spawn_unit_uses_retail_scheduling(self) -> None:
        body = (
            "func_80097038:\n"
            "\tsw\t$0,1256($17)\n\tsw\t$0,1260($17)\n"
            "\tsw\t$2,1264($17)\n\ts.s\t$f0,1020($17)\n"
            "\tsw\t$2,1140($17)\n\tli\t$2,0x00000001\t\t# 1\n"
            "\tsh\t$2,1164($17)\n\tli\t$2,0x0000003c\t\t# 60\n"
            "\tsh\t$2,1176($17)\n\tli\t$2,0x00000003\t\t# 3\n"
            "\tsh\t$2,1178($17)\n\tli\t$2,0x00000032\t\t# 50\n"
            "\tsh\t$2,1162($17)\n\tsh\t$2,1160($17)\n"
            "\tsh\t$2,1174($17)\n\tli\t$2,0x00000063\t\t# 99\n"
            "\tsh\t$2,1166($17)\n"
            "\tmfc1\t$4,$f0\n\tmfc1\t$4,$f2\n"
            "\tor\t$4,$4,$2\n.L34:\n\tlw\t$3,24($17)\n"
            "\t.set\tnoreorder\n\t.set\tnomacro\n"
            "\tbeql\t$3,$2,.L36\n\tli\t$2,0x00000002\t\t# 2\n"
            "\t.set\tmacro\n\t.set\treorder\n\n\tbeq\t$3,$0,.L37\n"
            "\tbeq\t$3,$2,.L38\n"
            ".L36:\n\tl.s\t$f0,36($17)\n\tl.s\t$f2,44($17)\n"
            "\tsw\t$2,1128($17)\n"
            + "\tandi\t$2,$4,0xffff\n" * 3
            + "\t.set\tnoreorder\n\t.set\tnomacro\n"
            "\tbne\t$2,$0,.L69\n\tli\t$2,0x00000010\t\t# 16\n"
            "\t.set\tmacro\n\t.set\treorder\n"
        )
        text = self.preprocess(body)
        self.assertIn("s.s\t$f0,1020($17)\n\tsw\t$0,1256($17)", text)
        self.assertIn("li\t$3,0x00000032", text)
        self.assertIn("beq\t$4,$2,.L36\n\tmove\t$5,$3", text)
        self.assertIn("li\t$2,0x00000002\t\t# 2\n\tsw\t$2,1128($17)", text)
        self.assertEqual(text.count("andi\t$2,$5,0xffff"), 3)
        self.assertIn("bne\t$2,$0,.L42\n\tnop", text)

        disabled = self.preprocess(body, disabled="SPAWN-UNIT-SCHEDULING")
        self.assertIn("beql\t$3,$2,.L36", disabled)
        self.assertIn("andi\t$2,$4,0xffff", disabled)

    def test_bank_spawn_uses_indexed_retail_switches(self) -> None:
        body = (
            "func_80088670:\n"
            "\tlw\t$17,1284($sp)\n\tli\t$18,-20\t\t\t# 0xffffffec\n"
            ".L104:\n\tlw\t$2,644($17)\n\t#nop\n"
            "\t.set\tnoreorder\n\t.set\tnomacro\n\tblez\t$2,.L103\n"
            "\tmove\t$16,$0\n\t.set\tmacro\n\t.set\treorder\n\n"
            "\taddu\t$23,$20,-5\n\tla\t$10,.L136\n"
            "\taddu\t$22,$18,$10\n\tmove\t$19,$17\n"
            "\taddu\t$4,$fp,$2\n\tlw\t$3,8($4)\n"
            "\tli\t$2,0x00000017\t\t# 23\n"
            "\tbne\t$3,$2,.L109\n\tl.s\t$f0,4($4)\n"
            "\ts.s\t$f0,44($sp)\n\tl.s\t$f0,0($4)\n\t#nop\n"
            "\ts.s\t$f0,40($sp)\n\t.set\tnoreorder\n\t.set\tnomacro\n"
            "\tbeq\t$2,$0,.L112\n\tsw\t$20,8($4)\n"
            "\t.set\tmacro\n\t.set\treorder\n\n"
            "\tsltu\t$2,$23,12\n\t.set\tnoreorder\n\t.set\tnomacro\n"
            "\tbeq\t$2,$0,.L111\n\tmove\t$5,$20\n"
            "\t.set\tmacro\n\t.set\treorder\n\n\tlw\t$2,0($22)\n"
            "\tla\t$10,.L134\n\taddu\t$2,$2,$10\n\tlw\t$2,0($2)\n"
            ".L112:\n\tmove\t$5,$20\n"
            "\tlw\t$2,644($19)\n\taddu\t$16,$16,1\n"
            "\tslt\t$2,$16,$2\n\tbne\t$2,$0,.L109\n.L103:\n"
            "\taddu\t$17,$17,4\n\taddu\t$20,$20,1\n"
            "\tbne\t$2,$0,.L104\n\taddu\t$18,$18,4\n"
        )
        text = self.preprocess(body)
        self.assertIn("lw\t$18,1284($sp)", text)
        self.assertIn("move\t$22,$19", text)
        self.assertIn("bne\t$2,$10,.L109\n\tmove\t$16,$20", text)
        self.assertIn("lw $2,%lo(.L136)($at)", text)
        self.assertIn("lw $2,%lo(.L134)($at)", text)
        self.assertIn(".L112:\n\tmove\t$5,$16", text)

        disabled = self.preprocess(body, disabled="BANK-SPAWN-SWITCHES")
        self.assertIn("lw\t$17,1284($sp)", disabled)
        self.assertIn("la\t$10,.L136", disabled)

    def test_bonus_crate_uses_retail_allocation(self) -> None:
        prologue = (
            "func_800A0CE0:\n"
            "\tsw\t$18,272($sp)\n\tmove\t$18,$4\n"
            "\tsw\t$17,268($sp)\n\tsw\t$16,264($sp)\n"
            ".L2:\n"
        )
        body = (
            "\taddu\t$19,$18,28\n\tsw\t$19,24($sp)\n"
            "\taddu\t$16,$17,$2\n\tlw\t$4,0($16)\n"
            "\tsw\t$19,24($sp)\n\ts.s\t$f22,28($sp)\n"
            "\tsw\t$19,24($sp)\n.L12:\n\ts.s\t$f22,28($sp)\n"
            "\tlw\t$2,0($16)\n\t#nop\n\tsll\t$2,$2,1\n"
            "\taddu\t$2,$17,$2\n"
            "\tli.s\t$f22,8.00000000000000000000e1\n\tmove\t$4,$20\n"
            "\taddu\t$6,$sp,32\n\tli.s\t$f0,8.00000000000000000000e1\n"
            "\tmove\t$6,$19\n\tli.s\t$f0,8.00000000000000000000e1\n"
            + "\tmul.s\t$f22,$f20,$f0\n" * 2
        )
        targets = {"$17": 18, "$18": 25, "$f20": 14, "$f22": 8}
        for token, target in targets.items():
            body += ("\tmove\t$0," + token + "\n") * (target - body.count(token))
        body = prologue + body + ".L1:\n"

        text = self.preprocess(body)
        self.assertIn("sw\t$17,268($sp)\n\tmove\t$17,$4", text)
        self.assertIn("addu\t$16,$17,28\n\tsw\t$16,24($sp)", text)
        self.assertIn("addu\t$19,$18,$2\n\tlw\t$4,0($19)", text)
        self.assertEqual(text.count("lwc1 $f20, %lo(RODATA_SYM_"), 3)
        self.assertEqual(text.count("mul.s\t$f20,$f22,$f20"), 2)

        disabled = self.preprocess(body, disabled="BONUS-CRATE-ALLOCATION")
        self.assertIn("sw\t$18,272($sp)\n\tmove\t$18,$4", disabled)
        self.assertEqual(disabled.count("mul.s\t$f22,$f20,$f0"), 2)

    def test_disabled_rule_leaves_symbol_load_for_gas(self) -> None:
        text = self.preprocess(
            "\tlw\t$2,D_801144A0($3)\n", disabled="MEM-SYM-BASE"
        )
        self.assertIn("lw\t$2,D_801144A0($3)", text)
        self.assertNotIn("%hi(D_801144A0)", text)


if __name__ == "__main__":
    unittest.main()
