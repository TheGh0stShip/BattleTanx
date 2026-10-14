#include "types.h"

typedef struct Gfx {
    u32 word0;
    u32 word1;
} Gfx;

#define TEXT_GFX_COMMAND(packet, w0, w1) \
    {                                    \
        Gfx *command = (packet)++;       \
        command->word0 = (w0);           \
        command->word1 = (w1);           \
    }

void begin_text_draw(Gfx **gfxp) __asm__("func_8010698C");

void begin_text_draw(Gfx **gfxp)
{
    Gfx *gfx = *gfxp;

    TEXT_GFX_COMMAND(gfx, 0xE7000000, 0);          /* pipe sync */
    TEXT_GFX_COMMAND(gfx, 0xBA001402, 0);          /* cycle type 1-cycle */
    TEXT_GFX_COMMAND(gfx, 0xBA000602, 0x40);       /* rgb dither bayer */
    TEXT_GFX_COMMAND(gfx, 0xBA000402, 0x20);       /* alpha dither noise */
    TEXT_GFX_COMMAND(gfx, 0xB900031D, 0x504240);   /* render mode */
    TEXT_GFX_COMMAND(gfx, 0xFC119623, 0xFF2FFFFF); /* combine mode */
    TEXT_GFX_COMMAND(gfx, 0xBB000001, 0x10001000); /* texture on */
    TEXT_GFX_COMMAND(gfx, 0xBA001301, 0);          /* texture perspective off */
    TEXT_GFX_COMMAND(gfx, 0xBA001001, 0);          /* texture lod off */
    TEXT_GFX_COMMAND(gfx, 0xBA001102, 0);          /* texture detail clamp */
    TEXT_GFX_COMMAND(gfx, 0xBA000E02, 0);          /* texture lut none */
    *gfxp = gfx;
}
