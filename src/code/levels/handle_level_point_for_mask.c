#include "types.h"

extern s32 get_difficulty_level(void) __asm__("func_8007AAA0");
extern void handle_level_point(u8 *level, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 index) __asm__("func_800824E4");

void handle_level_point_for_mask(u8 *level, s32 arg1, s32 arg2, s32 arg3, s32 arg4, u8 mask) __asm__("func_800849B0");

void handle_level_point_for_mask(u8 *level, s32 arg1, s32 arg2, s32 arg3, s32 arg4, u8 mask) {
    s32 i = 0;
    s32 count = get_difficulty_level();

    for (; i < count; i++) {
        if ((mask >> i) & 1) {
            handle_level_point(level, arg1, arg2, 0, arg3, arg4, i);
        }
    }
}
