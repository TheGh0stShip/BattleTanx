#include "types.h"

/* RODATA_VRAM 0x80074510 */
/* LDSYM func_8007AAF4=0x8007AAF4 */
/* LDSYM func_8007B1DC=0x8007B1DC */
/* LDSYM func_8007C6D8=0x8007C6D8 */
/* LDSYM func_8009FBE4=0x8009FBE4 */
/* LDSYM func_800A6688=0x800A6688 */
/* LDSYM func_800E3470=0x800E3470 */
/* LDSYM func_800E95A8=0x800E95A8 */
/* LDSYM func_800F3880=0x800F3880 */
/* LDSYM func_8010874C=0x8010874C */
/* LDSYM D_80074504=0x80074504 */
/* LDSYM D_80074508=0x80074508 */
/* LDSYM D_8007450C=0x8007450C */
/* LDSYM D_8007455C=0x8007455C */
/* LDSYM D_80074560=0x80074560 */
/* LDSYM D_80074564=0x80074564 */
/* LDSYM D_80074568=0x80074568 */
/* LDSYM D_8007456C=0x8007456C */
/* LDSYM D_80074570=0x80074570 */
/* LDSYM D_80074574=0x80074574 */
/* LDSYM D_80074578=0x80074578 */
/* LDSYM D_8007457C=0x8007457C */
/* LDSYM D_80074580=0x80074580 */
/* LDSYM D_80074584=0x80074584 */
/* LDSYM D_80074588=0x80074588 */
/* LDSYM D_8007458C=0x8007458C */
/* LDSYM D_80074590=0x80074590 */
/* LDSYM D_80074594=0x80074594 */
/* LDSYM D_80074598=0x80074598 */

typedef s32 M2C_UNK;
#define M2C_FIELD(base, type, offset) (*(type)((u8 *)(base) + (offset)))
#define NULL 0

void *func_8007AAF4();                              /* extern */
s32 func_8007B1DC();                                /* extern */
s32 func_8007C6D8();                                /* extern */
s32 func_8009FBE4(void *);                          /* extern */
void *func_800A6688(u8);                            /* extern */
s32 func_800E3470(void *);                          /* extern */
f32 func_800E95A8(s32);                             /* extern */
f32 func_800F3880(f32);                             /* extern */
s32 func_8010874C(f32 *, s32, M2C_UNK, u32 *, s32); /* extern */
extern f32 D_80074504;
extern f32 D_80074508;
extern f32 D_8007450C;
extern f32 D_8007455C;
extern f32 D_80074560;
extern f32 D_80074564;
extern f32 D_80074568;
extern f32 D_8007456C;
extern f32 D_80074570;
extern f32 D_80074574;
extern f32 D_80074578;
extern f32 D_8007457C;
extern f32 D_80074580;
extern f32 D_80074584;
extern f32 D_80074588;
extern f32 D_8007458C;
extern f32 D_80074590;
extern f32 D_80074594;
extern f32 D_80074598;


typedef struct MotionQuery {
    f32 x;
    f32 z;
    u32 hit;
    u8 pad[0x14];
} MotionQuery;

static inline s32 query_different_owner(void *entity, s32 range, MotionQuery *query) {
    u8 first;
    u8 second;

    if (func_8010874C(&query->x, range, 4, &query->hit,
                      M2C_FIELD(entity, s32 *, 0x504)) == 0) {
        goto different;
    }
    if (query->hit < 4U) {
        goto different;
    }
    if (M2C_FIELD(query->hit, s32 *, 8) != 0) {
        goto different;
    }
    first = func_8009FBE4(M2C_FIELD(query->hit, void **, 0xC));
    second = func_8009FBE4(entity);
    if (first != second) {
        goto different;
    }
    return 0;
different:
    return 1;
}
static inline s32 random_below(f32 limit, f32 threshold) {
    return func_800F3880(limit) < threshold;
}

