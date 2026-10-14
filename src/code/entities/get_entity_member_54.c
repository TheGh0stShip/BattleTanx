#include "types.h"

typedef struct EntityMember54 {
    u8 pad00[0x54];
    u8 member54[1];
} EntityMember54;

void *get_entity_member_54(EntityMember54 *entity) __asm__("func_8009E39C");

void *get_entity_member_54(EntityMember54 *entity)
{
    return entity->member54;
}
