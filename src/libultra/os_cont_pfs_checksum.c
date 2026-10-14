#include "types.h"

u16 __osSumcalc(u8 *data, s32 length)
{
    s32 i;
    u32 sum;
    u8 *current;

    sum = 0;
    current = data;
    for (i = 0; i < length; i++) {
        sum += *current++;
        sum &= 0xFFFF;
    }
    return sum;
}

s32 __osIdCheckSum(u16 *data, u16 *checksum, u16 *inverted_checksum)
{
    u16 value;
    u32 offset;

    value = 0;
    *checksum = *inverted_checksum = 0;
    for (offset = 0; offset < 0x1C; offset += 2) {
        value = *(u16 *)((u32)data + offset);
        *checksum += value;
        *inverted_checksum += ~value;
    }
    return 0;
}
