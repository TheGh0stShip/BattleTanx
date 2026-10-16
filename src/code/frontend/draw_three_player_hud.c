#include "types.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct GfxCommand {
    u32 w0;
    u32 w1;
} GfxCommand;

#define GFX_COORD(value) (((value) * 4) & 0xFFF)
#define GFX_WORDS(pkt, a, b)    \
    {                           \
        GfxCommand *_g = (pkt); \
        _g->w0 = (a);           \
        _g->w1 = (b);           \
    }

typedef struct HudRecord {
    u8 pad00[0xC];
    s32 unk0C;
    s32 state;
    u8 pad14[2];
    u16 unk16;
    u8 pad18[8];
    s16 unitId;
    u8 unk22;
    u8 pad23[5];
    s32 unk28;
    u8 pad2C[4];
    s32 unk30;
    s32 unk34;
    u8 pad38[2];
    s16 unk3A;
    s16 unk3C;
    u8 pad3E[0x17E];
    u8 color[3];
    u8 iconIndex;
    u8 pad1C0[0x48];
    s32 unk208;
    u8 pad20C[4];
    s32 unk210;
    u8 pad214[4];
    s32 message;
    s32 messageTime;
} HudRecord;

typedef struct HudItem {
    u8 pad00[0xD];
    u8 owner;
    u8 pad0E[0x1E];
    struct HudItem *next;
} HudItem;

typedef struct HudUnit {
    u8 pad00[0x1C];
    s32 health;
    s32 maxHealth;
    u8 pad24[0x74];
    HudItem *items;
    u8 pad9C[0x36C];
    u8 primaryLit;
    u8 secondaryLit;
    u8 pad40A[0x5E];
    s32 primarySlot;
    u8 pad46C[8];
    s32 weaponSlot;
    u8 pad478[8];
    s16 ammo[1];
} HudUnit;

typedef struct ModeState {
    s32 mode;
    s32 unk04;
    s32 team;
    u8 pad0C[0x1FC];
    s32 wave;
} ModeState;

typedef struct TeamInfo {
    s32 unk00;
    s32 unk04;
    s32 unk08;
    u8 pad0C[0x214];
} TeamInfo;

extern GfxCommand *gHudDisplayList __asm__("D_8037A174");
extern u8 gHudAlpha __asm__("D_8037A170");
extern u8 gHudTextures[] __asm__("D_8037AD78");
extern u8 gHudPortraits[] __asm__("D_80382D80");
extern s32 gGameMode __asm__("D_8012578C");
extern HudRecord *gHudRecord0 __asm__("D_8037A130");
extern HudRecord *gHudRecord1 __asm__("D_8037A134");
extern HudRecord *gHudRecord2 __asm__("D_8037A138");
extern HudUnit *gHudUnit0 __asm__("D_8037A120");
extern HudUnit *gHudUnit1 __asm__("D_8037A124");
extern HudUnit *gHudUnit2 __asm__("D_8037A128");
extern s32 gHudUnitActive[3] __asm__("D_8037A150");
extern char *gHudBannerText __asm__("D_8037A16C");
extern s32 gElapsedTicks __asm__("D_801B4AAC");
extern s32 gMessageClock __asm__("D_801B4AA8");
extern s32 D_801B4AD4;
extern s32 D_801B4AD8;
extern s32 D_801B4AE4;
extern TeamInfo D_80142DEC[];
extern s32 gWeaponIconIndex[] __asm__("D_8014165C");

