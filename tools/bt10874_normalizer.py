"""Fail-closed assembler normalization for ``find_segment_hit``.

KMC GCC emits the retail control flow and arithmetic, but two late allocation
and scheduling choices differ.  Keep the rule scoped to the retail symbol and
require each complete instruction window exactly once so source or compiler
drift fails loudly.
"""

PROLOGUE_BEFORE = """\
\tl.s\t$f0,0($11)
\tl.s\t$f4,0($fp)
\tl.s\t$f2,4($fp)
\tl.s\t$f22,.LC0
\tsub.s\t$f10,$f0,$f4
\tl.s\t$f0,4($11)
\tmove\t$13,$0
\tlw\t$24,176($sp)
\tsub.s\t$f8,$f0,$f2
\tmove\t$18,$7
\tmtc1\t$0,$f0
\tmove\t$14,$6
\tc.lt.s\t$f8,$f0
\tmov.s\t$f28,$f2
\t.set\tnomacro
\tbc1f\t.L2
\tmov.s\t$f26,$f4
\t.set\tmacro
"""

PROLOGUE_AFTER = """\
\tl.s\t$f0,4($11)
\tl.s\t$f4,4($fp)
\tl.s\t$f2,0($fp)
\tl.s\t$f22,.LC0
\tsub.s\t$f8,$f0,$f4
\tl.s\t$f0,0($11)
\tmove\t$13,$0
\tlw\t$24,176($sp)
\tsub.s\t$f10,$f0,$f2
\tmove\t$18,$7
\tmtc1\t$0,$f0
\tmove\t$14,$6
\tc.lt.s\t$f8,$f0
\tmov.s\t$f28,$f4
\t.set\tnomacro
\tbc1f\t.L2
\tmov.s\t$f26,$f2
\t.set\tmacro
"""

LOOP_ENTRY_BEFORE = """\
\tmfc1\t$2,$f0
\t.set\tnomacro
\tbltz\t$12,.L14
\taddu\t$22,$2,$3
\t.set\tmacro

\tmove\t$8,$0
"""

LOOP_ENTRY_AFTER = """\
\tmfc1\t$2,$f0
\taddu\t$22,$2,$3
\t.set\tnomacro
\tbltz\t$12,.L14
\tmove\t$8,$0
\t.set\tmacro

"""


def normalize_bt10874(text):
    """Return normalized text and the number of complete rules applied."""
    symbol = "func_8010874C:\n"
    end_symbol = "\t.end\tfunc_8010874C\n"
    if text.count(symbol) != 1 or text.count(end_symbol) != 1:
        raise RuntimeError("BT10874 function boundary drift")
    start = text.index(symbol)
    end = text.index(end_symbol, start)
    head, body, tail = text[:start], text[start:end], text[end:]
    for name, before, after in (
        ("prologue", PROLOGUE_BEFORE, PROLOGUE_AFTER),
        ("loop-entry", LOOP_ENTRY_BEFORE, LOOP_ENTRY_AFTER),
    ):
        if body.count(before) != 1 or body.count(after):
            raise RuntimeError(f"BT10874 {name} exact-one gate")
        body = body.replace(before, after, 1)
    return head + body + tail, 2


__all__ = ("normalize_bt10874",)
