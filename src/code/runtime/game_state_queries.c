#include "types.h"

typedef struct GameStateRecord {
    u8 pad000[0x204];
    s32 value204;
} GameStateRecord;

extern GameStateRecord *gCurrentGameState __asm__("D_801B4ABC");
extern s32 D_80134E5C;

s32 get_game_state_value_204(void) __asm__("func_8007AAC0");
s32 get_pending_game_state(void) __asm__("func_8007AAE4");

s32 get_game_state_value_204(void)
{
    GameStateRecord *state;

    state = gCurrentGameState;
    if (state != 0) {
        return state->value204;
    }
    return 0;
}

s32 get_pending_game_state(void)
{
    return D_80134E5C;
}
