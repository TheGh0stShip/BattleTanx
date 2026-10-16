#include "types.h"

#define NULL ((void *)0)

typedef struct GfxCommand {
    u32 w0;
    u32 w1;
} GfxCommand;

typedef struct HudNode {
    u8 pad00[0xD];
    u8 owner;
    u8 pad0E[0x2C - 0xE];
    struct HudNode *next;
} HudNode;

typedef struct HudUnit {
    u8 pad000[0x1C];
    s32 health;
    s32 maxHealth;
    u8 pad024[0x98 - 0x24];
    HudNode *markers;
    u8 pad09C[0x408 - 0x9C];
    u8 primaryLit;
    u8 specialLit;
    u8 pad40A[0x468 - 0x40A];
    s32 weapon;
    u8 pad46C[0x476 - 0x46C];
    u16 special;
    u8 pad478[0x480 - 0x478];
    u16 ammo[1];
} HudUnit;

typedef struct HudPlayer {
    u8 pad000[0x10];
    s32 state;
    u8 pad014[0x20 - 0x14];
    s16 unitId;
    u8 bonus;
    u8 pad023[0x3A - 0x23];
    s16 score;
    u8 pad03C[0x1BC - 0x3C];
    u8 red;
    u8 green;
    u8 blue;
    u8 team;
    u8 pad1C0[0x218 - 0x1C0];
    s32 message;
    s32 messageExpire;
} HudPlayer;

typedef struct HudBank4 {
    s32 ofs[8];
    u8 pixels[1];
} HudBank4;

typedef struct HudBank8 {
    s32 ofs[0x80];
    u8 pixels[1];
} HudBank8;

#define GFX_COORD(value) (((value) * 4) & 0xFFF)
#define GFX_WORDS(pkt, a, b)    \
    {                           \
        GfxCommand *_g = (pkt); \
        _g->w0 = (a);           \
        _g->w1 = (b);           \
    }

#define BANK4_PAL(i) ((u8 *)&gHudBank4 + gHudBank4.ofs[i])
#define BANK4_PIX(i) (&gHudBank4.pixels[gHudBank4.ofs[i]])

#define LOAD_TEX4(i, tile, size, mask)                               \
    GFX_WORDS(gHudDisplayList++, 0xFD500000, (u32)BANK4_PIX(i));    \
    GFX_WORDS(gHudDisplayList++, 0xF5500000, 0x07000200);           \
    GFX_WORDS(gHudDisplayList++, 0xE6000000, 0);                    \
    GFX_WORDS(gHudDisplayList++, 0xF3000000, tile);                 \
    GFX_WORDS(gHudDisplayList++, 0xE7000000, 0);                    \
    GFX_WORDS(gHudDisplayList++, size, 0x200);                      \
    GFX_WORDS(gHudDisplayList++, 0xF2000000, mask);                 \
    GFX_WORDS(gHudDisplayList++, 0xFD100000, (u32)BANK4_PAL(i));    \
    GFX_WORDS(gHudDisplayList++, 0xE8000000, 0);                    \
    GFX_WORDS(gHudDisplayList++, 0xF5000100, 0x07000000);           \
    GFX_WORDS(gHudDisplayList++, 0xE6000000, 0);                    \
    GFX_WORDS(gHudDisplayList++, 0xF0000000, 0x0703C000);           \
    GFX_WORDS(gHudDisplayList++, 0xE7000000, 0)

#define RECT(xh, yh, xl, yl)                                                                     \
    GFX_WORDS(gHudDisplayList++, 0xE4000000 | (GFX_COORD(xh) << 12) | GFX_COORD(yh),           \
              (GFX_COORD(xl) << 12) | GFX_COORD(yl));                                           \
    GFX_WORDS(gHudDisplayList++, 0xB4000000, 0);                                                \
    GFX_WORDS(gHudDisplayList++, 0xB3000000, 0x04000400)

#define GREY(v) ((v) << 24 | (v) << 16 | (v) << 8 | gHudAlpha)

