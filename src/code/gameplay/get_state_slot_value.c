#include "types.h"

typedef struct StateValueInfo {
    u8 pad00[0x3C];
    u8 value;
} StateValueInfo;

typedef struct StateValueSet {
    s32 type;
    s32 pad04[2];
    s32 entityIds[0x72];
    s32 values[1];
} StateValueSet;

extern StateValueInfo *get_entity_info(s32 id) __asm__("func_800A68C0");

s32 get_state_slot_value(StateValueSet *state, s32 slot) __asm__("func_8007D1F8");

s32 get_state_slot_value(StateValueSet *state, s32 slot)
{
    switch (state->type) {
    case 0:
    case 1:
    case 2:
    case 9:
        return state->values[slot];
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
        if (slot == 0) {
            return get_entity_info(state->entityIds[0])->value;
        }
        {
            s32 id = state->entityIds[slot];

            if (id == state->entityIds[0]) {
                return get_entity_info(9)->value;
            }
            return get_entity_info(id)->value;
        }
    case 8:
        return 5 | (-(slot != 0) & 7);
    default:
        return 0;
    }
}
