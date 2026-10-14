#include "types.h"

typedef struct LinkRecord {
    u8 pad00[3];
    u8 byte3;
    u8 byte4;
    u8 byte5;
    u8 byte6;
    u8 byte7;
    u32 word8;
} LinkRecord;

void clear_link_record(LinkRecord *record) __asm__("func_800E566C");

void clear_link_record(LinkRecord *record)
{
    record->byte4 = 0;
    record->byte5 = 0;
    record->byte6 = 0;
    record->byte7 = 0;
    record->word8 = 0;
    record->byte3 = 0;
}
