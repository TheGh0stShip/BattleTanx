#include "types.h"

s32 wrap_angle_delta(s32 from, s32 to) __asm__("func_800E289C");

s32 wrap_angle_delta(s32 from, s32 to) {
    to -= from;
    if (to > 0) {
        if (to > 0x8000) {
            return to - 0xFFFF;
        }
        return to;
    }
    if (to < -0x8000) {
        return to + 0xFFFF;
    }
    return to;
}
