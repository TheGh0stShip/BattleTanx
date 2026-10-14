#include "types.h"

typedef struct MotionFields {
    u8 pad00[0x6];
    s16 value06;
    u8 pad08[0x1E];
    s16 value26;
    u8 pad28[0x6];
    s16 value2E;
    u8 pad30[0x1E];
    s16 value4E;
    s8 value50;
} MotionFields;

void ai_clear_member_motion_fields(MotionFields *fields) __asm__("func_800E4D2C");

void ai_clear_member_motion_fields(MotionFields *fields)
{
    fields->value2E = 0;
    fields->value4E = 0;
    fields->value06 = 0;
    fields->value26 = 0;
    fields->value50 = 0;
}
