#include "types.h"

typedef struct Mtx {
    s32 m[4][4];
} Mtx;

#define FIX32TOF(value) ((f32)(value) / (f32)0x10000)

void guMtxL2F(f32 destination[4][4], Mtx *source)
{
    s32 i;
    s32 j;
    u32 first;
    u32 second;
    u32 *integer;
    u32 *fraction;
    s32 signedFirst;
    s32 signedSecond;

    integer = (u32 *)&source->m[0][0];
    fraction = (u32 *)&source->m[2][0];
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 2; j++) {
            first = (*integer & 0xFFFF0000) | ((*fraction >> 16) & 0xFFFF);
            second = ((*(integer++) << 16) & 0xFFFF0000) | (*(fraction++) & 0xFFFF);
            signedFirst = *((s32 *)&first);
            signedSecond = *((s32 *)&second);
            destination[i][j * 2] = FIX32TOF(signedFirst);
            destination[i][j * 2 + 1] = FIX32TOF(signedSecond);
        }
    }
}
