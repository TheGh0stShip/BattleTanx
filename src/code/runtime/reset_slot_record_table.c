#include "types.h"

typedef struct SlotRecord {
    s32 value00;
    s32 value04;
} SlotRecord;

extern SlotRecord gSlotRecords[][3][100] __asm__("D_802D5BC0");

extern s32 get_difficulty_level(void) __asm__("func_8007AAA0");

void reset_slot_record_table(void) __asm__("func_8009491C");

void reset_slot_record_table(void)
{
    s32 i;
    s32 j;
    s32 k;

    for (i = 0; i < get_difficulty_level(); i++) {
        for (j = 0; j < 3; j++) {
            for (k = 0; k < 100; k++) {
                gSlotRecords[i][j][k].value00 = 0x8FFF;
            }
        }
    }
}
