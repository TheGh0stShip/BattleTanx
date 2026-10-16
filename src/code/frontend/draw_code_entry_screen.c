#include "types.h"

/* SPAN 0x800DAE30..0x800DC93C */
/* RODATA_VRAM 0x80074268 */
/* LDSYM D_80135680=0x80135680 */
/* LDSYM D_8013568C=0x8013568C */
/* LDSYM D_80135724=0x80135724 */
/* LDSYM D_803275F4=0x803275F4 */
/* LDSYM D_803275F8=0x803275F8 */
/* LDSYM D_80327614=0x80327614 */
/* LDSYM D_80327674=0x80327674 */
/* LDSYM D_803276D4=0x803276D4 */
/* LDSYM D_80328420=0x80328420 */
/* LDSYM D_80328424=0x80328424 */
/* LDSYM D_80328428=0x80328428 */
/* LDSYM D_80328430=0x80328430 */
/* LDSYM D_80328440=0x80328440 */
/* LDSYM func_800AB95C=0x800AB95C */
/* LDSYM func_800F3D40=0x800F3D40 */
/* LDSYM func_800F4DFC=0x800F4DFC */
/* LDSYM func_801054E0=0x801054E0 */
/* LDSYM func_8010552C=0x8010552C */
/* LDSYM func_80105544=0x80105544 */
/* LDSYM func_8010555C=0x8010555C */
/* LDSYM func_80105584=0x80105584 */
/* LDSYM func_80106010=0x80106010 */
/* LDSYM func_8010698C=0x8010698C */

typedef struct Gfx { u32 w0; u32 w1; } Gfx;
typedef struct ResourceBundle { s32 count; s32 entryOffset[1]; } ResourceBundle;

#define GFX_COMMAND(packet, first, second) { Gfx *command = (packet); command->w0 = (first); command->w1 = (second); }
#define BUNDLE_ENTRY(index) (((ResourceBundle *)gResourceTarget)->entryOffset[index] + gResourceTarget)
#define LOAD_BUNDLE_PALETTE(index) \
    GFX_COMMAND(gFrontendDisplayList++, 0xFD100000U, BUNDLE_ENTRY(index)); \
    GFX_COMMAND(gFrontendDisplayList++, 0xE8000000U, 0); \
    GFX_COMMAND(gFrontendDisplayList++, 0xF5000100U, 0x07000000); \
    GFX_COMMAND(gFrontendDisplayList++, 0xE6000000U, 0); \
    GFX_COMMAND(gFrontendDisplayList++, 0xF0000000U, 0x073FC000); \
    GFX_COMMAND(gFrontendDisplayList++, 0xE7000000U, 0)

extern Gfx *gFrontendDisplayList __asm__("D_803276D4");
extern s32 gResourceTarget __asm__("D_803275F4");
extern s32 D_80327614, D_803275F8, D_80327674;
extern s32 D_80328420, D_80328424, D_80328428, D_80328440;
extern u8 D_80328430[], D_80135680[], D_8013568C[];
extern char *D_80135724[];
extern void draw_filled_rectangle(Gfx **, s32, s32, s32, s32, s32, s32, s32, s32) __asm__("func_800F4DFC");
extern s32 select_audio_mode(u32) __asm__("func_800AB95C");
extern void draw_paletted_image(Gfx **, u8 *, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, f32, f32) __asm__("func_800F3D40");
extern void begin_text_draw(Gfx **) __asm__("func_8010698C");
extern void set_texture_draw_color(s32, s32, s32, s32) __asm__("func_8010555C");
extern void select_texture_draw_entry(s32) __asm__("func_801054E0");
extern void set_texture_draw_position(s32, s32) __asm__("func_8010552C");
extern void draw_text(Gfx **, char *) __asm__("func_80105584");
extern void set_texture_draw_scale(f32, f32) __asm__("func_80105544");
extern void draw_text_char(Gfx **, s32) __asm__("func_80106010");

static inline s32 add_grid_offset(s32 x, s32 offset) { x += offset; return x; }
static inline s32 grid_text_y(s32 i) { s32 y; y = i * 0x15; y += 0x55; return y; }
static inline s32 grid_image_y(s32 i) { s32 y; y = i * 0x15; y += 0x50; return y; }

void draw_code_entry_screen(void) __asm__("func_800DAE30");

