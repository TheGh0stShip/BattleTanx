#include "types.h"

typedef s32 M2C_UNK;
#define M2C_FIELD(base, type, offset) (*(type)((u8 *)(base) + (offset)))
/* LDSYM D_800743A8=0x800743A8 */
/* LDSYM D_800743AC=0x800743AC */
/* LDSYM D_800743B0=0x800743B0 */
/* LDSYM D_8033A980=0x8033A980 */
/* LDSYM func_800A03B8=0x800A03B8 */
/* LDSYM func_800A6688=0x800A6688 */
/* LDSYM func_800DE3EC=0x800DE3EC */
/* LDSYM func_800E0D54=0x800E0D54 */
/* LDSYM func_800E19DC=0x800E19DC */
/* LDSYM func_800E3470=0x800E3470 */
#ifndef NULL
#define NULL 0
#endif
void *func_800A03B8();                           /* extern */
void *func_800A6688();                            /* extern */
u16 func_800DE3EC();      /* extern */
f32 func_800E0D54();                  /* extern */
s32 func_800E19DC();                             /* extern */
s32 func_800E3470();                          /* extern */
extern f32 D_800743A8;
extern f32 D_800743AC;
extern f32 D_800743B0;
extern M2C_UNK D_8033A980;

typedef struct LocalRoute {
    u16 *entries;
    u16 head;
    u16 tail;
    u16 count;
    u16 free;
    u16 capacity;
} LocalRoute;

typedef struct RouteState {
    u8 pad00000[0x11940];
    f32 x;
    f32 z;
} RouteState;

void initialize_route_search_state(void *arg0, void *arg1, void *arg2, u8 arg3,
                                   void *arg4, u8 *arg5) {
    LocalRoute sp10;
    u16 sp20[0xFC];
    f32 temp_f0;
    f32 temp_f20;
    f32 temp_f2;
    register s32 temp_s4 __asm__("$20");
    register s32 signMask __asm__("$23");
    u16 var_a0;
    register void *var_s3 __asm__("$19");
    register s32 var_s2 __asm__("$18");
    register s32 var_v1 __asm__("$3");
    s32 remaining;
    s8 *temp_v1;
    u8 *temp_v1_2;
    u8 *temp_v1_3;
    u8 *temp_v1_4;
    void *temp_v0_2;
    register u8 *base __asm__("$17") = arg0;
    u8 *initBase = base;
    register u8 *entity __asm__("$22") = arg4;
    u8 *weights = arg5;
    register void *position __asm__("$5");
    register void *none __asm__("$0");

    position = arg2;

    sp10.entries = sp20;
    sp10.head = 0;
    sp10.tail = 0;
    sp10.count = 0;
    sp10.free = 0;
    sp10.capacity = 0xF8;
    var_a0 = 0;
    do {
        initBase[(var_a0 & 0xFFFF) * 0x18] = 0;
        var_a0++;
    } while ((u32)(var_a0 & 0xFFFF) < 0xBB8U);
    ((RouteState *) base)->z = M2C_FIELD(entity, f32 *, 0x24);
    ((RouteState *) base)->x = M2C_FIELD(entity, f32 *, 0x2C);
    M2C_FIELD(base, void **, 0x11948) = (void *) (entity + 0x134);
    M2C_FIELD(base, u16 *, 0x11954) = func_800DE3EC(&sp10, position);
    if (M2C_FIELD(entity, u8 *, 0x35A) == 0) {
        goto block_4;
    }
    M2C_FIELD(entity, u16 *, 0x346) = func_800DE3EC(&sp10, &((RouteState *) base)->x);
block_4:
    {
    register u16 entityIndex __asm__("$2");
    entityIndex = M2C_FIELD(entity, u16 *, 0x346);
    M2C_FIELD(base, s16 *, 0x11958) = 0;
    M2C_FIELD(base, u8 **, 0x1194C) = weights;
    M2C_FIELD(base, u16 *, 0x11956) = entityIndex;
    }
    if (entity != NULL) {
        goto block_6;
    }
    M2C_FIELD(base, void **, 0x11950) = none;
    goto block_24;
block_6:
    {
    register void *team __asm__("$21");
    register void *computedTeam __asm__("$2");
    register s32 memberCount __asm__("$2");
    var_s2 = 0;
    computedTeam = (M2C_FIELD(func_800A6688(M2C_FIELD(entity, u8 *, 4)), u8 *, 0x1AE) * 0x52) + (u8 *)&D_8033A980;
    team = computedTeam;
    M2C_FIELD(base, void **, 0x11950) = team;
    temp_s4 = M2C_FIELD(base, s32 *, 0x1194C);
    memberCount = M2C_FIELD(team, u16 *, 0x26);
    if (memberCount <= 0) {
        goto block_24;
    }
    temp_f20 = D_800743A8;
    signMask = 0x80000000;
    var_s3 = team;
loop_8:
    temp_v0_2 = func_800A03B8(M2C_FIELD(var_s3, s16 *, 8));
    if (M2C_FIELD(temp_v0_2, u8 *, 1) == 0) {
        goto block_23;
    }
    if (temp_v0_2 == entity) {
        goto block_23;
    }
    if (M2C_FIELD(temp_v0_2, u16 *, 0x14) & 4) {
        goto block_23;
    }
    if (func_800E3470(temp_v0_2) != 0) {
        goto block_23;
    }
    temp_f0 = func_800E0D54(entity + 0x24, temp_v0_2 + 0x24);
    if (D_800743AC < temp_f0) {
        goto block_23;
    }
    temp_f2 = temp_f0 / D_800743B0;
    if (!(temp_f20 <= temp_f2)) {
        goto block_15;
    }
    goto block_17;
block_15:
    var_v1 = (s32) temp_f2;
    goto block_18;
block_17:
    var_v1 = (s32) (temp_f2 - temp_f20) | signMask;
block_18:
    remaining = 4 - var_v1;
    temp_v1_2 = (u8 *)(u32)M2C_FIELD(temp_v0_2, u16 *, 0x346);
    if ((remaining & 0xFFFF) == 0) {
        *(temp_v1_2 + temp_s4) = 0;
    } else {
        temp_v1_3 = temp_v1_2 + temp_s4;
        *temp_v1_3 += 1;
    }
block_23:
    var_s2 += 1;
    var_s3 += 2;
    if (var_s2 < M2C_FIELD(team, u16 *, 0x26)) {
        goto loop_8;
    }
    }
block_24:
    temp_v1_4 = weights + M2C_FIELD(base, u16 *, 0x11956);
    if (*temp_v1_4 == 0) {
        goto block_26;
    }
    *temp_v1_4 = 0;
block_26:
    M2C_FIELD(base, s32 *, 0x11960) = 0;
    M2C_FIELD(base, s32 *, 0x11964) = 2;
    if (!(func_800E19DC(M2C_FIELD(entity, u16 *, 0x346)) & 0xFF)) {
        goto block_28;
    }
    M2C_FIELD(base, s32 *, 0x11964) = 3;
    M2C_FIELD(base, s32 *, 0x11960) = (s32) (M2C_FIELD(base, s32 *, 0x11960) | 1);
block_28:
    if (!(func_800E19DC(M2C_FIELD(base, u16 *, 0x11954)) & 0xFF)) {
        goto block_30;
    }
    M2C_FIELD(base, s32 *, 0x11964) = 3;
    M2C_FIELD(base, s32 *, 0x11960) = (s32) (M2C_FIELD(base, s32 *, 0x11960) | 2);
block_30:
    M2C_FIELD(base, void **, 0x1195C) = entity;
    return;
}
