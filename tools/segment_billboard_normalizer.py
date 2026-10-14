import re


# --------------------------------------------------------------------------
# func_8009FFB8 (segment_billboard_matrix): lane-proven regional allocation /
# scheduling rules.  Generated from claude-work/output/close-9ffb8 (rules9.py,
# rules9_blocks.py); every block rule was verified there by value-level
# simulation (slots9.verify_slots / websafe) against whole-function liveness.
# ROT  : saved-register roles s4->s5, s5->s6, s6->s4 (frame save/restore lines
#        stay tied to their physical registers).
# P1   : entry copies scheduled into the prologue (retail order).
# H1   : the c.eq.s -> bc1t slot vacated by P1 receives the MIPS III hazard nop.
# P2,R3,R3b,R4 : per-value FP register renaming (plus two independent store
#        swaps) in the length, relative, plane/side and clipping blocks.
_SBM_ROT = {"$20": "$21", "$21": "$22", "$22": "$20"}
_SBM_FRAME = re.compile(r"^\t(sw|lw)\t\$(20|21|22),(352|356|360)\(\$sp\)$")
_SBM_REG = r"\$(?:f\d+|\d+|fp|sp|ra|at)\b"
_SBM_BLOCKS = [('P1',
  '\tsubu\t$sp,$sp,424\n'
  '\tsw\t$16,336($sp)\n'
  '\tmove\t$16,$5\n'
  '\tsw\t$18,344($sp)\n'
  '\tmove\t$18,$6\n'
  '\tsw\t$31,372($sp)\n'
  '\tsw\t$fp,368($sp)\n'
  '\tsw\t$23,364($sp)\n'
  '\tsw\t$22,360($sp)\n'
  '\tsw\t$21,356($sp)\n'
  '\tsw\t$20,352($sp)\n'
  '\tsw\t$19,348($sp)\n'
  '\tsw\t$17,340($sp)\n'
  '\ts.d\t$f30,416($sp)\n'
  '\ts.d\t$f28,408($sp)\n'
  '\ts.d\t$f26,400($sp)\n'
  '\ts.d\t$f24,392($sp)\n'
  '\ts.d\t$f22,384($sp)\n'
  '\ts.d\t$f20,376($sp)\n'
  '\tl.s\t$f4,0($16)\n'
  '\tl.s\t$f0,0($18)\n'
  '\tlw\t$22,440($sp)\n'
  '\tsub.s\t$f4,$f4,$f0\n'
  '\tlw\t$fp,448($sp)\n'
  '\ts.s\t$f4,168($sp)\n'
  '\tl.s\t$f0,8($16)\n'
  '\tl.s\t$f2,8($18)\n'
  '\tmul.s\t$f4,$f4,$f4\n'
  '\tsub.s\t$f0,$f0,$f2\n'
  '\ts.s\t$f0,176($sp)\n'
  '\tl.s\t$f2,4($16)\n'
  '\tl.s\t$f6,4($18)\n'
  '\tmul.s\t$f0,$f0,$f0\n'
  '\tsub.s\t$f2,$f2,$f6\n'
  '\tmul.s\t$f6,$f2,$f2\n'
  '\tadd.s\t$f4,$f4,$f0\n'
  '\tadd.s\t$f12,$f4,$f6\n'
  '\tsqrt.s\t$f8,$f12\n'
  '\tmove\t$17,$4\n'
  '\tmove\t$19,$0\n'
  '\tmove\t$20,$0\n'
  '\tmove\t$23,$7\n'
  '\tc.eq.s\t$f8,$f8\n'
  '\tmove\t$21,$22\n',
  [(0, {}),
   (8, {}),
   (21, {}),
   (6, {}),
   (23, {}),
   (12, {}),
   (38, {}),
   (1, {}),
   (2, {}),
   (3, {}),
   (4, {}),
   (11, {}),
   (39, {}),
   (7, {}),
   (41, {}),
   (5, {}),
   (9, {}),
   (10, {}),
   (13, {}),
   (14, {}),
   (15, {}),
   (16, {}),
   (17, {}),
   (18, {}),
   (43, {}),
   (40, {}),
   (19, {}),
   (20, {}),
   (22, {}),
   (24, {}),
   (25, {}),
   (26, {}),
   (27, {}),
   (28, {}),
   (29, {}),
   (30, {}),
   (31, {}),
   (32, {}),
   (33, {}),
   (34, {}),
   (35, {}),
   (36, {}),
   (37, {}),
   (42, {})]),
 ('P2',
  '\tl.s\t$f0,8($16)\n'
  '\tl.s\t$f2,8($18)\n'
  '\tmul.s\t$f4,$f4,$f4\n'
  '\tsub.s\t$f0,$f0,$f2\n'
  '\ts.s\t$f0,176($sp)\n'
  '\tl.s\t$f2,4($16)\n'
  '\tl.s\t$f6,4($18)\n'
  '\tmul.s\t$f0,$f0,$f0\n'
  '\tsub.s\t$f2,$f2,$f6\n'
  '\tmul.s\t$f6,$f2,$f2\n'
  '\tadd.s\t$f4,$f4,$f0\n'
  '\tadd.s\t$f12,$f4,$f6\n'
  '\tsqrt.s\t$f8,$f12\n'
  '\tc.eq.s\t$f8,$f8\n'
  '\tnop\n'
  '\t.set\tnoreorder\n'
  '\tbc1t\t.L4\n'
  '\ts.s\t$f2,172($sp)\n',
  [(0, {'$f0': '$f2', '$f2': '$f0'}),
   (1, {'$f0': '$f2', '$f2': '$f0'}),
   (2, {'$f0': '$f2', '$f2': '$f0'}),
   (3, {'$f0': '$f2', '$f2': '$f0'}),
   (4, {'$f0': '$f2', '$f2': '$f0'}),
   (5, {'$f0': '$f2', '$f2': '$f0'}),
   (6, {'$f0': '$f2', '$f2': '$f0'}),
   (7, {'$f0': '$f2', '$f2': '$f0'}),
   (8, {'$f0': '$f2', '$f2': '$f0'}),
   (9, {'$f0': '$f2', '$f2': '$f0'}),
   (10, {'$f0': '$f2', '$f2': '$f0'}),
   (11, {'$f0': '$f2', '$f2': '$f0'}),
   (12, {'$f0': '$f2', '$f2': '$f0'}),
   (13, {'$f0': '$f2', '$f2': '$f0'}),
   (14, {'$f0': '$f2', '$f2': '$f0'}),
   (15, {'$f0': '$f2', '$f2': '$f0'}),
   (16, {'$f0': '$f2', '$f2': '$f0'})]),
 ('R3',
  '\tl.s\t$f2,156($sp)\n'
  '\ts.s\t$f0,224($sp)\n'
  '\tl.s\t$f0,4($17)\n'
  '\t#nop\n'
  '\tsub.s\t$f0,$f0,$f2\n'
  '\taddu\t$4,$sp,216\n'
  '\t.set\tnoreorder\n'
  '\tjal\tfunc_8009EC0C\n'
  '\ts.s\t$f0,220($sp)',
  [(1, {}), (2, {}), (0, {}), (3, {}), (4, {}), (5, {}), (6, {})]),
 ('R3b',
  '\tl.s\t$f0,4($17)\n'
  '\tl.s\t$f2,156($sp)\n'
  '\t#nop\n'
  '\tsub.s\t$f0,$f0,$f2\n'
  '\taddu\t$4,$sp,216\n'
  '\t.set\tnoreorder\n'
  '\tjal\tfunc_8009EC0C\n'
  '\ts.s\t$f0,220($sp)',
  [(0, {'$f0': '$f2', '$f2': '$f0'}),
   (1, {'$f0': '$f2', '$f2': '$f0'}),
   (2, {'$f0': '$f2', '$f2': '$f0'}),
   (3, {'$f0': '$f2', '$f2': '$f0'}),
   (4, {'$f0': '$f2', '$f2': '$f0'}),
   (5, {'$f0': '$f2', '$f2': '$f0'})]),
 ('R4',
  '\tl.s\t$f0,216($sp)\n'
  '\tl.s\t$f26,220($sp)\n'
  '\tl.s\t$f22,224($sp)\n'
  '\tneg.s\t$f18,$f0\n'
  '\tmul.s\t$f2,$f18,$f6\n'
  '\ts.s\t$f22,320($sp)\n'
  '\tneg.s\t$f22,$f22\n'
  '\ts.s\t$f26,316($sp)\n'
  '\tneg.s\t$f26,$f26\n'
  '\ts.s\t$f0,312($sp)\n'
  '\ts.s\t$f18,312($sp)\n'
  '\tmul.s\t$f4,$f22,$f6\n'
  '\ts.s\t$f26,316($sp)\n'
  '\ts.s\t$f22,320($sp)\n'
  '\tl.s\t$f14,0($17)\n'
  '\t#nop\n'
  '\tadd.s\t$f14,$f14,$f2\n'
  '\tmul.s\t$f2,$f26,$f6\n'
  '\ts.s\t$f14,280($sp)\n'
  '\tl.s\t$f16,8($17)\n'
  '\tmul.s\t$f0,$f14,$f18\n'
  '\tadd.s\t$f16,$f16,$f4\n'
  '\ts.s\t$f16,288($sp)\n'
  '\tl.s\t$f12,4($17)\n'
  '\tmul.s\t$f4,$f16,$f22\n'
  '\tadd.s\t$f12,$f12,$f2\n'
  '\tmul.s\t$f2,$f12,$f26\n'
  '\tadd.s\t$f0,$f0,$f4\n'
  '\tadd.s\t$f0,$f0,$f2\n'
  '\tneg.s\t$f0,$f0\n'
  '\ts.s\t$f12,284($sp)\n'
  '\ts.s\t$f0,324($sp)\n'
  '\tl.s\t$f4,0($16)\n'
  '\t#nop\n'
  '\tsub.s\t$f4,$f4,$f14\n'
  '\ts.s\t$f4,296($sp)\n'
  '\tl.s\t$f2,8($16)\n'
  '\tmul.s\t$f4,$f4,$f18\n'
  '\tsub.s\t$f2,$f2,$f16\n'
  '\ts.s\t$f2,304($sp)\n'
  '\tl.s\t$f20,4($16)\n'
  '\tmul.s\t$f2,$f2,$f22\n'
  '\tsub.s\t$f20,$f20,$f12\n'
  '\ts.s\t$f20,300($sp)\n'
  '\tl.s\t$f8,0($18)\n'
  '\tmul.s\t$f20,$f20,$f26\n'
  '\tsub.s\t$f8,$f8,$f14\n'
  '\tl.s\t$f0,152($sp)\n'
  '\t#nop\n'
  '\tsub.s\t$f0,$f0,$f14\n'
  '\ts.s\t$f8,296($sp)\n'
  '\tmul.s\t$f8,$f8,$f18\n'
  '\tadd.s\t$f4,$f4,$f2\n'
  '\tl.s\t$f10,8($18)\n'
  '\tmul.s\t$f18,$f0,$f18\n'
  '\tsub.s\t$f10,$f10,$f16\n'
  '\tl.s\t$f6,156($sp)\n'
  '\tl.s\t$f2,160($sp)\n'
  '\tsub.s\t$f6,$f6,$f12\n'
  '\ts.s\t$f10,304($sp)\n'
  '\tmul.s\t$f10,$f10,$f22\n'
  '\tsub.s\t$f2,$f2,$f16\n'
  '\tl.s\t$f24,4($18)\n'
  '\ts.s\t$f2,304($sp)\n'
  '\tsub.s\t$f24,$f24,$f12\n'
  '\tmul.s\t$f2,$f2,$f22\n'
  '\tadd.s\t$f4,$f4,$f20\n'
  '\ts.s\t$f0,296($sp)\n'
  '\ts.s\t$f24,300($sp)\n'
  '\ts.s\t$f6,300($sp)\n'
  '\tmul.s\t$f6,$f6,$f26\n'
  '\ts.s\t$f14,D_8021C4C0\n'
  '\tadd.s\t$f8,$f8,$f10\n'
  '\ts.s\t$f12,D_8021C4C0+4\n'
  '\ts.s\t$f16,D_8021C4C0+8\n'
  '\tl.s\t$f0,0($17)\n'
  '\tadd.s\t$f18,$f18,$f2\n'
  '\tmul.s\t$f24,$f24,$f26\n'
  '\ts.s\t$f0,D_8021C4F0\n'
  '\tl.s\t$f0,4($17)\n'
  '\tadd.s\t$f18,$f18,$f6\n'
  '\tmtc1\t$0,$f2\n'
  '\ts.s\t$f0,D_8021C4F0+4\n'
  '\tc.lt.s\t$f18,$f2\n'
  '\tl.s\t$f0,8($17)\n'
  '\t#nop\n'
  '\ts.s\t$f0,D_8021C4F0+8\n'
  '\t.set\tnoreorder\n'
  '\tbc1t\t.L9\n'
  '\tadd.s\t$f8,$f8,$f24\n'
  '\t.set\tnoreorder\n'
  '\tlw\t$2,0($16)\n'
  '\tlw\t$3,4($16)\n'
  '\tlw\t$4,8($16)\n'
  '\tsw\t$2,184($sp)\n'
  '\tsw\t$3,188($sp)\n'
  '\tsw\t$4,192($sp)\n'
  '\tlw\t$2,0($18)\n'
  '\tlw\t$3,4($18)\n'
  '\tlw\t$4,8($18)\n'
  '\tsw\t$2,200($sp)\n'
  '\tsw\t$3,204($sp)\n'
  '\tsw\t$4,208($sp)\n'
  '\tli\t$2,0x00000001\t\t# 1\n'
  '\tc.lt.s\t$f4,$f2\n'
  '\taddu\t$5,$sp,184\n'
  '\t.set\tnoreorder\n'
  '\tbc1t\t.L11\n'
  '\taddu\t$6,$sp,200\n'
  '\t.set\tnoreorder\n'
  '\tmove\t$2,$0\n'
  '.L11:\n'
  '\tc.lt.s\t$f8,$f2\n'
  '\tnop\n'
  '\t.set\tnoreorder\n'
  '\tbc1t\t.L12\n'
  '\tli\t$3,0x00000001\t\t# 1\n'
  '\t.set\tnoreorder\n'
  '\tmove\t$3,$0\n'
  '.L12:\n'
  '\tand\t$2,$2,$3\n'
  '\tbne\t$2,$0,.L9\n'
  '\tnop\n'
  '\tc.lt.s\t$f4,$f2\n'
  '\tnop\n'
  '\t.set\tnoreorder\n'
  '\tbc1f\t.L14\n'
  '\taddu\t$4,$sp,312\n'
  '\t.set\tnoreorder\n'
  '\t.set\tnoreorder\n'
  '\tjal\tfunc_8009EB68\n'
  '\tmove\t$7,$5\n'
  '\t.set\tnoreorder\n'
  '\t.set\tnoreorder\n'
  '\tj\t.L15\n'
  '\tori\t$19,$19,0x0001\n'
  '\t.set\tnoreorder\n'
  '.L14:\n'
  '\tc.lt.s\t$f8,$f2\n'
  '\tnop',
  [(0, {}),
   (1, {}),
   (2, {'$f22': '$f24'}),
   (3, {'$f18': '$f22'}),
   (4, {'$f18': '$f22'}),
   (5, {'$f22': '$f24'}),
   (6, {'$f22': '$f24'}),
   (7, {}),
   (8, {}),
   (9, {}),
   (10, {'$f18': '$f22'}),
   (11, {'$f22': '$f24'}),
   (13, {'$f22': '$f24'}),
   (12, {}),
   (14, {'$f14': '$f18'}),
   (15, {'$f14': '$f18'}),
   (16, {}),
   (17, {'$f14': '$f18'}),
   (18, {'$f16': '$f20'}),
   (19, {'$f14': '$f18', '$f18': '$f22'}),
   (20, {'$f16': '$f20'}),
   (21, {'$f16': '$f20'}),
   (22, {}),
   (23, {'$f16': '$f20', '$f22': '$f24'}),
   (24, {}),
   (25, {}),
   (26, {}),
   (27, {}),
   (28, {}),
   (29, {}),
   (30, {}),
   (31, {'$f4': '$f6'}),
   (32, {'$f14': '$f18', '$f4': '$f6'}),
   (33, {'$f4': '$f6'}),
   (34, {}),
   (35, {'$f18': '$f22', '$f4': '$f6'}),
   (36, {'$f16': '$f20'}),
   (37, {}),
   (38, {'$f20': '$f14'}),
   (39, {'$f22': '$f24'}),
   (40, {'$f20': '$f14'}),
   (41, {'$f20': '$f14'}),
   (42, {'$f8': '$f10'}),
   (43, {'$f20': '$f14'}),
   (44, {'$f14': '$f18', '$f8': '$f10'}),
   (45, {}),
   (46, {'$f14': '$f18'}),
   (47, {'$f8': '$f10'}),
   (48, {'$f18': '$f22', '$f8': '$f10'}),
   (49, {'$f4': '$f6'}),
   (50, {'$f10': '$f8'}),
   (51, {'$f18': '$f22'}),
   (52, {'$f10': '$f8', '$f16': '$f20'}),
   (53, {'$f6': '$f4'}),
   (54, {}),
   (55, {'$f6': '$f4'}),
   (56, {'$f10': '$f8'}),
   (57, {'$f10': '$f8', '$f22': '$f24'}),
   (58, {'$f16': '$f20'}),
   (59, {'$f24': '$f16'}),
   (60, {}),
   (61, {'$f24': '$f16'}),
   (62, {'$f22': '$f24'}),
   (63, {'$f20': '$f14', '$f4': '$f6'}),
   (64, {}),
   (65, {'$f24': '$f16'}),
   (66, {'$f6': '$f4'}),
   (67, {'$f6': '$f4'}),
   (68, {'$f14': '$f18'}),
   (69, {'$f10': '$f8', '$f8': '$f10'}),
   (70, {}),
   (71, {'$f16': '$f20'}),
   (72, {}),
   (73, {'$f18': '$f22'}),
   (74, {'$f24': '$f16'}),
   (75, {}),
   (76, {}),
   (77, {'$f18': '$f22', '$f6': '$f4'}),
   (78, {}),
   (79, {}),
   (80, {'$f18': '$f22'}),
   (81, {}),
   (82, {}),
   (83, {}),
   (84, {'$f24': '$f16', '$f8': '$f10'}),
   (85, {}),
   (86, {}),
   (87, {}),
   (88, {}),
   (89, {}),
   (90, {}),
   (91, {}),
   (92, {}),
   (93, {}),
   (94, {}),
   (95, {}),
   (96, {}),
   (97, {}),
   (98, {'$f4': '$f6'}),
   (99, {}),
   (100, {}),
   (101, {}),
   (102, {}),
   (103, {'$f8': '$f10'}),
   (104, {}),
   (105, {}),
   (106, {}),
   (107, {}),
   (108, {}),
   (109, {}),
   (110, {}),
   (111, {'$f4': '$f6'}),
   (112, {}),
   (113, {}),
   (114, {}),
   (115, {}),
   (116, {}),
   (117, {}),
   (118, {}),
   (119, {'$f8': '$f10'}),
   (120, {})])]


