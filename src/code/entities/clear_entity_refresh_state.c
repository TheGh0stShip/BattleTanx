#include "types.h"
typedef struct Entity { u8 pad000[0x48]; u8 refresh[0x20]; u8 pad068[0x88]; u8 active; } Entity;
extern void set_refresh_record_value18(void *record, s32 value) __asm__("func_80078634");
void clear_entity_refresh_state(Entity *entity, s32 value) __asm__("func_800A4D34");
void clear_entity_refresh_state(Entity *entity, s32 value) { entity->active = 0; set_refresh_record_value18(entity->refresh, value); }
