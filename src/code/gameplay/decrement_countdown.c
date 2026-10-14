#include "types.h"

typedef struct CountdownOwner {
    u8 pad00[0x208];
    s32 countdown;
} CountdownOwner;

void decrement_countdown(CountdownOwner *owner) __asm__("func_800A4D1C");

void decrement_countdown(CountdownOwner *owner)
{
    if (owner->countdown > 0) {
        owner->countdown--;
    }
}
