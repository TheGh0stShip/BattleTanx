#include "types.h"

typedef struct Gfx {
    u32 w0;
    u32 w1;
} Gfx;

typedef struct ResourceBundle {
    s32 count;
    s32 entryOffset[3];
} ResourceBundle;

typedef struct UnitRecord {
    u8 pad00[0x14];
    u8 flag14;
} UnitRecord;

#define GFX_COMMAND(packet, first, second) { \
    Gfx *command = (packet); \
    command->w0 = (first); \
    command->w1 = (second); \
}

#define BUNDLE_ENTRY(index) (gPauseBundle.entryOffset[index] + (s32)&gPauseBundle)

extern Gfx *gMenuDisplayList __asm__("D_8037A174");
extern ResourceBundle gPauseBundle __asm__("D_8037FD80");
extern s32 gPauseSelection __asm__("D_801416EC");
extern u8 D_80125798;
extern u8 D_80125799;
extern u8 D_801B4AE0;
extern u8 D_80134E64;

extern void draw_filled_rectangle(Gfx **list, s32 left, s32 top, s32 right, s32 bottom, s32 red, s32 green, s32 blue,
                                  s32 alpha) __asm__("func_800F4DFC");
extern void draw_paletted_image(Gfx **list, u8 *texels, s32 arg2, s32 arg3, s32 width, s32 height, s32 tileWidth,
                                s32 tileHeight, s32 x, s32 y, s32 width2, s32 height2, s32 s, s32 t,
                                f32 scaleX, f32 scaleY) __asm__("func_800F3D40");
extern void begin_text_draw(Gfx **gfx) __asm__("func_8010698C");
extern void set_texture_draw_color(s32 red, s32 green, s32 blue, s32 alpha) __asm__("func_8010555C");
extern void select_texture_draw_entry(s32 index) __asm__("func_801054E0");
extern void set_texture_draw_position(s32 x, s32 y) __asm__("func_8010552C");
extern void draw_centered_text(Gfx **gfx, char *text, s32 left, s32 right) __asm__("func_80105A50");
extern s32 read_controller_buttons(s32 controller, s32 repeat) __asm__("func_80096920");
extern void func_8010D984(void);
extern s32 get_entity_capacity(void) __asm__("func_8007AAB0");
extern UnitRecord *get_entity_record(u16 index) __asm__("func_800A6688");

void draw_pause_menu(void) __asm__("func_800FFF78");

void draw_pause_menu(void)
{
    s32 buttons;
    u16 i;
    s32 count;

    GFX_COMMAND(gMenuDisplayList++, 0xE7000000U, 0);
    GFX_COMMAND(gMenuDisplayList++, 0xBA001402U, 0);
    GFX_COMMAND(gMenuDisplayList++, 0xB900031DU, 0x504240);
    GFX_COMMAND(gMenuDisplayList++, 0xFCFFFFFFU, 0xFFFCF279U);
    GFX_COMMAND(gMenuDisplayList++, 0xBA001301U, 0);
    GFX_COMMAND(gMenuDisplayList++, 0xBA001001U, 0);
    GFX_COMMAND(gMenuDisplayList++, 0xBA000C02U, 0);
    GFX_COMMAND(gMenuDisplayList++, 0xBA000903U, 0xC00);
    GFX_COMMAND(gMenuDisplayList++, 0xBA000E02U, 0);
    draw_filled_rectangle(&gMenuDisplayList, 0x5D, 0x52, 0x86, 0x4C, 0, 0, 0, 0xAF);
    GFX_COMMAND(gMenuDisplayList++, 0xE7000000U, 0);
    GFX_COMMAND(gMenuDisplayList++, 0xBA001402U, 0);
    GFX_COMMAND(gMenuDisplayList++, 0xB900031DU, 0x504240);
    GFX_COMMAND(gMenuDisplayList++, 0xFCFFFFFFU, 0xFFFCF279U);
    GFX_COMMAND(gMenuDisplayList++, 0xBA001301U, 0);
    GFX_COMMAND(gMenuDisplayList++, 0xBA001001U, 0);
    GFX_COMMAND(gMenuDisplayList++, 0xBA000C02U, 0);
    GFX_COMMAND(gMenuDisplayList++, 0xBA000903U, 0xC00);
    GFX_COMMAND(gMenuDisplayList++, 0xBA000E02U, 0x8000);
    GFX_COMMAND(gMenuDisplayList++, 0xFD100000U, BUNDLE_ENTRY(2));
    GFX_COMMAND(gMenuDisplayList++, 0xE8000000U, 0);
    GFX_COMMAND(gMenuDisplayList++, 0xF5000100U, 0x07000000);
    GFX_COMMAND(gMenuDisplayList++, 0xE6000000U, 0);
    GFX_COMMAND(gMenuDisplayList++, 0xF0000000U, 0x073FC000);
    GFX_COMMAND(gMenuDisplayList++, 0xE7000000U, 0);
    draw_paletted_image(&gMenuDisplayList, (u8 *)(BUNDLE_ENTRY(2) + 0x200), 2, 1, 0x86, 0x4C, 0x20, 0x20, 0x5D, 0x52,
                        0x86, 0x4C, 0, 0, 1.0f, 1.0f);
    begin_text_draw(&gMenuDisplayList);
    select_texture_draw_entry(2);
    if (gPauseSelection == 1) {
        set_texture_draw_color(0xE6, 0xAA, 0, 0xFF);
    } else {
        set_texture_draw_color(0x50, 0, 0, 0xFF);
    }
    set_texture_draw_position(0x63, 0x72);
    draw_centered_text(&gMenuDisplayList, "RESTART", 0x5D, 0xE3);
    if (gPauseSelection == 2) {
        set_texture_draw_color(0xE6, 0xAA, 0, 0xFF);
    } else {
        set_texture_draw_color(0x50, 0, 0, 0xFF);
    }
    set_texture_draw_position(0x63, 0x8A);
    draw_centered_text(&gMenuDisplayList, "QUIT GAME", 0x5D, 0xE3);
    if (gPauseSelection == 0) {
        set_texture_draw_color(0xE6, 0xAA, 0, 0xFF);
    } else {
        set_texture_draw_color(0x50, 0, 0, 0xFF);
    }
    set_texture_draw_position(0x63, 0x5A);
    draw_centered_text(&gMenuDisplayList, "CONTINUE", 0x5D, 0xE3);
    buttons = read_controller_buttons(0, 0);
    if (buttons & 0x10) {
        switch (gPauseSelection) {
        case 1:
            D_80125799 = 1;
            D_80125798 = 1;
            if (D_80134E64 == 0) {
                func_8010D984();
            }
            break;
        case 2:
            D_801B4AE0 = 2;
            D_80125798 = 1;
            break;
        }
        count = get_entity_capacity();
        for (i = 0; i < count; i++) {
            get_entity_record(i)->flag14 = 0;
        }
    } else {
        s32 sel;
        s32 delta = (buttons & 8) > 0;

        delta -= buttons & 1;
        sel = gPauseSelection + delta;
        gPauseSelection = sel;
        if (sel >= 3) {
            gPauseSelection = 0;
        }
        if (gPauseSelection < 0) {
            gPauseSelection = 2;
        }
    }
}
