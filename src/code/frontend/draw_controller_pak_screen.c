#include "types.h"

typedef struct Gfx {
    u32 w0;
    u32 w1;
} Gfx;

typedef struct PakScreenBundle {
    u8 pad00[0xC];
    s32 bannerOffset;
    u8 pad10[0x28];
    s32 backdropOffset;
} PakScreenBundle;

#define GFX_COMMAND(packet, first, second) { \
    Gfx *command = (packet); \
    command->w0 = (first); \
    command->w1 = (second); \
}

extern Gfx *gFrontendDisplayList __asm__("D_803276D4");
extern s32 gResourceTarget __asm__("D_803275F4");
extern s32 D_803275F8;
extern s32 D_80327674;
extern u8 D_80327F5E[];
extern s32 D_80328150;
extern s32 D_80328170;

extern void draw_filled_rectangle(Gfx **list, s32 left, s32 top, s32 right, s32 bottom, s32 red, s32 green, s32 blue,
                                  s32 alpha) __asm__("func_800F4DFC");
extern s32 select_audio_mode(u32 mode) __asm__("func_800AB95C");
extern void draw_paletted_image(Gfx **list, u8 *texels, s32 arg2, s32 arg3, s32 width, s32 height, s32 tileWidth,
                                s32 tileHeight, s32 x, s32 y, s32 width2, s32 height2, s32 s, s32 t,
                                f32 scaleX, f32 scaleY) __asm__("func_800F3D40");
extern void begin_text_draw(Gfx **gfx) __asm__("func_8010698C");
extern void set_texture_draw_color(s32 red, s32 green, s32 blue, s32 alpha) __asm__("func_8010555C");
extern void select_texture_draw_entry(s32 index) __asm__("func_801054E0");
extern void set_texture_draw_scale(f32 x, f32 y) __asm__("func_80105544");
extern void set_texture_draw_position(s32 x, s32 y) __asm__("func_8010552C");
extern void draw_text_in_span(Gfx **gfx, char *text, s32 left, s32 right) __asm__("func_80105A50");
extern void format_note_name(char *buf, u8 *name) __asm__("func_800A9564");
extern void draw_pak_prompt_buttons(s32 mode) __asm__("func_800CFEB0");

void draw_controller_pak_screen(void) __asm__("func_800CE554");

