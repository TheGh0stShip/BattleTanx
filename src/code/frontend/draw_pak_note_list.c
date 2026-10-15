#include "types.h"

typedef struct Gfx {
    u32 w0;
    u32 w1;
} Gfx;

typedef struct PakIconBundle {
    u8 pad00[0x4];
    s32 saveIconOffset;
    s32 loadIconOffset;
    u8 pad0C[0x4];
    s32 panelOffset;
} PakIconBundle;

typedef struct PakNote {
    u32 size;
    u8 pad04[0x6];
    u8 extension[0x4];
    u8 name[0x12];
} PakNote;

#define GFX_COMMAND(packet, first, second) { \
    Gfx *command = (packet); \
    command->w0 = (first); \
    command->w1 = (second); \
}

extern Gfx *gFrontendDisplayList __asm__("D_803276D4");
extern s32 gResourceTarget __asm__("D_803275F4");
extern s32 D_803275F8;
extern PakNote D_80327F50[16];
extern s32 D_80328150;
extern u8 D_80328158;
extern u8 D_80328159;
extern s32 D_8032815C;
extern s32 D_80328160;
extern s32 D_80328164;
extern s32 D_80328168;
extern u32 D_80134E70;
extern s32 D_80126710;

extern s32 func_800A942C(void);
extern s32 func_800A9484(s32 pak);
extern s32 func_800A95C0(s32 pak, PakNote *notes, s32 *count);
extern s32 func_800A9B70(s32 pak, s32 *freeBytes);
extern void draw_paletted_image(Gfx **list, u8 *texels, s32 arg2, s32 arg3, s32 width, s32 height, s32 tileWidth,
                                s32 tileHeight, s32 x, s32 y, s32 width2, s32 height2, s32 s, s32 t,
                                f32 scaleX, f32 scaleY) __asm__("func_800F3D40");
extern void begin_text_draw(Gfx **gfx) __asm__("func_8010698C");
extern void set_texture_draw_color(s32 red, s32 green, s32 blue, s32 alpha) __asm__("func_8010555C");
extern void select_texture_draw_entry(s32 index) __asm__("func_801054E0");
extern void set_texture_draw_position(s32 x, s32 y) __asm__("func_8010552C");
extern void draw_text(Gfx **gfx, char *text) __asm__("func_80105584");
extern void draw_number(Gfx **gfx, s64 value) __asm__("func_801055D4");
extern void format_note_name(char *buf, u8 *name) __asm__("func_800A9564");

void draw_pak_note_list(u8 highlight) __asm__("func_800CFEB0");

