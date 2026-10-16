"""Pure function-scoped list-setup and auxiliary-CFG post rules."""
import re

LIST_BEFORE=("\tsll\t$2,$3,1\n\taddu\t$2,$2,$3\n\tlhu\t$3,2($20)\n\tsll\t$2,$2,2\n\taddu\t$16,$5,$2\n\tlw\t$4,1396($19)\n\taddu\t$3,$3,$6\n\tsll\t$2,$3,1\n\taddu\t$2,$2,$3\n\tsll\t$2,$2,2\n\tlhu\t$3,2($16)\n\taddu\t$5,$5,$2\n\tlhu\t$2,2($5)\n\tsll\t$3,$3,2\n\taddu\t$fp,$4,$3\n\tlhu\t$3,14($5)\n\tsll\t$2,$2,2\n\taddu\t$2,$4,$2\n\tsw\t$2,132($sp)\n\tsll\t$3,$3,2\n\taddu\t$23,$4,$3\n")
LIST_AFTER=("\tsll\t$2,$3,1\n\taddu\t$2,$2,$3\n\tlhu\t$3,2($20)\n\tsll\t$2,$2,2\n\taddu\t$16,$5,$2\n\tlhu\t$4,2($16)\n\taddu\t$3,$3,$6\n\tsll\t$2,$3,1\n\taddu\t$2,$2,$3\n\tsll\t$2,$2,2\n\taddu\t$3,$5,$2\n\taddu\t$2,$2,$5\n\tlw\t$5,1396($19)\n\tsll\t$4,$4,2\n\tlhu\t$3,2($3)\n\tlhu\t$2,14($2)\n\taddu\t$fp,$5,$4\n\tsll\t$3,$3,2\n\taddu\t$3,$5,$3\n\tsll\t$2,$2,2\n\taddu\t$23,$5,$2\n\tsw\t$3,132($sp)\n")
AUX=re.compile(r"\taddu\t\$20,\$18,8\n\t\.set\tnomacro\n\tbeq\t\$2,\$0,(?P<null>\.L\d+)\n\taddu\t\$21,\$18,72\n\t\.set\tmacro\n\n\tsw\t\$16,12\(\$2\)\n\tsw\t\$20,16\(\$2\)\n\tsw\t\$21,20\(\$2\)\n(?P=null):\n\tsw\t\$2,36\(\$17\)\n(?P<join>\.L\d+):\n")

def normalize_bt92734_list_aux(text):
    if text.count("func_80092734:\n")!=1 or text.count("\t.end\tfunc_80092734\n")!=1: raise RuntimeError("boundary count")
    a=text.index("func_80092734:\n"); b=text.index("\t.end\tfunc_80092734\n",a); head,body,tail=text[:a],text[a:b],text[b:]
    if body.count(LIST_BEFORE)!=1 or body.count(LIST_AFTER): raise RuntimeError("list exact-one gate")
    body=body.replace(LIST_BEFORE,LIST_AFTER,1)
    matches=list(AUX.finditer(body))
    if len(matches)!=1: raise RuntimeError(f"aux exact-one gate: {len(matches)}")
    m=matches[0]; null,join=m.group('null'),m.group('join')
    if body.count(null+':')!=1 or body.count(join+':')!=1: raise RuntimeError("aux label definitions")
    new=("\taddu\t$20,$18,8\n\t.set\tnomacro\n\tbne\t$2,$0,.Laux_store\n\taddu\t$21,$18,72\n\t.set\tmacro\n\n"
         "\t.set\tnomacro\n\tj\t.Laux_done\n\tmove\t$2,$0\n\t.set\tmacro\n\n.Laux_store:\n\tsw\t$16,12($2)\n"
         "\tsw\t$20,16($2)\n\tsw\t$21,20($2)\n.Laux_done:\n\tsw\t$2,36($17)\n.Laux_join:\n")
    body=body[:m.start()]+new+body[m.end():]
    body=body.replace(join,'.Laux_join')
    return head+body+tail,1
