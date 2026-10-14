#include "types.h"

/* One bit of a restoring square root: try setting bit `shift` of the root. */
#define SQRT_STEP(shift)                                                   \
    trial = (root << ((shift) + 1)) + (1 << (2 * (shift)));               \
    if (value >= trial) {                                                  \
        root += 1 << (shift);                                              \
        value -= trial;                                                    \
    }

u32 integer_sqrt(u32 value) __asm__("func_80109094");

u32 integer_sqrt(u32 value)
{
    u32 root;
    u32 trial;

    root = 0;
    SQRT_STEP(15)
    SQRT_STEP(14)
    SQRT_STEP(13)
    SQRT_STEP(12)
    SQRT_STEP(11)
    SQRT_STEP(10)
    SQRT_STEP(9)
    SQRT_STEP(8)
    SQRT_STEP(7)
    SQRT_STEP(6)
    SQRT_STEP(5)
    SQRT_STEP(4)
    SQRT_STEP(3)
    SQRT_STEP(2)
    SQRT_STEP(1)
    trial = (root << 1) + 1;
    return root + (value >= trial);
}