void draw_pak_note_list(u8 highlight)
{
    char buf[16];
    s32 i;

    if (D_8032815C == 0) {
        return;
    }
    if (D_80328160 != 0 && D_80328160 >= 3) {
        return;
    }
    if ((D_80134E70++ & 0x3F) == 0) {
        D_8032815C = func_800A942C();
        if (D_8032815C != 0) {
            D_80328160 = func_800A9484(D_8032815C);
            if (D_80328160 == 2 || D_80328160 == 0) {
                D_80328160 = func_800A95C0(D_8032815C, D_80327F50, &D_80328168);
                if (D_80328160 == 0) {
                    D_80328160 = func_800A9B70(D_8032815C, &D_80328164);
                }
            }
        } else {
            D_80328160 = 0;
        }
        if (D_80328160 == 0) {
            D_80328160 = D_80126710;
        }
    }
    /* The retail build does not advance the list here, so the combine command overwrites this sync. */
    GFX_COMMAND(gFrontendDisplayList, 0xE7000000U, 0);
    GFX_COMMAND(gFrontendDisplayList++, 0xFCFFFFFFU, 0xFFFCF279U);
    GFX_COMMAND(gFrontendDisplayList++, 0xBA000E02U, 0x8000);
    GFX_COMMAND(gFrontendDisplayList++, 0xB900031DU, 0x00504240);
    GFX_COMMAND(gFrontendDisplayList++, 0xFD100000U,
                ((PakIconBundle *)gResourceTarget)->panelOffset + gResourceTarget);
    GFX_COMMAND(gFrontendDisplayList++, 0xE8000000U, 0);
    GFX_COMMAND(gFrontendDisplayList++, 0xF5000100U, 0x07000000);
    GFX_COMMAND(gFrontendDisplayList++, 0xE6000000U, 0);
    GFX_COMMAND(gFrontendDisplayList++, 0xF0000000U, 0x073FC000);
    GFX_COMMAND(gFrontendDisplayList++, 0xE7000000U, 0);
    draw_paletted_image(&gFrontendDisplayList,
                        (u8 *)(((PakIconBundle *)gResourceTarget)->panelOffset + gResourceTarget + 0x200), 2, 1,
                        0x10B, 0x47, 0x20, 0x20, D_803275F8 + 0x1A, 0x97, 0x10B, 0x47, 0, 0, 1.0f, 1.0f);
    if (D_80328158 != 0) {
        GFX_COMMAND(gFrontendDisplayList++, 0xFD100000U,
                    ((PakIconBundle *)gResourceTarget)->loadIconOffset + gResourceTarget);
        GFX_COMMAND(gFrontendDisplayList++, 0xE8000000U, 0);
        GFX_COMMAND(gFrontendDisplayList++, 0xF5000100U, 0x07000000);
        GFX_COMMAND(gFrontendDisplayList++, 0xE6000000U, 0);
        GFX_COMMAND(gFrontendDisplayList++, 0xF0000000U, 0x073FC000);
        GFX_COMMAND(gFrontendDisplayList++, 0xE7000000U, 0);
        draw_paletted_image(&gFrontendDisplayList,
                            (u8 *)(((PakIconBundle *)gResourceTarget)->loadIconOffset + gResourceTarget + 0x200), 2,
                            1, 0xD, 0xD, 0x20, 0x20, D_803275F8 + 0x1A, 0x99, 0xD, 0xD, 0, 0, 1.0f, 1.0f);
        D_80328158--;
    }
    if (D_80328159 != 0) {
        GFX_COMMAND(gFrontendDisplayList++, 0xFD100000U,
                    ((PakIconBundle *)gResourceTarget)->saveIconOffset + gResourceTarget);
        GFX_COMMAND(gFrontendDisplayList++, 0xE8000000U, 0);
        GFX_COMMAND(gFrontendDisplayList++, 0xF5000100U, 0x07000000);
        GFX_COMMAND(gFrontendDisplayList++, 0xE6000000U, 0);
        GFX_COMMAND(gFrontendDisplayList++, 0xF0000000U, 0x073FC000);
        GFX_COMMAND(gFrontendDisplayList++, 0xE7000000U, 0);
        draw_paletted_image(&gFrontendDisplayList,
                            (u8 *)(((PakIconBundle *)gResourceTarget)->saveIconOffset + gResourceTarget + 0x200), 2,
                            1, 0xE, 0xC, 0x20, 0x20, D_803275F8 + 0x1A, 0xC1, 0xE, 0xC, 0, 0, 1.0f, 1.0f);
        D_80328159--;
    }
    begin_text_draw(&gFrontendDisplayList);
    select_texture_draw_entry(1);
    set_texture_draw_position(D_803275F8 + 0x103, 0x8D);
    draw_text(&gFrontendDisplayList, "Used:");
    set_texture_draw_position(D_803275F8 + 0xF0, 0xD2);
    draw_text(&gFrontendDisplayList, "Free:");
    set_texture_draw_position(D_803275F8 + 0x119, 0xD2);
    draw_number(&gFrontendDisplayList, D_80328164 / 256);
    for (i = 0; i < 5; i++) {
        if (i + D_80328150 < 16) {
            set_texture_draw_position(D_803275F8 + 0x2B, i * 10 + 0x9B);
            if (highlight != 0 && i == 0) {
                set_texture_draw_color(200, 200, 200, 255);
            } else {
                set_texture_draw_color(255, 80, 0, 255);
            }
            if (D_80327F50[i + D_80328150].name[0] == 0) {
                draw_text(&gFrontendDisplayList, "Empty");
            } else {
                format_note_name(buf, D_80327F50[i + D_80328150].name);
                draw_text(&gFrontendDisplayList, buf);
                draw_text(&gFrontendDisplayList, ".");
                format_note_name(buf, D_80327F50[i + D_80328150].extension);
                draw_text(&gFrontendDisplayList, buf);
            }
            set_texture_draw_position(D_803275F8 + 0x114, i * 10 + 0x9B);
            draw_number(&gFrontendDisplayList, D_80327F50[i + D_80328150].size >> 8);
        }
    }
}
