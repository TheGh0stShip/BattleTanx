#include "types.h"

typedef struct EntityRuntimeState {
    u8 pad00[0x9C];
    u32 word9C;
    u32 wordA0;
    u8 padA4[0x2A0];
    u16 half344;
    u8 pad346[2];
    u8 byte348;
    u8 pad349;
    u8 byte34A;
} EntityRuntimeState;

void entity_clear_transient_state(EntityRuntimeState *entity)
    __asm__("func_800E349C");

void entity_clear_transient_state(EntityRuntimeState *entity)
{
    entity->word9C = 0;
    entity->wordA0 = 0;
    entity->half344 = 0;
    entity->byte34A = 0;
    entity->byte348 = 0;
}
