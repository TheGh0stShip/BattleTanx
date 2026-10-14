#include "types.h"

#ifndef NULL
#define NULL 0
#endif

s32 func_800E1818(s32, u16 *, u16 *);
extern f32 D_80074428;
extern void *D_80135834;

void get_waypoint_midpoint(s32 arg0, void *arg1) __asm__("func_800E0B00");

void get_waypoint_midpoint(s32 arg0, void *arg1) {
    u16 sp10;
    u16 sp12;
    void *var_a1;
    void *var_v1;

    func_800E1818(arg0 & 0xFFFF, &sp10, &sp12);
    var_a1 = NULL;
    if ((sp10 < (u16) (*(u16 *)((s8 *)(D_80135834) + (8)))) && (sp10 != 0)) {
        var_a1 = (*(s32 *)((s8 *)(D_80135834) + (0xC))) + (sp10 * 8);
    }
    if (sp12 >= (u16) (*(u16 *)((s8 *)(D_80135834) + (8)))) {
        var_v1 = NULL;
    } else if (sp12 == 0) {
        var_v1 = NULL;
    } else {
        var_v1 = (*(s32 *)((s8 *)(D_80135834) + (0xC))) + (sp12 * 8);
    }
    (*(f32 *)((s8 *)(arg1) + (4))) = (f32) (((*(f32 *)((s8 *)(var_a1) + (4))) + (*(f32 *)((s8 *)(var_v1) + (4)))) / D_80074428);
    (*(f32 *)((s8 *)(arg1) + (0))) = (f32) (((*(f32 *)((s8 *)(var_a1) + (0))) + (*(f32 *)((s8 *)(var_v1) + (0)))) / D_80074428);
}
