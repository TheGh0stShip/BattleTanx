#include "types.h"

typedef struct RuntimePair {
    u16 first;
    u16 second;
} RuntimePair;

typedef struct RuntimeRecord {
    u8 pad00[0x10];
    RuntimePair *pairs;
    u8 pad14[0xC];
    s32 value20;
} RuntimeRecord;

extern RuntimeRecord *D_80135834;

void set_runtime_record_value20(s32 value) __asm__("func_800E097C");
void clear_runtime_record_pair(u16 index) __asm__("func_800E098C");

void set_runtime_record_value20(s32 value)
{
    D_80135834->value20 = value;
}

void clear_runtime_record_pair(u16 index)
{
    register RuntimePair *pair __asm__("$2");

    pair = &D_80135834->pairs[index];
    pair->first = 0;
    pair->second = 0;
}
