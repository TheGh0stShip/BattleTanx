#include "types.h"

typedef struct GfxCommand {
    u32 w0;
    u32 w1;
} GfxCommand;

typedef struct PlayerStats {
    u8 pad000[0x28];
    s32 stat28;
    s32 stat2C;
    s32 stat30;
    u8 pad034[0x188];
    u8 colorRed;
    u8 colorGreen;
    u8 colorBlue;
} PlayerStats;

#define GFX_WORDS(pkt, a, b)    \
    {                           \
        GfxCommand *_g = (pkt); \
        _g->w0 = (a);           \
        _g->w1 = (b);           \
    }

extern GfxCommand *gTextDisplayList __asm__("D_8037A174");
extern s32 gElapsedTicks __asm__("D_801B4AAC");
extern char D_800750D8[];
extern char D_800750E0[];
extern char D_800750EC[];
extern char D_800750FC[];
extern char D_8007510C[];
extern char D_80075114[];
extern u8 D_8037FD80[];
extern s32 D_8037FD84[2];
extern u8 D_8037FF80[];

extern void set_texture_draw_color(s32 red, s32 green, s32 blue, s32 alpha) __asm__("func_8010555C");
extern void func_80102A30(s32 x, s32 y);
extern s32 D_801428E4[];
extern s32 D_801428F4[];
extern s32 gPlayerCount __asm__("D_8037A140");
extern PlayerStats *get_entity_record(u16 index) __asm__("func_800A6688");
extern void begin_text_draw(GfxCommand **gfx) __asm__("func_8010698C");
extern void set_text_scale_mode(s32 mode) __asm__("func_801054E0");
extern void set_texture_draw_position(s32 x, s32 y) __asm__("func_8010552C");
extern void draw_text_string(GfxCommand **gfx, char *text) __asm__("func_80105584");
extern void draw_text_number(GfxCommand **gfx, s64 value) __asm__("func_801055D4");
extern void emit_minutes_seconds_text(GfxCommand **gfx, s64 total) __asm__("func_8010595C");
extern void draw_texture_rect(GfxCommand **gfx, u8 *texture, s32 fmt, s32 siz, s32 width, s32 height, s32 arg6,
                              s32 arg7, s32 x, s32 y, s32 arg10, s32 arg11, s32 arg12, s32 arg13, f32 scaleX,
                              f32 scaleY) __asm__("func_800F3D40");

void draw_party_stats_screen(void) __asm__("func_80104CD8");

void draw_party_stats_screen(void)
{
    PlayerStats *stats;
    u16 i;

    stats = get_entity_record(0);
    set_texture_draw_color(stats->colorRed, stats->colorGreen, stats->colorBlue, 0xFF);
    func_80102A30(0x17, 0xF);
    stats = get_entity_record(1);
    set_texture_draw_color(stats->colorRed, stats->colorGreen, stats->colorBlue, 0xFF);
    func_80102A30(0xA3, 0xF);
    stats = get_entity_record(2);
    set_texture_draw_color(stats->colorRed, stats->colorGreen, stats->colorBlue, 0xFF);
    func_80102A30(0x17, 0x7B);
    stats = get_entity_record(3);
    set_texture_draw_color(stats->colorRed, stats->colorGreen, stats->colorBlue, 0xFF);
    func_80102A30(0xA3, 0x7B);
    set_texture_draw_color(0xFF, 0xFF, 0xFF, 0xFF);
    set_text_scale_mode(4);
    for (i = 0; i < gPlayerCount; i++) {
        stats = get_entity_record(i);
        begin_text_draw(&gTextDisplayList);
        set_texture_draw_position(D_801428E4[i], D_801428F4[i]);
        draw_text_string(&gTextDisplayList, D_800750D8);
        set_texture_draw_position(D_801428E4[i] + 0x64, D_801428F4[i]);
        draw_text_number(&gTextDisplayList, stats->stat28);
        set_texture_draw_position(D_801428E4[i], D_801428F4[i] + 0xA);
        draw_text_string(&gTextDisplayList, D_800750E0);
        set_texture_draw_position(D_801428E4[i] + 0x64, D_801428F4[i] + 0xA);
        draw_text_number(&gTextDisplayList, stats->stat30);
        set_texture_draw_position(D_801428E4[i], D_801428F4[i] + 0x14);
        draw_text_string(&gTextDisplayList, D_800750EC);
        set_texture_draw_position(D_801428E4[i] + 0x64, D_801428F4[i] + 0x14);
        draw_text_number(&gTextDisplayList, stats->stat2C);
        set_texture_draw_position(D_801428E4[i], D_801428F4[i] + 0x1E);
        draw_text_string(&gTextDisplayList, D_800750FC);
        set_texture_draw_position(D_801428E4[i] + 0x6E, D_801428F4[i] + 0x1E);
        emit_minutes_seconds_text(&gTextDisplayList, gElapsedTicks / 30);
        set_texture_draw_position(D_801428E4[i] + 0xD, D_801428F4[i] + 0x32);
        draw_text_string(&gTextDisplayList, D_8007510C);
        set_texture_draw_position(D_801428E4[i] + 0x53, D_801428F4[i] + 0x32);
        draw_text_string(&gTextDisplayList, D_80075114);
        GFX_WORDS(gTextDisplayList++, 0xFCFFFFFF, 0xFFFCF279);
        GFX_WORDS(gTextDisplayList++, 0xBA000E02, 0x8000);
        GFX_WORDS(gTextDisplayList++, 0xFD100000, (u32)&D_8037FD80[D_8037FD84[1]]);
        GFX_WORDS(gTextDisplayList++, 0xE8000000, 0);
        GFX_WORDS(gTextDisplayList++, 0xF5000100, 0x07000000);
        GFX_WORDS(gTextDisplayList++, 0xE6000000, 0);
        GFX_WORDS(gTextDisplayList++, 0xF0000000, 0x073FC000);
        GFX_WORDS(gTextDisplayList++, 0xE7000000, 0);
        draw_texture_rect(&gTextDisplayList, &D_8037FF80[D_8037FD84[1]], 2, 1, 9, 9, 0x20, 0x20, D_801428E4[i],
                          D_801428F4[i] + 0x32, 9, 9, 0, 0, 1.0f, 1.0f);
        GFX_WORDS(gTextDisplayList++, 0xFD100000, (u32)&D_8037FD80[D_8037FD84[0]]);
        GFX_WORDS(gTextDisplayList++, 0xE8000000, 0);
        GFX_WORDS(gTextDisplayList++, 0xF5000100, 0x07000000);
        GFX_WORDS(gTextDisplayList++, 0xE6000000, 0);
        GFX_WORDS(gTextDisplayList++, 0xF0000000, 0x073FC000);
        GFX_WORDS(gTextDisplayList++, 0xE7000000, 0);
        draw_texture_rect(&gTextDisplayList, &D_8037FF80[D_8037FD84[0]], 2, 1, 9, 9, 0x20, 0x20, D_801428E4[i] + 0x46,
                          D_801428F4[i] + 0x32, 9, 9, 0, 0, 1.0f, 1.0f);
    }
}
