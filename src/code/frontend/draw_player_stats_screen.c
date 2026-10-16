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
    draw_text_string(&gTextDisplayList, "KILLS ");
    set_texture_draw_position(0xB4, 0x43);
    draw_text_number(&gTextDisplayList, stats->stat28);
    set_texture_draw_position(0x28, 0x4F);
    draw_text_string(&gTextDisplayList, "UNITS LOST");
    set_texture_draw_position(0xB4, 0x4F);
    draw_text_number(&gTextDisplayList, stats->stat30);
    set_texture_draw_position(0x28, 0x5B);
    draw_text_string(&gTextDisplayList, "FRIENDLY FIRE");
    set_texture_draw_position(0xB4, 0x5B);
    draw_text_number(&gTextDisplayList, stats->stat2C);
    set_texture_draw_position(0x28, 0x67);
    draw_text_string(&gTextDisplayList, "TIME");
    set_texture_draw_position(0xBE, 0x67);
    emit_minutes_seconds_text(&gTextDisplayList, gElapsedTicks / 30);
    set_texture_draw_position(0x28, 0x73);
    draw_text_string(&gTextDisplayList, "SCORE");
    set_texture_draw_position(0xB4, 0x73);
    draw_text_number(&gTextDisplayList, stats->stat210);
    func_8010316C();
}

typedef struct GfxCommand {
    u32 w0;
    u32 w1;
} GfxCommand;

typedef struct GameModeInfo {
    u32 mode;
    s32 variant;
} GameModeInfo;

typedef struct IconSheet {
    s32 count;
    s32 offsets[2];
    u8 pad0C[0x1F4];
    u8 texels[1];
} IconSheet;

#define GFX_WORDS(pkt, a, b)    \
    {                           \
        GfxCommand *_g = (pkt); \
        _g->w0 = (a);           \
        _g->w1 = (b);           \
    }

extern GfxCommand *gResultsDisplayList __asm__("D_8037A174");
extern IconSheet gIconSheet __asm__("D_8037FD80");

extern void *get_results_record(u16 index) __asm__("func_800A6688");
extern GameModeInfo *get_game_mode(void) __asm__("func_8007AAF4");
extern s32 get_record_result(void *record) __asm__("func_800A42B0");
extern void set_results_text_color(s32 red, s32 green, s32 blue, s32 alpha) __asm__("func_8010555C");
extern void begin_results_text(GfxCommand **gfx) __asm__("func_8010698C");
extern void set_results_text_mode(s32 mode) __asm__("func_801054E0");
extern void set_results_text_position(s32 x, s32 y) __asm__("func_8010552C");
extern void draw_results_text(GfxCommand **gfx, char *text) __asm__("func_80105584");
extern void draw_texture_rect(GfxCommand **gfx, u8 *texture, s32 fmt, s32 siz, s32 width, s32 height, s32 arg6,
                              s32 arg7, s32 x, s32 y, s32 arg10, s32 arg11, s32 arg12, s32 arg13, f32 scaleX,
                              f32 scaleY) __asm__("func_800F3D40");
extern char D_80075068[];

#define LOAD_ICON(n)                                                                       \
    GFX_WORDS(gResultsDisplayList++, 0xFD100000, (u32)((u8 *)&gIconSheet + gIconSheet.offsets[n]));    \
    GFX_WORDS(gResultsDisplayList++, 0xE8000000, 0);                                          \
    GFX_WORDS(gResultsDisplayList++, 0xF5000100, 0x07000000);                                 \
    GFX_WORDS(gResultsDisplayList++, 0xE6000000, 0);                                          \
    GFX_WORDS(gResultsDisplayList++, 0xF0000000, 0x073FC000);                                 \
    GFX_WORDS(gResultsDisplayList++, 0xE7000000, 0);

#define DRAW_ICON(n, x, y) \
    draw_texture_rect(&gResultsDisplayList, &gIconSheet.texels[gIconSheet.offsets[n]], 2, 1, 9, 9, 0x20, 0x20, x, y, \
                      9, 9, 0, 0, 1.0f, 1.0f)

