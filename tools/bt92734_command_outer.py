"""Pure function-scoped command outer-register normalization."""
old='''\taddu\t$6,$5,$2
\taddu\t$4,$4,$16
\tsll\t$2,$4,1
\taddu\t$2,$2,$4
 #APP
 #NO_APP
\t#.set\tvolatile
\tlw\t$3,0($6)
\t#.set\tnovolatile
\tsll\t$2,$2,2
\taddu\t$7,$5,$2
\t#.set\tvolatile
\tsw\t$3,0($7)
\t#.set\tnovolatile
\t#.set\tvolatile
\tlhu\t$2,8($6)
\t#.set\tnovolatile
\t#nop
\t#.set\tvolatile
\tsh\t$2,8($7)
\t#.set\tnovolatile
\t#.set\tvolatile
\tlw\t$8,4($6)
\t#.set\tnovolatile
\tlw\t$3,1408($19)
\t#.set\tvolatile
\tlw\t$9,4($7)
\t#.set\tnovolatile
\tsll\t$8,$8,3
\taddu\t$8,$3,$8
\tlw\t$2,0($8)
\tsll\t$9,$9,3
\t.set\tnoreorder
\tbeq\t$2,$12,.L33
\taddu\t$9,$3,$9
'''
new='''\taddu\t$7,$5,$2
\taddu\t$4,$4,$16
\tsll\t$2,$4,1
\taddu\t$2,$2,$4
 #APP
 #NO_APP
\t#.set\tvolatile
\tlw\t$3,0($7)
\t#.set\tnovolatile
\tsll\t$2,$2,2
\taddu\t$8,$5,$2
\t#.set\tvolatile
\tsw\t$3,0($8)
\t#.set\tnovolatile
\t#.set\tvolatile
\tlhu\t$2,8($7)
\t#.set\tnovolatile
\t#nop
\t#.set\tvolatile
\tsh\t$2,8($8)
\t#.set\tnovolatile
\t#.set\tvolatile
\tlw\t$2,4($7)
\t#.set\tnovolatile
\tlw\t$4,1408($19)
\t#.set\tvolatile
\tlw\t$3,4($8)
\t#.set\tnovolatile
\tsll\t$2,$2,3
\taddu\t$8,$2,$4
\tlw\t$2,0($8)
\tsll\t$3,$3,3
\t.set\tnoreorder
\tbeq\t$2,$12,.L33
\taddu\t$9,$3,$4
'''
# Actual post-generic dialect for the integrated semantic source.
old=old.replace("\t.set\tnoreorder\n\tbeq\t$2,$12,.L33\n\taddu\t$9,$3,$9\n",
                "\t.set\tnomacro\n\tbeq\t$2,$12,.L32\n\taddu\t$9,$3,$9\n\t.set\tmacro\n\n")
new=new.replace("\t.set\tnoreorder\n\tbeq\t$2,$12,.L33\n\taddu\t$9,$3,$4\n",
                "\t.set\tnomacro\n\tbeq\t$2,$12,.L32\n\taddu\t$9,$3,$4\n\t.set\tmacro\n\n")

def normalize_bt92734_command_outer(text):
    if text.count('func_80092734:\n')!=1 or text.count('\t.end\tfunc_80092734\n')!=1:
        raise RuntimeError('outer boundary count')
    a=text.index('func_80092734:\n'); b=text.index('\t.end\tfunc_80092734\n',a)
    head,body,tail=text[:a],text[a:b],text[b:]
    if body.count(old)!=1 or body.count(new): raise RuntimeError('outer exact-one gate')
    if len(old.splitlines())!=len(new.splitlines()): raise RuntimeError('outer length invariant')
    return head+body.replace(old,new,1)+tail,1
