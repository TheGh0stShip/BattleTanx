#include "types.h"

extern s32 format_string(char *dst, char *format, ...) __asm__("func_8011CC84");
extern void set_text_draw_position(s32 x, s32 y) __asm__("func_8010552C");
extern void draw_text_string(void *graphics, char *text) __asm__("func_80105584");
extern u8 gTextGraphics[] __asm__("D_8037A174");

void draw_rank_title(u32 rank) __asm__("func_800D3D10");

void draw_rank_title(u32 rank)
{
    char text[32];

    switch (rank) {
    case 0:
        format_string(text, "YOUR RANK: WEASEL");
        break;
    case 1:
        format_string(text, "YOUR RANK: NEWBIE");
        break;
    case 2:
        format_string(text, "YOUR RANK: ARMORED AMATEUR");
        break;
    case 3:
        format_string(text, "YOUR RANK: CAPTAIN COMPETENT");
        break;
    case 4:
        format_string(text, "YOUR RANK: BATTLE ASSASSIN");
        break;
    case 5:
        format_string(text, "YOUR RANK: CRUSHER");
        break;
    case 6:
        format_string(text, "YOUR RANK: DEVASTATOR");
        break;
    case 7:
        format_string(text, "YOUR RANK: WIZARD OF WAR");
        break;
    case 8:
        format_string(text, "YOUR RANK: NATURAL DISASTER");
        break;
    case 9:
        format_string(text, "YOUR RANK: ARMORED ADMIRAL");
        break;
    case 10:
    case 11:
    case 12:
    case 13:
        format_string(text, "YOUR RANK: BATTLELORD");
        break;
    default:
        format_string(text, "YOU ARE TOO GOOD TO BE RANKED");
        break;
    }
    set_text_draw_position(0x2E, 0x56);
    draw_text_string(gTextGraphics, text);
}
