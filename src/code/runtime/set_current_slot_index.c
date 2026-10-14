#include "types.h"

typedef struct CurrentSlotOwner {
    u8 pad00[0x3C];
    s32 current;
} CurrentSlotOwner;

void set_current_slot_index(CurrentSlotOwner *owner, s16 index)
{
    owner->current = index;
}
