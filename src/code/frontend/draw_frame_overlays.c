#include "types.h"

typedef struct Gfx {
    u32 w0;
    u32 w1;
} Gfx;

typedef struct ResourceBundle {
    s32 count;
    s32 entryOffset[3];
} ResourceBundle;

typedef struct DisplayListBuffer {
    Gfx commands[0x1000];
} DisplayListBuffer;

typedef struct TitleImage {
    s32 width;
    s32 height;
    s32 pad08;
    s32 pad0C;
} TitleImage;

typedef struct CaptionEntry {
    s32 unk0;
    s32 unk4;
} CaptionEntry;

#define GFX_COMMAND(packet, first, second) { \
    Gfx *command = (packet); \
    command->w0 = (first); \
    command->w1 = (second); \
}

#define BUNDLE_ENTRY(index) (gHudBundle.entryOffset[index] + (s32)&gHudBundle)

extern Gfx *gHudDisplayList __asm__("D_8037A174");
extern u8 gHudAlpha __asm__("D_8037A170");
extern s32 gHudViewportCount __asm__("D_8037A140");
extern u32 gDisplayListIndex __asm__("D_801416F4");
extern DisplayListBuffer gDisplayListBuffers[] __asm__("D_80362120");
extern u8 gMasterDisplayList[] __asm__("D_01000138");
extern ResourceBundle gHudBundle __asm__("D_8037FD80");
extern s32 gGameMode __asm__("D_8012578C");
extern s32 D_801B4AD4;
extern u32 D_801B4AD0;
extern s32 D_801B4AC0;
extern u8 D_801B4AE8;
extern u8 D_80135770;
extern u8 D_8013576F;
extern s32 D_80327B4C;
extern CaptionEntry D_8014268C[];
extern s32 D_8037A164;
extern TitleImage D_80141770[];
extern u8 gTitleImage[] __asm__("D_80382D80");
extern s32 D_80362110;
extern s32 D_801428D8;
extern s32 D_801428DC;
extern s32 D_801428E0;
extern char *D_8037A168;
extern u8 D_8037FD78;
extern s32 D_80134E58;
extern u8 D_B030BFE0[];
extern u8 D_B03102D0[];
extern u8 D_B0312D90[];
extern u8 D_B0316C60[];

extern s32 get_difficulty_level(void) __asm__("func_8007AAA0");
extern void func_8007EF40(void *dl);
extern void func_8007EF1C(void *dl);
extern void func_800F66F0(void);
extern void begin_text_draw(Gfx **gfx) __asm__("func_8010698C");
extern void select_texture_draw_entry(s32 index) __asm__("func_801054E0");
extern void set_texture_draw_color(s32 red, s32 green, s32 blue, s32 alpha) __asm__("func_8010555C");
extern void set_texture_draw_position(s32 x, s32 y) __asm__("func_8010552C");
extern void draw_centered_text(Gfx **gfx, char *text, s32 left, s32 right) __asm__("func_80105A50");
extern void draw_text(Gfx **gfx, char *text) __asm__("func_80105584");
extern void func_80105C68(Gfx **gfx, s32 a, s32 b, s32 c, s32 d);
extern void draw_paletted_image(Gfx **list, u8 *texels, s32 arg2, s32 arg3, s32 width, s32 height, s32 tileWidth,
                                s32 tileHeight, s32 x, s32 y, s32 width2, s32 height2, s32 s, s32 t,
                                f32 scaleX, f32 scaleY) __asm__("func_800F3D40");
extern void func_800B8804(Gfx **gfx);
extern void func_800BC4A8(Gfx **gfx);
extern void func_800BFFC8(Gfx **gfx);
extern void func_800C3730(Gfx **gfx);
extern void func_800C4E44(Gfx **gfx);
extern void func_80105290(Gfx **gfx);
extern void draw_pause_menu(void) __asm__("func_800FFF78");
extern s32 *get_game_mode(void) __asm__("func_8007AAF4");
extern s32 find_sound_instance(s32 soundId, s32 index) __asm__("func_800796F0");
extern void func_800F4794(s32 arg0);
extern s32 game_mode_is_3_through_6(void) __asm__("func_8007C6D8");
extern void rom_dma_read(u8 *romAddress, void *destination, u32 size) __asm__("func_80077930");
extern void draw_player_hud(s32 mode) __asm__("func_800F6934");
extern void draw_two_player_hud(s32 mode) __asm__("func_800F8120");
extern void draw_three_player_hud(s32 mode) __asm__("func_800F9F34");
extern void draw_four_player_hud(s32 mode) __asm__("func_800FC674");

