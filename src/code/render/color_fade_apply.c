#include "types.h"

typedef struct ColorFade {
    u8 pad00[0xC];
    u8 fromR;
    u8 fromG;
    u8 fromB;
    u8 toR;
    u8 toG;
    u8 toB;
    u8 pad12[2];
    s32 duration;
    s32 elapsed;
} ColorFade;

extern void func_8007D430(s32 r, s32 g, s32 b) __asm__("func_8007D430");

void color_fade_apply(ColorFade *fade) __asm__("func_800F3234");

void color_fade_apply(ColorFade *fade) {
    s32 elapsed = fade->elapsed;
    s32 duration = fade->duration;

    func_8007D430((u8)(fade->fromR + ((fade->toR - fade->fromR) * elapsed) / duration),
                  (u8)(fade->fromG + ((fade->toG - fade->fromG) * elapsed) / duration),
                  (u8)(fade->fromB + ((fade->toB - fade->fromB) * elapsed) / duration));
}
