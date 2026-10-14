#include "types.h"

extern s32 get_entity_capacity(void) __asm__("func_8007AAB0");
extern s32 D_8033AAC8[];

void set_all_entity_slot_flags(void) __asm__("func_800E4A38");

void set_all_entity_slot_flags(void) {
    u16 i;

    for (i = 0; i < get_entity_capacity(); i++) {
        D_8033AAC8[i] = 1;
    }
}
