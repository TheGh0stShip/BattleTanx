#include "types.h"

typedef struct SpawnEffect {
    u8 pad00[0x24];
    f32 heading;
} SpawnEffect;

typedef struct SpawnContact {
    u8 pad00[0x8];
    s32 kind;
    s32 unit;
} SpawnContact;

typedef struct SpawnResult {
    s32 action;
    void *points;
} SpawnResult;

#define SPAWN_RESULT_POINTS 0xA

extern u8 D_8013957C[];
extern u8 D_801395B8[];
extern u8 D_8033B630;
extern u8 D_8033B631;

extern s32 func_800E3470(s32 unit);

void effect_select_spawn_points_on_message(SpawnEffect *effect, SpawnContact *contact, s32 message, s32 unused,
                                           SpawnResult *result) __asm__("func_800EECA0");

void effect_select_spawn_points_on_message(SpawnEffect *effect, SpawnContact *contact, s32 message, s32 unused,
                                           SpawnResult *result)
{
    SpawnResult *out = result;

    if (message == 0 && contact->kind == 0) {
        if (func_800E3470(contact->unit) != 0) {
            if (effect->heading < 0.0f) {
                if (D_8033B630 != 0) {
                    out->action = SPAWN_RESULT_POINTS;
                    out->points = D_8013957C;
                    return;
                }
            } else if (D_8033B631 != 0) {
                out->action = SPAWN_RESULT_POINTS;
                out->points = D_801395B8;
                return;
            }
        }
        out->action = 1;
    }
}
