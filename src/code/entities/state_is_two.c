#include "types.h"

typedef struct EntityState {
    u8 pad00[0x350];
    u8 state;
} EntityState;

s32 entity_state_is_two(const EntityState *entity) __asm__("func_800E3460");

s32 entity_state_is_two(const EntityState *entity)
{
    return entity->state == 2;
}
