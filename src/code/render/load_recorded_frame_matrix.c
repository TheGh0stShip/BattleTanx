#include "types.h"

extern f32 D_800749E0;
extern f32 D_800749E4;
extern s32 gDemoPlaybackActive __asm__("D_80137900");
extern s32 gDemoFrame __asm__("D_8033B5F0");
extern s32 D_8033B5F4;
extern s32 D_8033B600;
extern u8 *D_8033B618;
extern f32 (*D_8033B61C)[3];

void load_recorded_frame_matrix(f32 out[4][4], s32 offset) __asm__("func_800EC7A8");

void load_recorded_frame_matrix(f32 out[4][4], s32 offset) {
    s32 i;
    s32 j;
    s32 frame;
    f32 (*src)[3];
    s32 last;

    if (gDemoPlaybackActive != 0) {
        if (offset == 0) {
            out[0][3] = 0;
            out[1][3] = 0;
            out[2][3] = 0;
            out[3][3] = D_800749E0;
            for (i = 0; i < 4; i++) {
                for (j = 0; j < 3; j++) {
                    out[i][j] = D_8033B61C[i][j];
                }
            }
            return;
        }
        frame = gDemoFrame + offset;
        last = D_8033B600 - 1;
        if (frame > last) {
            frame = last;
        }
        src = (f32 (*)[3])(D_8033B618 + frame * D_8033B5F4);
        out[0][3] = 0;
        out[1][3] = 0;
        out[2][3] = 0;
        out[3][3] = D_800749E4;
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 3; j++) {
                out[i][j] = src[i][j];
            }
        }
    }
}
