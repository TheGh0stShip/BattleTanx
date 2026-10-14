#include "types.h"

typedef struct HalfwordRecord {
    u16 pad00;
    u16 first;
    u16 second;
    u8 pad06[0xA];
    u16 third;
} HalfwordRecord;

void set_record_halfwords(HalfwordRecord *record, u16 first, u16 second,
                          u16 third) __asm__("func_80109354");

void set_record_halfwords(HalfwordRecord *record, u16 first, u16 second,
                          u16 third)
{
    record->first = first;
    record->second = second;
    record->third = third;
}
