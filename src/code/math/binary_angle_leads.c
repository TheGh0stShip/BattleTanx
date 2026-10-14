#include "types.h"

s32 binary_angle_leads(u16 angle, u16 reference) __asm__("func_800E27E4");

s32 binary_angle_leads(u16 angle, u16 reference) {
    u16 delta;

    if (angle > reference) {
        delta = angle - reference;
        return delta < 0x8000;
    }
    delta = reference - angle;
    return delta > 0x8000;
}
