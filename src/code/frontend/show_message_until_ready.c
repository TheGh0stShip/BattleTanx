#include "types.h"

extern u64 osGetTime(void) __asm__("func_801120A0");
extern void load_texture_draw_font(s32 font) __asm__("func_801053B0");
extern void begin_text_draw(u32 **gfx) __asm__("func_8010698C");
extern void set_texture_draw_color(s32 red, s32 green, s32 blue, s32 alpha) __asm__("func_8010555C");
extern void set_text_font(s32 font) __asm__("func_801054E0");
extern void set_texture_draw_position(s32 x, s32 y) __asm__("func_8010552C");
extern void draw_text_in_span(u32 **gfx, char *text, s32 left, s32 right) __asm__("func_80105A50");
extern void draw_filled_rectangle(u32 **gfx, s32 left, s32 top, s32 right, s32 bottom, s32 red, s32 green,
                                  s32 blue, s32 alpha) __asm__("func_800F4DFC");
extern void scan_controllers_and_paks(void) __asm__("func_800A90E0");
extern void func_8007968C(void);
extern void func_8007D850(void);
extern void func_8007D998(void);
extern void func_8007EEF8(s32, u32 *);
extern u64 D_80145DA0;
extern s32 D_80126714;
extern s32 D_803276D0;
extern u32 *gFrameDisplayList __asm__("D_803276D4");
extern u32 *gTextDisplayList __asm__("D_803276D4");
extern u32 *gCaptionDisplayList __asm__("D_803276D4");
extern s32 D_803276D8;
extern char D_800731B0[];

s32 show_message_until_ready(void) __asm__("func_800AC070");

s32 show_message_until_ready(void)
{
    u64 deadline;
    register u64 now __asm__("$16");
    s32 next;
    s32 mask;
    s32 dl;
    u32 *cmd;

    load_texture_draw_font(1);
    deadline = 0;
next_frame:
    func_8007D850();
    gFrameDisplayList = (u32 *)(D_803276D0 + D_803276D8 * 0x11000);
    draw_filled_rectangle(&gFrameDisplayList, 0, 0, 320, 240, 0, 0, 0, 255);
    begin_text_draw(&gTextDisplayList);
    set_texture_draw_color(200, 200, 200, 255);
    set_text_font(1);
    set_texture_draw_position(0, 0x55);
    draw_text_in_span(&gCaptionDisplayList, D_800731B0, 0, 320);
    cmd = gFrameDisplayList;
    dl = D_803276D0 + D_803276D8 * 0x11000;
    gFrameDisplayList = cmd + 2;
    cmd[0] = 0xB8000000;
    cmd[1] = 0;
    func_8007EEF8(dl, cmd);
    next = D_803276D8 + 1;
    mask = -(next < 3);
    D_803276D8 = next & mask;
    func_8007968C();
    func_8007D998();
    if ((now = osGetTime() * 1000000 / D_80145DA0) <= deadline) {
        goto next_frame;
    }
    scan_controllers_and_paks();
    deadline = now + 500000;
    if (D_80126714 == 0) {
        goto next_frame;
    }
    return 0;
}
