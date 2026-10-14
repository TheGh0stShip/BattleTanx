#include "types.h"

typedef struct {
    u8 pad000[0x28];
    s32 stat28;
    s32 stat2C;
    s32 stat30;
    u8 pad034[0x1DC];
    s32 stat210;
} PlayerStats;

extern void *gTextDisplayList __asm__("D_8037A174");
extern s32 gElapsedTicks __asm__("D_801B4AAC");
extern char D_800750D8[];
extern char D_800750E0[];
extern char D_800750EC[];
extern char D_800750FC[];
extern char D_80075104[];

extern void set_texture_draw_color(s32 red, s32 green, s32 blue, s32 alpha) __asm__("func_8010555C");
extern void func_80102050(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern PlayerStats *get_entity_record(u16 index) __asm__("func_800A6688");
extern void begin_text_draw(void **gfx) __asm__("func_8010698C");
extern void set_text_scale_mode(s32 mode) __asm__("func_801054E0");
extern void set_texture_draw_position(s32 x, s32 y) __asm__("func_8010552C");
extern void draw_text_string(void **gfx, char *text) __asm__("func_80105584");
extern void draw_text_number(void **gfx, s64 value) __asm__("func_801055D4");
extern void emit_minutes_seconds_text(void **gfx, s64 total) __asm__("func_8010595C");
extern void func_8010316C(void);

void draw_player_stats_screen(void) __asm__("func_80102F8C");

void draw_player_stats_screen(void) {
    PlayerStats *stats;

    set_texture_draw_color(0xFF, 0, 0, 0xFF);
    func_80102050(0x1C, 0x2D, 1, 0);
    stats = get_entity_record(0);
    begin_text_draw(&gTextDisplayList);
    set_texture_draw_color(0xFF, 0xFF, 0xFF, 0xFF);
    set_text_scale_mode(4);
    set_texture_draw_position(0x28, 0x43);
    draw_text_string(&gTextDisplayList, D_800750D8);
    set_texture_draw_position(0xB4, 0x43);
    draw_text_number(&gTextDisplayList, stats->stat28);
    set_texture_draw_position(0x28, 0x4F);
    draw_text_string(&gTextDisplayList, D_800750E0);
    set_texture_draw_position(0xB4, 0x4F);
    draw_text_number(&gTextDisplayList, stats->stat30);
    set_texture_draw_position(0x28, 0x5B);
    draw_text_string(&gTextDisplayList, D_800750EC);
    set_texture_draw_position(0xB4, 0x5B);
    draw_text_number(&gTextDisplayList, stats->stat2C);
    set_texture_draw_position(0x28, 0x67);
    draw_text_string(&gTextDisplayList, D_800750FC);
    set_texture_draw_position(0xBE, 0x67);
    emit_minutes_seconds_text(&gTextDisplayList, gElapsedTicks / 30);
    set_texture_draw_position(0x28, 0x73);
    draw_text_string(&gTextDisplayList, D_80075104);
    set_texture_draw_position(0xB4, 0x73);
    draw_text_number(&gTextDisplayList, stats->stat210);
    func_8010316C();
}
