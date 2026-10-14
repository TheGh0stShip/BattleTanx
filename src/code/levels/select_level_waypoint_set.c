#include "types.h"

#ifndef NULL
#define NULL 0
#endif

s32 func_800E09B0(s32);
s32 func_800E1648(s32, s32 *);
extern s16 D_80135838;
extern s32 D_8013583C;
extern s32 D_80328450;

void select_level_waypoint_set(s16 arg0) __asm__("func_800E055C");

void select_level_waypoint_set(s16 arg0) {
    s32 temp_v0;

    D_80135838 = arg0;
    temp_v0 = func_800E09B0(arg0 & 0xFFFF);
    D_8013583C = temp_v0;
    func_800E1648(temp_v0, &D_80328450);
}
