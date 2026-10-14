#include "types.h"

void func_800A4D1C(void *value)
{
    s32 *counter = (s32 *)((u8 *)value + 0x208);

    if (*counter > 0) {
        (*counter)--;
    }
}
