#include "types.h"

typedef struct EffectRecord {
    u8 pad00[0x2C];
    struct EffectRecord *next;
} EffectRecord;

typedef struct EffectEntity {
    u8 pad00[0x1AE];
    u8 ownerId;
} EffectEntity;

typedef struct EffectSubject {
    u8 pad00[0x4];
    u8 entityId;
    u8 pad05[0x93];
    EffectRecord *effects;
} EffectSubject;

typedef struct EffectOwnerRef {
    u8 pad00[0xC];
    u8 entityId;
} EffectOwnerRef;

typedef struct EffectSelection {
    u8 pad00[0x8];
    void *active;
    EffectSubject *subject;
} EffectSelection;

extern EffectEntity *get_effect_entity(u8 entityId) __asm__("func_800A6688");
extern void release_effect(EffectRecord *effect, u8 ownerId) __asm__("func_800A6E30");

void release_matching_owner_effects(EffectOwnerRef *owner, EffectSelection *selection, s32 blocked)
    __asm__("func_800A74AC");

void release_matching_owner_effects(EffectOwnerRef *owner, EffectSelection *selection, s32 blocked)
{
    EffectSubject *subject;
    EffectEntity *subjectEntity;
    EffectRecord *effect;
    EffectRecord *next;

    if (blocked == 0 && selection->active == 0) {
        subject = selection->subject;
        subjectEntity = get_effect_entity(subject->entityId);
        if (subjectEntity->ownerId == get_effect_entity(owner->entityId)->ownerId) {
            effect = subject->effects;
            while (effect != 0) {
                next = effect->next;
                release_effect(effect, owner->entityId);
                effect = next;
            }
            subject->effects = 0;
        }
    }
}