def _sbm_is_instr(line: str) -> bool:
    s = line.strip()
    return bool(s) and not s.startswith(".") and not s.startswith("#") \
        and not re.match(r"^[.$\w]+:", s)


def _sbm_apply_slots(old: str, slots) -> str:
    lines = old.split("\n")
    idx = [i for i, l in enumerate(lines) if _sbm_is_instr(l)]
    src = [lines[i] for i in idx]
    if sorted(j for j, _ in slots) != list(range(len(src))):
        raise RuntimeError("func_8009FFB8 rule slots are not a permutation")
    out = list(lines)
    for k, i in enumerate(idx):
        j, m = slots[k]
        out[i] = re.sub(_SBM_REG, lambda mo: m.get(mo.group(0), mo.group(0)), src[j])
    return "\n".join(out)


def shape_segment_billboard_matrix(text: str) -> str:
    """Regional register-role and schedule rules for func_8009FFB8 (fail closed)."""
    if "func_8009FFB8:" not in text:
        return text
    match = re.search(r"\nfunc_8009FFB8:\n.*?\n\t\.end\tfunc_8009FFB8\n", text, flags=re.S)
    if match is None:
        raise RuntimeError("func_8009FFB8 body not found")
    lines = match.group(0).split("\n")
    frames = 0
    for i, line in enumerate(lines):
        if _SBM_FRAME.match(line):
            frames += 1
            continue
        if _sbm_is_instr(line):
            lines[i] = re.sub(_SBM_REG, lambda mo: _SBM_ROT.get(mo.group(0), mo.group(0)), line)
    if frames != 6:
        raise RuntimeError("func_8009FFB8 frame lines changed (%d)" % frames)
    body = "\n".join(lines)
    for name, old, slots in _SBM_BLOCKS:
        if body.count(old) != 1:
            raise RuntimeError("func_8009FFB8 rule %s fired %d times (expected 1)" % (name, body.count(old)))
        body = body.replace(old, _sbm_apply_slots(old, slots), 1)
        if name == "P1":
            hazard = "\tc.eq.s\t$f8,$f8\n\t.set\tnoreorder\n\tbc1t\t.L4\n"
            if body.count(hazard) != 1:
                raise RuntimeError("func_8009FFB8 hazard slot rule did not fire once")
            body = body.replace(hazard, "\tc.eq.s\t$f8,$f8\n\tnop\n\t.set\tnoreorder\n\tbc1t\t.L4\n", 1)
    return text[:match.start()] + body + text[match.end():]
