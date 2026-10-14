#include "types.h"

typedef struct RuntimeSlot {
    void *value;
    u8 pad04[0xC];
} RuntimeSlot;

extern RuntimeSlot D_80125A70[];

s32 runtime_slot_is_active(s32 index) __asm__("func_800E51A0");

s32 runtime_slot_is_active(s32 index)
{
    return D_80125A70[index].value != 0;
}
