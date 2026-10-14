#include "types.h"

typedef struct ContactEffect {
    u8 pad00[0x18];
    s32 resultValue;
    u8 pad1C[0x4];
    u8 consumed;
    u8 pad21[0xB];
    s32 ownerClass;
} ContactEffect;

typedef struct ContactRecord {
    u8 pad00[0x8];
    s32 kind;
    void *unit;
} ContactRecord;

typedef struct ContactResult {
    s32 action;
    s32 value;
} ContactResult;

extern u8 get_owner_class(void *unit) __asm__("func_8009FBE4");
extern s32 entity_state_is_two(void *unit) __asm__("func_800E3460");
extern void func_8008B89C();

void effect_handle_unit_contact(ContactEffect *effect, ContactRecord *contact, void *unused, ContactResult *result)
    __asm__("func_80091608");
void effect_handle_unit_contact_event(ContactEffect *effect, ContactRecord *contact, s32 event, s32 data,
                                      ContactResult *result) __asm__("func_800916B8");

void effect_handle_unit_contact(ContactEffect *effect, ContactRecord *contact, void *unused, ContactResult *result)
{
    if (effect->consumed == 0 && contact->kind == 0
        && get_owner_class(contact->unit) != effect->ownerClass
        && entity_state_is_two(contact->unit) == 0) {
        result->action = 3;
        result->value = effect->resultValue;
        effect->consumed = 1;
        func_8008B89C(effect);
        return;
    }
    result->action = 1;
}

void effect_handle_unit_contact_event(ContactEffect *effect, ContactRecord *contact, s32 event, s32 data,
                                      ContactResult *result)
{
    if (event != 0) {
        return;
    }
    if (effect->consumed == 0 && contact->kind == 0
        && get_owner_class(contact->unit) != effect->ownerClass
        && entity_state_is_two(contact->unit) == 0) {
        result->action = 3;
        result->value = effect->resultValue;
        effect->consumed = 1;
        func_8008B89C(effect);
        return;
    }
    result->action = 1;
}
