import re,glob,sys,os
ASM = 'asm/us/functions'  # set by bundle_entries.py from the repository root
INS=re.compile(r'^\s*/\*\s*([0-9A-F]+)\s+([0-9A-F]+)\s+[0-9A-F]+\s*\*/\s+(\S+)\s*(.*)$')
def num(s):
    s=s.strip()
    m=re.match(r'\((0x[0-9A-F]+) (>>|&) (16|0xFFFF)\)',s)
    if m:
        v=int(m.group(1),16); return v>>16 if m.group(2)=='>>' else v&0xFFFF
    return int(s,0)
def parse(fn):
    out=[]
    for ln in open(os.path.join(ASM,fn+'.s')):
        m=INS.match(ln)
        if m: out.append((int(m.group(2),16),m.group(3),[a.strip() for a in re.split(r',\s*(?![^()]*\))',m.group(4))] if m.group(4) else []))
    return out
CALLS={'func_800F3D40','func_800F41C0','func_80105A50','func_80105C68','func_80105D90','func_80105F24','func_80105584','func_80106010'}
def track(fn,base='D_803275F4'):
    ins=parse(fn); R={'$zero':('C',0)}; S={}; res=[]
    def g(r): return R.get(r)
    def step(op,a):
        d=a[0] if a else None
        try:
          if op=='lw' and '%lo('+base+')' in a[1]: R[d]=('B',); return
          if op=='lui' and not a[1].startswith('%'): R[d]=('C',num(a[1])<<16); return
          if op in('lw','lh','lhu','lb','lbu'):
            m=re.match(r'(-?0x[0-9A-F]+|-?\d+)\((\$\w+)\)',a[1])
            if m:
              if m.group(2)=='$sp' and op=='lw' and int(m.group(1),0) in S: R[d]=S[int(m.group(1),0)]; return
              if g(m.group(2))==('B',) and op=='lw': R[d]=('O',int(m.group(1),0)); return
            R.pop(d,None); return
          if op=='sw':
            m=re.match(r'(-?0x[0-9A-F]+|\d+)\(\$sp\)',a[1])
            if m: S[int(m.group(1),0)]=g(a[0])
            return
          if op in('addu','or') :
            x,y=g(a[1]),g(a[2])
            if y==('C',0) or y is None and a[2]=='$zero': R[d]=x; return
            if x==('C',0): R[d]=y; return
            for p,q in((x,y),(y,x)):
              if p and p[0]=='O' and q==('B',): R[d]=('E',p[1],0); return
              if p and p[0]=='E' and q and q[0]=='C': R[d]=('E',p[1],p[2]+q[1]); return
            if x and y and x[0]=='C' and y[0]=='C': R[d]=('C',x[1]+y[1] if op=='addu' else x[1]|y[1]); return
            R.pop(d,None); return
          if op in('addiu','ori'):
            x=g(a[1]); v=num(a[2])
            if x and x[0]=='C': R[d]=('C',x[1]+v if op=='addiu' else x[1]|v); return
            if x and x[0]=='E' and op=='addiu': R[d]=('E',x[1],x[2]+v); return
            R.pop(d,None); return
          if d and d.startswith('$') and op not in('sb','sh','swc1','sdc1','beq','bne','beqz','bnez','blez','bgtz','bltz','bgez','j','jr','b','mtc1') : R.pop(d,None)
        except Exception as e: R.pop(d,None)
    i=0; mode='S'
    while i<len(ins):
        addr,op,a=ins[i]
        if op=='jal':
            if i+1<len(ins): step(ins[i+1][1],ins[i+1][2])
            if a[0]=='func_800AB95C':
                v=g('$a0'); mode=v[1] if v and v[0]=='C' else 'S'
            regs={k:g(k) for k in('$a0','$a1','$a2','$a3')}; st={k:S.get(k) for k in range(0x10,0x40,4)}
            if a[0] in CALLS or any(v and v[0]=='E' for v in list(regs.values())+list(st.values())):
                res.append((hex(addr),a[0],regs,st,mode))
            for k in list(R):
                if not k.startswith('$s') and k not in('$fp','$sp','$zero'): R.pop(k)
            i+=2; continue
        if op in('sw',) and a[1].startswith('0x') and '$v' in a[1] or op=='sw':
            pass
        if op in('lw','lh','lhu','lb','lbu','sw','sh','sb'):
            m=re.match(r'(-?0x[0-9A-F]+|-?\d+)\((\$\w+)\)',a[1]) if len(a)>1 else None
            if m and g(m.group(2)) and g(m.group(2))[0]=='E':
                v=g(m.group(2)); res.append((hex(addr),'MEM:'+op,{'$a1':('E',v[1],v[2]+int(m.group(1),0))},{},mode))
        step(op,a)
        # FD setimg with entry
        i+=1
    return res
if __name__=='__main__':
    for fn in sys.argv[1:]:
        for r in track(fn): print(fn,r)


def fmt(f):
    out=[]
    for addr,fn,R,S,mode in track(f):
        E=[(k,v) for k,v in list(R.items())+[('sp%x'%k,v) for k,v in S.items()] if v and v[0]=='E']
        C=lambda v: v[1] if v and v[0]=='C' else '?'
        if fn in('func_800F3D40',):
            out.append((addr,mode,'draw3D40',R['$a1'],C(R['$a2']),C(R['$a3']),C(S[16]),C(S[20])))
        elif fn=='func_800F41C0':
            out.append((addr,mode,'draw41C0',R['$a1'],R['$a2'],C(R['$a3']),C(S[16])))
        elif E: out.append((addr,mode,fn,E))
    return out
