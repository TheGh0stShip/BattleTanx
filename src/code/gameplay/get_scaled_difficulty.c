#include "types.h"

#ifndef NULL
#define NULL 0
#endif

extern f32 D_80074390;
extern f32 D_80074394;
extern f32 D_80074398;
extern s32 D_80125858;

f32 get_scaled_difficulty(void) __asm__("func_800DDC68");

f32 get_scaled_difficulty(void) {
    f32 temp_f2;
    f32 var_f0;

    temp_f2 = (f32) D_80125858;
    var_f0 = D_80074394;
    if (D_80074390 < temp_f2) {
        var_f0 = temp_f2 * D_80074398;
    }
    return var_f0;
}
