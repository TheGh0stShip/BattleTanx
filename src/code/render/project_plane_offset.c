#include "types.h"

#ifndef NULL
#define NULL 0
#endif

void project_plane_offset(void *arg0, void *arg1, f32 arg2, f32 arg3, void *arg4) __asm__("func_800786F4");

void project_plane_offset(void *arg0, void *arg1, f32 arg2, f32 arg3, void *arg4) {
    (*(f32 *)((s8 *)(arg4) + (0))) = (f32) ((*(f32 *)((s8 *)(arg1) + (0))) + (arg2 * (*(f32 *)((s8 *)(arg0) + (0x48)))) + (arg3 * (*(f32 *)((s8 *)(arg0) + (0x4C)))));
    (*(f32 *)((s8 *)(arg4) + (4))) = (f32) ((*(f32 *)((s8 *)(arg1) + (4))) + (arg2 * (*(f32 *)((s8 *)(arg0) + (0x58)))) + (arg3 * (*(f32 *)((s8 *)(arg0) + (0x5C)))));
    (*(f32 *)((s8 *)(arg4) + (8))) = (f32) ((*(f32 *)((s8 *)(arg1) + (8))) + (arg2 * (*(f32 *)((s8 *)(arg0) + (0x68)))) + (arg3 * (*(f32 *)((s8 *)(arg0) + (0x6C)))));
}
