#include "types.h"

typedef struct AttachedEffect {
    u8 pad00[0xC];
    s32 position0C;
    s32 position10;
    s32 owner;
    s32 handle;
    u8 state;
    u8 flags;
} AttachedEffect;

#define ATTACHED_EFFECT_KIND 0x12

extern AttachedEffect *allocate_effect(s32 group, s32 kind, s32 size) __asm__("func_8008AD10");
extern s32 func_80106D18(AttachedEffect *effect, s32 position0C, s32 position10, s32 arg3, s32 arg4, s32 arg5,
                         s32 arg6, s32 mode, s32 id);

s32 spawn_attached_effect(s32 owner, s32 position0C, s32 position10, u16 id, s32 arg4, s32 arg5, s32 arg6,
                          s32 arg7, u8 flags) __asm__("func_800907CC");

s32 spawn_attached_effect(s32 owner, s32 position0C, s32 position10, u16 id, s32 arg4, s32 arg5, s32 arg6,
                          s32 arg7, u8 flags)
{
    AttachedEffect *effect;

    effect = allocate_effect(0, ATTACHED_EFFECT_KIND, sizeof(AttachedEffect));
    if (effect == 0) {
        return -1;
    }
    effect->owner = owner;
    effect->flags = flags;
    effect->handle = func_80106D18(effect, position0C, position10, arg4, arg5, arg6, arg7,
                                   (flags & 1) ? 0x20 : 0xF95F, id);
    effect->position0C = position0C;
    effect->position10 = position10;
    effect->state = 0;
    return 0;
}
