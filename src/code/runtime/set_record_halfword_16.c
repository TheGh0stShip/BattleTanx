#include "types.h"

typedef struct RecordHalfword16 {
    u8 pad00[0x16];
    s16 value;
} RecordHalfword16;

void set_record_halfword_16(void *arg0, RecordHalfword16 *record, s16 value)
{
    record->value = value;
}
