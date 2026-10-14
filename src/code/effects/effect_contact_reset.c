#include "types.h"

typedef struct ResetEffect {
    u8 pad00[0x1C];
    s8 active;
} ResetEffect;

typedef struct ResetContact {
    u8 pad00[0x8];
    s32 kind;
} ResetContact;

#define CONTACT_KIND_2 2
#define CONTACT_KIND_16 0x16

void effect_contact_reset(ResetEffect *effect, ResetContact *contact, s32 unused, s32 *result)
    __asm__("func_8008CE74");
void effect_event_reset(ResetEffect *effect, ResetContact *contact, s32 event, s32 data, s32 *result)
    __asm__("func_8008CE9C");

void effect_contact_reset(ResetEffect *effect, ResetContact *contact, s32 unused, s32 *result)
{
    switch (contact->kind) {
    case CONTACT_KIND_2:
    case CONTACT_KIND_16:
        *result = 0;
        effect->active = 0;
        break;
    }
}

void effect_event_reset(ResetEffect *effect, ResetContact *contact, s32 event, s32 data, s32 *result)
{
    if (event != 0) {
        return;
    }
    switch (contact->kind) {
    case CONTACT_KIND_2:
    case CONTACT_KIND_16:
        *result = 0;
        effect->active = 0;
        break;
    }
}
