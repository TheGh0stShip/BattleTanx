#include "types.h"

typedef struct EntityState {
    u8 pad00[0x350];
    u8 state;
} EntityState;

s32 entity_state_is_one(const EntityState *entity) __asm__("func_800E3470");

s32 entity_state_is_one(const EntityState *entity)
{
    return entity->state == 1;
}
