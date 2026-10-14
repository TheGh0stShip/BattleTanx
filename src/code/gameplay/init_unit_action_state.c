#include "types.h"

typedef struct ActionState {
    s32 value00;
    s32 *value04;
    s32 value08;
    s32 value0C;
    s32 *value10;
    s32 value14;
} ActionState;

typedef struct ActionUnit {
    u8 pad000[0x344];
    s16 value344;
    u8 pad346[2];
    s8 value348;
    u8 pad349;
    s8 value34A;
} ActionUnit;

extern ActionUnit *get_unit(s16 id) __asm__("func_800A03B8");
extern s32 *func_800E377C(s32 parameter, s32 *list, s32 enabled);

void init_unit_action_state(ActionState *state, s16 unitId, u16 parameter, s32 enabled)
    __asm__("func_800E3980");

void init_unit_action_state(ActionState *state, s16 unitId, u16 parameter, s32 enabled) {
    s32 *list = &state->value08;
    s32 *entry;

    state->value10 = 0;
    state->value14 = -1;
    state->value0C = 0;
    state->value08 = 0;
    state->value04 = 0;
    if (enabled != 0) {
        ActionUnit *unit;

        state->value00 = 6;
        unit = get_unit(unitId);
        unit->value344 = 0;
        unit->value34A = 0;
        unit->value348 = 0;
    } else {
        state->value00 = 2;
        state->value04 = list;
    }
    entry = func_800E377C(parameter, list, enabled);
    if (entry != 0) {
        state->value10 = entry;
        state->value14 = entry[1];
    }
}
