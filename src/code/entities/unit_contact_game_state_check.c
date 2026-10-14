#include "types.h"

typedef struct StateContactUnit {
    u8 pad00[0x4];
    u8 ownerId;
} StateContactUnit;

typedef struct StateContact {
    u8 pad00[0x8];
    s32 kind;
    StateContactUnit *unit;
} StateContact;

#define GAME_STATE_4 4
#define CONTACT_RESULT_9 9

extern s32 *get_current_game_state(void) __asm__("func_8007AAF4");
extern void func_800A70E0(StateContactUnit *unit, s32 object);

void unit_contact_game_state_check(s32 object, StateContact *contact, s32 unused, s32 *result)
    __asm__("func_800A7328");
void unit_event_game_state_check(s32 object, StateContact *contact, s32 event, s32 data, s32 *result)
    __asm__("func_800A739C");

void unit_contact_game_state_check(s32 object, StateContact *contact, s32 unused, s32 *result)
{
    if (contact->kind == 0) {
        func_800A70E0(contact->unit, object);
        if (*get_current_game_state() == GAME_STATE_4 && contact->unit->ownerId == 0) {
            *result = CONTACT_RESULT_9;
        }
    }
}

void unit_event_game_state_check(s32 object, StateContact *contact, s32 event, s32 data, s32 *result)
{
    if (event == 0 && contact->kind == 0) {
        func_800A70E0(contact->unit, object);
        if (*get_current_game_state() == GAME_STATE_4 && contact->unit->ownerId == 0) {
            *result = CONTACT_RESULT_9;
        }
    }
}