extern GfxCommand *gHudDisplayList __asm__("D_8037A174");
extern u8 gHudAlpha __asm__("D_8037A170");
extern HudBank4 gHudBank4 __asm__("D_8037AD78");
extern HudBank8 gHudBank8 __asm__("D_80382D80");
extern HudPlayer *gHudPlayer0 __asm__("D_8037A130");
extern HudPlayer *gHudPlayer1 __asm__("D_8037A134");
extern HudPlayer *gHudPlayer2 __asm__("D_8037A138");
extern HudPlayer *gHudPlayer3 __asm__("D_8037A13C");
extern HudUnit *gHudUnit0 __asm__("D_8037A120");
extern HudUnit *gHudUnit1 __asm__("D_8037A124");
extern HudUnit *gHudUnit2 __asm__("D_8037A128");
extern HudUnit *gHudUnit3 __asm__("D_8037A12C");
extern s32 gHudViewActive[4] __asm__("D_8037A150");
extern s32 gGameMode __asm__("D_8012578C");
extern s32 gGameTicks __asm__("D_801B4AA8");
extern u16 D_8014163C[4];
extern u16 D_80141644[4];
extern u16 D_8014164C[4];
extern u16 D_80141654[4];
extern s32 D_801416A0[];

extern HudPlayer *get_entity_record(u16 index) __asm__("func_800A6688");
extern HudUnit *get_unit(s16 id) __asm__("func_800A03B8");
extern void draw_party_stats_screen(void) __asm__("func_80104CD8");
extern void draw_viewport_message_pair(s32 messageId, s32 viewport, s32 viewportCount, char *customText)
    __asm__("func_80101E9C");
extern void draw_texture_rect(GfxCommand **gfx, u8 *texture, s32 fmt, s32 siz, s32 width, s32 height, s32 arg6,
                              s32 arg7, s32 x, s32 y, s32 arg10, s32 arg11, s32 arg12, s32 arg13, f32 scaleX,
                              f32 scaleY) __asm__("func_800F3D40");
extern void func_80100550(s32 arg0);
extern void draw_hud_level_map(s32 arg0) __asm__("func_801009E8");
extern s32 *get_game_mode(void) __asm__("func_8007AAF4");
extern s32 game_mode_is_3_through_6(void) __asm__("func_8007C6D8");
extern void draw_filled_rectangle(GfxCommand **list, s32 left, s32 top, s32 right, s32 bottom, s32 red, s32 green,
                                  s32 blue, s32 alpha) __asm__("func_800F4DFC");
extern void begin_text_draw(GfxCommand **gfx) __asm__("func_8010698C");
extern void set_text_scale_mode(s32 mode) __asm__("func_801054E0");
extern void set_texture_draw_color(s32 red, s32 green, s32 blue, s32 alpha) __asm__("func_8010555C");
extern void set_texture_draw_position(s32 x, s32 y) __asm__("func_8010552C");
extern void draw_text_number(GfxCommand **gfx, s64 value) __asm__("func_801055D4");
extern void draw_short_segment_bar(s32 x, s32 y, s32 value, s32 max) __asm__("func_800FFB58");

void draw_four_player_hud(void) __asm__("func_800FC674");

#define SETUP_VIEW(p)                                              \
    gHudPlayer##p = get_entity_record(p);                         \
    gHudUnit##p = get_unit(gHudPlayer##p->unitId);                \
    active##p = 0;                                                 \
    if (gHudPlayer##p->state == 1) {                              \
        active##p = gHudUnit##p != NULL;                           \
    }                                                              \
    gHudViewActive[p] = active##p

#define MARKERS(p, XH, XL, YH, YL)                                                                  \
    if (gHudViewActive[p] != 0) {                                                                   \
        for (node = gHudUnit##p->markers, markerX = 0; node != NULL; node = node->next, markerX += 5) {        \
            idx = get_entity_record(node->owner)->team + 9;                                         \
            LOAD_TEX4(idx, 0x070FF400, 0xF5400400, 0x0007C07C);                                     \
            RECT(XH, YH, XL, YL);                                                                   \
        }                                                                                           \
    }