void draw_results_menu_options(void) __asm__("func_8010316C");

void draw_results_menu_options(void)
{
    void *record;

    record = get_results_record(0);
    switch (get_game_mode()->mode) {
    case 0:
    case 1:
    case 2:
    case 9:
        set_results_text_position(0x72, 0x7E);
        draw_results_text(&gResultsDisplayList, "REPLAY");
        set_results_text_position(0xBC, 0x7E);
        draw_results_text(&gResultsDisplayList, "EXIT");
        GFX_WORDS(gResultsDisplayList++, 0xFCFFFFFF, 0xFFFCF279);
        GFX_WORDS(gResultsDisplayList++, 0xBA000E02, 0x8000);
        LOAD_ICON(1);
        DRAW_ICON(1, 0x66, 0x7E);
        LOAD_ICON(0);
        DRAW_ICON(0, 0xB0, 0x7E);
        break;
    case 3:
    case 4:
    case 5:
    case 6:
        begin_results_text(&gResultsDisplayList);
        set_results_text_mode(4);
        set_results_text_color(0xFF, 0xFF, 0xFF, 0xFF);
        if (get_record_result(record) == 2) {
            if (get_game_mode()->variant == 0x10) {
                set_results_text_position(0x3A, 0x9C);
                draw_results_text(&gResultsDisplayList, D_80075068);
            } else {
                set_results_text_position(0x8D, 0x9C);
                draw_results_text(&gResultsDisplayList, "SAVE AND CONTINUE");
                set_results_text_position(0x3A, 0x9C);
                draw_results_text(&gResultsDisplayList, D_80075068);
            }
        } else if (get_record_result(record) == 0) {
            set_results_text_position(0x72, 0x9C);
            draw_results_text(&gResultsDisplayList, "REPLAY");
            set_results_text_position(0xBC, 0x9C);
            draw_results_text(&gResultsDisplayList, "EXIT");
        }
        GFX_WORDS(gResultsDisplayList++, 0xFCFFFFFF, 0xFFFCF279);
        GFX_WORDS(gResultsDisplayList++, 0xBA000E02, 0x8000);
        LOAD_ICON(1);
        if (get_record_result(record) == 2) {
            if (get_game_mode()->variant == 0x10) {
                DRAW_ICON(1, 0x2E, 0x9C);
            } else {
                DRAW_ICON(1, 0x2E, 0x9C);
                LOAD_ICON(0);
                DRAW_ICON(0, 0x81, 0x9C);
            }
        } else if (get_record_result(record) == 0) {
            DRAW_ICON(1, 0x66, 0x9C);
            LOAD_ICON(0);
            DRAW_ICON(0, 0xB0, 0x9C);
        }
        break;
    case 7:
        begin_results_text(&gResultsDisplayList);
        set_results_text_mode(4);
        set_results_text_color(0xFF, 0xFF, 0xFF, 0xFF);
        if (get_record_result(record) == 0) {
            set_results_text_position(0x8D, 0x9C);
            draw_results_text(&gResultsDisplayList, "SAVE AND CONTINUE");
            set_results_text_position(0x3A, 0x9C);
            draw_results_text(&gResultsDisplayList, D_80075068);
        } else if (get_record_result(record) == 2) {
            set_results_text_position(0xBC, 0x9C);
            draw_results_text(&gResultsDisplayList, D_80075068);
        }
        GFX_WORDS(gResultsDisplayList++, 0xFCFFFFFF, 0xFFFCF279);
        GFX_WORDS(gResultsDisplayList++, 0xBA000E02, 0x8000);
        if (get_record_result(record) == 0) {
            LOAD_ICON(1);
            DRAW_ICON(1, 0x2E, 0x9C);
            LOAD_ICON(0);
            DRAW_ICON(0, 0x81, 0x9C);
        } else if (get_record_result(record) == 2) {
            LOAD_ICON(1);
            DRAW_ICON(1, 0x66, 0x9C);
        }
        break;
    }
}
