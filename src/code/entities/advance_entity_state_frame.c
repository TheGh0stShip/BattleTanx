#include "types.h"

typedef struct EntityFrameRange {
    u8 pad00[0x10];
    s32 frameLimit;
    s32 frame;
} EntityFrameRange;

void advance_entity_state_frame(EntityFrameRange *entity, s32 *state)
    __asm__("func_800F2ED4");

void advance_entity_state_frame(EntityFrameRange *entity, s32 *state)
{
    entity->frame++;
    if (entity->frame >= entity->frameLimit) {
        *state = 2;
    }
}
