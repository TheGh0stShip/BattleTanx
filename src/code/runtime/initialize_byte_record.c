#include "types.h"

typedef struct ByteRecord {
    u8 first;
    u8 second;
    u8 third;
    u8 pad03;
    u8 bytes[4];
    s32 value;
} ByteRecord;

void initialize_byte_record(ByteRecord *record, u8 first, u8 second, u8 third)
    __asm__("func_800E5688");

void initialize_byte_record(ByteRecord *record, u8 first, u8 second, u8 third)
{
    record->first = first;
    record->second = second;
    record->third = third;
    record->bytes[0] = 0;
    record->bytes[1] = 0;
    record->bytes[2] = 0;
    record->bytes[3] = 0;
    record->value = 0;
    record->pad03 = 0;
}
