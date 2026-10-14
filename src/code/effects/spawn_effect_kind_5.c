#include "types.h"

typedef struct ModelGroup {
    u8 pad00[0x52];
    s16 setIndex;
    u8 pad54[0x4];
} ModelGroup;

typedef struct ModelSet {
    u8 count;
    u8 pad01[0x3];
} ModelSet;

typedef struct ModelTables {
    u8 pad000[0x568];
    ModelGroup *groups;
    ModelSet *sets;
} ModelTables;

typedef struct ModelEffect {
    u8 pad00[0xC];
    u8 flags;
    u8 value0D;
    u8 value0E;
    u8 pad0F;
    s16 value10;
    s16 value12;
    s16 group;
    u8 value16;
    u8 pad17;
    s32 handle;
    s32 value1C;
    u8 pad20[0x4];
    s32 value24;
} ModelEffect;

extern ModelEffect *allocate_effect(s32 group, s32 kind, s32 size) __asm__("func_8008AD10");
extern ModelTables *get_part_tables(void) __asm__("func_800821C0");
extern s32 func_80106D18(ModelEffect *, s32, s32, s32, s32, s32, s32, s32, s32);

ModelEffect *spawn_effect_kind_5(s32 group, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, u16 arg7,
                                 s32 flags, u8 arg9) __asm__("func_80091E98");

ModelEffect *spawn_effect_kind_5(s32 group, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, u16 arg7,
                                 s32 flags, u8 arg9) {
    ModelEffect *effect;
    ModelTables *tables;
    ModelGroup *groupInfo;
    ModelSet *set;
    s16 attr;
    u8 mode;

    effect = allocate_effect(0, 5, 0x28);
    mode = flags;
    if (effect == 0) {
        return 0;
    }
    effect->group = group;
    tables = get_part_tables();
    groupInfo = &tables->groups[effect->group];
    set = &tables->sets[groupInfo->setIndex];
    effect->handle = func_80106D18(effect, arg1, arg2, arg3, arg4, arg5, arg6, 0xF85F, arg7);
    if (flags & 8) {
        effect->value0D = set->count - 2;
    } else if (flags & 4) {
        effect->value0D = set->count - 1;
    } else {
        effect->value0D = set->count;
    }
    attr = (-((mode & 0x20) == 0) & 0x11) | 1;
    effect->value0E = 0;
    effect->value10 = 0;
    effect->flags = mode;
    effect->value12 = attr;
    effect->value24 = 0;
    effect->value1C = 0;
    effect->value16 = arg9;
    return effect;
}
