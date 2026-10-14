#include "types.h"

typedef struct EntityFrameState {
    u8 pad00[0x24];
    s32 frame;
} EntityFrameState;

void finish_entity_state_after_frame(EntityFrameState *entity, s32 *state)
    __asm__("func_800F2614");

void finish_entity_state_after_frame(EntityFrameState *entity, s32 *state)
{
    if (entity->frame >= 16) {
        *state = 2;
    }
}
