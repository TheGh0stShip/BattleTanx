#include "types.h"
typedef struct EntityTarget { u8 pad000[0x44C]; s32 timer; void *target; } EntityTarget;
extern void *D_801B4AA0;
void refresh_entity_target(EntityTarget *entity) __asm__("func_8009D4B4");
void refresh_entity_target(EntityTarget *entity) { if (entity->target != D_801B4AA0) { *(s32 *)((u8 *)entity + 0x94) = 0; entity->timer = 0; entity->target = D_801B4AA0; } }
