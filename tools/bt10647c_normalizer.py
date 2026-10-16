"""Fail-closed allocation normalization for ``draw_text_char_fixed``."""

PACKETS_BEFORE = """\
\taddu\t$3,$18,8
\tsrl\t$3,$3,3
\tsll\t$3,$3,9
\tsw\t$2,0($7)
\tli\t$2,-177733632\t\t\t# 0xf5680000
\tor\t$3,$3,$2
\tli\t$2,-436207616\t\t\t# 0xe6000000
\tsw\t$5,4($7)
\tsll\t$7,$25,14
\tsw\t$3,0($9)
\tsw\t$14,4($9)
\tsw\t$2,0($8)
\tli\t$2,-201326592\t\t\t# 0xf4000000
\tor\t$2,$6,$2
\tor\t$2,$7,$2
\taddu\t$5,$17,$20
\tsll\t$5,$5,2
\tandi\t$5,$5,0x0fff
\taddu\t$4,$25,$18
\tsll\t$4,$4,14
\tsw\t$0,4($8)
\tsw\t$2,0($10)
\tli\t$2,0x07000000\t\t# 117440512
\tor\t$2,$5,$2
\tor\t$2,$4,$2
\tsw\t$2,4($10)
\tli\t$2,-419430400\t\t\t# 0xe7000000
\tsw\t$2,0($11)
\tli\t$2,-234881024\t\t\t# 0xf2000000
\tor\t$4,$4,$5
\tsw\t$0,4($11)
\tsw\t$3,0($12)
\tsw\t$15,4($12)
\tsw\t$4,4($13)
\tlw\t$4,D_803AAD8C
\tlw\t$3,D_803AAD88
\tor\t$6,$6,$2
\tor\t$7,$7,$6
\tsw\t$7,0($13)
\tsll\t$5,$4,2
\tsll\t$2,$3,2
\tandi\t$2,$2,0x0fff
\tsll\t$2,$2,12
\tandi\t$5,$5,0x0fff
\tor\t$2,$2,$5
\tsw\t$2,4($16)
\ttrunc.w.s $f4,$f2,$2
\tmfc1\t$5,$f4
\t#nop
\taddu\t$3,$3,$5
\ttrunc.w.s $f2,$f0,$2
\tmfc1\t$5,$f2
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
\tmtc1\t$25,$f0
\tcvt.d.w\t$f0,$f0
\tmul.d\t$f2,$f0,$f2
\tsll\t$4,$4,2
"""

PACKETS_AFTER = """\
\taddu\t$4,$18,8
\tsrl\t$4,$4,3
\tsll\t$4,$4,9
\tsw\t$2,0($7)
\tli\t$2,-177733632\t\t\t# 0xf5680000
\tor\t$4,$4,$2
\tli\t$2,-436207616\t\t\t# 0xe6000000
\tsw\t$5,4($7)
\tsll\t$7,$25,14
\tsw\t$4,0($9)
\tsw\t$14,4($9)
\tsw\t$2,0($8)
\tli\t$2,-201326592\t\t\t# 0xf4000000
\tor\t$2,$6,$2
\tor\t$2,$7,$2
\taddu\t$5,$17,$20
\taddu\t$3,$25,$18
\tsll\t$3,$3,14
\tsll\t$5,$5,2
\tandi\t$5,$5,0x0fff
\tsw\t$0,4($8)
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
\tsw\t$15,4($12)
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
\ttrunc.w.s $f4,$f2,$2
\tmfc1\t$2,$f4
\taddu\t$3,$3,$2
\tsll\t$3,$3,2
\ttrunc.w.s $f2,$f0,$2
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
\tmtc1\t$25,$f0
\tcvt.d.w\t$f0,$f0
\tmul.d\t$f2,$f0,$f2
\tsll\t$3,$3,12
"""


def normalize_bt10647c(text):
    symbol = "func_8010647C:\n"
    end_symbol = "\t.end\tfunc_8010647C\n"
    if text.count(symbol) != 1 or text.count(end_symbol) != 1:
        raise RuntimeError("BT10647C function boundary drift")
    start = text.index(symbol)
    end = text.index(end_symbol, start)
    head, body, tail = text[:start], text[start:end], text[end:]

    first = "\tlbu\t$18,153($2)\n"
    last = "\tsw\t$24,0($21)\n.L1:\n"
    if body.count(first) != 1 or body.count(last) != 1:
        raise RuntimeError("BT10647C allocation-window drift")
    left = body.index(first)
    right = body.index(last, left) + len(last)
    window = body[left:right]
    if "$__bt10647c" in window:
        raise RuntimeError("BT10647C temporary register collision")
    window = window.replace("$17", "$__bt10647c")
    window = window.replace("$18", "$17")
    window = window.replace("$__bt10647c", "$18")
    body = body[:left] + window + body[right:]
    if body.count(PACKETS_BEFORE) != 1 or body.count(PACKETS_AFTER):
        raise RuntimeError("BT10647C packet window exact-one gate")
    body = body.replace(PACKETS_BEFORE, PACKETS_AFTER, 1)
    return head + body + tail, 2


__all__ = ("normalize_bt10647c",)