void update_ai_combat_decision(void *arg0, void *arg1, s32 arg2) {
    MotionQuery query;
    register void *entity __asm__("$17") = arg0;
    register void *out __asm__("$22") = arg1;
    f32 temp_f20;
    f32 temp_f20_2;
    f32 temp_f20_3;
    f32 temp_f24;
    f32 temp_f4;
    f32 var_f20;
    f32 var_f22;
    f32 var_f2;
    s16 temp_v0;
    s32 temp_s0_3;
    s32 temp_s2_2;
    s32 temp_v0_2;
    register s32 var_s0 __asm__("$16");
    register s32 var_s5 __asm__("$21");
    register s32 var_v0 __asm__("$2");
    s32 var_v0_2;
    s32 var_v0_3;
    s32 var_v0_4;
    register s32 var_s3 __asm__("$19");
    register s32 var_s4 __asm__("$20");
    void *temp_a0;
    void *temp_a0_2;
    void *temp_s0;

    var_s3 = 0;
    var_s4 = 0;
    temp_s0 = func_800A6688(M2C_FIELD(entity, u8 *, 4));
    temp_f4 = func_800E95A8(M2C_FIELD(entity, s32 *, 0x368));
    if (M2C_FIELD(entity, s32 *, 0x18) == 2) {
        if (M2C_FIELD(entity, u16 *, 0x14) & 4) {
            var_f2 = M2C_FIELD(temp_s0, f32 *, 0x324);
        } else {
            var_f2 = M2C_FIELD(temp_s0, f32 *, 0x328);
        }
    } else {
        var_f2 = M2C_FIELD(temp_s0, f32 *, 0x320);
    }
    var_s5 = 1;
    if (!(temp_f4 < ((var_f2 * D_80074504) / D_80074508))) {
        var_s5 = 0;
    }
    if (((var_s5 == 0) || (M2C_FIELD(entity, s32 *, 0x18) == 1)) && (arg2 != 0)) {
        if (entity == NULL) {
            goto no_target;
        }
        query.x = M2C_FIELD(entity, f32 *, 0x2C);
        query.z = M2C_FIELD(entity, f32 *, 0x24);
        var_v0 = query_different_owner(entity, arg2, &query);
        goto target_done;
no_target:
        var_v0 = 0;
target_done:
        if (var_v0 != 0) {
            if (func_8007C6D8() == 0) {
                register s32 temp_s2 __asm__("$18");
                temp_s2 = M2C_FIELD(entity, s32 *, 0x374);
                var_f20 = D_8007450C;
                var_s0 = 0;
                switch (temp_s2) {
                case 2:
                    var_f20 = D_8007455C;
                    var_s0 = 4;
                    break;
                case 3:
                    var_f20 = D_80074560;
                    var_s0 = 5;
                    break;
                case 7:
                    var_f20 = D_80074564;
                    var_s0 = 0xB;
                    break;
                case 15:
                    var_f20 = D_80074568;
                    var_s0 = 7;
                    break;
                case 19:
                    var_f20 = D_8007456C;
                    var_s0 = 0xD;
                    break;
                case 9:
                    var_f20 = D_80074570;
                    var_s0 = 0xC;
                    break;
                case 1:
                    var_s0 = 6;
                    var_f20 = D_80074574;
                    break;
                }
                if (M2C_FIELD(entity, u16 *, 0x14) & 4) {
                    var_f20 /= D_80074578;
                }
                if (random_below(D_8007457C, var_f20)) {
                    temp_a0 = (var_s0 * 2) + entity;
                    temp_v0 = M2C_FIELD(temp_a0, s16 *, 0x480);
                    if (temp_v0 != 0) {
                        goto keep_counter;
                    }
                    if (temp_s2 == 1) {
                        goto keep_counter;
                    }
                    M2C_FIELD(temp_a0, s16 *, 0x480) = (s16) (temp_v0 + 1);
keep_counter:
                    M2C_FIELD(entity, s32 *, 0x474) = var_s0;
                    var_s4 = 1;
                } else {
                    goto block_50;
                }
            } else {
                temp_f20 = M2C_FIELD(func_8007AAF4(), f32 *, 0x21C) * D_80074580 * D_80074584;
                var_f22 = (f32) func_8007B1DC() / temp_f20;
                temp_f24 = D_80074588;
                if (temp_f24 < var_f22) {
                    var_f22 = temp_f24;
                }
                if (M2C_FIELD(entity, s32 *, 0xB4) == 1) {
                    temp_a0_2 = M2C_FIELD(entity, void **, 0xC4);
                    temp_s2_2 = M2C_FIELD(entity, u8 *, 0x15) & 4;
                    temp_s0_3 = M2C_FIELD(temp_a0_2, u8 *, 0x15) & 4;
                    temp_v0_2 = func_800E3470(temp_a0_2) & 0xFF;
                    if (temp_s0_3 != 0) {
                        if (temp_v0_2 == 0) {
                            temp_f20_2 = (var_f22 * D_8007458C) + D_80074590;
                            if (random_below(temp_f24, temp_f20_2)) {
                                var_s4 = 1;
                                M2C_FIELD(entity, s32 *, 0x474) = 5;
                                M2C_FIELD(entity, u16 *, 0x48A) = (u16) (M2C_FIELD(entity, u16 *, 0x48A) + 1);
                            } else {
                                goto block_50;
                            }
                        } else {
                            goto block_50;
                        }
                    } else if (temp_s2_2 != 0) {
                        temp_f20_3 = (var_f22 * D_80074594) + D_80074598;
                        if (random_below(temp_f24, temp_f20_3)) {
                            M2C_FIELD(entity, s32 *, 0x474) = 0;
                            var_s4 = 1;
                        } else {
                            goto block_50;
                        }
                    } else {
                        goto block_50;
                    }
                } else {
block_50:
                    var_s3 = 1;
                }
            }
            if (var_s4 & var_s5) {
                var_s3 = 1;
                var_s4 = 0;
            }
            M2C_FIELD(out, s8 *, 0xC) = var_s3;
            M2C_FIELD(out, s8 *, 0xD) = var_s3;
            M2C_FIELD(out, s8 *, 0xE) = var_s4;
            M2C_FIELD(out, s8 *, 0xF) = var_s4;
            if ((var_s5 == 0) && ((var_s4 | var_s3) != 0)) {
                M2C_FIELD(entity, s32 *, 0x368) = func_8007B1DC();
            }
        }
    }
}
