#include "types.h"

typedef struct MemberLinkState {
    s32 word0;
    s32 word4;
    f32 scale;
    s32 wordC;
    u16 half10;
    u16 half12;
    u8 byte14;
    u8 byte15;
    u8 enabled;
} MemberLinkState;

void initialize_member_link_state(MemberLinkState *state) __asm__("func_800E1EE0");

void initialize_member_link_state(MemberLinkState *state)
{
    state->wordC = 0;
    state->word4 = 0;
    state->word0 = 0;
    state->half10 = 0;
    state->half12 = 0;
    state->byte14 = 0;
    state->byte15 = 0;
    state->enabled = 1;
    state->scale = 1.0f;
}
