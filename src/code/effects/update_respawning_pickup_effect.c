#include "types.h"

typedef struct PickupVec2 {
    f32 x;
    f32 y;
} PickupVec2;

typedef struct PickupQuad {
    PickupVec2 v[4];
} PickupQuad;

typedef struct RespawningPickup {
    u8 pad00[0xC];
    PickupVec2 pos;
    u8 pad14[4];
    s32 value18;
    s32 value1C;
    u8 value20;
    u8 pad21[3];
    s32 value24;
    s32 value28;
} RespawningPickup;

extern s32 game_mode_is_3_through_6(void) __asm__("func_8007C6D8");
extern u32 func_800F38F4(void);
extern s32 create_effect_motion(RespawningPickup *effect, s32 x, s32 y, s32 minX, s32 maxX, s32 minY,
                                s32 maxY, s32 mode, s32 flags) __asm__("func_80106D18");
extern void func_80107170(s32 motion);
extern PickupQuad D_80071E64;
extern u8 D_80134E66;
extern s32 gGameTicks __asm__("D_801B4AA8");
extern u8 gWeightTable[] __asm__("D_802D5BA0");
extern u8 D_802D5BB7;

void update_respawning_pickup_effect(RespawningPickup *pickup, s32 *state) __asm__("func_800913AC");

void update_respawning_pickup_effect(RespawningPickup *pickup, s32 *state) {
    if ((pickup->value20 != 0 && (game_mode_is_3_through_6() != 0 || D_80134E66 == 0))
        || (pickup->value28 != 0 && (pickup->value20 != 0 || gGameTicks >= pickup->value28))) {
        *state = 2;
        func_80107170(pickup->value1C);
        return;
    }
    if (pickup->value28 != 0) {
        return;
    }
    if (pickup->value20 != 0) {
        pickup->value20 = 0;
        func_80107170(pickup->value1C);
        {
            s32 delay = func_800F38F4() % 3600 + 1800;

            pickup->value24 = gGameTicks + delay;
        }
        return;
    }
    if (pickup->value24 != 0 && pickup->value24 < gGameTicks) {
        s32 roll;
        s32 i = 0;
        s32 j;
        PickupVec2 *pos;
        PickupQuad corners;
        PickupQuad offsets;

        pickup->value24 = 0;
        roll = func_800F38F4() % D_802D5BB7;
        while (roll >= gWeightTable[i]) {
            roll -= gWeightTable[i++];
        }
        pickup->value18 = i;
        pos = &pickup->pos;
        offsets = D_80071E64;
        for (j = 0; j < 4; j++) {
            corners.v[j].y = offsets.v[j].y + pos->y;
            corners.v[j].x = offsets.v[j].x + pos->x;
        }
        pickup->value1C = create_effect_motion(pickup, pickup->pos.y, pickup->pos.x, -35, 35, -35, 35, 2, 0);
    }
}
