#include "types.h"

typedef struct ActionTarget {
    u8 pad000[0x14C];
    u32 value;
} ActionTarget;

typedef struct ActionFloatSource {
    u8 pad00[0x4];
    ActionTarget *target;
    u8 pad08[0x18];
    f32 value;
} ActionFloatSource;

s32 store_action_float_as_uint(ActionFloatSource *source) __asm__("func_800E6C14");

s32 store_action_float_as_uint(ActionFloatSource *source)
{
    source->target->value = source->value;
    return -1;
}
