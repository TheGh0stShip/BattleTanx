#include "types.h"

typedef struct SlotIdEntry {
    s32 state;
    s32 id;
} SlotIdEntry;

extern SlotIdEntry D_802D5BC0[][3][100];

s32 collect_unique_slot_ids(s32 *out, s32 index) __asm__("func_80095C1C");

s32 collect_unique_slot_ids(s32 *out, s32 index)
{
    s32 count = 0;
    s32 group;
    s32 i;
    s32 j;
    s32 id;

    for (group = 0; group < 3; group++) {
        for (i = 0; i < 100; i++) {
            if (D_802D5BC0[index][group][i].state != 0x8FFF) {
                id = D_802D5BC0[index][group][i].id;
                for (j = 0; j < count; j++) {
                    if (out[j] == id) {
                        goto next;
                    }
                }
                out[count++] = id;
            }
        next:;
        }
    }
    return count;
}
