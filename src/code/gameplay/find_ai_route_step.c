#include "types.h"

typedef s32 M2C_UNK;
#define M2C_FIELD(base, type, offset) (*(type)((u8 *)(base) + (offset)))
/* LDSYM func_800A03B8=0x800A03B8 */
/* LDSYM func_800DEE8C=0x800DEE8C */
/* LDSYM func_800DF214=0x800DF214 */
/* LDSYM func_800DF60C=0x800DF60C */
/* LDSYM func_800DF6F4=0x800DF6F4 */
/* LDSYM func_800DF7D0=0x800DF7D0 */
/* LDSYM func_800E09B0=0x800E09B0 */
/* LDSYM func_800E0C8C=0x800E0C8C */
/* LDSYM func_800E1648=0x800E1648 */
/* LDSYM func_800E3470=0x800E3470 */
/* LDSYM D_80074404=0x80074404 */
/* LDSYM D_80074408=0x80074408 */
/* LDSYM D_8007440C=0x8007440C */
/* LDSYM D_80074410=0x80074410 */
/* LDSYM D_80135830=0x80135830 */
/* LDSYM D_80135840=0x80135840 */
/* LDSYM D_80328458=0x80328458 */
#ifndef NULL
#define NULL 0
#endif
void *func_800A03B8();                           /* extern */
M2C_UNK func_800DEE8C(); /* extern */
u32 func_800DF214();                             /* extern */
M2C_UNK func_800DF60C();                 /* extern */
s16 func_800DF6F4();                          /* extern */
M2C_UNK func_800DF7D0();                      /* extern */
void *func_800E09B0();                             /* extern */
f32 func_800E0C8C();                  /* extern */
M2C_UNK func_800E1648();                 /* extern */
s32 func_800E3470();                          /* extern */
extern f32 D_80074404;
extern f32 D_80074408;
extern f32 D_8007440C;
extern f32 D_80074410;
extern void *D_80135830;
extern f32 D_80135840[];
extern M2C_UNK D_80328458;

static inline s32 copy_index(s32 value) { return value; }
static inline u32 loop_value(s32 value) { return value & 0xffff; }

static inline s32 route_member_count(void *team) {
    return M2C_FIELD(team, u16 *, 0x26);
}

u16 find_ai_route_step(s32 arg0, s32 arg1, s32 arg2, s32 arg3) __asm__("func_800DFA68");

