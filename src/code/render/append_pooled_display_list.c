#include "types.h"

typedef struct GfxWord {
    u32 w0;
    u32 w1;
} GfxWord;

extern void bcopy(const void *src, void *dst, s32 size) __asm__("func_801106A0");
extern s16 gDisplayListPoolUsed __asm__("D_80125800");
extern u8 gDisplayListPoolBank __asm__("D_80125802");
extern GfxWord gDisplayListPool[2][0x400] __asm__("D_801C2F40");

GfxWord *append_pooled_display_list(GfxWord *src, s32 count, GfxWord *next) __asm__("func_8008067C");

GfxWord *append_pooled_display_list(GfxWord *src, s32 count, GfxWord *next) {
    GfxWord *dst;

    if (gDisplayListPoolUsed + count + 1 > 0x400) {
        return next;
    } else {
        s16 used = gDisplayListPoolUsed;
        gDisplayListPoolUsed += count + 1;
        dst = &gDisplayListPool[gDisplayListPoolBank][used];
        bcopy(src, dst, count * sizeof(GfxWord));
        {
            GfxWord *g = dst + count;
            g->w0 = 0x06010000;
            g->w1 = (u32)next;
        }
        return dst;
    }
}
