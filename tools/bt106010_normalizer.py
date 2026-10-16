"""Fail-closed packet-scheduling normalization for ``draw_text_char``."""

PACKETS_BEFORE = """\
\tor\t$2,$7,$6
\tli\t$3,-201326592\t\t\t# 0xf4000000
\tor\t$2,$2,$3
\taddu\t$3,$8,$19
\tsll\t$3,$3,14
\tsw\t$0,4($9)
\tsw\t$2,0($10)
\tli\t$2,0x07000000\t\t# 117440512
\tor\t$2,$5,$2
\tor\t$2,$3,$2
\tsw\t$2,4($10)
\tli\t$2,-419430400\t\t\t# 0xe7000000
\tsw\t$2,0($11)
\tsw\t$0,4($11)
\tsw\t$4,0($12)
\tlw\t$4,D_803AAD8C
\tli\t$2,-234881024\t\t\t# 0xf2000000
\tor\t$3,$3,$5
\tsw\t$17,4($12)
\tsw\t$3,4($13)
\tlw\t$3,D_803AAD88
\tor\t$6,$6,$2
\tor\t$7,$7,$6
\tsw\t$7,0($13)
\tsll\t$5,$4,2
\tandi\t$5,$5,0x0fff
\tsll\t$2,$3,2
\tandi\t$2,$2,0x0fff
\tsll\t$2,$2,12
\tor\t$2,$2,$5
\tsw\t$2,4($16)
\ttrunc.w.s $f4,$f2,$5
\tmfc1\t$2,$f4
\ttrunc.w.s $f2,$f0,$6
\tmfc1\t$5,$f2
\taddu\t$3,$3,$2
\tsll\t$3,$3,2
\tandi\t$3,$3,0x0fff
\tsll\t$3,$3,12
\t.section .rodata
RODATA_SYM_0:
\t.align 3
\t.double 3.20000000000000000000e1
\t.text
\t.set\tnoat
\tlui $at, %hi(RODATA_SYM_0)
\tldc1 $f2, %lo(RODATA_SYM_0)($at)
\t.set\tat
\taddu\t$4,$4,$5
\tmtc1\t$8,$f0
\tcvt.d.w\t$f0,$f0
\tmul.d\t$f2,$f0,$f2
\tsll\t$4,$4,2
"""

PACKETS_AFTER = """\
\tli\t$2,-201326592\t\t\t# 0xf4000000
\tor\t$2,$6,$2
\tor\t$2,$7,$2
\taddu\t$3,$8,$19
\tsll\t$3,$3,14
\tsw\t$0,4($9)
\tsw\t$2,0($10)
\tli\t$2,0x07000000\t\t# 117440512
\tor\t$2,$5,$2
\tor\t$2,$3,$2
\tsw\t$2,4($10)
\tli\t$2,-419430400\t\t\t# 0xe7000000
\tsw\t$2,0($11)
\tli\t$2,-234881024\t\t\t# 0xf2000000
\tor\t$3,$3,$5
\tsw\t$0,4($11)
\tsw\t$4,0($12)
\tsw\t$17,4($12)
\tsw\t$3,4($13)
\tlw\t$3,D_803AAD88
\tlw\t$4,D_803AAD8C
\tor\t$6,$6,$2
\tor\t$7,$7,$6
\tsw\t$7,0($13)
\tsll\t$2,$3,2
\tsll\t$5,$4,2
\tandi\t$2,$2,0x0fff
\tsll\t$2,$2,12
\tandi\t$5,$5,0x0fff
\tor\t$2,$2,$5
\tsw\t$2,4($16)
\ttrunc.w.s $f4,$f2,$5
\tmfc1\t$2,$f4
\taddu\t$3,$3,$2
\tsll\t$3,$3,2
\ttrunc.w.s $f2,$f0,$6
\tmfc1\t$2,$f2
\taddu\t$4,$4,$2
\tsll\t$4,$4,2
\t.section .rodata
RODATA_SYM_0:
\t.align 3
\t.double 3.20000000000000000000e1
\t.text
\t.set\tnoat
\tlui $at, %hi(RODATA_SYM_0)
\tldc1 $f2, %lo(RODATA_SYM_0)($at)
\t.set\tat
\tandi\t$3,$3,0x0fff
\tmtc1\t$8,$f0
\tcvt.d.w\t$f0,$f0
\tmul.d\t$f2,$f0,$f2
\tsll\t$3,$3,12
"""


def normalize_bt106010(text):
    symbol = "func_80106010:\n"
    end_symbol = "\t.end\tfunc_80106010\n"
    if text.count(symbol) != 1 or text.count(end_symbol) != 1:
        raise RuntimeError("BT106010 function boundary drift")
    start = text.index(symbol)
    end = text.index(end_symbol, start)
    head, body, tail = text[:start], text[start:end], text[end:]
    if body.count(PACKETS_BEFORE) != 1 or body.count(PACKETS_AFTER):
        raise RuntimeError("BT106010 packet window exact-one gate")
    return head + body.replace(PACKETS_BEFORE, PACKETS_AFTER, 1) + tail, 1


__all__ = ("normalize_bt106010",)
