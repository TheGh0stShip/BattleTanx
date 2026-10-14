#include "types.h"

typedef struct LinkedEffect {
    u8 pad00[0x1C];
    u8 value1C;
    u8 flags;
    u16 value1E;
} LinkedEffect;

typedef struct LinkedEffectMessage {
    u8 pad00[0x8];
    u32 kind;
    s32 value0C;
} LinkedEffectMessage;

typedef struct LinkedEffectSource {
    u8 pad00[0xC];
    u16 value0C;
    u8 pad0E[0xA];
    u8 value18;
} LinkedEffectSource;

extern void release_effect(LinkedEffect *effect) __asm__("func_8008B89C");
extern void func_80099CD8(s32, s32);

void linked_effect_handle_message(LinkedEffect *effect, LinkedEffectMessage *message,
                                  LinkedEffectSource *source, s32 *result) __asm__("func_80090B1C");

void linked_effect_handle_message(LinkedEffect *effect, LinkedEffectMessage *message,
                                  LinkedEffectSource *source, s32 *result)
{
    switch (message->kind) {
    case 34:
        if ((effect->flags & 4) && source->value18 == 0) {
            break;
        }
    case 2:
    case 12:
    case 22:
        release_effect(effect);
        *result = 0;
        break;
    case 0:
        func_80099CD8(message->value0C, 0x23);
        effect->value1C = 1;
        effect->value1E = source->value0C;
        release_effect(effect);
        *result = 4;
        break;
    case 5:
    case 18:
        release_effect(effect);
        break;
    }
}
