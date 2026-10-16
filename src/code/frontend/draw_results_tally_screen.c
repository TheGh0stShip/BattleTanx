#include "types.h"

extern void func_80102050(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern void func_8010316C(void);
extern void func_800DD310(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, char *out);
extern s32 classify_list_row(s32 row, s32 count1, s32 count2, s32 count3, s32 count4, s32 *isFirst, s32 *offset) __asm__("func_800D1F20");
extern void draw_icon_grid(s32 count) __asm__("func_800D1BA0");
extern void set_text_font(s32 font) __asm__("func_801054C0");
extern void set_text_scale_mode(s32 mode) __asm__("func_801054E0");
extern void set_texture_draw_position(s32 x, s32 y) __asm__("func_8010552C");
extern void set_texture_draw_color(s32 red, s32 green, s32 blue, s32 alpha) __asm__("func_8010555C");
extern void draw_text_string(void **gfx, char *text) __asm__("func_80105584");
extern void draw_text_integer(void **gfx, s64 value) __asm__("func_80105688");
extern void draw_text_mark_digits(void **gfx, char *text) __asm__("func_80105750");
extern void draw_text(void **gfx, char *text, s32 arg2, s32 width) __asm__("func_80105A50");
extern void begin_text_draw(void **gfx) __asm__("func_8010698C");
extern s32 format_string(char *dst, char *fmt, ...) __asm__("func_8011CC84");
extern s16 allocate_and_play_sound(u32 index, s32 priority) __asm__("func_800796F0");

extern void *gTextDisplayList __asm__("D_8037A174");

extern u8 D_80134E64;
extern char D_80073C80[];
extern char D_80073C8C[];
extern char D_80073C94[];
extern char D_80073C9C[];
extern char D_80073CA8[];
extern char D_80073CBC[];
extern char D_80073CC8[];
extern char D_80073CDC[];
extern char D_80073CEC[];
extern char D_80073CF8[];
extern char D_80073D08[];
extern char D_80073D14[];
extern char D_80073D18[];
extern char D_80073D34[];

void draw_results_tally_screen(s32 row, s32 score, s32 kills, s32 time2, s32 time1, s32 bonus,
                               s32 count1, s32 count2, s32 count3, s32 showFooter, s32 footerA,
                               s32 footerB) __asm__("func_800D20E4");

static inline void draw_footer_label(char *local, char *value) {
    format_string(local, D_80073C80, value);
    set_texture_draw_position(0, 0xBE);
    draw_text(&gTextDisplayList, local, 0, 0x140);
}

static inline void draw_time_in(s32 y, s32 ticks, char *buf) {
    s32 seconds;
    s32 minutes;

    seconds = ticks / 30;
    minutes = seconds / 60;
    format_string(buf, D_80073D14, seconds % 60 + 100);
    format_string(buf + 8, D_80073D18, minutes, buf + 1);
    set_texture_draw_color(0xFF, 0xFF, 0xFF, 0xFF);
    set_texture_draw_position(0xEC, y);
    draw_text_mark_digits(&gTextDisplayList, buf + 8);
}

static inline void draw_label(s32 y, char *text) {
    set_texture_draw_color(0xFF, 0xFF, 0xFF, 0xFF);
    set_texture_draw_position(0x2E, y);
    draw_text_string(&gTextDisplayList, text);
}

static inline void draw_value(s32 r, s32 g, s32 b, s32 y, s32 value) {
    set_texture_draw_color(r, g, b, 0xFF);
    set_texture_draw_position(0x10C, y);
    draw_text_integer(&gTextDisplayList, value);
}

static inline void draw_time(s32 y, s32 ticks) {
    char secondsText[8];
    char text[0x10];
    s32 seconds;
    s32 minutes;

    seconds = ticks / 30;
    minutes = seconds / 60;
    format_string(secondsText, D_80073D14, seconds % 60 + 100);
    format_string(text, D_80073D18, minutes, secondsText + 1);
    set_texture_draw_color(0xFF, 0xFF, 0xFF, 0xFF);
    set_texture_draw_position(0xEC, y);
    draw_text_mark_digits(&gTextDisplayList, text);
}

void draw_results_tally_screen(s32 row, s32 score, s32 kills, s32 time2, s32 time1, s32 bonus,
                               s32 count1, s32 count2, s32 count3, s32 showFooter, s32 footerA,
                               s32 footerB) {
    s32 isFirst;
    s32 offset;
    s32 section;
    s32 total;
    s32 shown;
    s32 n;
    s32 count;

    section = classify_list_row(row, count1, count2, bonus, count3, &isFirst, &offset);
    count = count1 + count2;
    count--;
    total = score + bonus;
    set_texture_draw_color(0xFA, 0x1E, 0x1E, 0xFF);
    func_80102050(0x1C, 0x17, 1, 1);
    func_8010316C();
    set_text_font(8);
    set_texture_draw_color(0xFF, 0, 0, 0xFF);
    begin_text_draw(&gTextDisplayList);
    set_texture_draw_color(0xFF, 0xFF, 0xFF, 0xFF);
    {
        {
            char value[16];
            char label[32];
            char *valuep;

            valuep = value;
            set_text_scale_mode(4);
            if (showFooter) {
                func_800DD310(footerA, count, total, footerB, D_80134E64, valuep);
                draw_footer_label(label, valuep);
            }
        }
    }
    {
        char buf[32];

    switch (section) {
    case 0:
        break;
    case 1:
        if (isFirst) {
            allocate_and_play_sound(0x26, 0);
        }
        draw_label(0x3A, D_80073C8C);
        if (offset >= 0x10) {
            draw_value(0xFF, 0xFF, 0, 0x3A, score);
        }
        break;
    case 2:
        if (isFirst) {
            allocate_and_play_sound(0x26, 0);
        }
        draw_value(0xFF, 0xFF, 0, 0x3A, score);
        draw_label(0x3A, D_80073C8C);
        draw_label(0x46, D_80073C94);
        if (offset >= 0x10) {
            draw_value(0xFF, 0xFF, 0xFF, 0x46, kills);
        }
        break;
    case 3:
        if (isFirst) {
            allocate_and_play_sound(0x26, 0);
        }
        draw_value(0xFF, 0xFF, 0, 0x3A, score);
        draw_label(0x3A, D_80073C8C);
        draw_value(0xFF, 0xFF, 0xFF, 0x46, kills);
        draw_label(0x46, D_80073C94);
        draw_label(0x52, D_80073C9C);
        if (offset >= 0x10) {
            draw_time_in(0x52, time1, buf);
        }
        break;
    case 4:
        if (isFirst) {
            allocate_and_play_sound(0x26, 0);
        }
        draw_value(0xFF, 0xFF, 0, 0x3A, score);
        draw_label(0x3A, D_80073C8C);
        draw_value(0xFF, 0xFF, 0xFF, 0x46, kills);
        draw_label(0x46, D_80073C94);
        draw_time_in(0x52, time1, buf);
        draw_label(0x52, D_80073C9C);
        draw_label(0x5E, D_80073D08);
        if (offset >= 0x10) {
            draw_time_in(0x5E, time2, buf);
        }
        break;
    case 5:

        shown = score + offset / 2 * 200;
        if (score + bonus < shown) {
            shown = score + bonus;
        } else if (offset != 0 && !(offset & 1)) {
            allocate_and_play_sound(0x1C, 0);
        }
        draw_value(0xFF, 0xFF, 0, 0x3A, shown);
        draw_label(0x3A, D_80073C8C);
        draw_value(0xFF, 0xFF, 0xFF, 0x46, kills);
        draw_label(0x46, D_80073C94);
        draw_time(0x52, time1);
        draw_label(0x52, D_80073C9C);
        draw_time(0x5E, time2);
        draw_label(0x5E, D_80073D08);
        format_string(buf, D_80073D34, bonus - (shown - score));
        set_texture_draw_color(0, 0xFF, 0, 0xFF);
        set_texture_draw_position(0x2E, 0x76);
        draw_text_string(&gTextDisplayList, buf);
        break;
    case 6:
        draw_value(0xFF, 0xFF, 0, 0x3A, score + bonus);
        draw_label(0x3A, D_80073C8C);
        draw_value(0xFF, 0xFF, 0xFF, 0x46, kills);
        draw_label(0x46, D_80073C94);
        draw_time(0x52, time1);
        draw_label(0x52, D_80073C9C);
        draw_time(0x5E, time2);
        draw_label(0x5E, D_80073D08);
        draw_label(0x6A, D_80073CA8);
        draw_value(0xFF, 0xFF, 0xFF, 0x6A, count1);
        n = offset / 6;
        if (count1 < n) {
            n = count1;
        } else if (offset != 0 && offset == n * 6) {
            allocate_and_play_sound(1, 0);
        }
        draw_icon_grid(n);
        break;
    case 7:
        draw_value(0xFF, 0xFF, 0, 0x3A, score + bonus);
        draw_label(0x3A, D_80073C8C);
        draw_value(0xFF, 0xFF, 0xFF, 0x46, kills);
        draw_label(0x46, D_80073C94);
        draw_time(0x52, time1);
        draw_label(0x52, D_80073C9C);
        draw_time(0x5E, time2);
        draw_label(0x5E, D_80073D08);
        if (count2 != 0) {
            draw_label(0x6A, D_80073CC8);
            draw_value(0xFF, 0xFF, 0xFF, 0x6A, count2);
        } else {
            draw_label(0x6A, D_80073CDC);
        }
        n = offset / 40;
        if (count2 < n) {
            n = count2;
        } else if (offset != 0 && offset == n * 40) {
            allocate_and_play_sound(3, 0);
        }
        draw_icon_grid(count1 + n);
        break;
    case 8:
        draw_value(0xFF, 0xFF, 0, 0x3A, score + bonus);
        draw_label(0x3A, D_80073C8C);
        draw_value(0xFF, 0xFF, 0xFF, 0x46, kills);
        draw_label(0x46, D_80073C94);
        draw_time(0x52, time1);
        draw_label(0x52, D_80073C9C);
        draw_time(0x5E, time2);
        draw_label(0x5E, D_80073D08);
        if (count3 != 0) {
            draw_label(0x6A, D_80073CEC);
            draw_value(0xFF, 0xFF, 0xFF, 0x6A, count3);
        } else {
            draw_label(0x6A, D_80073CF8);
        }
        n = offset / 40;
        if (count3 < n) {
            n = count3;
        } else if (offset != 0 && offset == n * 40) {
            allocate_and_play_sound(0xD, 0);
        }
        draw_icon_grid(count1 + count2 - n);
        break;
    case 9:
        draw_value(0xFF, 0xFF, 0, 0x3A, score + bonus);
        draw_label(0x3A, D_80073C8C);
        draw_value(0xFF, 0xFF, 0xFF, 0x46, kills);
        draw_label(0x46, D_80073C94);
        draw_time(0x52, time1);
        draw_label(0x52, D_80073C9C);
        draw_time(0x5E, time2);
        draw_label(0x5E, D_80073D08);
        draw_label(0x6A, D_80073CBC);
        n = count1 + count2;
        n -= count3;
        draw_value(0xFF, 0xFF, 0xFF, 0x6A, n);
        draw_icon_grid(n);
        break;
    }
    }
}
