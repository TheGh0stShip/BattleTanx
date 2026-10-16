#include "types.h"

typedef struct GfxCommand {
    u32 w0;
    u32 w1;
} GfxCommand;

#define GFX_WORDS(pkt, a, b)    \
    {                           \
        GfxCommand *_g = (pkt); \
        _g->w0 = (a);           \
        _g->w1 = (b);           \
    }

extern GfxCommand *gFrameDisplayList __asm__("D_803276D4");
extern s32 gMenuTextureBank __asm__("D_803275F4");
extern s32 gMenuScrollX __asm__("D_803275F8");
extern s32 D_80327614;
extern s32 D_80327674;
extern s32 D_80126714;
extern s32 D_80134FF0[];
extern s32 D_80135000[];
extern s32 D_80135010[];
extern u8 D_80135020[];
extern s32 D_80135034[];
extern s32 D_80135044[];
extern char D_80135058[][9][11];
extern char D_801351E4[][9];
extern s32 D_80328290[];
extern u8 D_803282A0[];
extern u32 D_803282A8[][17];
extern u8 D_803283B8[];

extern s32 func_800AB95C(s32 mode);
extern void func_800F4DFC(GfxCommand **gfx, s32 x0, s32 y0, s32 x1, s32 y1, s32 r, s32 g, s32 b, s32 a);
extern void draw_texture_rect(GfxCommand **gfx, u8 *texture, s32 fmt, s32 siz, s32 width, s32 height, s32 arg6,
                              s32 arg7, s32 x, s32 y, s32 arg10, s32 arg11, s32 arg12, s32 arg13, f32 scaleX,
                              f32 scaleY) __asm__("func_800F3D40");
extern void begin_text_draw(GfxCommand **gfx) __asm__("func_8010698C");
extern void set_text_scale_mode(s32 mode) __asm__("func_801054E0");
extern void set_texture_draw_position(s32 x, s32 y) __asm__("func_8010552C");
extern void set_texture_draw_color(s32 red, s32 green, s32 blue, s32 alpha) __asm__("func_8010555C");
extern void draw_text_string(GfxCommand **gfx, char *text) __asm__("func_80105584");
extern void func_80105F24(GfxCommand **gfx, char *text, s32 x, s32 y);

#define TEX(idx) (((s32 *)gMenuTextureBank)[idx] + gMenuTextureBank)

#define LOAD_TLUT(tex)                                                \
    GFX_WORDS(gFrameDisplayList++, 0xFD100000, (u32)(tex));           \
    GFX_WORDS(gFrameDisplayList++, 0xE8000000, 0);                    \
    GFX_WORDS(gFrameDisplayList++, 0xF5000100, 0x07000000);           \
    GFX_WORDS(gFrameDisplayList++, 0xE6000000, 0);                    \
    GFX_WORDS(gFrameDisplayList++, 0xF0000000, 0x073FC000);           \
    GFX_WORDS(gFrameDisplayList++, 0xE7000000, 0)

#define DRAW_TEX(idx, w, h, x, y, s)                                                                       \
    LOAD_TLUT(TEX(idx));                                                                                   \
    draw_texture_rect(&gFrameDisplayList, (u8 *)(TEX(idx) + 0x200), 2, 1, w, h, 0x20, 0x20, x, y, w, h, 0, 0, s, s)

void draw_controls_help_screen(void) __asm__("func_800D455C");

