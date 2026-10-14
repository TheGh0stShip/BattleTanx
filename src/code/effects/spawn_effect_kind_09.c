#include "types.h"

typedef struct EffectKind09 {
    u8 pad00[0xC];
    u8 value0C;
    u8 value0D;
    s8 value0E;
    u8 pad0F[0x1];
    s16 value10;
    s16 index;
    s32 value14;
    s32 value18;
    s16 value1C;
    u8 pad1E[0x2];
} EffectKind09;

typedef struct EffectKind09Entry {
    u8 pad00[0x52];
    s16 slot;
    u8 pad54[0x4];
} EffectKind09Entry;

typedef struct EffectKind09Slot {
    u8 value00;
    u8 pad01[0x3];
} EffectKind09Slot;

typedef struct EffectKind09Context {
    u8 pad000[0x568];
    EffectKind09Entry *entries;
    EffectKind09Slot *slots;
} EffectKind09Context;

extern EffectKind09 *allocate_effect(s32 group, s32 kind, s32 size) __asm__("func_8008AD10");
extern EffectKind09Context *get_spawn_context(void) __asm__("func_800821C0");
extern s32 func_80106D18(EffectKind09 *, s32, s32, s32, s32, s32, s32, s32, s32);

EffectKind09 *spawn_effect_kind_09(s32 index, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, u16 flags, u8 value0C) __asm__("func_80091D6C");

EffectKind09 *spawn_effect_kind_09(s32 index, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, u16 flags, u8 value0C)
{
    EffectKind09 *effect;
    EffectKind09Context *context;
    EffectKind09Slot *slot;
    EffectKind09Entry *entry;

    effect = allocate_effect(0, 9, 0x20);
    if (effect == 0) {
        return 0;
    }
    effect->value0C = value0C;
    effect->index = index;
    context = get_spawn_context();
    entry = &context->entries[effect->index];
    slot = &context->slots[entry->slot];
    effect->value14 = func_80106D18(effect, arg1, arg2, arg3, arg4, arg5, arg6, 0x56, flags);
    {
        EffectKind09 *e = effect;
        u8 v = slot->value00;
        e->value0E = 0;
        e->value10 = 0;
        e->value1C = 0xA;
        e->value18 = 0;
        e->value0D = v;
        return e;
    }
}
