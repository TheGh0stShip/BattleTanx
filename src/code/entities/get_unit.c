#include "types.h"

extern u8 D_802D8180[];

void *get_unit(s16 id) __asm__("func_800A03B8");

void *get_unit(s16 id)
{
    if (id == 0xFF) {
        return 0;
    }
    return D_802D8180 + id * 1288;
}
