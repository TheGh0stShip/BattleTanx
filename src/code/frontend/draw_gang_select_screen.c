#include "types.h"

typedef struct Gfx { u32 w0; u32 w1; } Gfx;
typedef struct ResourceBundle { s32 count; s32 entryOffset[1]; } ResourceBundle;

#define GFX_COMMAND(packet, first, second) { Gfx *command = (packet); command->w0 = (first); command->w1 = (second); }
#define BUNDLE_AT(base, index) (((ResourceBundle *)(base))->entryOffset[index] + (base))
/* Gang art banks: 0xBC00-byte resource bundles that follow the first 0xA000 bytes of the target. */
#define GANG_BUNDLE(i) (gResourceTarget + 0xA000 + D_80134010[i] * 0xBC00)
#define GANG_ENTRY(i, k) (((s32 *)GANG_BUNDLE(i))[(k) + 1] + GANG_BUNDLE(i))
#define BUNDLE_ENTRY(index) BUNDLE_AT(gResourceTarget, index)
/* Icon tables hold 1-based bundle entry numbers (0 = none). */
#define ICON_ENTRY(icon) (((s32 *)gResourceTarget)[icon] + gResourceTarget)
#define LOAD_PALETTE(addr, lut) \
    GFX_COMMAND(gFrontendDisplayList++, 0xFD100000U, (addr)); \
    GFX_COMMAND(gFrontendDisplayList++, 0xE8000000U, 0); \
    GFX_COMMAND(gFrontendDisplayList++, 0xF5000100U, 0x07000000); \
    GFX_COMMAND(gFrontendDisplayList++, 0xE6000000U, 0); \
    GFX_COMMAND(gFrontendDisplayList++, 0xF0000000U, (lut)); \
    GFX_COMMAND(gFrontendDisplayList++, 0xE7000000U, 0)
#define LOAD_BUNDLE_PALETTE(index) LOAD_PALETTE(BUNDLE_ENTRY(index), 0x073FC000)
#define DRAW_BUNDLE_IMAGE(index, w, h, x, y, scale) \
    draw_paletted_image(&gFrontendDisplayList, (u8 *)(BUNDLE_ENTRY(index) + 0x200), 2, 1, w, h, 0x20, 0x20, x, y, w, h, 0, 0, scale, scale)
#define BUNDLE_IMAGE(index, w, h, x, y, scale) \
    LOAD_BUNDLE_PALETTE(index); \
    DRAW_BUNDLE_IMAGE(index, w, h, x, y, scale)
#define RESET_COMBINE() \
    GFX_COMMAND(gFrontendDisplayList++, 0xFCFFFFFFU, 0xFFFCF279U); \
    GFX_COMMAND(gFrontendDisplayList++, 0xBA000E02U, 0x8000); \
    GFX_COMMAND(gFrontendDisplayList++, 0xB900031DU, 0x00504240)

extern Gfx *gFrontendDisplayList __asm__("D_803276D4");
extern s32 gResourceTarget __asm__("D_803275F4");
extern s32 D_80327614;
extern s32 D_80328400[];
extern s32 D_80327F00[];
extern s32 D_80327F10[];
extern u8 D_80327F20[];
extern s32 D_80327F3C;
extern s32 D_80134E58;
extern s32 D_80134010[];
extern char *D_80134AAC[];
extern s32 D_80134AD4[];
extern s32 D_80134AFC[];
extern s32 D_80134B24[];
extern s32 D_80134B38[];
extern s32 D_80134B48[];
extern s32 D_80134B58[];
extern s32 D_80134B68[];
extern s32 D_80134B78[];
extern void draw_filled_rectangle(Gfx **, s32, s32, s32, s32, s32, s32, s32, s32) __asm__("func_800F4DFC");
extern s32 select_audio_mode(u32) __asm__("func_800AB95C");
extern void draw_paletted_image(Gfx **, u8 *, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, f32, f32) __asm__("func_800F3D40");
extern void draw_ci8_image(Gfx **, u8 *, u8 *, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, f32, f32) __asm__("func_800F41C0");
extern void begin_text_draw(Gfx **) __asm__("func_8010698C");
extern void set_texture_draw_color(s32, s32, s32, s32) __asm__("func_8010555C");
extern void select_texture_draw_entry(s32) __asm__("func_801054E0");
extern void set_texture_draw_position(s32, s32) __asm__("func_8010552C");
extern void draw_text(Gfx **, char *) __asm__("func_80105584");
extern void draw_text_in_span(Gfx **, char *, s32, s32) __asm__("func_80105A50");

