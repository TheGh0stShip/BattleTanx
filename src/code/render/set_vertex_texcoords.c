#include "types.h"

#ifndef NULL
#define NULL 0
#endif

void *func_8007F060();

void set_vertex_texcoords(s32 arg0, s32 arg1) __asm__("func_800A9F80");

void set_vertex_texcoords(s32 arg0, s32 arg1) {
    void *temp_v0;

    temp_v0 = func_8007F060();
    (*(s16 *)((s8 *)(temp_v0) + (0x1A))) = (s16) (arg0 << 6);
    (*(s16 *)((s8 *)(temp_v0) + (0x1C))) = (s16) (arg1 << 6);
}
