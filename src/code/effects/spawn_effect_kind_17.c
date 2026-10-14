#include "types.h"

typedef struct {
    u8 pad00[0xC];
    s32 value0C;
    f32 value10;
    f32 value14;
    s32 value18;
    s32 value1C;
    s32 value20;
} EffectKind17;

extern EffectKind17 *allocate_effect(s32 group, s32 kind, s32 size) __asm__("func_8008AD10");
extern s32 func_80106D18(EffectKind17 *, s32, s32, s32, s32, s32, s32, s32, s32);

EffectKind17 *spawn_effect_kind_17(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) __asm__("func_800F2044");

EffectKind17 *spawn_effect_kind_17(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    EffectKind17 *e;

    e = allocate_effect(1, 0x17, 0x24);
    if (e == 0) {
        return 0;
    }
    e->value14 = arg0;
    e->value10 = arg1;
    e->value20 = arg2;
    e->value18 = arg3;
    e->value0C = arg4;
    e->value1C = func_80106D18(e, arg0, arg1, -0x55, 0x55, -0x55, 0x55, 4, 0);
    return e;
}