#define BADGE(p, XH, YH, XL, YL)                                                                  \
    GFX_WORDS(gHudDisplayList++, 0xFA000101,                                                      \
              gHudPlayer##p->red << 24 | gHudPlayer##p->green << 16 | gHudPlayer##p->blue << 8 | gHudAlpha); \
    if (gHudViewActive[p] != 0) {                                                                 \
        RECT(XH, YH, XL, YL);                                                                     \
    }

#define SCORE(p, X, Y)                                                                    \
    if (gHudViewActive[p] != 0) {                                                         \
        set_texture_draw_position(X, Y);                                                  \
        score = gHudPlayer##p->score;                                                    \
        value = game_mode_is_3_through_6() ? score : gHudPlayer##p->bonus + score;        \
        draw_text_number(&gHudDisplayList, value);                                        \
    }

#define PANEL(p, X, YB)                                                                       \
    if (gHudViewActive[p] != 0) {                                                             \
        special##p = gHudUnit##p->special;                                                   \
        height##p = 0xD;                                                                      \
        specialAmmo##p = gHudUnit##p->ammo[special##p];                                      \
        if (special##p != 0) {                                                                \
            height##p = 0x20;                                                                 \
        }                                                                                     \
        draw_filled_rectangle(&gHudDisplayList, X, YB - height##p, 0x23, height##p, 0x32, 0x32, 0x32, 0xD2); \
        GFX_WORDS(gHudDisplayList++, 0xFC119623, 0xFF2FFFFF);                                 \
        GFX_WORDS(gHudDisplayList++, 0xBA000E02, 0x8000);                                     \
        GFX_WORDS(gHudDisplayList++, 0xB900031D, 0x00504240);                                 \
        GFX_WORDS(gHudDisplayList++, 0xFA000101, 0xFFFFFF00 | gHudAlpha);                     \
        RECT(X + 0x23, YB, X, YB - height##p);                                                \
    }

#define SPECIAL(p, X, Y, PRE, POST)                                                            \
    if ((gHudViewActive[p] != 0) & (special##p != 0)) {                                        \
        shade = gHudUnit##p->specialLit ? 0xFF : 0x40;                                        \
        PRE                                                                                    \
        GFX_WORDS(gHudDisplayList++, 0xFA000101, GREY(shade));                                 \
        LOAD_TEX4(D_801416A0[special##p], 0x070FF400, 0xF5400400, 0x0007C07C);                 \
        RECT(X + 0xD, Y + 0xD, X, Y);                                                          \
        POST                                                                                   \
        begin_text_draw(&gHudDisplayList);                                                     \
        set_texture_draw_position(X + 0x17, Y + 1);                                            \
        draw_text_number(&gHudDisplayList, specialAmmo##p);                                    \
    }

#define PRIMARY(p, X, Y)                                                                       \
    if (gHudViewActive[p] != 0) {                                                              \
        shade = gHudUnit##p->primaryLit ? 0xFF : 0x40;                                        \
        GFX_WORDS(gHudDisplayList++, 0xFA000101, GREY(shade));                                 \
        RECT(X + 0x15, Y - height##p, X, Y - 8 - height##p);                                   \
    }

void draw_four_player_hud(void)
{
    u16 special0, special1, special2, special3;
    u16 height0, height1, height2, height3;
    u16 specialAmmo0, specialAmmo1, specialAmmo2, specialAmmo3;
    s32 active0, active1, active2, active3;
    u16 i;
    HudPlayer *player;
    HudNode *node;
    u8 markerX;
    s32 score;
    u8 shade;
    s32 idx;
    s32 mode;
    s32 count;
    s32 value;

    count = 4;
    height0 = 0;
    height1 = 0;
    height2 = 0;
    height3 = 0;
    SETUP_VIEW(0);
    SETUP_VIEW(1);
    SETUP_VIEW(2);
    specialAmmo0 = 0;
    special0 = 0;
    specialAmmo1 = 0;
    special1 = 0;
    specialAmmo2 = 0;
    special2 = 0;
    specialAmmo3 = 0;
    special3 = 0;
    SETUP_VIEW(3);

    if (gGameMode == 7) {
        draw_party_stats_screen();
        return;
    }
    mode = 1;
    for (i = 0; i < count; i++) {
        markerX = 0;
        if (get_entity_record(i)->state == 0 || get_entity_record(i)->state == 2) {
            GFX_WORDS(gHudDisplayList++, 0xE7000000, 0);
            GFX_WORDS(gHudDisplayList++, 0xBA001402, 0);
            GFX_WORDS(gHudDisplayList++, 0xB900031D, 0x00504240);
            GFX_WORDS(gHudDisplayList++, 0xFCFFFFFF, 0xFFFCF279);
            GFX_WORDS(gHudDisplayList++, 0xBA001301, 0);
            GFX_WORDS(gHudDisplayList++, 0xBA001001, 0);
            GFX_WORDS(gHudDisplayList++, 0xBA000C02, 0);
            GFX_WORDS(gHudDisplayList++, 0xBA000903, 0xC00);
            GFX_WORDS(gHudDisplayList++, 0xBA000E02, 0x8000);
            if (get_entity_record(i)->state == 0) {
                GFX_WORDS(gHudDisplayList++, 0xFD100000, (u32)((u8 *)&gHudBank8 + gHudBank8.ofs[7]));
                GFX_WORDS(gHudDisplayList++, 0xE8000000, 0);
                GFX_WORDS(gHudDisplayList++, 0xF5000100, 0x07000000);
                GFX_WORDS(gHudDisplayList++, 0xE6000000, 0);
                GFX_WORDS(gHudDisplayList++, 0xF0000000, 0x073FC000);
                GFX_WORDS(gHudDisplayList++, 0xE7000000, 0);
                draw_texture_rect(&gHudDisplayList, &gHudBank8.pixels[gHudBank8.ofs[7]], 2, 1, 0x44, 0x19, 0x20,
                                  0x20, D_8014164C[i], D_80141654[i], 0x44, 0x19, 0, 0, 1.0f, 1.0f);
            } else {
                GFX_WORDS(gHudDisplayList++, 0xFD100000, (u32)((u8 *)&gHudBank8 + gHudBank8.ofs[12]));
                GFX_WORDS(gHudDisplayList++, 0xE8000000, 0);
                GFX_WORDS(gHudDisplayList++, 0xF5000100, 0x07000000);
                GFX_WORDS(gHudDisplayList++, 0xE6000000, 0);
                GFX_WORDS(gHudDisplayList++, 0xF0000000, 0x073FC000);
                GFX_WORDS(gHudDisplayList++, 0xE7000000, 0);
                draw_texture_rect(&gHudDisplayList, &gHudBank8.pixels[gHudBank8.ofs[12]], 2, 1, 0x5A, 0x19, 0x20,
                                  0x20, D_8014163C[i], D_80141644[i], 0x5A, 0x19, 0, 0, 1.0f, 1.0f);
            }
        } else {
            player = get_entity_record(i);
            if (player->message != 0) {
                draw_viewport_message_pair(player->message, i, mode + 2, (char *)player);
                if (gGameTicks > player->messageExpire) {
                    player->message = 0;
                }
            }
        }
    }
    func_80100550(mode + 3);
    GFX_WORDS(gHudDisplayList++, 0xFC119623, 0xFF2FFFFF);
    GFX_WORDS(gHudDisplayList++, 0xBA000E02, 0x8000);
    GFX_WORDS(gHudDisplayList++, 0xB900031D, 0x00504240);
    GFX_WORDS(gHudDisplayList++, 0xFA000101, 0xFFFFFF00 | gHudAlpha);
    MARKERS(0, markerX + 0x36, markerX + 0x16, 0x31, 0x11)
    MARKERS(1, 0x139 - markerX, 0x119 - markerX, 0x31, 0x11)
    MARKERS(2, markerX + 0x36, markerX + 0x16, 0x9F, 0x7F)
    MARKERS(3, 0x139 - markerX, 0x119 - markerX, 0x9F, 0x7F)
    if (*get_game_mode() != 0 && *get_game_mode() != 9 && *get_game_mode() != 7) {
        GFX_WORDS(gHudDisplayList++, 0xFC119623, 0xFF2FFFFF);
        GFX_WORDS(gHudDisplayList++, 0xBA000E02, 0x8000);
        GFX_WORDS(gHudDisplayList++, 0xB900031D, 0x00504240);
        LOAD_TEX4(18, 0x070FF400, 0xF5400400, 0x0007C07C);
        BADGE(0, 0x36, 0x31, 0x16, 0x11)
        BADGE(1, 0x142, 0x31, 0x122, 0x11)
        BADGE(2, 0x36, 0x9F, 0x16, 0x7F)
        BADGE(3, 0x142, 0x9F, 0x122, 0x7F)
        begin_text_draw(&gHudDisplayList);
        set_text_scale_mode(1);
        set_texture_draw_color(0xAA, 0xAA, 0xAA, 0xFF);
        SCORE(0, 0x20, 0x10)
        SCORE(1, 0x118, 0x10)
        SCORE(2, 0x20, 0x7E)
        SCORE(3, 0x118, 0x7E)
    }
    LOAD_TEX4(17, 0x071FF200, 0xF5400800, 0x000FC07C);
    PANEL(0, 0x16, 0x74)
    PANEL(1, 0x106, 0x74)
    PANEL(2, 0x16, 0xE0)
    PANEL(3, 0x106, 0xE0)
    set_text_scale_mode(1);
    SPECIAL(0, 0x19, 0x63, , )
    SPECIAL(1, 0x109, 0x63, GFX_WORDS(gHudDisplayList++, 0xBA000E02, 0x8000);, )
    SPECIAL(2, 0x19, 0xCF, GFX_WORDS(gHudDisplayList++, 0xBA000E02, 0x8000);, )
    SPECIAL(3, 0x109, 0xCF, GFX_WORDS(gHudDisplayList++, 0xBA000E02, 0x8000);,
            GFX_WORDS(gHudDisplayList++, 0xFA000101, 0xFFFFFF00 | gHudAlpha);)
    GFX_WORDS(gHudDisplayList++, 0xFC119623, 0xFF2FFFFF);
    GFX_WORDS(gHudDisplayList++, 0xBA000E02, 0x8000);
    GFX_WORDS(gHudDisplayList++, 0xB900031D, 0x00504240);
    LOAD_TEX4(15, 0x070FF400, 0xF5400400, 0x0007C07C);
    PRIMARY(0, 0x19, 0x81)
    PRIMARY(1, 0x109, 0x81)
    PRIMARY(2, 0x19, 0xED)
    PRIMARY(3, 0x109, 0xED)
    begin_text_draw(&gHudDisplayList);
    set_text_scale_mode(1);
    if (gHudViewActive[0] != 0) {
        set_texture_draw_position(0x30, 0x77 - height0);
        draw_text_number(&gHudDisplayList, (s16)gHudUnit0->ammo[gHudUnit0->weapon]);
    }
    if (gHudViewActive[1] != 0) {
        set_texture_draw_position(0x120, 0x77 - height1);
        draw_text_number(&gHudDisplayList, (s16)gHudUnit1->ammo[gHudUnit1->weapon]);
    }
    if (gHudViewActive[2] != 0) {
        set_texture_draw_position(0x30, 0xE3 - height2);
        draw_text_number(&gHudDisplayList, (s16)gHudUnit2->ammo[gHudUnit2->weapon]);
    }
    if (gHudViewActive[3] != 0) {
        set_texture_draw_position(0x120, 0xE3 - height3);
        draw_text_number(&gHudDisplayList, (s16)gHudUnit3->ammo[gHudUnit3->weapon]);
    }
    if (gHudViewActive[0] != 0) {
        draw_short_segment_bar(0x42, 0xE, gHudUnit0->health, gHudUnit0->maxHealth);
    }
    if (gHudViewActive[1] != 0) {
        draw_short_segment_bar(0xCB, 0xE, gHudUnit1->health, gHudUnit1->maxHealth);
    }
    if (gHudViewActive[2] != 0) {
        draw_short_segment_bar(0x42, 0x7D, gHudUnit2->health, gHudUnit2->maxHealth);
    }
    if (gHudViewActive[3] != 0) {
        draw_short_segment_bar(0xCB, 0x7D, gHudUnit3->health, gHudUnit3->maxHealth);
    }
    draw_hud_level_map(mode | 2);
}
