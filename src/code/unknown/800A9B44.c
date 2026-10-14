#include "types.h"

s32 func_800A9B44(u8 *data) {
    s32 sum = 0;
    u8 *current = data + 4;
    u8 *end = data + 0x100;

    do {
        sum += *current++;
    } while ((s32)current < (s32)end);
    return sum;
}
