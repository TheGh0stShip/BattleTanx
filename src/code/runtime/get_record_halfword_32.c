#include "types.h"

typedef struct RecordHalfword32 {
    u8 pad00[0x32];
    s16 value;
} RecordHalfword32;

s16 get_record_halfword_32(RecordHalfword32 *record)
{
    return record->value;
}
