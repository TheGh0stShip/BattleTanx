#include "types.h"

extern s32 gScrollingTextOffset __asm__("D_801416F0");

void reset_scrolling_text_offset(void) __asm__("func_8010527C");

void reset_scrolling_text_offset(void)
{
    gScrollingTextOffset = 250;
}