u16 find_ai_route_step(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    volatile s32 routeScratch;
    s32 sp1C;
    s32 sp24;
    f32 temp_f0;
    f32 edgeCost;
    f32 treeKey;
    f32 temp_f20;
    f32 temp_f20_2;
    f32 temp_f22;
    f32 temp_f2;
    register f32 temp_f2_2 __asm__("$f2");
    register s16 temp_v0_3 __asm__("$23");
    s32 temp_fp;
    register s32 temp_s3 __asm__("$19");
    register void *temp_s4 __asm__("$20");
    register s8 *temp_s5_2 __asm__("$21");
    register s32 var_s1 __asm__("$17");
    register s32 var_s6 __asm__("$22");
    s32 var_v0;
    s32 var_v0_2;
    s32 var_v0_3;
    u16 *var_a0;
    u16 *var_a0_2;
    u16 *var_a0_3;
    u16 temp_a0;
    u16 temp_a2;
    s32 temp_s0_2;
    s32 currentIndex;
    u16 temp_s5;
    s32 var_v1;
    s32 var_v1_2;
    s32 var_v1_3;
    void *temp_s0;
    register void *temp_s0_3 __asm__("$16");
    void *temp_s0_4;
    void *temp_s0_5;
    void *temp_s1;
    void *temp_s1_2;
    void *temp_s2;
    void *temp_s2_3;
    register void *temp_s3_2 __asm__("$19");
    void *temp_v0;
    void *temp_v0_2;
    void *temp_v0_4;
    register void *temp_v0_5 __asm__("$2");
    void *temp_v0_6;
    void *temp_v0_7;
    void *temp_v0_8;
    void *temp_v0_9;
    register void *var_s2 __asm__("$18");
    void *tree_base2;
    void *tree_base3;
    void *tree_base1;
    f32 *costTable = D_80135840;

    func_800DEE8C(D_80135830, 0, arg2, 0, arg3, &D_80328458);
    temp_s2 = D_80135830;
    temp_a0 = M2C_FIELD(temp_s2, u16 *, 0x11954);
    temp_s0 = temp_s2 + (temp_a0 * 0x18);
    temp_s1 = temp_s0 + 0x10;
    func_800E1648(func_800E09B0(temp_a0), temp_s1);
    M2C_FIELD(temp_s0, s8 *, 0) = 1;
    M2C_FIELD(temp_s0, s8 *, 1) = 1;
    M2C_FIELD(temp_s0, s16 *, 2) = 0;
    M2C_FIELD(temp_s0, s16 *, 4) = 0;
    M2C_FIELD(temp_s0, s16 *, 6) = 0;
    temp_f0 = func_800E0C8C(temp_s1, temp_s2 + 0x11940);
    M2C_FIELD(temp_s0, f32 *, 8) = 0.0f;
    tree_base1 = D_80135830;
    M2C_FIELD(temp_s0, f32 *, 0xC) = (f32) (temp_f0 + M2C_FIELD(temp_s0, f32 *, 8));
    temp_a2 = M2C_FIELD(tree_base1, u16 *, 0x11954);
    var_a0 = tree_base1 + 0x11958;
    temp_v0 = tree_base1 + (temp_a2 * 0x18);
    M2C_FIELD(temp_v0, s8 *, 1) = 0;
    M2C_FIELD(temp_v0, s16 *, 4) = 0;
    M2C_FIELD(temp_v0, s16 *, 6) = 0;
    treeKey = M2C_FIELD(temp_v0, f32 *, 0xC);
    while ((var_v1 = *var_a0) != 0) {
    var_v0 = var_v1 * 2;
    temp_v0_2 = tree_base1 + ((var_v0 + var_v1) * 8);
    var_a0 = temp_v0_2 + 4;
    if (treeKey <= M2C_FIELD(temp_v0_2, f32 *, 0xC)) {
        goto block_4;
    }
    var_a0 = temp_v0_2 + 6;
block_4:
    }
    *var_a0 = temp_a2;
    sp1C = 0;
loop_6:
    temp_v0_3 = func_800DF6F4(D_80135830);
    temp_s0_2 = temp_v0_3 & 0xFFFF;
    if (temp_s0_2 == 0) {
        goto block_32;
    }
    if (temp_s0_2 == M2C_FIELD(D_80135830, u16 *, 0x11956)) {
        goto block_43;
    }
    sp24 = (s32)func_800E09B0(temp_s0_2);
    var_s6 = 0;
    currentIndex = copy_index(temp_s0_2);
    temp_fp = currentIndex * 0x18;
loop_9:
    temp_v0_4 = sp24 + ((var_s6 & 0xFFFF) * 4);
    if (M2C_FIELD(temp_v0_4, u16 *, 2) == 0) {
        goto block_30;
    }
    temp_s5 = M2C_FIELD(temp_v0_4, u16 *, 2) / 3;

    var_v0 = func_800DF214(temp_s5);
    temp_s0_3 = D_80135830;
    if ((u32) M2C_FIELD(temp_s0_3, u32 *, 0x11964) < (u32)var_v0) {
        goto block_30;
    }
    var_v0 = temp_s5 * 3;
    temp_s3 = var_v0 * 8;
    temp_s1_2 = temp_s0_3 + temp_s3;
    if (M2C_FIELD(temp_s1_2, u8 *, 0) == 0) {
        goto block_21;
    }
    temp_s0_4 = temp_s0_3 + temp_fp;
    edgeCost = ((f32) *((u8 *)M2C_FIELD(temp_s0_3, void **, 0x1194C) + currentIndex) * D_80074404) + D_80074408 + costTable[func_800DF214(currentIndex)];
    temp_f2 = M2C_FIELD(temp_s0_4, f32 *, 8) + func_800E0C8C(temp_s0_4 + 0x10, temp_s1_2 + 0x10) + edgeCost;
    temp_f20 = temp_f2;
    if (M2C_FIELD(temp_s1_2, f32 *, 8) <= temp_f2) {
        goto block_30;
    }
    if (M2C_FIELD(temp_s1_2, u8 *, 1) != 0) {
        goto block_15;
    }
    func_800DF60C(D_80135830, temp_s5);
block_15:
    tree_base2 = D_80135830;
    M2C_FIELD(temp_s1_2, s16 *, 2) = temp_v0_3;
    temp_f2_2 = temp_f20 + (M2C_FIELD(temp_s1_2, f32 *, 0xC) - M2C_FIELD(temp_s1_2, f32 *, 8));
    M2C_FIELD(temp_s1_2, f32 *, 8) = temp_f20;
    var_a0_2 = tree_base2 + 0x11958;
    temp_v0_5 = tree_base2 + temp_s3;
    M2C_FIELD(temp_s1_2, f32 *, 0xC) = temp_f2_2;
    M2C_FIELD(temp_v0_5, s8 *, 1) = 0;
    M2C_FIELD(temp_v0_5, s16 *, 4) = 0;
    M2C_FIELD(temp_v0_5, s16 *, 6) = 0;
    treeKey = M2C_FIELD(temp_v0_5, f32 *, 0xC);
    while ((var_v1_2 = *var_a0_2) != 0) {
    var_v0_2 = var_v1_2 * 2;
    temp_v0_6 = tree_base2 + ((var_v0_2 + var_v1_2) * 8);
    var_a0_2 = temp_v0_6 + 4;
    if (treeKey <= M2C_FIELD(temp_v0_6, f32 *, 0xC)) {
        goto block_19;
    }
        var_a0_2 = temp_v0_6 + 6;
block_19:
    }
    *var_a0_2 = temp_s5;
    goto block_30;
block_21:
    temp_s2_3 = temp_s1_2 + 0x10;
    func_800E1648(func_800E09B0(temp_s5), temp_s2_3);
    M2C_FIELD(temp_s1_2, u8 *, 0) = 1U;
    M2C_FIELD(temp_s1_2, u8 *, 1) = 1U;
    M2C_FIELD(temp_s1_2, s16 *, 2) = temp_v0_3;
    M2C_FIELD(temp_s1_2, s16 *, 4) = 0;
    M2C_FIELD(temp_s1_2, s16 *, 6) = 0;
    temp_f22 = func_800E0C8C(temp_s2_3, temp_s0_3 + 0x11940);
    if (currentIndex != 0) {
        goto block_23;
    }
    M2C_FIELD(temp_s1_2, f32 *, 8) = 0.0f;
    goto block_24;
block_23:
    temp_s0_5 = temp_s0_3 + temp_fp;
        temp_f20_2 = ((f32) *((u8 *)M2C_FIELD(temp_s0_3, void **, 0x1194C) + currentIndex) * D_8007440C) + D_80074410 + costTable[func_800DF214(currentIndex)];
    M2C_FIELD(temp_s1_2, f32 *, 8) = (f32) (M2C_FIELD(temp_s0_5, f32 *, 8) + func_800E0C8C(temp_s0_5 + 0x10, temp_s2_3) + temp_f20_2);
block_24:
    tree_base3 = D_80135830;
    var_a0_2 = tree_base3 + 0x11958;
    temp_v0_7 = tree_base3 + ((temp_s5 & 0xFFFF) * 0x18);
    M2C_FIELD(temp_s1_2, f32 *, 0xC) = (f32) (M2C_FIELD(temp_s1_2, f32 *, 8) + temp_f22);
    M2C_FIELD(temp_v0_7, s8 *, 1) = 0;
    M2C_FIELD(temp_v0_7, s16 *, 4) = 0;
    M2C_FIELD(temp_v0_7, s16 *, 6) = 0;
    treeKey = M2C_FIELD(temp_v0_7, f32 *, 0xC);
    while ((var_v1_3 = *var_a0_2) != 0) {
    var_v0_3 = var_v1_3 * 2;
    temp_v0_8 = tree_base3 + ((var_v0_3 + var_v1_3) * 8);
    var_a0_2 = temp_v0_8 + 4;
    if (treeKey <= M2C_FIELD(temp_v0_8, f32 *, 0xC)) {
        goto block_28;
    }
    var_a0_2 = temp_v0_8 + 6;
block_28:
    }
block_29:
    *var_a0_2 = temp_s5;
block_30:
    var_s6 += 1;
    if (loop_value(var_s6) < 3U) {
        goto loop_9;
    }
    goto loop_6;
block_32:
    temp_s3_2 = M2C_FIELD(D_80135830, void **, 0x11950);
    temp_s5_2 = M2C_FIELD(D_80135830, s32 *, 0x1194C);
    temp_s4 = M2C_FIELD(D_80135830, s32 *, 0x1195C);
    if (temp_s3_2 == NULL) {
        goto block_41;
    }
    var_s1 = 0;
    if (route_member_count(temp_s3_2) <= 0) {
        goto block_41;
    }
    var_s2 = temp_s3_2;
loop_35:
    temp_v0_9 = func_800A03B8(M2C_FIELD(var_s2, s16 *, 8));
    if (M2C_FIELD(temp_v0_9, u8 *, 1) == 0) {
        goto block_40;
    }
    if (temp_v0_9 == temp_s4) {
        goto block_40;
    }
    if (M2C_FIELD(temp_v0_9, u16 *, 0x14) & 4) {
        goto block_40;
    }
    if (func_800E3470(temp_v0_9) != 0) {
        goto block_40;
    }
    *(temp_s5_2 + M2C_FIELD(temp_v0_9, u16 *, 0x346)) = 0;
block_40:
    var_s1 += 1;
    var_s2 += 2;
    if (var_s1 < route_member_count(temp_s3_2)) {
        goto loop_35;
    }
block_41:
    if (sp1C != 0) {
        goto block_44;
    }
    return 0U;
block_43:
    sp1C = 1;
    goto block_32;
block_44:
    func_800DF7D0(D_80135830);
    return M2C_FIELD(D_80135830, u16 *, 0x11954);
}
