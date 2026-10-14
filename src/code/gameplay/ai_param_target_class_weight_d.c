#include "ai_play_stack.h"

typedef struct ClassInfo {
    u8 pad00[0x18];
    s32 kind;
} ClassInfo;

typedef struct ClassTarget {
    u8 pad000[0x1AF];
    u8 active;
    u8 pad1B0[0x8];
    ClassInfo *info;
} ClassTarget;

typedef struct ClassOwner {
    u8 pad000[0x1A8];
    u16 targetId;
} ClassOwner;

extern f32 D_800747FC;
extern f32 D_80074800;
extern f32 D_80074804;

extern ClassTarget *get_entity_record(u16 index) __asm__("func_800A6688");

f32 ai_param_target_class_weight_d(AiActionContext *context) __asm__("func_800E8C84");

f32 ai_param_target_class_weight_d(AiActionContext *context)
{
    ClassTarget *target;
    u16 targetId;
    f32 weight;

    targetId = ((ClassOwner *)context->owner)->targetId;
    if (targetId != 0xFF) {
        target = get_entity_record(targetId);
        if (target->active != 0) {
            switch (target->info->kind) {
            case 0:
                weight = D_800747FC;
                goto done;
            case 1:
                weight = D_80074800;
                goto done;
            }
        }
    }
    weight = 0.0f;
done:
    return D_80074804 - weight;
}
