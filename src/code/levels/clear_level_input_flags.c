#include "types.h"

#ifndef NULL
#define NULL 0
#endif

extern void *D_80135834;

void clear_level_input_flags(void) __asm__("func_800DDBCC");

void clear_level_input_flags(void) {
    if (D_80135834 != NULL) {
        (*(s8 *)((s8 *)((*(void **)((s8 *)(D_80135834) + (0x1C)))) + (9))) = 0;
        (*(s8 *)((s8 *)((*(void **)((s8 *)(D_80135834) + (0x1C)))) + (0xA))) = 0;
        (*(s8 *)((s8 *)((*(void **)((s8 *)(D_80135834) + (0x1C)))) + (0xB))) = 0;
        (*(s8 *)((s8 *)((*(void **)((s8 *)(D_80135834) + (0x1C)))) + (0xE))) = 0;
        (*(s8 *)((s8 *)((*(void **)((s8 *)(D_80135834) + (0x1C)))) + (0xD))) = 0;
        (*(s8 *)((s8 *)((*(void **)((s8 *)(D_80135834) + (0x1C)))) + (0xC))) = 0;
    }
}
