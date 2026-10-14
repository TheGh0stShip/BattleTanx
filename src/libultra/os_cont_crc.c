#include "types.h"

#define ADDRESS_CRC_GENERATOR 0x15
#define ADDRESS_CRC_MASK 0x1F
#define DATA_CRC_GENERATOR 0x85

u8 __osContAddressCrc(u16 addr)
{
    u8 temp = 0;
    u8 temp2;
    int i;

    for (i = 0; i < 16; i++) {
        temp2 = (temp & 0x10) ? ADDRESS_CRC_GENERATOR : 0;
        temp <<= 1;
        temp |= (u8)((addr & 0x400) ? 1 : 0);
        addr <<= 1;
        temp ^= temp2;
    }
    return temp & ADDRESS_CRC_MASK;
}

u8 __osContDataCrc(u8 *data)
{
    u8 temp = 0;
    u8 temp2;
    int i, j;

    for (i = 0; i <= 32; i++, data++) {
        for (j = 7; j >= 0; j--) {
            temp2 = (temp & 0x80) ? DATA_CRC_GENERATOR : 0;
            temp <<= 1;
            if (i == 32)
                temp |= 0;
            else
                temp |= ((*data & (1 << j)) ? 1 : 0);
            temp ^= temp2;
        }
    }
    return temp;
}