void draw_gang_select_screen(void) __asm__("func_800C83D4");

void draw_gang_select_screen(void)
{
    s32 col, i, mode, icon;

    GFX_COMMAND(gFrontendDisplayList++, 0xE7000000U, 0);
    GFX_COMMAND(gFrontendDisplayList++, 0xBA001402U, 0);
    GFX_COMMAND(gFrontendDisplayList++, 0xFCFFFFFFU, 0xFFFCF279U);
    GFX_COMMAND(gFrontendDisplayList++, 0xB900031DU, 0x0F0A4000);
    GFX_COMMAND(gFrontendDisplayList++, 0xBA001301U, 0);
    GFX_COMMAND(gFrontendDisplayList++, 0xBA001001U, 0);
    GFX_COMMAND(gFrontendDisplayList++, 0xBA000C02U, 0);
    GFX_COMMAND(gFrontendDisplayList++, 0xBA000903U, 0xC00);
    GFX_COMMAND(gFrontendDisplayList++, 0xBA000E02U, 0x8000);
    GFX_COMMAND(gFrontendDisplayList++, 0xFCFFFFFFU, 0xFFFCF279U);
    GFX_COMMAND(gFrontendDisplayList++, 0xBA000E02U, 0x8000);
    LOAD_BUNDLE_PALETTE(18);
    for (i = 0; i < 4; i++) {
        for (col = 0; col < 6; col++) {
            draw_paletted_image(&gFrontendDisplayList, (u8 *)(BUNDLE_ENTRY(18) + 0x200), 2, 1, 0x40, 0x40, 0x20, 0x20,
                                col * 64, i * 64, 0x40, 0x40, 0, 0, 1.0f, 1.0f);
        }
    }
    BUNDLE_IMAGE(2, 0x114, 6, 0x16, 0xC8, 1.0f);
    BUNDLE_IMAGE(3, 0x114, 6, 0x16, 0x7A, 1.0f);
    BUNDLE_IMAGE(4, 6, 0x97, 0x16, 0x32, 1.0f);
    BUNDLE_IMAGE(5, 6, 0x97, 0x124, 0x32, 1.0f);
    BUNDLE_IMAGE(6, 0x114, 6, 0x16, 0x2C, 1.0f);
    BUNDLE_IMAGE(7, 6, 0x97, 0x9D, 0x32, 1.0f);
    for (i = 0; i < 4; i++) {
        if (D_80328400[i] == 4) continue;
        GFX_COMMAND(gFrontendDisplayList++, 0xBA000E02U, 0x8000);
        GFX_COMMAND(gFrontendDisplayList++, 0xFC119623U, 0xFF2FFFFFU);
        GFX_COMMAND(gFrontendDisplayList++, 0xB900031DU, 0x00504240);
        GFX_COMMAND(gFrontendDisplayList++, 0xFA000101U, (u8)D_80327F00[i] | ~0xFF);
        BUNDLE_IMAGE(0, 0x81, 0x48, D_80134B38[i], D_80134B48[i], 1.0f);
        LOAD_PALETTE(GANG_ENTRY(i, 2) + (D_80134B24[D_80328400[i]] << 5), 0x0703C000);
        draw_ci8_image(&gFrontendDisplayList, (u8 *)(GANG_ENTRY(i, 2) + 0xA0), (u8 *)(GANG_ENTRY(i, 2) + (D_80134B24[D_80328400[i]] << 5)),
                       0x82, 0x33, 0x20, 0x20, D_80134B38[i], D_80134B48[i] + 8, 0x81, 0x33, 0, 0, 1.0f, 1.0f);
        if ((icon = D_80134AD4[D_80134010[i]]) != 0) {
            LOAD_PALETTE(ICON_ENTRY(icon), 0x073FC000);
            draw_paletted_image(&gFrontendDisplayList, (u8 *)(ICON_ENTRY(icon) + 0x200), 2, 1, 0x17, 0x17, 0x20, 0x20,
                                D_80134B38[i] + 0x6A, D_80134B48[i], 0x17, 0x17, 0, 0, 1.0f, 1.0f);
        }
        if ((icon = D_80134AFC[D_80134010[i]]) != 0) {
            LOAD_PALETTE(ICON_ENTRY(icon), 0x073FC000);
            draw_paletted_image(&gFrontendDisplayList, (u8 *)(ICON_ENTRY(icon) + 0x200), 2, 1, 0x17, 0x17, 0x20, 0x20,
                                D_80134B38[i] + 0x53, D_80134B48[i], 0x17, 0x17, 0, 0, 1.0f, 1.0f);
        }
        GFX_COMMAND(gFrontendDisplayList++, 0xFA000101U, ((0xFF - D_80327F00[i]) & 0xFF) | ~0xFF);
        LOAD_PALETTE(GANG_ENTRY(i, 0), 0x073FC000);
        draw_paletted_image(&gFrontendDisplayList, (u8 *)(GANG_ENTRY(i, 0) + 0x200), 2, 1, 0x81, 0x48, 0x20, 0x20,
                            D_80134B38[i], D_80134B48[i], 0x81, 0x48, 0, 0, 1.0f, 1.0f);
        D_80327F00[i] += D_80327F10[i];
        if (D_80327F00[i] >= 0x100) D_80327F00[i] = 0xFF;
        if (D_80327F00[i] < 0) D_80327F00[i] = 0;
        begin_text_draw(&gFrontendDisplayList);
        if ((i == 0 && D_80327F3C != -2)
            || (i < D_80134E58 ? D_80327F20[i] != 0 : (D_80327F20[0] != 0 || i != D_80327F3C))) {
            set_texture_draw_color(100, 100, 100, 0xFF);
        } else {
            set_texture_draw_color(200, 200, 200, 0xFF);
        }
        set_texture_draw_position(0, D_80134B78[i]);
        draw_text_in_span(&gFrontendDisplayList, D_80134AAC[D_80134010[i]], D_80134B58[i], D_80134B68[i]);
        if (D_80327F20[i] != 0 || (i >= D_80134E58 && D_80327F20[0] != 0)) {
            set_texture_draw_position(0, D_80134B78[i] - 0xF);
            draw_text_in_span(&gFrontendDisplayList, "Ready", D_80134B58[i], D_80134B68[i]);
        }
    }
    RESET_COMBINE();
    BUNDLE_IMAGE(8, 0x8F, 0x18, 0x59, 0x12, 1.0f);
    begin_text_draw(&gFrontendDisplayList);
    set_texture_draw_color(0xC8, 0xC8, 0xC8, 0xFF);
    select_texture_draw_entry(3);
    set_texture_draw_position(0x24, 0xD1);
    draw_text(&gFrontendDisplayList, "HELP");
    mode = select_audio_mode(0);
    if (D_80327614 != 0) {
        draw_filled_rectangle(&gFrontendDisplayList, 0x3E, 0x4C, 0xC3, 0x69, 0, 0, 0, 0xC8);
        RESET_COMBINE();
        BUNDLE_IMAGE(7, 9, 9, 0x51, 0x52, 1.0f);
        BUNDLE_IMAGE(9, 9, 9, 0x5E, 0x52, 1.0f);
        BUNDLE_IMAGE(12, 9, 9, 0x51, 0x61, 1.0f);
        BUNDLE_IMAGE(1, 9, 9, 0x5E, 0x61, 1.0f);
        BUNDLE_IMAGE(6, 9, 9, 0x51, 0x70, 1.0f);
        BUNDLE_IMAGE(8, 9, 9, 0x5E, 0x70, 1.0f);
        BUNDLE_IMAGE(0, 9, 9, 0x5E, 0x7F, 1.0f);
        BUNDLE_IMAGE(10, 9, 9, 0x5E, 0x8E, 1.0f);
        BUNDLE_IMAGE(11, 9, 9, 0x5E, 0xA5, 1.0f);
        begin_text_draw(&gFrontendDisplayList);
        set_texture_draw_color(0xC8, 0xC8, 0x14, 0xA0);
        select_texture_draw_entry(3);
        set_texture_draw_position(0x73, 0x52);
        draw_text(&gFrontendDisplayList, "CHOOSE TEAM");
        set_texture_draw_position(0x73, 0x61);
        draw_text(&gFrontendDisplayList, "SHOW GANG-TANKS");
        set_texture_draw_position(0x73, 0x70);
        draw_text(&gFrontendDisplayList, "SELECT GANG");
        set_texture_draw_position(0x73, 0x7F);
        draw_text(&gFrontendDisplayList, "PREVIOUS SCREEN");
        set_texture_draw_position(0x73, 0x8E);
        draw_text(&gFrontendDisplayList, "DONE");
        set_texture_draw_position(0x73, 0xA5);
        draw_text(&gFrontendDisplayList, "EXIT HELP");
    }
    RESET_COMBINE();
    BUNDLE_IMAGE(11, 9, 9, 0x17, 0xD1, 1.0f);
    select_audio_mode(mode);
}
