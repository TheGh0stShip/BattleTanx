#include "types.h"

typedef struct LevelModelTransform {
    f32 m[4][4];
    s32 value40;
} LevelModelTransform;

typedef struct LevelModelInstance {
    u8 pad00[0x10];
    s32 value10;
    s32 value14;
    s32 value18;
    s32 modelIndex;
} LevelModelInstance;

extern LevelModelTransform D_80074348;
extern s16 D_802D5A30[];

extern s32 get_spawn_session(void) __asm__("func_800821C0");
extern void set_yaw_transform(LevelModelTransform *xf, s32 x, s32 y, s32 z, u16 angle) __asm__("func_800A7744");
extern void submit_level_model(s32 world, s16 model, LevelModelTransform *xf, s32 mode, s32 a4, s32 *pos)
    __asm__("func_80084A74");

void submit_unrotated_level_model(LevelModelInstance *inst) __asm__("func_800DD8B8");

void submit_unrotated_level_model(LevelModelInstance *inst)
{
    LevelModelTransform transform = D_80074348;

    set_yaw_transform(&transform, inst->value14, inst->value18, inst->value10, 0);
    submit_level_model(get_spawn_session(), D_802D5A30[inst->modelIndex], &transform, 3, 0, &inst->value10);
}