void draw_code_entry_screen(void)
{
    u8 *letters;
    s32 col, x, offset, start, i, mode;

    GFX_COMMAND(gFrontendDisplayList++, 0xE7000000U, 0);
    GFX_COMMAND(gFrontendDisplayList++, 0xBA001402U, 0);
    GFX_COMMAND(gFrontendDisplayList++, 0xFCFFFFFFU, 0xFFFCF279U);
    GFX_COMMAND(gFrontendDisplayList++, 0xB900031DU, 0x0F0A4000);
    GFX_COMMAND(gFrontendDisplayList++, 0xBA001301U, 0);
    GFX_COMMAND(gFrontendDisplayList++, 0xBA001001U, 0);
    GFX_COMMAND(gFrontendDisplayList++, 0xBA000C02U, 0);
    GFX_COMMAND(gFrontendDisplayList++, 0xBA000903U, 0xC00);
    GFX_COMMAND(gFrontendDisplayList++, 0xBA000E02U, 0x8000);
    draw_filled_rectangle(&gFrontendDisplayList, D_803275F8, 0x46, 0x140, 0xF0, 0, 0, 0, 0xFF);
    GFX_COMMAND(gFrontendDisplayList++, 0xFCFFFFFFU, 0xFFFCF279U);
    GFX_COMMAND(gFrontendDisplayList++, 0xBA000E02U, 0x8000);
    mode = select_audio_mode(0);
    if (D_80327674 != 0) {
        LOAD_BUNDLE_PALETTE(13);
        draw_paletted_image(&gFrontendDisplayList, (u8 *)(BUNDLE_ENTRY(13) + 0x200), 2, 1, 0x140, 0x46, 0x20, 0x20, 0, 0, 0x140, 0x46, 0, 0, 1.0f, 1.0f);
    }
    GFX_COMMAND(gFrontendDisplayList++, 0xB900031DU, 0x00504240);
    LOAD_BUNDLE_PALETTE(15);
    draw_paletted_image(&gFrontendDisplayList, (u8 *)(BUNDLE_ENTRY(15) + 0x200), 2, 1, 0x140, 0xB7, 0x20, 0x20, D_803275F8, 0x39, 0x140, 0xB7, 0, 0, 1.0f, 1.0f);
    select_audio_mode(mode);
    LOAD_BUNDLE_PALETTE(8);
    draw_paletted_image(&gFrontendDisplayList, (u8 *)(BUNDLE_ENTRY(8) + 0x200), 2, 1, 0x9C, 0x1E, 0x20, 0x20, D_803275F8 + 0x52, 0x16, 0x9C, 0x1E, 0, 0, 1.0f, 1.0f);
    draw_filled_rectangle(&gFrontendDisplayList, D_803275F8 + 0x20, 0x4B, 0x100, 0x5A, 0, 0, 0, 0x80);
    draw_filled_rectangle(&gFrontendDisplayList, D_803275F8 + 0x8C, 0xA5, 0x94, 0x29, 0, 0, 0, 0x80);
    GFX_COMMAND(gFrontendDisplayList++, 0xFCFFFFFFU, 0xFFFCF279U);
    GFX_COMMAND(gFrontendDisplayList++, 0xBA000E02U, 0x8000);
    LOAD_BUNDLE_PALETTE(0);
    draw_paletted_image(&gFrontendDisplayList, (u8 *)(BUNDLE_ENTRY(0) + 0x200), 2, 1, 5, 0x5A, 0x20, 0x20, D_803275F8 + 0x20, 0x4B, 5, 0x5A, 0, 0, 1.0f, 1.0f);
    LOAD_BUNDLE_PALETTE(1);
    draw_paletted_image(&gFrontendDisplayList, (u8 *)(BUNDLE_ENTRY(1) + 0x200), 2, 1, 0xF6, 5, 0x20, 0x20, D_803275F8 + 0x25, 0x4B, 0xF6, 5, 0, 0, 1.0f, 1.0f);
    LOAD_BUNDLE_PALETTE(2);
    draw_paletted_image(&gFrontendDisplayList, (u8 *)(BUNDLE_ENTRY(2) + 0x200), 2, 1, 5, 0x83, 0x20, 0x20, D_803275F8 + 0x11B, 0x4B, 5, 0x83, 0, 0, 1.0f, 1.0f);
    LOAD_BUNDLE_PALETTE(3);
    draw_paletted_image(&gFrontendDisplayList, (u8 *)(BUNDLE_ENTRY(3) + 0x200), 2, 1, 0x8A, 5, 0x20, 0x20, D_803275F8 + 0x91, 0xC9, 0x8A, 5, 0, 0, 1.0f, 1.0f);
    LOAD_BUNDLE_PALETTE(4);
    draw_paletted_image(&gFrontendDisplayList, (u8 *)(BUNDLE_ENTRY(4) + 0x200), 2, 1, 5, 0x29, 0x20, 0x20, D_803275F8 + 0x8C, 0xA5, 5, 0x29, 0, 0, 1.0f, 1.0f);
    LOAD_BUNDLE_PALETTE(5);
    draw_paletted_image(&gFrontendDisplayList, (u8 *)(BUNDLE_ENTRY(5) + 0x200), 2, 1, 0xF6, 5, 0x20, 0x20, D_803275F8 + 0x25, 0xA0, 0xF6, 5, 0, 0, 1.0f, 1.0f);
    LOAD_BUNDLE_PALETTE(6);
    draw_paletted_image(&gFrontendDisplayList, (u8 *)(BUNDLE_ENTRY(6) + 0x200), 2, 1, 0xF6, 5, 0x20, 0x20, D_803275F8 + 0x25, 0x8A, 0xF6, 5, 0, 0, 1.0f, 1.0f);
    begin_text_draw(&gFrontendDisplayList);
    select_texture_draw_entry(2);
    set_texture_draw_scale(1.0f, 1.0f);
    set_texture_draw_color(0xC8, 0xC8, 0xC8, 0xFF);
    letters = D_80135680;
    offset = 0;
    for (i = 0; i < 2; i++) {
        x = 0x2F;
        for (col = 0; col < 11; col++) {
            if (D_80328424 == i && D_80328420 == col) {
                do {
                    GFX_COMMAND(gFrontendDisplayList++, 0xFA000101U, 0xFFAA00FFU);
                    draw_paletted_image(&gFrontendDisplayList, (u8 *)BUNDLE_ENTRY(7), 3, 1, 0x18, 0x18, 0x20, 0x20,
                                        add_grid_offset(x, offset) + D_803275F8 - 5, grid_image_y(i), 0x15, 0x15, 0, 0, 1.0f, 1.0f);
                } while (0);
            }
            set_texture_draw_position(add_grid_offset(x, offset) + D_803275F8, grid_text_y(i));
            x += 0x15;
            draw_text_char(&gFrontendDisplayList, letters[col]);
        }
        offset = 11;
        letters = D_8013568C;
    }
    start = (0xF6 - D_80328428 * 21) / 2;
    for (i = 0, x = 0x28; i < D_80328428; i++, x += 0x15) {
        set_texture_draw_position(start + x + D_803275F8, 0x92);
        draw_text_char(&gFrontendDisplayList, D_80328430[i]);
    }
    select_texture_draw_entry(3);
    if (D_80328424 == 2 && D_80328420 == 0) set_texture_draw_color(0xFF, 0x96, 0, 0xFF);
    set_texture_draw_position(D_803275F8 + 0xA9, 0x7D);
    draw_text(&gFrontendDisplayList, "Erase");
    if (D_80328424 == 2 && D_80328420 == 1) set_texture_draw_color(0xFF, 0x96, 0, 0xFF);
    else set_texture_draw_color(0xC8, 0xC8, 0xC8, 0xFF);
    set_texture_draw_position(D_803275F8 + 0xE6, 0x7D);
    draw_text(&gFrontendDisplayList, "Enter");
    set_texture_draw_color(0xC8, 0xC8, 0xC8, 0xFF);
    if (D_80328440 != -1) {
        set_texture_draw_position(D_803275F8 + 0x96, 0xA9);
        draw_text(&gFrontendDisplayList, D_80135724[D_80328440]);
    }
    set_texture_draw_color(0xC8, 0xC8, 0xC8, 0xFF);
    select_texture_draw_entry(3);
    set_texture_draw_position(D_803275F8 + 0xFB, 0xD1);
    draw_text(&gFrontendDisplayList, "HELP");
    mode = select_audio_mode(0);
    if (D_80327614 != 0) {
        draw_filled_rectangle(&gFrontendDisplayList, 0x3E, 0x4C, 0xC3, 0x67, 0, 0, 0, 0xC8);
        GFX_COMMAND(gFrontendDisplayList++, 0xFCFFFFFFU, 0xFFFCF279U);
        GFX_COMMAND(gFrontendDisplayList++, 0xBA000E02U, 0x8000);
        GFX_COMMAND(gFrontendDisplayList++, 0xB900031DU, 0x00504240);
        LOAD_BUNDLE_PALETTE(12);
        draw_paletted_image(&gFrontendDisplayList, (u8 *)(BUNDLE_ENTRY(12) + 0x200), 2, 1, 9, 9, 0x20, 0x20, 0x47, 0x56, 9, 9, 0, 0, 1.0f, 1.0f);
        LOAD_BUNDLE_PALETTE(1);
        draw_paletted_image(&gFrontendDisplayList, (u8 *)(BUNDLE_ENTRY(1) + 0x200), 2, 1, 9, 9, 0x20, 0x20, 0x54, 0x56, 9, 9, 0, 0, 1.0f, 1.0f);
        LOAD_BUNDLE_PALETTE(6);
        draw_paletted_image(&gFrontendDisplayList, (u8 *)(BUNDLE_ENTRY(6) + 0x200), 2, 1, 9, 9, 0x20, 0x20, 0x47, 0x65, 9, 9, 0, 0, 1.0f, 1.0f);
        LOAD_BUNDLE_PALETTE(8);
        draw_paletted_image(&gFrontendDisplayList, (u8 *)(BUNDLE_ENTRY(8) + 0x200), 2, 1, 9, 9, 0x20, 0x20, 0x54, 0x65, 9, 9, 0, 0, 1.0f, 1.0f);
        LOAD_BUNDLE_PALETTE(0);
        draw_paletted_image(&gFrontendDisplayList, (u8 *)(BUNDLE_ENTRY(0) + 0x200), 2, 1, 9, 9, 0x20, 0x20, 0x54, 0x74, 9, 9, 0, 0, 1.0f, 1.0f);
        LOAD_BUNDLE_PALETTE(10);
        draw_paletted_image(&gFrontendDisplayList, (u8 *)(BUNDLE_ENTRY(10) + 0x200), 2, 1, 9, 9, 0x20, 0x20, 0x54, 0x83, 9, 9, 0, 0, 1.0f, 1.0f);
        LOAD_BUNDLE_PALETTE(11);
        draw_paletted_image(&gFrontendDisplayList, (u8 *)(BUNDLE_ENTRY(11) + 0x200), 2, 1, 9, 9, 0x20, 0x20, 0x54, 0xA1, 9, 9, 0, 0, 1.0f, 1.0f);
        begin_text_draw(&gFrontendDisplayList);
        set_texture_draw_color(0xC8, 0xC8, 0x14, 0xA0);
        select_texture_draw_entry(3);
        set_texture_draw_position(0x67, 0x56); draw_text(&gFrontendDisplayList, "HIGHLIGHT UP-DOWN");
        set_texture_draw_position(0x67, 0x65); draw_text(&gFrontendDisplayList, "HIGHLIGHT LEFT-RIGHT");
        set_texture_draw_position(0x67, 0x74); draw_text(&gFrontendDisplayList, "PREVIOUS SCREEN");
        set_texture_draw_position(0x67, 0x83); draw_text(&gFrontendDisplayList, "SELECT");
        set_texture_draw_position(0x67, 0xA1); draw_text(&gFrontendDisplayList, "EXIT HELP");
    }
    GFX_COMMAND(gFrontendDisplayList++, 0xFCFFFFFFU, 0xFFFCF279U);
    GFX_COMMAND(gFrontendDisplayList++, 0xBA000E02U, 0x8000);
    GFX_COMMAND(gFrontendDisplayList++, 0xB900031DU, 0x00504240);
    LOAD_BUNDLE_PALETTE(11);
    draw_paletted_image(&gFrontendDisplayList, (u8 *)(BUNDLE_ENTRY(11) + 0x200), 2, 1, 9, 9, 0x20, 0x20,
                        D_803275F8 + 0xEE, 0xD1, 9, 9, 0, 0, 1.0f, 1.0f);
    select_audio_mode(mode);
}
