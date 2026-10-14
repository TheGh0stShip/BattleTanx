#include "types.h"

typedef struct CallbackValue {
    u8 pad00[0xC];
    s32 value;
} CallbackValue;

s32 get_callback_value(CallbackValue *callback)
{
    return callback->value;
}
