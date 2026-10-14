#include "types.h"

extern s32 D_8033B5F0;
extern s32 D_8033B628;
extern s32 D_8033B62C;

void initialize_pending_counter(void) __asm__("func_800ECB34");

void initialize_pending_counter(void)
{
    if (D_8033B628 == -1) {
        D_8033B62C = 0x10;
        D_8033B628 = D_8033B5F0;
    }
}
