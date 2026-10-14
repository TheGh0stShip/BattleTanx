#include "types.h"

typedef struct EntityCountdown {
    u8 pad00[0x3C];
    u8 countdown;
} EntityCountdown;

void decrement_entity_countdown(EntityCountdown *entity, s32 *state) __asm__("func_800F16E4");

void decrement_entity_countdown(EntityCountdown *entity, s32 *state)
{
    entity->countdown--;
    if (entity->countdown == 0) {
        *state = 2;
    }
}
