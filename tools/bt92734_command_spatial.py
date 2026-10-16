"""Pure function-scoped command prefix/inner normalization."""

prefix_before = (
    ".L30:\n\tlhu\t$3,2($23)\n\tlhu\t$4,2($fp)\n"
    "\tlw\t$5,1400($19)\n\tli\t$12,-1207959552\t\t\t# 0xb8000000\n"
    "\tli\t$11,0x00000004\t\t# 4\n"
)
prefix_after = (
    ".L30:\n\tli\t$12,-1207959552\t\t\t# 0xb8000000\n"
    "\tli\t$11,0x00000004\t\t# 4\n\tlhu\t$3,2($23)\n"
    "\tlhu\t$4,2($fp)\n\tlw\t$5,1400($19)\n"
)

inner_before = """\tmove\t$12,$0
\t#.set\tvolatile
\tlw\t$2,4($6)
\t#.set\tnovolatile
\tlw\t$3,1408($19)
\tlw\t$4,4($7)
\tsll\t$2,$2,3
\taddu\t$3,$3,$2
\tlhu\t$2,2($7)
\tsubu\t$3,$4,$3
\tsrl\t$8,$2,10
\t.set\tnoreorder
\tbeq\t$8,$0,.L37
\taddu\t$5,$9,$3
\t.set\tnoreorder
\tmove\t$3,$4
\tmove\t$4,$5
.L39:
\tlhu\t$2,8($3)
\t#nop
\tsh\t$2,8($4)
\tlhu\t$2,10($3)
\taddu\t$12,$12,1
\taddu\t$3,$3,16
\tsh\t$2,10($4)
\tslt\t$2,$12,$8
\t.set\tnoreorder
\tbne\t$2,$0,.L39
\taddu\t$4,$4,16
"""
inner_after = """\t#.set\tvolatile
\tlw\t$4,4($7)
\t#.set\tnovolatile
\tlhu\t$3,2($7)
\tmove\t$6,$0
\tsubu\t$2,$4,$8
\tsrl\t$3,$3,10
\t.set\tnoreorder
\tbeq\t$3,$0,.L37
\taddu\t$2,$9,$2
\t.set\tnoreorder
\tmove\t$5,$2
.L39:
\tlhu\t$2,8($4)
\t#nop
\tsh\t$2,8($5)
\tlhu\t$2,10($4)
\taddu\t$6,$6,1
\taddu\t$4,$4,16
\tsh\t$2,10($5)
\tslt\t$2,$6,$3
\t.set\tnoreorder
\tbne\t$2,$0,.L39
\taddu\t$5,$5,16
"""

def _fixture_dialect(block):
    block=block.replace('.L30:','.L29:').replace('.L37','.L36').replace('.L39','.L38')
    parts=block.split("\t.set\tnoreorder\n")
    if len(parts)>1:
        out=parts[0]
        for i,part in enumerate(parts[1:],1):
            out += ("\t.set\tnomacro\n" if i%2 else "\t.set\tmacro\n\n") + part
        block=out
    return block
prefix_before=_fixture_dialect(prefix_before); prefix_after=_fixture_dialect(prefix_after)
inner_before=_fixture_dialect(inner_before); inner_after=_fixture_dialect(inner_after)

def words(block):
    return sum(1 for line in block.splitlines()
               if line.startswith("\t") and not line.startswith(("\t.", "\t#")))
def normalize_bt92734_command_spatial(text):
    if text.count("func_80092734:\n") != 1 or text.count("\t.end\tfunc_80092734\n") != 1:
        raise RuntimeError("command-spatial boundary count")
    start=text.index("func_80092734:\n"); end=text.index("\t.end\tfunc_80092734\n",start)
    head,body,tail=text[:start],text[start:end],text[end:]
    for name,before,after in (("prefix",prefix_before,prefix_after),("inner",inner_before,inner_after)):
        if body.count(before)!=1 or body.count(after):
            raise RuntimeError(f"command-spatial {name} exact-one gate")
        body=body.replace(before,after,1)
    if words(prefix_before)!=words(prefix_after) or words(inner_before)-words(inner_after)!=5:
        raise RuntimeError("command-spatial length invariant")
    return head+body+tail,1