void draw_controls_help_screen(void)
{
    s32 i;
    s32 width;
    s32 saved;
    s32 left;
    s32 right;
    s32 j;
    s32 y;
    s32 tx;
    u8 k;
    u8 bit;
    u32 bits;
    s32 n;

    width = D_80135044[D_80126714];
    GFX_WORDS(gFrameDisplayList++, 0xE7000000, 0);
    GFX_WORDS(gFrameDisplayList++, 0xBA001402, 0);
    GFX_WORDS(gFrameDisplayList++, 0xFCFFFFFF, 0xFFFCF279);
    GFX_WORDS(gFrameDisplayList++, 0xB900031D, 0x0F0A4000);
    GFX_WORDS(gFrameDisplayList++, 0xBA001301, 0);
    GFX_WORDS(gFrameDisplayList++, 0xBA001001, 0);
    GFX_WORDS(gFrameDisplayList++, 0xBA000C02, 0);
    GFX_WORDS(gFrameDisplayList++, 0xBA000903, 0xC00);
    GFX_WORDS(gFrameDisplayList++, 0xBA000E02, 0x8000);
    left = gMenuScrollX;
    right = left;
    left &= ~left >> 31;
    func_800F4DFC(&gFrameDisplayList, left, 0x46, right + 0x140, 0xAA, 0, 0, 0, 0xFF);
    saved = func_800AB95C(0);
    GFX_WORDS(gFrameDisplayList++, 0xFCFFFFFF, 0xFFFCF279);
    GFX_WORDS(gFrameDisplayList++, 0xBA000E02, 0x8000);
    if (D_80327674 != 0) {
        DRAW_TEX(14, 0x140, 0x46, 0, 0, 1.0f);
    }
    GFX_WORDS(gFrameDisplayList++, 0xB900031D, 0x504240);
    DRAW_TEX(15, 0x140, 0xB7, gMenuScrollX, 0x39, 1.0f);
    func_800AB95C(saved);
    DRAW_TEX(23, 0x105, 0x1D, gMenuScrollX + 0x1D, 0x16, 1.0f);
    func_800F4DFC(&gFrameDisplayList, left + 0x1E + width, 0x45, D_80126714 * 0x41 + 4, 0x99, 0, 0, 0, 0x80);
    GFX_WORDS(gFrameDisplayList++, 0xFCFFFFFF, 0xFFFCF279);
    GFX_WORDS(gFrameDisplayList++, 0xBA000E02, 0x8000);
    DRAW_TEX(12, 5, 0x83, gMenuScrollX + 0x5E + width, 0x57, 1.0f);
    DRAW_TEX(11, 5, 0x83, gMenuScrollX + 0x1E + width, 0x57, 1.0f);
    DRAW_TEX(10, 0x45, 5, gMenuScrollX + 0x1E + width, 0xDA, 1.0f);
    DRAW_TEX(13, 0x45, 0x12, gMenuScrollX + 0x1E + width, 0x45, 1.0f);

    for (i = 0; i < D_80126714; i++) {
        GFX_WORDS(gFrameDisplayList++, 0xFCFFFFFF, 0xFFFCF279);
        GFX_WORDS(gFrameDisplayList++, 0xBA000E02, 0x8000);
        if (i > 0) {
            DRAW_TEX(D_80134FF0[i], 0x41, 0x12, gMenuScrollX + 0x1E + i * 0x40 + 4 + width, 0x45, 1.0f);
            DRAW_TEX(D_80135000[i], 5, 0x83, gMenuScrollX + 0x5E + i * 0x40 + width, 0x57, 1.0f);
            DRAW_TEX(D_80135010[i], 0x41, 5, gMenuScrollX + 0x1E + i * 0x40 + 4 + width, 0xDA, 1.0f);
        }
        tx = 0x22 + i * 0x40 + width;
        y = D_80328290[i] * 0xC + 0x56;
        DRAW_TEX(24, 0x3D, 0xD, tx + gMenuScrollX, y, 1.0f);
        tx = 0x55 + i * 0x40 + width;
        y = 0x58;
        for (j = 0; j < D_80135034[D_803283B8[i]]; j++) {
            n = j;
            for (k = 0; k < 17; k++) {
                if (D_803282A8[i][k] < 0x100000) {
                    if (--n == -1) {
                        break;
                    }
                }
            }
            bits = *(D_803282A8[i] + k);
            bit = 1;
            if (bits == 0) {
                bit = 0;
            } else {
                goto test;
            next:
                bit++;
            test:
                if (!(bits & 1)) {
                    bits >>= 1;
                    goto next;
                }
            }
            DRAW_TEX(D_80135020[bit], 9, 9, tx + gMenuScrollX, y, 1.0f);
            y += 0xC;
        }
        y = 0x58;
        begin_text_draw(&gFrameDisplayList);
        set_text_scale_mode(1);
        set_texture_draw_color(0xFF, 0xFF, 0xFF, 0xFF);
        tx = width + i * 0x40 + 0x23;
        for (j = 0; j < D_80135034[D_803283B8[i]]; j++) {
            set_texture_draw_position(tx + gMenuScrollX, y);
            draw_text_string(&gFrameDisplayList, D_80135058[D_803283B8[i]][j]);
            y += 0xC;
        }
        y += (9 - j) * 0xC;
        set_texture_draw_position(tx + gMenuScrollX, y);
        draw_text_string(&gFrameDisplayList, D_801351E4[D_803282A0[i]]);
        y += 0xC;
        set_texture_draw_position(tx + gMenuScrollX, y);
        draw_text_string(&gFrameDisplayList, "Done");
    }

    if (D_80327614 != 0) {
        saved = func_800AB95C(0);
        func_800F4DFC(&gFrameDisplayList, 0x1E, 0x37, 0x104, 0xA5, 0, 0, 0, 0xC8);
        GFX_WORDS(gFrameDisplayList++, 0xFCFFFFFF, 0xFFFCF279);
        GFX_WORDS(gFrameDisplayList++, 0xBA000E02, 0x8000);
        GFX_WORDS(gFrameDisplayList++, 0xB900031D, 0x504240);
        DRAW_TEX(6, 9, 9, 0x44, 0x3C, 1.0f);
        DRAW_TEX(3, 9, 9, 0x51, 0x3C, 1.0f);
        DRAW_TEX(4, 9, 9, 0x44, 0x78, 1.0f);
        DRAW_TEX(5, 9, 9, 0x51, 0x78, 1.0f);
        DRAW_TEX(12, 9, 9, 0x51, 0xCD, 1.0f);
        begin_text_draw(&gFrameDisplayList);
        set_texture_draw_color(0xC8, 0xC8, 0x14, 0xA0);
        set_text_scale_mode(3);
        set_texture_draw_position(0x6B, 0x3C);
        draw_text_string(&gFrameDisplayList, " HIGHLIGHT SELECTION");
        set_texture_draw_position(0x6B, 0x78);
        draw_text_string(&gFrameDisplayList, " CHANGE CONTROL MODES");
        set_texture_draw_color(0xFF, 0x50, 0, 0xA0);
        set_texture_draw_position(0x3B, 0x4B);
        draw_text_string(&gFrameDisplayList, "PRESS ANY BUTTON TO CHANGE");
        set_texture_draw_position(0x48, 0x5A);
        draw_text_string(&gFrameDisplayList, "BUTTON CONFIGURATION");
        func_80105F24(&gFrameDisplayList, "EASY -", 0x64, 0x87);
        set_texture_draw_position(0x6B, 0x87);
        draw_text_string(&gFrameDisplayList, " TURRET LOCKED TO BODY");
        func_80105F24(&gFrameDisplayList, "ARCADE -", 0x64, 0x96);
        set_texture_draw_position(0x6B, 0x96);
        draw_text_string(&gFrameDisplayList, " DYNAMIC CONTROL");
        func_80105F24(&gFrameDisplayList, " GUNNER -", 0x64, 0xA5);
        set_texture_draw_position(0x6B, 0xA5);
        draw_text_string(&gFrameDisplayList, " CONTROL TURRET");
        func_80105F24(&gFrameDisplayList, "DRIVER -", 0x64, 0xB4);
        set_texture_draw_position(0x6B, 0xB4);
        draw_text_string(&gFrameDisplayList, " CONTROL TANK BODY");
        set_texture_draw_color(0xC8, 0xC8, 0x14, 0xA0);
        set_texture_draw_position(0x6B, 0xCD);
        draw_text_string(&gFrameDisplayList, " EXIT HELP");
        func_800AB95C(saved);
    }
}
