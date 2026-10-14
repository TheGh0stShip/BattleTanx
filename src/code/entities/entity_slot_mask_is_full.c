#include "types.h"

extern s32 D_802E17A8[];
extern u16 D_802E17D8[];

s32 entity_slot_mask_is_full(s32 index) __asm__("func_80096834");

s32 entity_slot_mask_is_full(s32 index)
{
    return (D_802E17D8[D_802E17A8[index] * 3] & 0xF) == 0xF;
}
