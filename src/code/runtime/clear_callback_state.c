#include "types.h"

typedef struct CallbackState {
    u8 pad00[0x18];
    u32 state;
} CallbackState;

void clear_callback_state(CallbackState *callback) __asm__("func_800F2120");

void clear_callback_state(CallbackState *callback)
{
    callback->state = 0;
}
