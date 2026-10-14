#include "types.h"

typedef struct HalfwordPairRecord {
    u8 pad00[8];
    u16 first;
    u16 second;
} HalfwordPairRecord;

void copy_halfword_pair(const HalfwordPairRecord *source,
                        HalfwordPairRecord *destination)
    __asm__("func_800917C4");

void copy_halfword_pair(const HalfwordPairRecord *source,
                        HalfwordPairRecord *destination)
{
    u16 value;

    value = source->first;
    destination->first = value;
    value = source->second;
    destination->second = value;
}
