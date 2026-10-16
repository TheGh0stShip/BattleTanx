"""Pure, function-scoped pre-generic rules for update_effect_kind_5."""

OPEN_BEFORE = ("\tblez\t$18,.L4\n\tl.d\t$f22,D_80071EA8\n\tl.d\t$f20,D_80071EB0\n"
               "\tl.s\t$f26,D_80071EB8\n\tl.s\t$f24,D_80071EBC\n"
               "\tli\t$21,0x000000ff\t\t# 255\n.L5:\n")
OPEN_AFTER = ("\tblez\t$18,.L4\n\tli\t$21,0x000000ff\t\t# 255\n"
              "\tl.d\t$f22,D_80071EA8\n\tl.d\t$f20,D_80071EB0\n"
              "\tl.s\t$f26,D_80071EB8\n\tl.s\t$f24,D_80071EBC\n.L5:\n")
ED_BEFORE = ("\taddu\t$2,$2,$3\n\tlw\t$3,16($2)\n\t#nop\n\tsw\t$3,16($sp)\n"
 "\tlw\t$3,20($2)\n\t#nop\n\tsw\t$3,20($sp)\n\tlw\t$3,24($2)\n\t#nop\n\tsw\t$3,24($sp)\n"
 "\tlw\t$3,28($2)\n\t#nop\n\tsw\t$3,28($sp)\n\tlw\t$3,32($2)\n\t#nop\n\tsw\t$3,32($sp)\n"
 "\tlw\t$3,36($2)\n\t#nop\n\tsw\t$3,36($sp)\n\tlw\t$4,0($2)\n")
ED_AFTER = ("\taddu\t$2,$2,$3\n\tlw\t$3,16($2)\n\tlw\t$4,20($2)\n\tlw\t$5,24($2)\n"
 "\tlw\t$6,28($2)\n\tsw\t$3,16($sp)\n\tsw\t$4,20($sp)\n\tsw\t$5,24($sp)\n"
 "\tsw\t$6,28($sp)\n\tlw\t$3,32($2)\n\tlw\t$4,36($2)\n\tsw\t$3,32($sp)\n"
 "\tsw\t$4,36($sp)\n\tlw\t$4,0($2)\n")

def normalize_bt92734_pre(text):
    if text.count("func_80092734:\n") != 1 or text.count("\t.end\tfunc_80092734\n") != 1:
        raise RuntimeError("BT92734 pre boundary count")
    start = text.index("func_80092734:\n")
    end = text.index("\t.end\tfunc_80092734\n", start)
    head, body, tail = text[:start], text[start:end], text[end:]
    for name, before, after in (("opening", OPEN_BEFORE, OPEN_AFTER), ("EDADC", ED_BEFORE, ED_AFTER)):
        if body.count(before) != 1 or body.count(after):
            raise RuntimeError(f"BT92734 {name} exact-one gate")
        body = body.replace(before, after, 1)
    return head + body + tail, 1
