/* Recovered from retail BattleTanx. */
#include "types.h"
/* RODATA_VRAM 0x80073F30 */
/* LDSYM D_80073C80=0x80073C80 */
/* LDSYM D_80073CA8=0x80073CA8 */
/* LDSYM D_80073CBC=0x80073CBC */
/* LDSYM D_80073CC8=0x80073CC8 */
/* LDSYM D_80073CDC=0x80073CDC */
/* LDSYM D_80073D90=0x80073D90 */
/* LDSYM D_80073D9C=0x80073D9C */
/* LDSYM D_80073DB0=0x80073DB0 */
/* LDSYM D_80134E64=0x80134E64 */
/* LDSYM D_80134FC0=0x80134FC0 */
/* LDSYM D_80134FD4=0x80134FD4 */
/* LDSYM D_80134FD8=0x80134FD8 */
/* LDSYM D_80134FDC=0x80134FDC */
/* LDSYM D_8037A174=0x8037A174 */
/* LDSYM func_800796F0=0x800796F0 */
/* LDSYM func_800D1BA0=0x800D1BA0 */
/* LDSYM func_800D3D10=0x800D3D10 */
/* LDSYM func_800DD310=0x800DD310 */
/* LDSYM func_80102050=0x80102050 */
/* LDSYM func_8010316C=0x8010316C */
/* LDSYM func_801054E0=0x801054E0 */
/* LDSYM func_8010552C=0x8010552C */
/* LDSYM func_8010555C=0x8010555C */
/* LDSYM func_80105584=0x80105584 */
/* LDSYM func_80105A50=0x80105A50 */
/* LDSYM func_8010698C=0x8010698C */
/* LDSYM func_8011CC84=0x8011CC84 */

typedef struct Gfx {
    u32 w0;
    u32 w1;
} Gfx;

