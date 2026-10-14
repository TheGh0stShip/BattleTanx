#include "types.h"

typedef struct SpawnOwner {
    u8 pad00[4];
    s32 value04;
} SpawnOwner;

typedef struct EffectKind1C {
    u8 pad00[0xC];
    u8 value0C;
    u8 slot;
    u8 pad0E[2];
    s32 value10;
    s16 delay;
    u8 pad16[2];
    s32 value18;
    f32 value1C;
    f32 value20;
    u16 value24;
    u8 pad26[2];
    SpawnOwner *owner;
    s32 value2C;
    u8 value30;
    u8 value31;
} EffectKind1C;

typedef struct SpawnCounts {
    u8 pad000[0x560];
    u8 counts[4];
} SpawnCounts;

extern EffectKind1C *allocate_effect(s32 group, s32 kind, s32 size) __asm__("func_8008AD10");
extern SpawnCounts *get_spawn_counts(void) __asm__("func_800821C0");
extern u8 D_80134E64;

s32 spawn_effect_kind_1c(SpawnOwner *owner, u16 flags, f32 arg2, f32 arg3, u16 arg4, u8 arg5) __asm__("func_8010D480");

s32 spawn_effect_kind_1c(SpawnOwner *owner, u16 flags, f32 arg2, f32 arg3, u16 arg4, u8 arg5)
{
    EffectKind1C *e;
    s32 step = 0x1E;

    e = allocate_effect(1, 0x1C, 0x34);
    if (e == 0) {
        return -1;
    }
    if (D_80134E64 == 0) {
        step = 0x2D;
    }
    e->value10 = (flags >> 2) & 3;
    e->value0C = 0;
    e->slot = flags & 3;
    e->value18 = 0;
    e->owner = owner;
    e->delay = step * ((flags >> 4) & 0xFF);
    if (owner != 0) {
        e->value2C = owner->value04;
    }
    e->value1C = arg2;
    e->value20 = arg3;
    e->value24 = arg4;
    e->value30 = arg5;
    e->value31 = (flags >> 12) & 3;
    get_spawn_counts()->counts[e->slot]++;
    return 0;
}