extern ModeState *get_game_mode(void) __asm__("func_8007AAF4");
extern s32 game_mode_is_3_through_6(void) __asm__("func_8007C6D8");
extern s32 get_match_time_bonus(s32 *arg0) __asm__("func_8007D384");
extern HudUnit *get_unit(s16 id) __asm__("func_800A03B8");
extern HudRecord *get_entity_record(u16 index) __asm__("func_800A6688");
extern void func_800D20E4(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
extern void draw_value_text_with_notice(s32 level, s32 value) __asm__("func_800D39A4");
extern void func_800D3E28(s32, s32, s32, s32, s32, s32, s32);
extern void draw_paletted_image(GfxCommand **list, u8 *texels, s32 arg2, s32 arg3, s32 width, s32 height,
                                s32 tileWidth, s32 tileHeight, s32 x, s32 y, s32 width2, s32 height2, s32 s,
                                s32 t, f32 scaleX, f32 scaleY) __asm__("func_800F3D40");
extern void draw_filled_rectangle(GfxCommand **list, s32 left, s32 top, s32 right, s32 bottom, s32 red,
                                  s32 green, s32 blue, s32 alpha) __asm__("func_800F4DFC");
extern void draw_short_segment_bar(s32 x, s32 y, s32 value, s32 max) __asm__("func_800FFB58");
extern void draw_player_unit_markers(s32 count) __asm__("func_80100550");
extern void func_8010435C(void);
extern u16 gPortraitX[] __asm__("D_8014162C");
extern u16 gPortraitY[] __asm__("D_80141634");
extern u16 gDeadPortraitX[] __asm__("D_8014161C");
extern u16 gDeadPortraitY[] __asm__("D_80141624");
extern s32 gSecondaryIconIndex[] __asm__("D_801416A0");
extern void draw_hud_level_map(s32) __asm__("func_801009E8");
extern void draw_viewport_message_pair(s32 messageId, s32 viewport, s32 viewportCount, void *customText)
    __asm__("func_80101E9C");
extern void draw_player_stats_screen(void) __asm__("func_80102F8C");
extern void select_texture_draw_entry(s32 index) __asm__("func_801054E0");
extern void set_texture_draw_position(s32 x, s32 y) __asm__("func_8010552C");
extern void set_texture_draw_color(s32 red, s32 green, s32 blue, s32 alpha) __asm__("func_8010555C");
extern void draw_number(GfxCommand **gfx, s64 value) __asm__("func_801055D4");
extern void draw_centered_text_integer(GfxCommand **gfx, s64 value) __asm__("func_801057DC");
extern void draw_text(GfxCommand **gfx, char *text, s32 x, s32 width) __asm__("func_80105A50");
extern void begin_text_draw(GfxCommand **gfx) __asm__("func_8010698C");

#define HUD_OFFSET(i) (((s32 *)gHudTextures)[i])
#define HUD_PALETTE(i) ((u32)(gHudTextures + HUD_OFFSET(i)))
#define HUD_PIXELS(i) ((u32)(gHudTextures + 0x20 + HUD_OFFSET(i)))

#define HUD_LOAD_CI4(i, loadBlock, settile, size)                                \
    GFX_WORDS(gHudDisplayList++, 0xFD500000, HUD_PIXELS(i));                     \
    GFX_WORDS(gHudDisplayList++, 0xF5500000, 0x07000200);                        \
    GFX_WORDS(gHudDisplayList++, 0xE6000000, 0);                                 \
    GFX_WORDS(gHudDisplayList++, 0xF3000000, loadBlock);                         \
    GFX_WORDS(gHudDisplayList++, 0xE7000000, 0);                                 \
    GFX_WORDS(gHudDisplayList++, settile, 0x200);                                \
    GFX_WORDS(gHudDisplayList++, 0xF2000000, size);                              \
    GFX_WORDS(gHudDisplayList++, 0xFD100000, HUD_PALETTE(i));                    \
    GFX_WORDS(gHudDisplayList++, 0xE8000000, 0);                                 \
    GFX_WORDS(gHudDisplayList++, 0xF5000100, 0x07000000);                        \
    GFX_WORDS(gHudDisplayList++, 0xE6000000, 0);                                 \
    GFX_WORDS(gHudDisplayList++, 0xF0000000, 0x0703C000);                        \
    GFX_WORDS(gHudDisplayList++, 0xE7000000, 0);

#define HUD_LOAD_SMALL(i) HUD_LOAD_CI4(i, 0x070FF400, 0xF5400400, 0x0007C07C)
#define HUD_LOAD_WIDE(i) HUD_LOAD_CI4(i, 0x073FF200, 0xF5400800, 0x000FC0FC)

#define HUD_RECT(w0, w1)                                       \
    GFX_WORDS(gHudDisplayList++, w0, w1);                      \
    GFX_WORDS(gHudDisplayList++, 0xB4000000, 0);               \
    GFX_WORDS(gHudDisplayList++, 0xB3000000, 0x04000400);

#define HUD_COMBINE(color)                                     \
    GFX_WORDS(gHudDisplayList++, 0xFC119623, 0xFF2FFFFF);      \
    GFX_WORDS(gHudDisplayList++, 0xBA000E02, 0x8000);          \
    GFX_WORDS(gHudDisplayList++, 0xB900031D, 0x504240);        \
    GFX_WORDS(gHudDisplayList++, 0xFA000101, color);

#define PORTRAIT_OFFSET(i) (((s32 *)gHudPortraits)[i])


#define HUD_LOAD_TALL(i) HUD_LOAD_CI4(i, 0x071FF200, 0xF5400800, 0x000FC07C)

void draw_three_player_hud(void) __asm__("func_800F9F34");

void draw_three_player_hud(void) {
    u16 slot0;
    u16 slot1;
    u16 slot2;
    u16 height0;
    u16 height1;
    u16 height2;
    u16 ammo0;
    u16 ammo1;
    u16 ammo2;
    u16 i;
    HudRecord *rec;
    HudItem *item;
    u8 x;
    u8 shade;
    s32 icon;
    s32 kills;

    height0 = 0;
    height1 = 0;
    height2 = 0;
    gHudRecord0 = get_entity_record(0);
    gHudUnit0 = get_unit(gHudRecord0->unitId);
    gHudUnitActive[0] = gHudRecord0->state == 1 && gHudUnit0 != NULL;
    gHudRecord1 = get_entity_record(1);
    gHudUnit1 = get_unit(gHudRecord1->unitId);
    gHudUnitActive[1] = gHudRecord1->state == 1 && gHudUnit1 != NULL;
    gHudRecord2 = get_entity_record(2);
    gHudUnit2 = get_unit(gHudRecord2->unitId);
    gHudUnitActive[2] = gHudRecord2->state == 1 && gHudUnit2 != NULL;
    ammo0 = 0;
    slot0 = 0;
    ammo1 = 0;
    slot1 = 0;
    ammo2 = 0;
    slot2 = 0;
    if (gGameMode == 7) {
        func_8010435C();
        return;
    }
    for (i = 0; i < 3; i++) {
        if (get_entity_record(i)->state == 0 || get_entity_record(i)->state == 2) {
            GFX_WORDS(gHudDisplayList++, 0xE7000000, 0);
            GFX_WORDS(gHudDisplayList++, 0xBA001402, 0);
            GFX_WORDS(gHudDisplayList++, 0xB900031D, 0x504240);
            GFX_WORDS(gHudDisplayList++, 0xFCFFFFFF, 0xFFFCF279);
            GFX_WORDS(gHudDisplayList++, 0xBA001301, 0);
            GFX_WORDS(gHudDisplayList++, 0xBA001001, 0);
            GFX_WORDS(gHudDisplayList++, 0xBA000C02, 0);
            GFX_WORDS(gHudDisplayList++, 0xBA000903, 0xC00);
            GFX_WORDS(gHudDisplayList++, 0xBA000E02, 0x8000);
            if (get_entity_record(i)->state == 0) {
                GFX_WORDS(gHudDisplayList++, 0xFD100000, (u32)(gHudPortraits + PORTRAIT_OFFSET(7)));
                GFX_WORDS(gHudDisplayList++, 0xE8000000, 0);
                GFX_WORDS(gHudDisplayList++, 0xF5000100, 0x07000000);
                GFX_WORDS(gHudDisplayList++, 0xE6000000, 0);
                GFX_WORDS(gHudDisplayList++, 0xF0000000, 0x073FC000);
                GFX_WORDS(gHudDisplayList++, 0xE7000000, 0);
                draw_paletted_image(&gHudDisplayList, gHudPortraits + PORTRAIT_OFFSET(7) + 0x200, 2, 1, 0x44, 0x19,
                                    0x20, 0x20, gPortraitX[i], gPortraitY[i], 0x44, 0x19, 0, 0, 1.0f, 1.0f);
            } else {
                GFX_WORDS(gHudDisplayList++, 0xFD100000, (u32)(gHudPortraits + PORTRAIT_OFFSET(12)));
                GFX_WORDS(gHudDisplayList++, 0xE8000000, 0);
                GFX_WORDS(gHudDisplayList++, 0xF5000100, 0x07000000);
                GFX_WORDS(gHudDisplayList++, 0xE6000000, 0);
                GFX_WORDS(gHudDisplayList++, 0xF0000000, 0x073FC000);
                GFX_WORDS(gHudDisplayList++, 0xE7000000, 0);
                draw_paletted_image(&gHudDisplayList, gHudPortraits + PORTRAIT_OFFSET(12) + 0x200, 2, 1, 0x5A, 0x19,
                                    0x20, 0x20, gDeadPortraitX[i], gDeadPortraitY[i], 0x5A, 0x19, 0, 0, 1.0f, 1.0f);
            }
        } else {
            rec = get_entity_record(i);
            if (rec->message != 0) {
                draw_viewport_message_pair(rec->message, i, 2, rec);
                if (gMessageClock > rec->messageTime) {
                    rec->message = 0;
                }
            }
        }
    }
    draw_player_unit_markers(3);
    HUD_COMBINE(gHudAlpha | 0xFFFFFF00);
    if (gHudUnitActive[0]) {
        item = gHudUnit0->items;
        x = 0;
        while (item != NULL) {
            icon = get_entity_record(item->owner)->iconIndex + 9;
            HUD_LOAD_SMALL(icon);
            HUD_RECT(0xE4000000 | (GFX_COORD(0x139 - x) << 12) | GFX_COORD(0x31),
                     (GFX_COORD(0x119 - x) << 12) | GFX_COORD(0x11));
            item = item->next;
            x += 5;
        }
    }
    if (gHudUnitActive[1]) {
        item = gHudUnit1->items;
        x = 0;
        while (item != NULL) {
            icon = get_entity_record(item->owner)->iconIndex + 9;
            HUD_LOAD_SMALL(icon);
            HUD_RECT(0xE4000000 | (GFX_COORD(x + 0x36) << 12) | GFX_COORD(0x9F),
                     (GFX_COORD(x + 0x16) << 12) | GFX_COORD(0x7F));
            item = item->next;
            x += 5;
        }
    }
    if (gHudUnitActive[2]) {
        item = gHudUnit2->items;
        x = 0;
        while (item != NULL) {
            icon = get_entity_record(item->owner)->iconIndex + 9;
            HUD_LOAD_SMALL(icon);
            HUD_RECT(0xE4000000 | (GFX_COORD(0x139 - x) << 12) | GFX_COORD(0x9F),
                     (GFX_COORD(0x119 - x) << 12) | GFX_COORD(0x7F));
            item = item->next;
            x += 5;
        }
    }
    if (get_game_mode()->mode != 0 && get_game_mode()->mode != 9 && get_game_mode()->mode != 7) {
        GFX_WORDS(gHudDisplayList++, 0xFC119623, 0xFF2FFFFF);
        GFX_WORDS(gHudDisplayList++, 0xBA000E02, 0x8000);
        GFX_WORDS(gHudDisplayList++, 0xB900031D, 0x504240);
        HUD_LOAD_SMALL(18);
        GFX_WORDS(gHudDisplayList++, 0xFA000101,
                  (gHudRecord0->color[0] << 24) | (gHudRecord0->color[1] << 16) | (gHudRecord0->color[2] << 8) | gHudAlpha);
        if (gHudUnitActive[0]) {
            HUD_RECT(0xE45080C4, 0x00488044);
        }
        GFX_WORDS(gHudDisplayList++, 0xFA000101,
                  (gHudRecord1->color[0] << 24) | (gHudRecord1->color[1] << 16) | (gHudRecord1->color[2] << 8) | gHudAlpha);
        if (gHudUnitActive[1]) {
            HUD_RECT(0xE40D827C, 0x000581FC);
        }
        GFX_WORDS(gHudDisplayList++, 0xFA000101,
                  (gHudRecord2->color[0] << 24) | (gHudRecord2->color[1] << 16) | (gHudRecord2->color[2] << 8) | gHudAlpha);
        if (gHudUnitActive[2]) {
            HUD_RECT(0xE450827C, 0x004881FC);
        }
        begin_text_draw(&gHudDisplayList);
        select_texture_draw_entry(1);
        set_texture_draw_color(0xAA, 0xAA, 0xAA, 0xFF);
        if (gHudUnitActive[0]) {
            set_texture_draw_position(0x118, 0x10);
            kills = gHudRecord0->unk3A;
            draw_number(&gHudDisplayList, game_mode_is_3_through_6() ? kills : gHudRecord0->unk22 + kills);
        }
        if (gHudUnitActive[1]) {
            set_texture_draw_position(0x20, 0x7E);
            kills = gHudRecord1->unk3A;
            draw_number(&gHudDisplayList, game_mode_is_3_through_6() ? kills : gHudRecord1->unk22 + kills);
        }
        if (gHudUnitActive[2]) {
            set_texture_draw_position(0x118, 0x7E);
            kills = gHudRecord2->unk3A;
            draw_number(&gHudDisplayList, game_mode_is_3_through_6() ? kills : gHudRecord2->unk22 + kills);
        }
    }
    HUD_LOAD_TALL(17);
    if (gHudUnitActive[0]) {
        slot0 = gHudUnit0->weaponSlot;
        height0 = 0xD;
        ammo0 = gHudUnit0->ammo[slot0];
        if (slot0 != 0) {
            height0 = 0x20;
        }
        draw_filled_rectangle(&gHudDisplayList, 0x106, 0x74 - height0, 0x23, height0, 0x32, 0x32, 0x32, 0xD2);
        HUD_COMBINE(gHudAlpha | 0xFFFFFF00);
        HUD_RECT(0xE44A41D0, (GFX_COORD(0x106) << 12) | GFX_COORD(0x74 - height0));
    }
    if (gHudUnitActive[1]) {
        slot1 = gHudUnit1->weaponSlot;
        height1 = 0xD;
        ammo1 = gHudUnit1->ammo[slot1];
        if (slot1 != 0) {
            height1 = 0x20;
        }
        draw_filled_rectangle(&gHudDisplayList, 0x16, 0xE0 - height1, 0x23, height1, 0x32, 0x32, 0x32, 0xD2);
        HUD_COMBINE(gHudAlpha | 0xFFFFFF00);
        HUD_RECT(0xE40E4380, (GFX_COORD(0x16) << 12) | GFX_COORD(0xE0 - height1));
    }
    if (gHudUnitActive[2]) {
        slot2 = gHudUnit2->weaponSlot;
        height2 = 0xD;
        ammo2 = gHudUnit2->ammo[slot2];
        if (slot2 != 0) {
            height2 = 0x20;
        }
        draw_filled_rectangle(&gHudDisplayList, 0x106, 0xE0 - height2, 0x23, height2, 0x32, 0x32, 0x32, 0xD2);
        HUD_COMBINE(gHudAlpha | 0xFFFFFF00);
        HUD_RECT(0xE44A4380, (GFX_COORD(0x106) << 12) | GFX_COORD(0xE0 - height2));
    }
    select_texture_draw_entry(1);
    if (gHudUnitActive[0] && slot0 != 0) {
        shade = gHudUnit0->secondaryLit ? 0xFF : 0x40;
        GFX_WORDS(gHudDisplayList++, 0xFA000101, (shade << 24) | (shade << 16) | (shade << 8) | gHudAlpha);
        HUD_LOAD_SMALL(gSecondaryIconIndex[slot0]);
        HUD_RECT(0xE44581C0, 0x0042418C);
        begin_text_draw(&gHudDisplayList);
        set_texture_draw_position(0x120, 0x64);
        draw_number(&gHudDisplayList, ammo0);
    }
    if (gHudUnitActive[1] && slot1 != 0) {
        shade = gHudUnit1->secondaryLit ? 0xFF : 0x40;
        GFX_WORDS(gHudDisplayList++, 0xBA000E02, 0x8000);
        GFX_WORDS(gHudDisplayList++, 0xFA000101, (shade << 24) | (shade << 16) | (shade << 8) | gHudAlpha);
        HUD_LOAD_SMALL(gSecondaryIconIndex[slot1]);
        HUD_RECT(0xE4098370, 0x0006433C);
        begin_text_draw(&gHudDisplayList);
        set_texture_draw_position(0x30, 0xD0);
        draw_number(&gHudDisplayList, ammo1);
    }
    if (gHudUnitActive[2] && slot2 != 0) {
        shade = gHudUnit2->secondaryLit ? 0xFF : 0x40;
        GFX_WORDS(gHudDisplayList++, 0xBA000E02, 0x8000);
        GFX_WORDS(gHudDisplayList++, 0xFA000101, (shade << 24) | (shade << 16) | (shade << 8) | gHudAlpha);
        HUD_LOAD_SMALL(gSecondaryIconIndex[slot2]);
        HUD_RECT(0xE4458370, 0x0042433C);
        begin_text_draw(&gHudDisplayList);
        set_texture_draw_position(0x120, 0xD0);
        draw_number(&gHudDisplayList, ammo2);
    }
    GFX_WORDS(gHudDisplayList++, 0xFC119623, 0xFF2FFFFF);
    GFX_WORDS(gHudDisplayList++, 0xBA000E02, 0x8000);
    GFX_WORDS(gHudDisplayList++, 0xB900031D, 0x504240);
    HUD_LOAD_SMALL(15);
    if (gHudUnitActive[0]) {
        shade = gHudUnit0->primaryLit ? 0xFF : 0x40;
        GFX_WORDS(gHudDisplayList++, 0xFA000101, (shade << 24) | (shade << 16) | (shade << 8) | gHudAlpha);
        HUD_RECT(0xE4478000 | GFX_COORD(0x81 - height0), 0x00424000 | GFX_COORD(0x79 - height0));
    }
    if (gHudUnitActive[1]) {
        shade = gHudUnit1->primaryLit ? 0xFF : 0x40;
        GFX_WORDS(gHudDisplayList++, 0xFA000101, (shade << 24) | (shade << 16) | (shade << 8) | gHudAlpha);
        HUD_RECT(0xE40B8000 | GFX_COORD(0xED - height1), 0x00064000 | GFX_COORD(0xE5 - height1));
    }
    if (gHudUnitActive[2]) {
        shade = gHudUnit2->primaryLit ? 0xFF : 0x40;
        GFX_WORDS(gHudDisplayList++, 0xFA000101, (shade << 24) | (shade << 16) | (shade << 8) | gHudAlpha);
        HUD_RECT(0xE4478000 | GFX_COORD(0xED - height2), 0x00424000 | GFX_COORD(0xE5 - height2));
    }
    begin_text_draw(&gHudDisplayList);
    select_texture_draw_entry(1);
    if (gHudUnitActive[0]) {
        set_texture_draw_position(0x121, 0x77 - height0);
        draw_number(&gHudDisplayList, gHudUnit0->ammo[gHudUnit0->primarySlot]);
    }
    if (gHudUnitActive[1]) {
        set_texture_draw_position(0x31, 0xE3 - height1);
        draw_number(&gHudDisplayList, gHudUnit1->ammo[gHudUnit1->primarySlot]);
    }
    if (gHudUnitActive[2]) {
        set_texture_draw_position(0x121, 0xE3 - height2);
        draw_number(&gHudDisplayList, gHudUnit2->ammo[gHudUnit2->primarySlot]);
    }
    if (gHudUnitActive[0]) {
        draw_short_segment_bar(0x86, 0x10, gHudUnit0->health, gHudUnit0->maxHealth);
    }
    if (gHudUnitActive[1]) {
        draw_short_segment_bar(0x42, 0x7E, gHudUnit1->health, gHudUnit1->maxHealth);
    }
    if (gHudUnitActive[2]) {
        draw_short_segment_bar(0xCB, 0x7D, gHudUnit2->health, gHudUnit2->maxHealth);
    }
    draw_hud_level_map(2);
}
