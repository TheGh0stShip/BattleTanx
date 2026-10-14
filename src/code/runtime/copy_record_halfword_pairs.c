#include "types.h"

typedef struct RecordHalfwordPair {
    u8 pad00[8];
    u16 value8;
    u16 valueA;
    u8 pad0C[4];
} RecordHalfwordPair;

void copy_record_halfword_pairs(s32 count, RecordHalfwordPair *source,
                                RecordHalfwordPair *destination)
    __asm__("func_800917D8");

void copy_record_halfword_pairs(s32 count, RecordHalfwordPair *source,
                                RecordHalfwordPair *destination)
{
    s32 i;

    for (i = 0; i < count; i++) {
        destination[i].value8 = source[i].value8;
        destination[i].valueA = source[i].valueA;
    }
}
