#include "types.h"

typedef struct RecordByte0C {
    u8 pad00[0xC];
    u8 value;
} RecordByte0C;

extern void func_800A6E30(RecordByte0C *record, u8 value);

void dispatch_record_byte_0c(RecordByte0C *record) __asm__("func_800A70BC");

void dispatch_record_byte_0c(RecordByte0C *record)
{
    func_800A6E30(record, record->value);
}
