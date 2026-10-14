#include "types.h"

extern s32 get_frame_time(void) __asm__("func_8007B1DC");
extern f32 D_8007488C;
extern f32 D_80074890;

f32 ai_normalized_elapsed_time(s32 startTime) __asm__("func_800E95A8");

f32 ai_normalized_elapsed_time(s32 startTime)
{
    s32 elapsed = get_frame_time() - startTime;

    if (elapsed >= 9000) {
        return D_80074890;
    }
    return (f32)elapsed / D_8007488C;
}
