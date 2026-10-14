#include "types.h"

typedef struct ModelTransform {
    f32 m[4][4];
    s32 value40;
} ModelTransform;

typedef struct ModelInstance {
    u8 pad00[0xC];
    f32 value0C;
    f32 value10;
    u16 value14;
} ModelInstance;

extern ModelTransform D_80071AA0;
extern s16 D_802D5A60;

extern s32 get_spawn_session(void) __asm__("func_800821C0");
extern void set_model_transform(ModelTransform *xf, f32 a, f32 b, u16 angle) __asm__("func_800A76BC");
extern void submit_level_model(s32 world, s16 model, ModelTransform *xf, s32 mode, s32 a4, f32 *pos)
    __asm__("func_80084A74");

void submit_model_instance(ModelInstance *inst) __asm__("func_8008CDB0");

void submit_model_instance(ModelInstance *inst) {
    s32 session;
    f32 pos[2];
    ModelTransform transform = D_80071AA0;

    set_model_transform(&transform, inst->value0C, inst->value10, inst->value14);
    session = get_spawn_session();
    pos[1] = inst->value0C;
    pos[0] = inst->value10;
    submit_level_model(session, D_802D5A60, &transform, 2, 0, pos);
}
