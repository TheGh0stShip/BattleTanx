#include "types.h"

#ifndef NULL
#define NULL 0
#endif

s32 func_800A942C();
s32 func_800A9484(s32);
s32 func_800A95C0(s32, s32 *, s32 *);
s32 func_800A9B70(s32, s32 *);
extern s32 D_80126710;
extern s32 D_80327F50;
extern s32 D_8032815C;
extern s32 D_80328160;
extern s32 D_80328164;
extern s32 D_80328168;

s32 controller_pak_probe_status(void) __asm__("func_800CF374");

s32 controller_pak_probe_status(void) {
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;

    temp_v0 = func_800A942C();
    D_8032815C = temp_v0;
    if (temp_v0 != 0) {
        temp_v0_2 = func_800A9484(temp_v0);
        D_80328160 = temp_v0_2;
        if (((temp_v0_2 == 2) | (temp_v0_2 == 0)) != 0) {
            temp_v0_3 = func_800A95C0(D_8032815C, &D_80327F50, &D_80328168);
            D_80328160 = temp_v0_3;
            if (temp_v0_3 == 0) {
                D_80328160 = func_800A9B70(D_8032815C, &D_80328164);
                goto block_5;
            }
        } else {
            goto block_5;
        }
    } else {
        D_80328160 = 0;
block_5:
        if (D_80328160 == 0) {
            D_80328160 = D_80126710;
        }
    }
    return D_80328160;
}
