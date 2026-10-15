#!/usr/bin/env python3
"""Initialized program image ledger for BattleTanx (USA Rev 0), ROM 0x1000..0xD7040."""
import hashlib, re, sys, struct, tomllib, glob, os
from collections import defaultdict
ROOT = sys.argv[1]; OUT = sys.argv[2]
ROM_SHA1 = "535860d941738ac1210c20a9b80114fea0e0ff17"
rom = open(f"{ROOT}/baseroms/us/baserom.z64", "rb").read()
assert hashlib.sha1(rom).hexdigest() == ROM_SHA1, "base ROM SHA-1 mismatch"
D = 0x80070000; IMG = (0x1000, 0xD7040); LIBULTRA_ROM = 0x80110480 - D
SECTIONS = [(0x1000, 0x1040, ".text(entry)"), (0x1040, 0x6000, ".rodata"),
            (0x6000, 0xB5550, ".text"), (0xB5550, 0xD7040, ".data")]
RESERVED = [(0x1000, 0x1040)] + [(a - D, b - D) for a, b in [
    (0x80077098, 0x800771BC), (0x8007D430, 0x8007E138), (0x801106A0, 0x801109B0),
    (0x80111E14, 0x80111F90), (0x80112570, 0x801125F0), (0x80114858, 0x8011490C),
    (0x80116B60, 0x80116C6C), (0x80124350, 0x80125550)]]
def sect(a):
    for s, e, n in SECTIONS:
        if s <= a < e: return n
def w32(a): return struct.unpack(">I", rom[a:a+4])[0]
# functions
cat = tomllib.loads(open(f"{ROOT}/config/us/recomp_function_boundaries.toml").read())
sys.path.insert(0, f"{ROOT}/tools")
from generate_splat_config import canonical_functions
funcs = sorted((f["vram"] - D, f["vram"] - D + f["size"], f["name"]) for f in canonical_functions(cat["section"][0]))
def func_at(a):
    for s, e, n in funcs:
        if s <= a < e: return (s, e, n)
# unit sources
src_of = {}
for m in ("matching_units", "matching_kmc_units", "matching_asm_units"):
    for line in open(f"{ROOT}/config/us/{m}.tsv"):
        if line.startswith("#") or not line.strip(): continue
        p = line.rstrip("\n").split("\t"); s = int(p[0], 0); n = int(p[1], 0)
        for fs, fe, fn in funcs:
            if s <= fs < s + n: src_of[fs] = p[2]
rows = []
for line in open(f"{ROOT}/config/us/matching_data_units.tsv"):
    if line.startswith("#") or not line.strip(): continue
    p = line.rstrip("\n").split("\t"); rows.append((int(p[0], 0), int(p[0], 0) + int(p[1], 0), p[2], p[3]))
rows.sort()
def owner_kind(fs, src):
    if src and ("libultra/" in src or "libgcc/" in src or "boot/" in src): return "lib"
    if fs >= LIBULTRA_ROM or fs < 0x1040: return "lib"
    return "game"
# reference scan over ROM code (lui/addiu/load/store pairing per function)
LOADS = {0x20: ("lb", 1), 0x24: ("lbu", 1), 0x21: ("lh", 2), 0x25: ("lhu", 2), 0x23: ("lw", 4),
         0x31: ("lwc1", 4), 0x35: ("ldc1", 8), 0x37: ("ld", 8), 0x22: ("lwl", 4), 0x26: ("lwr", 4),
         0x28: ("sb", 1), 0x29: ("sh", 2), 0x2B: ("sw", 4), 0x39: ("swc1", 4), 0x3D: ("sdc1", 8), 0x3F: ("sd", 8),
         0x09: ("addiu", 0), 0x0D: ("ori", 0)}
