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

/* Five-entry spawn point tables in effect_script_data.c. */
extern u8 D_8013957C[];
extern u8 D_801395B8[];
extern u8 D_8033B630;
extern u8 D_8033B631;

extern s32 func_800E3470(s32 unit);

void effect_select_spawn_points(SpawnEffect *effect, SpawnContact *contact, s32 unused, SpawnResult *result)
    __asm__("func_800EEBEC");

void effect_select_spawn_points(SpawnEffect *effect, SpawnContact *contact, s32 unused, SpawnResult *result)
{
    if (contact->kind != 0) {
        return;
    }
    if (func_800E3470(contact->unit) != 0) {
        if (effect->heading < 0.0f) {
            if (D_8033B630 != 0) {
                result->action = SPAWN_RESULT_POINTS;
                result->points = D_8013957C;
                return;
            }
        } else if (D_8033B631 != 0) {
            result->action = SPAWN_RESULT_POINTS;
            result->points = D_801395B8;
            return;
        }
    }
    result->action = 1;
}
