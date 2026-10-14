#include "types.h"

typedef struct ModeValueObject {
    u8 pad00[0xB4];
    u32 mode;
    s32 value;
} ModeValueObject;

extern void apply_mode_value(ModeValueObject *obj, s32 arg1, s32 value) __asm__("func_800E2AF0");

void apply_mode_value_if_valid(ModeValueObject *obj, s32 arg1) __asm__("func_800E2CFC");

void apply_mode_value_if_valid(ModeValueObject *obj, s32 arg1)
{
    s32 value;

    if (obj->mode != 0) {
        if (obj->mode >= 5) {
            return;
        }
        value = obj->value;
    } else {
        value = 0;
    }
    apply_mode_value(obj, arg1, value);
}
