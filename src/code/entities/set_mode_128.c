#include "types.h"

typedef struct EntityMode {
    u8 pad00[0x40A];
    u8 mode;
} EntityMode;

s32 entity_set_mode_128(EntityMode *entity) __asm__("func_800E2620");

s32 entity_set_mode_128(EntityMode *entity)
{
    s32 mode = 0x80;

    entity->mode = mode;
    return mode;
}