refs = defaultdict(list)  # rom addr -> [(func_start, op, width)]
for fs, fe, fn in funcs:
    hi = {}
    for pc in range(fs, fe, 4):
        ins = w32(pc); op = ins >> 26; rs = (ins >> 21) & 31; rt = (ins >> 16) & 31; imm = ins & 0xFFFF
        if op == 0x0F: hi[rt] = imm << 16; continue
        if op in LOADS and rs in hi:
            off = imm if op == 0x0D else (imm - 0x10000 if imm & 0x8000 else imm)
            addr = (hi[rs] + off) & 0xFFFFFFFF
            a = addr - D
            if IMG[0] <= a < IMG[1]:
                refs[a].append((fs, LOADS[op][0], LOADS[op][1]))
            if op in (0x09, 0x0D) and rt != rs: hi.pop(rt, None)
            if op in (0x09, 0x0D) and rt == rs: hi.pop(rt, None)
        elif op == 0 and (ins & 0x3F) in (0x21, 0x25, 0x20, 0x23, 0x2B) and ((ins >> 11) & 31) in hi:
            pass
# pointer words inside data regions (jump tables, pointer tables)
code_set = funcs
def is_code(a):
    f = func_at(a); return f is not None
ptrrefs = defaultdict(list)  # target -> [source addr]
for s, e, n in SECTIONS[1:]:
    if n == ".text": continue
    for a in range(s, e, 4):
        v = w32(a) - D
        if IMG[0] <= v < IMG[1] and not is_code(a): ptrrefs[v].append(a)
# owned intervals
owned = [(s, e, "code", n) for s, e, n in funcs] + [(s, e, "row", (src, sec)) for s, e, src, sec in rows]
owned.sort()
for x, y in zip(owned, owned[1:]):
    assert x[1] <= y[0], ("overlap", hex(x[0]), hex(y[0]))
# gaps
gaps = []; cur = IMG[0]
for s, e, k, v in owned:
    if s > cur: gaps.append((cur, s))
    cur = max(cur, e)
if cur < IMG[1]: gaps.append((cur, IMG[1]))
def in_reserved(a, b): return any(a < re_ and b > rs_ for rs_, re_ in RESERVED)
def ascii_run(a, b):
    bs = rom[a:b].rstrip(b"\0")
    return len(bs) >= 2 and all(32 <= c < 127 or c in (9, 10) for c in bs)
ledger = []  # (start,end,section,class,detail)
for s, e, k, v in owned:
    if k == "row":
        cls = "matched"
        ledger.append((s, e, sect(s), "matched", f"{v[0]} {v[1]}"))
starts_owned = sorted(set([s for s, e, k, v in owned]))
unmatched_pieces = []
# Non-function bytes inside .text that decode as instructions (catalogue gaps), by inspection:
# jr ra / prologue / register flow into the following function.
TEXT_CODE = {0x720C, 0x96B4, 0x9B80, 0xC33C, 0x1633C, 0x1B030, 0x2176C, 0x24704, 0x26D04, 0x3B200,
             0x3B634, 0x6D798, 0x6D860, 0x6DC5C, 0x6F55C, 0x71118, 0x71710, 0x751B8, 0x82120,
             0x9E158, 0xA1684, 0xA31A0, 0xA3244, 0xA3338}
