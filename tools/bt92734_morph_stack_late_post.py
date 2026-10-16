"""Pure, fail-closed post rules for func_80092734 assembler-phase text."""
import re

FUNCTION_START = "func_80092734:\n"
FUNCTION_END = "\t.end\tfunc_80092734\n"

MORPH_BEFORE = '''.L11:
\t.set\tnomacro
\tbeq\t$22,$0,.L45
\tmove\t$16,$0
\t.set\tmacro

\tlhu\t$13,126($sp)
\t#nop
\tsll\t$20,$13,16
.L46:
\tlhu\t$2,2($fp)
\tlw\t$6,1400($19)
\tsra\t$4,$20,16
\tlw\t$13,132($sp)
\tlhu\t$5,2($23)
\taddu\t$2,$2,$16
\tsll\t$3,$2,1
\taddu\t$3,$3,$2
\tlhu\t$2,2($13)
\tsll\t$3,$3,2
\taddu\t$7,$6,$3
\taddu\t$5,$5,$16
\tlw\t$7,4($7)
\taddu\t$2,$2,$16
\tsll\t$3,$2,1
\taddu\t$3,$3,$2
\tsll\t$3,$3,2
\taddu\t$3,$6,$3
\tsll\t$2,$5,1
\taddu\t$2,$2,$5
\tsll\t$2,$2,2
\taddu\t$6,$6,$2
\tlw\t$5,4($3)
\taddu\t$16,$16,1
\tlw\t$2,1408($19)
\tlw\t$6,4($6)
\tsll\t$7,$7,3
\tsll\t$5,$5,3
\taddu\t$5,$2,$5
\tsll\t$6,$6,3
\taddu\t$6,$2,$6
\t.set\tnomacro
\tjal\tfunc_80091A60
\taddu\t$7,$2,$7
\t.set\tmacro

\tslt\t$2,$16,$22
\tbne\t$2,$0,.L46
\tnop
'''

MORPH_AFTER = '''.L11:
\t.set\tnomacro
\tbeq\t$22,$0,.L45
\tmove\t$16,$0
\t.set\tmacro

\tlhu\t$13,126($sp)
\t#nop
\tsll\t$20,$13,16
.L46:
\tlhu\t$2,2($fp)
\tsra\t$4,$20,16
\tlw\t$6,1400($19)
\tlhu\t$5,2($23)
\tlw\t$13,132($sp)
\taddu\t$2,$2,$16
\tsll\t$3,$2,1
\taddu\t$3,$3,$2
\tsll\t$3,$3,2
\taddu\t$8,$6,$3
\tlhu\t$3,2($13)
\taddu\t$5,$5,$16
\tsll\t$2,$5,1
\taddu\t$2,$2,$5
\tsll\t$2,$2,2
\taddu\t$7,$6,$2
\taddu\t$3,$3,$16
\tsll\t$2,$3,1
\taddu\t$2,$2,$3
\tsll\t$2,$2,2
\taddu\t$6,$6,$2
\tlw\t$5,4($6)
\taddu\t$16,$16,1
\tlw\t$2,1408($19)
\tlw\t$6,4($7)
\tlw\t$7,4($8)
\tsll\t$5,$5,3
\taddu\t$5,$2,$5
\tsll\t$6,$6,3
\taddu\t$6,$2,$6
\tsll\t$7,$7,3
\t.set\tnomacro
\tjal\tfunc_80091A60
\taddu\t$7,$2,$7
\t.set\tmacro

\tslt\t$2,$16,$22
\tbne\t$2,$0,.L46
\tnop
'''

LOOKUP = re.compile(
    r"\tlw\t\$18,1384\(\$(?P<base>2|19)\)\n"
    r"\tsll\t\$2,\$3,1\n\taddu\t\$2,\$2,\$3\n"
    r"\tsll\t\$2,\$2,2\n\tsubu\t\$2,\$2,\$3\n"
    r"\tsll\t\$2,\$2,3\n\taddu\t\$18,\$18,\$2\n"
)

def _scope(text):
    if text.count(FUNCTION_START) != 1 or text.count(FUNCTION_END) != 1:
        raise RuntimeError("func_80092734 boundary count changed")
    start = text.index(FUNCTION_START)
    end = text.index(FUNCTION_END, start)
    return text[:start], text[start:end], text[end:]

def normalize_bt92734_morph_stack_late(text):
    """Return (rewritten_text, fire_count), scoped solely to func_80092734."""
    head, body, tail = _scope(text)
    if body.count(MORPH_BEFORE) != 1 or body.count(MORPH_AFTER):
        raise RuntimeError("morph exact-one gate failed")
    body = body.replace(MORPH_BEFORE, MORPH_AFTER, 1)

    chains = (
        ("weight", "\tsh\t$2,126($sp)\n", "\tlhu\t$13,126($sp)\n",
         "\tsh\t$2,110($sp)\n", "\tlhu\t$13,110($sp)\n", 126, 110),
        ("target", "\tsw\t$3,132($sp)\n", "\tlw\t$13,132($sp)\n",
         "\tsw\t$3,100($sp)\n", "\tlw\t$13,100($sp)\n", 132, 100),
    )
    for name, producer, consumer, new_producer, new_consumer, old, new in chains:
        if body.count(producer) != 1 or body.count(consumer) != 1:
            raise RuntimeError(f"{name} producer/consumer exact-one gate failed")
        if body.index(producer) >= body.index(consumer):
            raise RuntimeError(f"{name} def-use order changed")
        refs = re.findall(rf"\t(?:l[bhw]u?|s[bhw])\t[^\n]*,{old}\(\$sp\)\n", body)
        if refs != [producer, consumer]:
            raise RuntimeError(f"{name} old-slot references changed")
        if re.search(rf"\t(?:l[bhw]u?|s[bhw])\t[^\n]*,{new}\(\$sp\)\n", body):
            raise RuntimeError(f"{name} destination slot is occupied")
        body = body.replace(producer, new_producer, 1).replace(consumer, new_consumer, 1)

    matches = list(LOOKUP.finditer(body))
    if len(matches) != 3 or [m.group("base") for m in matches] != ["2", "2", "19"]:
        raise RuntimeError("late object-lookup exact-three gate failed")
    def lookup_replacement(match):
        base = match.group("base")
        return (f"\tlw\t$4,1384(${base})\n\tsll\t$2,$3,1\n"
                "\taddu\t$2,$2,$3\n\tsll\t$2,$2,2\n\tsubu\t$2,$2,$3\n"
                "\tsll\t$2,$2,3\n\taddu\t$18,$4,$2\n")
    body, count = LOOKUP.subn(lookup_replacement, body)
    if count != 3:
        raise RuntimeError("late object-lookup rewrite count changed")
    reload_old, reload_new = "\tlw\t$3,92($sp)\n", "\tlw\t$13,92($sp)\n"
    store_old, store_new = "\tsw\t$2,0($3)\n", "\tsw\t$2,0($13)\n"
    if body.count(reload_old) != 3 or body.count(store_old) != 2:
        raise RuntimeError("late state def-use multiplicity changed")
    if body.count(reload_new) or body.count(store_new):
        raise RuntimeError("late state destination registers already present")
    body = body.replace(reload_old, reload_new).replace(store_old, store_new)
    return head + body + tail, 12