void draw_controller_pak_screen(void)
{
    char name[16];
    s32 mode;
    s32 left;

    left = D_803275F8;
    GFX_COMMAND(gFrontendDisplayList++, 0xE7000000U, 0);
    GFX_COMMAND(gFrontendDisplayList++, 0xBA001402U, 0);
    GFX_COMMAND(gFrontendDisplayList++, 0xFCFFFFFFU, 0xFFFCF279U);
    GFX_COMMAND(gFrontendDisplayList++, 0xB900031DU, 0x0F0A4000);
    GFX_COMMAND(gFrontendDisplayList++, 0xBA001301U, 0);
    GFX_COMMAND(gFrontendDisplayList++, 0xBA001001U, 0);
    GFX_COMMAND(gFrontendDisplayList++, 0xBA000C02U, 0);
    GFX_COMMAND(gFrontendDisplayList++, 0xBA000903U, 0xC00);
    GFX_COMMAND(gFrontendDisplayList++, 0xBA000E02U, 0x8000);
    draw_filled_rectangle(&gFrontendDisplayList, (left < 0) ? 0 : left, 0x46, left + 320, 0xAA, 0, 0, 0, 0xFF);
    GFX_COMMAND(gFrontendDisplayList++, 0xFCFFFFFFU, 0xFFFCF279U);
    GFX_COMMAND(gFrontendDisplayList++, 0xBA000E02U, 0x8000);
    mode = select_audio_mode(0);
    if (D_80327674 != 0) {
        GFX_COMMAND(gFrontendDisplayList++, 0xFD100000U,
                    ((PakScreenBundle *)gResourceTarget)->backdropOffset + gResourceTarget);
        GFX_COMMAND(gFrontendDisplayList++, 0xE8000000U, 0);
        GFX_COMMAND(gFrontendDisplayList++, 0xF5000100U, 0x07000000);
        GFX_COMMAND(gFrontendDisplayList++, 0xE6000000U, 0);
        GFX_COMMAND(gFrontendDisplayList++, 0xF0000000U, 0x073FC000);
        GFX_COMMAND(gFrontendDisplayList++, 0xE7000000U, 0);
        draw_paletted_image(&gFrontendDisplayList,
                            (u8 *)(((PakScreenBundle *)gResourceTarget)->backdropOffset + gResourceTarget + 0x200), 2,
                            1, 320, 0x46, 0x20, 0x20, 0, 0, 320, 0x46, 0, 0, 1.0f, 1.0f);
    }
    GFX_COMMAND(gFrontendDisplayList++, 0xB900031DU, 0x00504240);
    select_audio_mode(mode);
    GFX_COMMAND(gFrontendDisplayList++, 0xFD100000U,
                ((PakScreenBundle *)gResourceTarget)->bannerOffset + gResourceTarget);
    GFX_COMMAND(gFrontendDisplayList++, 0xE8000000U, 0);
    GFX_COMMAND(gFrontendDisplayList++, 0xF5000100U, 0x07000000);
    GFX_COMMAND(gFrontendDisplayList++, 0xE6000000U, 0);
    GFX_COMMAND(gFrontendDisplayList++, 0xF0000000U, 0x073FC000);
    GFX_COMMAND(gFrontendDisplayList++, 0xE7000000U, 0);
    draw_paletted_image(&gFrontendDisplayList,
                        (u8 *)(((PakScreenBundle *)gResourceTarget)->bannerOffset + gResourceTarget + 0x200), 2, 1,
                        0xD5, 0x1D, 0x20, 0x20, D_803275F8 + 0x35, 0x16, 0xD5, 0x1D, 0, 0, 1.0f, 1.0f);
    begin_text_draw(&gFrontendDisplayList);
    set_texture_draw_color(255, 80, 0, 255);
    select_texture_draw_entry(3);
    set_texture_draw_scale(1.0f, 1.0f);
    set_texture_draw_position(0, 0x55);
    switch (D_80328170) {
    case 8:
        draw_text_in_span(&gFrontendDisplayList, "Controller Pak Connection Error", D_803275F8, D_803275F8 + 320);
        set_texture_draw_position(100, 130);
        draw_text_in_span(&gFrontendDisplayList, "B: Cancel     A: Check connection", 0, 320);
        break;
    case 9:
        draw_text_in_span(&gFrontendDisplayList, "Corrupt Controller Pak detected", D_803275F8, D_803275F8 + 320);
        set_texture_draw_position(0, 125);
        draw_text_in_span(&gFrontendDisplayList, "A: Attempt Repair (data may be lost)", D_803275F8,
                          D_803275F8 + 320);
        set_texture_draw_position(100, 140);
        draw_text_in_span(&gFrontendDisplayList, "B: Continue without saving", 0, 320);
        break;
    case 10:
        draw_text_in_span(&gFrontendDisplayList, "Controller Pak has been swapped", D_803275F8, D_803275F8 + 320);
        set_texture_draw_position(0, 105);
        draw_text_in_span(&gFrontendDisplayList, "Use this Controller Pak?", D_803275F8, D_803275F8 + 320);
        set_texture_draw_position(100, 130);
        draw_text_in_span(&gFrontendDisplayList, "B: Cancel     A: OK", 0, 320);
        draw_pak_prompt_buttons(0);
        break;
    case 11:
        draw_text_in_span(&gFrontendDisplayList, "Save Game Error", D_803275F8, D_803275F8 + 320);
        set_texture_draw_position(100, 130);
        draw_text_in_span(&gFrontendDisplayList, "B: Cancel     A: Retry", 0, 320);
        break;
    case 7:
        draw_text_in_span(&gFrontendDisplayList, "Save Game", D_803275F8, D_803275F8 + 320);
        set_texture_draw_position(100, 130);
        draw_text_in_span(&gFrontendDisplayList, "B: Cancel     A: Save", 0, 320);
        draw_pak_prompt_buttons(0);
        break;
    case 6:
        draw_text_in_span(&gFrontendDisplayList, "Create BattleTanx Note", D_803275F8, D_803275F8 + 320);
        set_texture_draw_position(100, 130);
        draw_text_in_span(&gFrontendDisplayList, "B: Cancel     A: Create", 0, 320);
        draw_pak_prompt_buttons(0);
        break;
    case 2:
        draw_text_in_span(&gFrontendDisplayList, "No Controller Pak found", D_803275F8, D_803275F8 + 320);
        set_texture_draw_position(0, 100);
        draw_text_in_span(&gFrontendDisplayList, "Insert Controller Pak now", D_803275F8, D_803275F8 + 320);
        set_texture_draw_position(100, 130);
        draw_text_in_span(&gFrontendDisplayList, "B: Cancel     A: Check for Controller Pak", 0, 320);
        break;
    case 3:
        draw_text_in_span(&gFrontendDisplayList, "No Controller Pak found", D_803275F8, D_803275F8 + 320);
        set_texture_draw_position(0, 100);
        draw_text_in_span(&gFrontendDisplayList, "You will not be able to save", D_803275F8, D_803275F8 + 320);
        set_texture_draw_position(100, 130);
        draw_text_in_span(&gFrontendDisplayList, "B: Cancel     A: Check for Controller Pak", 0, 320);
        break;
    case 4:
    case 5:
        draw_text_in_span(&gFrontendDisplayList, "Are you sure you want to delete", D_803275F8 + 24,
                          D_803275F8 + 296);
        set_texture_draw_position(D_803275F8 + 24, 100);
        format_note_name(name, &D_80327F5E[D_80328150 * 32]);
        draw_text_in_span(&gFrontendDisplayList, name, D_803275F8 + 24, D_803275F8 + 296);
        set_texture_draw_position(D_803275F8 + 24, 120);
        draw_text_in_span(&gFrontendDisplayList, "B: Cancel     A: Delete", D_803275F8 + 24, D_803275F8 + 296);
        draw_pak_prompt_buttons(1);
        break;
    case 0:
        draw_text_in_span(&gFrontendDisplayList, "Select which Game Note to delete", D_803275F8 + 24,
                          D_803275F8 + 296);
        set_texture_draw_position(D_803275F8 + 24, 120);
        draw_text_in_span(&gFrontendDisplayList, "B: Exit     A: Delete", D_803275F8 + 24, D_803275F8 + 296);
        draw_pak_prompt_buttons(1);
        break;
    case 1:
        draw_text_in_span(&gFrontendDisplayList, "No space for BattleTanx Game Note", D_803275F8 + 24,
                          D_803275F8 + 296);
        set_texture_draw_position(D_803275F8 + 24, 100);
        draw_text_in_span(&gFrontendDisplayList, "Select which Game Note to delete", D_803275F8 + 24,
                          D_803275F8 + 296);
        set_texture_draw_position(D_803275F8 + 24, 120);
        draw_text_in_span(&gFrontendDisplayList, "B: Exit     A: Delete", D_803275F8 + 24, D_803275F8 + 296);
        draw_pak_prompt_buttons(1);
        break;
    }
}