def jrra(a, b): return any(w32(x) == 0x03E00008 for x in range(a, b, 4))
for gs, ge in gaps:
    sec0 = sect(gs)
    if sec0 in (".text", ".text(entry)") and ge <= 0xB5550:
        body = rom[gs:ge]; al = 16 if ge % 16 == 0 else (8 if ge % 8 == 0 else 4)
        if in_reserved(gs, ge):
            ledger.append((gs, ge, sec0, "reserved (other work)", "non-function bytes in .text"))
        elif not body.strip(b"\0") and ge - gs < al:
            ledger.append((gs, ge, sec0, "padding", f"zero fill 0x00 x{ge-gs}; next function 0x{ge+D:08X} is {al}-byte aligned"))
        elif gs in TEXT_CODE:
            cls = "reserved (other work)" if gs >= LIBULTRA_ROM else "unmatched"
            ledger.append((gs, ge, sec0, cls, f"uncatalogued instructions (jr ra x{sum(w32(x)==0x03E00008 for x in range(gs,ge,4))}); function boundary missing from catalogue"))
        elif ge - gs < al and not jrra(gs, ge):
            ledger.append((gs, ge, sec0, "padding", f"non-zero linker fill ({body.hex()}); next function 0x{ge+D:08X} is {al}-byte aligned"))
        else:
            ledger.append((gs, ge, sec0, "unmatched", "non-function bytes in .text"))
        continue
    pts = sorted(set([gs] + [a for a in list(refs) + list(ptrrefs) if gs < a < ge]))
    pts.append(ge)
    for a, b in zip(pts, pts[1:]):
        body = rom[a:b]
        nz = a + len(body.rstrip(b"\0"))
        if a in refs and a not in ptrrefs and all(w > 0 for _, _, w in refs[a]):
            nz = max(nz, a + max(w for _, _, w in refs[a]))
        pstart = (nz + 3) & ~3
        al = 16 if b % 16 == 0 else (8 if b % 8 == 0 else 4)
        pad = None; note = ""
        if pstart < b and b - pstart < al:
            if b == ge:
                pad = (pstart, b)
            else:
                note = f"ends with {b-pstart} zero bytes before {al}-aligned reference 0x{b+D:08X} (candidate intra-pool alignment pad)"
        end = pad[0] if pad else b
        if end > a:
            ledger.append((a, end, sect(a), "reserved (other work)" if in_reserved(a, end) else "unmatched", note))
        if pad:
            nxt = "image end" if b == IMG[1] else f"next owned item 0x{b+D:08X}"
            ledger.append((pad[0], pad[1], sect(pad[0]), "padding", f"zero fill 0x00 x{pad[1]-pad[0]}; {nxt} is {al}-byte aligned"))
ledger.sort()
# merge sections splits: ensure ledger complete over the non-code image
lc = []; cur = IMG[0]
fi = 0
codeiv = [(s, e) for s, e, n in funcs]
allv = sorted([(s, e, "code") for s, e in codeiv] + [(s, e, "l") for s, e, *_ in ledger])
for s, e, _ in allv:
    assert s == cur, hex(s) + " " + hex(cur); cur = e
assert cur == IMG[1]
# split ledger at section boundaries
out = []
for s, e, sec, cls, det in ledger:
    for ss, se, sn in SECTIONS:
        a, b = max(s, ss), min(e, se)
        if a < b: out.append((a, b, sn, cls, det))
ledger = out
# lib-owned unmatched -> reserved
def consumers(a, b):
    c = set()
    for x in range(a, b):
        for fs, op, w in refs.get(x, []): c.add((fs, op, x))
    return c
def ptr_sources(a, b):
    return sorted(set(s for x in range(a, b) for s in ptrrefs.get(x, [])))
final = []
for s, e, sec, cls, det in ledger:
    if cls == "unmatched":
        cs = consumers(s, e)
        fns = set(fs for fs, _, _ in cs)
        if fns and all(owner_kind(f, src_of.get(f)) == "lib" for f in fns): cls = "reserved (other work)"; det = "library-owned consumer"
        if not fns and s >= LIBULTRA_ROM and sec == ".text": cls = "reserved (other work)"; det = "library text area"
    final.append((s, e, sec, cls, det))
ledger = final
def fname(fs):
    f = func_at(fs); return f[2] if f else hex(fs + D)
def piece_of(p):
    for s, e, *_ in ledger:
        if s <= p < e: return (s, e)
    return (p, p + 4)
