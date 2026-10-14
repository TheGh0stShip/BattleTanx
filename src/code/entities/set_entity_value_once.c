#include "types.h"

typedef struct EntityValueSlot {
    u8 pad000[0x34C];
    void *value;
    u8 pad350[0x8];
    u8 valueState;
} EntityValueSlot;

void set_entity_value_once(EntityValueSlot *entity, void *value) __asm__("func_800E3C18");

void set_entity_value_once(EntityValueSlot *entity, void *value)
{
    if (entity->value == 0) {
        entity->value = value;
        entity->valueState = 0;
    }
}