extern void func_80102050(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern void func_8010316C(void);
extern void func_800DD310(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, char *out);
extern void set_text_scale_mode(s32 mode) __asm__("func_801054E0");
extern void set_texture_draw_position(s32 x, s32 y) __asm__("func_8010552C");
extern void set_texture_draw_color(s32 red, s32 green, s32 blue, s32 alpha) __asm__("func_8010555C");
extern void draw_text(Gfx **gfx, char *text, s32 arg2, s32 width) __asm__("func_80105A50");
extern void draw_text_string(Gfx **gfx, char *text) __asm__("func_80105584");
extern void begin_text_draw(Gfx **gfx) __asm__("func_8010698C");
extern s32 format_string(char *dst, char *fmt, ...) __asm__("func_8011CC84");
extern s16 allocate_and_play_sound(u32 index, s32 priority) __asm__("func_800796F0");
extern void draw_icon_grid(s32 count) __asm__("func_800D1BA0");
extern void draw_rank_title(u32 rank) __asm__("func_800D3D10");

extern Gfx *D_8037A174;
extern Gfx *D_8037A174_1 __asm__("D_8037A174");
extern Gfx *D_8037A174_6 __asm__("D_8037A174");
extern Gfx *D_8037A174_7 __asm__("D_8037A174");
extern Gfx *D_8037A174_9 __asm__("D_8037A174");
extern Gfx *D_8037A174_12 __asm__("D_8037A174");
extern Gfx *D_8037A174_13 __asm__("D_8037A174");
extern Gfx *D_8037A174_15 __asm__("D_8037A174");
extern u8 D_80134E64;
extern s32 D_80134FC0[8];
extern s32 gMenuGridBase __asm__("D_80134FD4");
extern s32 D_80134FD8;
extern s32 D_80134FDC;
extern char D_80073C80[];
extern char D_80073CA8[];
extern char D_80073CBC[];
extern char D_80073CC8[];
extern char D_80073CDC[];
extern char D_80073D90[];
extern char D_80073D9C[];
extern char D_80073DB0[];

void draw_round_over_screen(s32 score, s32 wave, s32 small, s32 large, s32 arg4, s32 arg5, s32 arg6)
    __asm__("func_800D3E28");

static inline void draw_footer_label(char *local, char *value)
{
    format_string(local, D_80073C80, value);
    set_texture_draw_position(0, 0xBE);
    draw_text(&D_8037A174, local, 0, 0x140);
}
static inline void draw_title_label(char *local)
{
    format_string(local, D_80073D90);
    set_texture_draw_position(0x49, 0x1E);
    draw_text(&D_8037A174, local, 0, 0x140);
}

static inline void draw_stage_label(char *local, s32 value)
{
    format_string(local, D_80073D9C, value);
    set_texture_draw_position(0, 0x3E);
    draw_text(&D_8037A174, local, 0, 0x140);
}

void draw_round_over_screen(s32 score, s32 wave, s32 small, s32 large, s32 arg4, s32 arg5, s32 arg6)
{
    s32 exact[2];
    s32 *exactp;
    char text[32];
    char value[16];
    char line[32];
    s32 stage;
    s32 count;
    s32 i;

    if (score == 0) {
        D_80134FD8 = gMenuGridBase + small * 6 + 15;
        D_80134FDC = D_80134FD8 + large * 40 + 30;
    }
    exactp = exact;
    for (i = 0; i < 8; i++) {
        if (score < D_80134FC0[i]) {
            *exactp = score == D_80134FC0[i - 1];
            exact[1] = score - D_80134FC0[i - 1];
            stage = i;
            goto found;
        }
    }
    stage = 8;
found:
    count = small + large;
    count--;
    set_texture_draw_color(0xFA, 0x1E, 0x1E, 0xFF);
    func_80102050(0x1C, 0x17, 0, 1);
    func_8010316C();
    set_texture_draw_color(0xFF, 0, 0, 0xFF);
    begin_text_draw(&D_8037A174_1);
    set_text_scale_mode(2);
    draw_title_label(text);
    set_texture_draw_color(0xFF, 0xFF, 0xFF, 0xFF);
    set_text_scale_mode(4);
    func_800DD310(arg4, count, arg5, arg6, D_80134E64, value);
    draw_footer_label(line, value);
    switch (stage) {
    case 1:
        break;
    case 2:
        if (exact[0]) {
            allocate_and_play_sound(0x26, 0);
        }
        draw_stage_label(text, wave);
        break;
    case 3:
        if (exact[0]) {
            allocate_and_play_sound(0x26, 0);
        }
        draw_stage_label(text, wave);
        set_texture_draw_position(0x2E, 0x56);
        draw_text_string(&D_8037A174_6, D_80073DB0);
        break;
    case 5:
        set_texture_draw_color(0xFF, 0xFF, 0xFF, 0xFF);
        set_texture_draw_position(0x2E, 0x6A);
        draw_text_string(&D_8037A174_7, D_80073CA8);
    case 4:
        draw_stage_label(text, wave);
        draw_rank_title(wave);
        break;
    case 6:
        set_texture_draw_color(0xFF, 0xFF, 0xFF, 0xFF);
        set_texture_draw_position(0x2E, 0x6A);
        draw_text_string(&D_8037A174_9, D_80073CA8);
        draw_stage_label(text, wave);
        draw_rank_title(wave);
        count = exact[1] / 6;
        if (small < count) {
            count = small;
        } else if (exact[1] != 0 && exact[1] == count * 6) {
            allocate_and_play_sound(1, 0);
        }
        draw_icon_grid(count);
        break;
    case 7:
        draw_stage_label(text, wave);
        draw_rank_title(wave);
        if (large != 0) {
            set_texture_draw_color(0xFF, 0xFF, 0xFF, 0xFF);
            set_texture_draw_position(0x2E, 0x6A);
            draw_text_string(&D_8037A174_12, D_80073CC8);
        } else {
            set_texture_draw_color(0xFF, 0xFF, 0xFF, 0xFF);
            set_texture_draw_position(0x2E, 0x6A);
            draw_text_string(&D_8037A174_13, D_80073CDC);
        }
        count = exact[1] / 40;
        if (large < count) {
            count = large;
        } else if (exact[1] != 0 && exact[1] == count * 40) {
            allocate_and_play_sound(3, 0);
        }
        draw_icon_grid(small + count);
        break;
    case 8:
        draw_stage_label(text, wave);
        draw_rank_title(wave);
        set_texture_draw_color(0xFF, 0xFF, 0xFF, 0xFF);
        set_texture_draw_position(0x2E, 0x6A);
        draw_text_string(&D_8037A174_15, D_80073CBC);
        draw_icon_grid(small + large);
        break;
    }
}
