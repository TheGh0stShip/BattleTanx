"""Pure function-scoped descriptor-base and duplicate-z post rules."""

DESC_BEFORE = ("\tlw\t$3,24($17)\n\t#nop\n\tsll\t$2,$3,2\n"
               "\taddu\t$2,$2,$3\n\tsll\t$2,$2,3\n\tla\t$3,D_803B8248\n"
               "\taddu\t$2,$2,$3\n\tlw\t$3,16($2)\n")
DESC_AFTER = ("\tlw\t$3,24($17)\n\tla\t$4,D_803B8248\n\t#nop\n"
              "\tsll\t$2,$3,2\n\taddu\t$2,$2,$3\n\tsll\t$2,$2,3\n"
              "\taddu\t$2,$2,$4\n\tlw\t$3,16($2)\n")
CONFIG_BEFORE = ("\tli\t$2,0x00000001\t\t# 1\n\tsw\t$2,40($sp)\n"
                 "\tl.s\t$f0,76($18)\n")
CONFIG_AFTER = ("\tli\t$2,0x00000001\t\t# 1\n\tsw\t$2,40($sp)\n"
                "\tl.s\t$f0,72($18)\n\ts.s\t$f0,52($sp)\n"
                "\tl.s\t$f0,76($18)\n")


def normalize_bt92734_descriptor_config(text):
    start_marker = "func_80092734:\n"
    end_marker = "\t.end\tfunc_80092734\n"
    if text.count(start_marker) != 1 or text.count(end_marker) != 1:
        raise RuntimeError("BT92734 descriptor/config boundary count")
    start = text.index(start_marker)
    end = text.index(end_marker, start)
    head, body, tail = text[:start], text[start:end], text[end:]
    for name, before, after in (
        ("descriptor-base", DESC_BEFORE, DESC_AFTER),
        ("duplicate-z", CONFIG_BEFORE, CONFIG_AFTER),
    ):
        if body.count(before) != 1 or body.count(after):
            raise RuntimeError(f"BT92734 {name} exact-one gate")
        body = body.replace(before, after, 1)
    return head + body + tail, 1
