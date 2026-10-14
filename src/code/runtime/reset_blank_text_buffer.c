#include "types.h"

extern s32 D_80328420;
extern s32 D_80328424;
extern s32 D_80328428;
extern s8 D_80328430[];
extern s8 D_8032843A;
extern s32 D_8032843C;
extern s32 D_80328440;

void reset_blank_text_buffer(void) __asm__("func_800DAD60");

void reset_blank_text_buffer(void) {
    s32 i;
    s32 fill = ' ';
    s8 *cursor;

    D_80328420 = 0;
    D_80328424 = 0;
    D_80328440 = -1;
    D_8032843C = 0;
    D_8032843A = 0;
    D_80328428 = 0;
    for (i = 9, cursor = &D_80328430[9]; i >= 0; i--, cursor--) {
        *cursor = fill;
    }
}
