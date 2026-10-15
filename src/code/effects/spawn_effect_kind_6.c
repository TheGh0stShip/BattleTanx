#include "types.h"

typedef struct SlotRecord {
    u8 pad00[0x54];
    u16 value54;
    u8 pad56[2];
} SlotRecord;

typedef struct SpawnSession {
    u8 pad000[0x568];
    SlotRecord *slots;
} SpawnSession;

typedef struct EffectKind6 {
    u8 pad00[0xC];
    f32 z;
    f32 x;
    s16 value14;
    s16 value16;
    s16 value18;
    u8 pad1A[2];
    s32 handle;
    s32 slot;
    s16 value24;
    s16 value26;
    u16 value28;
    s16 value2A;
    u8 pad2C;
    u8 flags;
} EffectKind6;

extern EffectKind6 *allocate_effect(s32 group, s32 kind, s32 size) __asm__("func_8008AD10");
extern SpawnSession *get_spawn_session(void) __asm__("func_800821C0");
extern s32 create_effect_motion(EffectKind6 *, s32, s32, s32, s32, s32, s32, s32, s32)
    __asm__("func_80106D18");

s32 spawn_effect_kind_6(f32 x, f32 z, s32 slot, s16 value14, u16 value28, u8 flags)
    __asm__("func_800EF984");

s32 spawn_effect_kind_6(f32 x, f32 z, s32 slot, s16 value14, u16 value28, u8 flags)
{
    EffectKind6 *effect;
    SpawnSession *session;

    effect = allocate_effect(0, 6, sizeof(EffectKind6));
    if (effect == 0) {
        return -1;
    }
    session = get_spawn_session();
    effect->slot = slot;
    effect->value24 = session->slots[slot].value54 + (flags & 1);
    if (flags & 1) {
        effect->value26 = session->slots[slot].value54 + 2;
    }
    effect->value2A = 10;
    effect->x = x;
    effect->z = z;
    effect->value18 = 0;
    effect->value16 = 0;
    effect->value14 = value14;
    effect->value28 = value28;
    effect->flags = flags;
    effect->handle = create_effect_motion(effect, x, z, 10, -10, 10, -10, 0x52, 0);
    return 0;
}