void draw_frame_overlays(void) __asm__("func_800F5B6C");

void draw_frame_overlays(void)
{
    s32 mode;
    s32 phase;
    s32 offset;
    u8 *src;
    u32 size;
    u8 *end;
    s32 width;

    gHudAlpha = 0xFF;
    gHudViewportCount = get_difficulty_level();
    gHudDisplayList = gDisplayListBuffers[gDisplayListIndex].commands;
    func_8007EF40(gMasterDisplayList);
    func_8007EF1C(gMasterDisplayList);
    GFX_COMMAND(gHudDisplayList++, 0xE7000000U, 0);
    GFX_COMMAND(gHudDisplayList++, 0xBA001402U, 0);
    GFX_COMMAND(gHudDisplayList++, 0xFCFFFFFFU, 0xFFFCF279U);
    GFX_COMMAND(gHudDisplayList++, 0xB900031DU, 0x0F0A4000);
    GFX_COMMAND(gHudDisplayList++, 0xBA001301U, 0);
    GFX_COMMAND(gHudDisplayList++, 0xBA001001U, 0);
    GFX_COMMAND(gHudDisplayList++, 0xBA000C02U, 0);
    GFX_COMMAND(gHudDisplayList++, 0xBA000903U, 0xC00);
    GFX_COMMAND(gHudDisplayList++, 0xBA000E02U, 0x8000);
    func_800F66F0();
    if (gGameMode == 9 || gGameMode == 10) {
        if (D_801B4AD4 == 0) {
            begin_text_draw(&gHudDisplayList);
            select_texture_draw_entry(2);
            set_texture_draw_color(0xFA, 0x1E, 0x1E, 0xFF);
            set_texture_draw_position(0, 0x64);
            draw_centered_text(&gHudDisplayList, "Insert Rumble Paks Now", 0, 0x140);
            select_texture_draw_entry(4);
            set_texture_draw_color(0xFF, 0xFF, 0xFF, 0xFF);
            set_texture_draw_position(0x64, 0x8C);
            draw_text(&gHudDisplayList, "PRESS    TO CONTINUE");
            GFX_COMMAND(gHudDisplayList++, 0xFCFFFFFFU, 0xFFFCF279U);
            GFX_COMMAND(gHudDisplayList++, 0xBA000E02U, 0x8000);
            GFX_COMMAND(gHudDisplayList++, 0xFD100000U, BUNDLE_ENTRY(1));
            GFX_COMMAND(gHudDisplayList++, 0xE8000000U, 0);
            GFX_COMMAND(gHudDisplayList++, 0xF5000100U, 0x07000000);
            GFX_COMMAND(gHudDisplayList++, 0xE6000000U, 0);
            GFX_COMMAND(gHudDisplayList++, 0xF0000000U, 0x073FC000);
            GFX_COMMAND(gHudDisplayList++, 0xE7000000U, 0);
            draw_paletted_image(&gHudDisplayList, (u8 *)(BUNDLE_ENTRY(1) + 0x200), 2, 1, 9, 9, 0x20, 0x20, 0x8E, 0x8C,
                                9, 9, 0, 0, 1.0f, 1.0f);
        }
    } else if (gGameMode == 8 || D_80135770 != 0 || D_8013576F != 0) {
        if (D_80327B4C == 0xF) {
            func_800B8804(&gHudDisplayList);
        }
        if (D_80327B4C == 0x10) {
            func_800BC4A8(&gHudDisplayList);
        }
        if (D_80327B4C == 0x11) {
            func_800BFFC8(&gHudDisplayList);
        }
        if (D_80327B4C == 0x12) {
            func_800C3730(&gHudDisplayList);
        }
        if (D_80327B4C == 0x13) {
            func_800C4E44(&gHudDisplayList);
        }
        if (D_80327B4C == 2) {
            func_80105290(&gHudDisplayList);
        }
    } else if (gGameMode == 2) {
        draw_pause_menu();
    } else {
        if (gGameMode == 3 && D_801B4AD0 < 0x11) {
            if (*get_game_mode() == 7) {
                gGameMode = 4;
            } else {
                begin_text_draw(&gHudDisplayList);
                select_texture_draw_entry(4);
                set_texture_draw_color(0xFF, 0xFF, 0xFF, ~D_801B4AD4 & 0xFF);
                set_texture_draw_position(0x23, 0x20);
                func_80105C68(&gHudDisplayList, D_8014268C[D_801B4AD0].unk4, D_8014268C[D_801B4AD0].unk0, 0xE, 0);
            }
        }
        mode = gGameMode;
        if (mode == 4) {
            if (D_801B4AE8 != 0) {
                find_sound_instance(0xC, 0);
                D_801B4AE8 = 0;
            }
            if (D_801B4AD4 == D_801B4AC0 * 3) {
                find_sound_instance(0x14, 0);
            }
            offset = D_801B4AD4 - D_801B4AC0 * 4;
            phase = D_801B4AD4 / D_801B4AC0;
            offset = (offset >= 0) ? offset * 0x10 : 0;
            GFX_COMMAND(gHudDisplayList++, 0xBA000602U, 0x40);
            GFX_COMMAND(gHudDisplayList++, 0xBA000402U, 0x30);
            if (D_8037A164 != -1) {
                GFX_COMMAND(gHudDisplayList++, 0xE7000000U, 0);
                GFX_COMMAND(gHudDisplayList++, 0xBA001402U, 0);
                GFX_COMMAND(gHudDisplayList++, 0xB900031DU, 0x504240);
                GFX_COMMAND(gHudDisplayList++, 0xFCFFFFFFU, 0xFFFCF279U);
                GFX_COMMAND(gHudDisplayList++, 0xBA001301U, 0);
                GFX_COMMAND(gHudDisplayList++, 0xBA001001U, 0);
                GFX_COMMAND(gHudDisplayList++, 0xBA000C02U, 0);
                GFX_COMMAND(gHudDisplayList++, 0xBA000903U, 0xC00);
                GFX_COMMAND(gHudDisplayList++, 0xBA000E02U, 0x8000);
                width = D_80141770[D_8037A164].width;
                GFX_COMMAND(gHudDisplayList++, 0xFD100000U, gTitleImage);
                GFX_COMMAND(gHudDisplayList++, 0xE8000000U, 0);
                GFX_COMMAND(gHudDisplayList++, 0xF5000100U, 0x07000000);
                GFX_COMMAND(gHudDisplayList++, 0xE6000000U, 0);
                GFX_COMMAND(gHudDisplayList++, 0xF0000000U, 0x073FC000);
                GFX_COMMAND(gHudDisplayList++, 0xE7000000U, 0);
                draw_paletted_image(&gHudDisplayList, gTitleImage + 0x200, 2, 1, D_80141770[D_8037A164].width,
                                    D_80141770[D_8037A164].height, 0x20, 0x20,
                                    (0x140 - width) / 2, 0x26 - offset,
                                    D_80141770[D_8037A164].width, D_80141770[D_8037A164].height, 0, 0, 1.0f, 1.0f);
            }
            if ((u32)phase < 3) {
                if (D_80362110 != phase) {
                    find_sound_instance(1, 0);
                }
                func_800F4794(phase);
                D_801428D8++;
                if (game_mode_is_3_through_6()) {
                    begin_text_draw(&gHudDisplayList);
                    select_texture_draw_entry(4);
                    set_texture_draw_color(0xFF, 0xFF, 0xFF, 0xFF);
                    set_texture_draw_position(0, 0x78);
                    draw_centered_text(&gHudDisplayList, D_8037A168, 0, 0x140);
                }
            }
            D_80362110 = phase;
            D_801428DC++;
            D_801428E0++;
        }
        if (gGameMode == 1 && D_8037FD78 < 3 && ++D_8037FD78 == 3 && D_80134E58 > 0) {
            if (D_80134E58 < 3) {
                end = D_B03102D0;
                src = D_B030BFE0;
            } else if (D_80134E58 < 5) {
                end = D_B0316C60;
                src = D_B0312D90;
            } else {
                goto draw_hud;
            }
            size = end - src;
            if (size > 0x5000) {
                return;
            }
            rom_dma_read(src, gTitleImage, size);
        }
    draw_hud:
        if (gGameMode == 1 || gGameMode == 5 || gGameMode == 6 || gGameMode == 7) {
            switch (gHudViewportCount) {
            case 1:
                draw_player_hud(gGameMode);
                break;
            case 2:
                draw_two_player_hud(gGameMode);
                break;
            case 3:
                draw_three_player_hud(gGameMode);
                break;
            case 4:
                draw_four_player_hud(gGameMode);
                break;
            }
        }
    }
    GFX_COMMAND(gHudDisplayList++, 0xB8000000U, 0);
    func_8007EF40(gDisplayListBuffers[gDisplayListIndex].commands);
    gDisplayListIndex++;
    if (gDisplayListIndex >= 3) {
        gDisplayListIndex = 0;
    }
}