def describe(s, e):
    cs = sorted(consumers(s, e)); ps = ptr_sources(s, e)
    ops = defaultdict(set)
    for fs, op, x in cs: ops[fs].add(op)
    # type evidence
    body = rom[s:e]; ev = []
    allops = set(op for fs, op, x in cs)
    if ps:
        tgt_code = all(is_code(w32(p) - D) for p in ps) if False else None
    words = [w32(x) for x in range(s, e - 3, 4)]
    codeptrs = [w for w in words if is_code(w - D) and IMG[0] <= w - D < IMG[1]]
    if words and len(codeptrs) == len(words):
        tf = set(func_at(w - D)[2] for w in codeptrs)
        ev.append(f"jump/pointer table: {len(words)} code pointers into {','.join(sorted(tf))}")
    elif ascii_run(s, e) and len(body.rstrip(b"\0")) >= 4 and not ({"lwc1", "ldc1"} & allops): ev.append("ASCII string(s): " + repr(body.rstrip(b'\0')[:48].decode('latin1')))
    if "ldc1" in allops: ev.append("ldc1 => f64 constant(s)")
    if "lwc1" in allops: ev.append("lwc1 => f32 constant(s)")
    if allops & {"sw", "sh", "sb", "swc1", "sdc1", "sd"}: ev.append("stored to => writable .data/.bss-like object")
    if "addiu" in allops: ev.append("address taken (array/struct/string)")
    if ps:
        ev.append("pointed to by data words at " + ",".join(f"0x{p:X}" for p in ps[:4]))
        for p in ps[:4]:
            r = next((r for r in rows if r[0] <= p < r[1]), None)
            if r: ev.append(f"pointer source inside matched {r[2]} {r[3]}")
            else:
                pc = sorted(set(fname(fs) for fs, _, _ in consumers(*piece_of(p))))
                if pc: ev.append(f"pointer source 0x{p:X} used by {','.join(pc)}")
    owners = sorted(ops)
    own = []
    for fs in owners:
        own.append(f"{fname(fs)}@{fs+D:08X}[{'/'.join(sorted(ops[fs]))}]{'(src:'+src_of[fs]+')' if fs in src_of else ''}")
    return own, ev
with open(f"{OUT}/initialized_data_ledger.tsv", "w") as f:
    f.write("rom_start\trom_end\tvram_start\tvram_end\tsize\tsection\tclass\tdetail\n")
    for s, e, sec, cls, det in ledger:
        f.write(f"0x{s:X}\t0x{e:X}\t0x{s+D:08X}\t0x{e+D:08X}\t0x{e-s:X}\t{sec}\t{cls}\t{det}\n")
tot = defaultdict(int); pending = []
with open(f"{OUT}/unmatched.tsv", "w") as f:
    f.write("rom_start\trom_end\tvram_start\tsize\tsection\tconsumers\ttype_evidence\tproposed_owner\tcandidate_row\n")
    for s, e, sec, cls, det in ledger:
        tot[(sec, cls)] += e - s
        if cls != "unmatched": continue
        own, ev = describe(s, e)
        fns = [o for o in own]
        if len(own) == 1:
            o = own[0]; srcm = re.search(r"\(src:([^)]*)\)", o)
            prop = (f"rodata pool of {o.split('@')[0]}" if sec == ".rodata" else f"data object used by {o.split('@')[0]}") + (f" -> add row to {srcm.group(1)}" if srcm else " (function not yet matched)")
        elif len(own) > 1:
            prop = "shared object (multiple consumers): place in a data TU with the consumers' module"
        elif ev and ev[0].startswith("jump"):
            prop = "jump table of target function (rodata pool)"
        else:
            prop = "unknown: no direct %hi/%lo or pointer reference found (likely interior of previous object or indexed access)"
        pending.append([s, e, sec, own, ev, prop])
    # group contiguous pieces with an identical single consumer into candidate rows
    groups = []
    for it in pending:
        key = it[3][0].split("[")[0] + (re.search(r"\(src:[^)]*\)", it[3][0]) or [""])[0] if len(it[3]) == 1 else None
        if groups and key and groups[-1][0] == key and groups[-1][2] == it[0] and groups[-1][3] == it[2]:
            groups[-1][2] = it[1]
        else:
            groups.append([key, it[0], it[1], it[2]])
        it.append(groups[-1])
    for s, e, sec, own, ev, prop, g in pending:
        cand = f"0x{g[1]:X}+0x{g[2]-g[1]:X}" if g[0] else "-"
        f.write(f"0x{s:X}\t0x{e:X}\t0x{s+D:08X}\t0x{e-s:X}\t{sec}\t{'; '.join(own) or '-'}\t{'; '.join(ev) or '-'}\t{prop}\t{cand}\n")
    with open(f"{OUT}/candidate_rows.tsv", "w") as g2:
        g2.write("rom_start\tsize\tsection\tconsumer\n")
        for key, a, b, sec in groups:
            if key: g2.write(f"0x{a:X}\t0x{b-a:X}\t{sec}\t{key}\n")
for k in sorted(tot): print(k, hex(tot[k]), tot[k])
print("data total (image - functions):", IMG[1] - IMG[0] - sum(e - s for s, e, n in funcs))
