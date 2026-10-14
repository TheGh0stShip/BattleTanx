#include "types.h"

typedef struct Field1CRecord {
    u8 pad00[0x1C];
    s32 value;
} Field1CRecord;

void clear_field_1c_if_disabled(Field1CRecord *record, s32 enabled) __asm__("func_8010CB4C");

void clear_field_1c_if_disabled(Field1CRecord *record, s32 enabled)
{
    if (enabled == 0) {
        record->value = 0;
    }
}
