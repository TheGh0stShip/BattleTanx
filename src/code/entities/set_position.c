#include "types.h"

typedef struct PositionedEntity {
    u8 pad00[0x30];
    f32 position[3];
} PositionedEntity;

void entity_set_position(PositionedEntity *entity, f32 *position)
    __asm__("func_800A76A0");

void entity_set_position(PositionedEntity *entity, f32 *position)
{
    f32 value;

    value = position[0];
    entity->position[0] = value;
    value = position[1];
    entity->position[1] = value;
    value = position[2];
    entity->position[2] = value;
}
