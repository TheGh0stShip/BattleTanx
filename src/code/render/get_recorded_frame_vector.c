#include "types.h"

extern s32 gDemoPlaybackActive __asm__("D_80137900");
extern f32 (*D_8033B61C)[3];

f32 *get_recorded_frame_vector(s32 index) __asm__("func_800EC700");

f32 *get_recorded_frame_vector(s32 index) {
    f32 *result;

    if (gDemoPlaybackActive != 0) {
        result = D_8033B61C[index + 4];
    } else {
        result = 0;
    }
    return result;
}
