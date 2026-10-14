#include "types.h"

extern u8 D_80125D50[];

void *get_entity_record_68(s32 index) __asm__("func_80096768");

void *get_entity_record_68(s32 index)
{
    return D_80125D50 + index * 68;
}
