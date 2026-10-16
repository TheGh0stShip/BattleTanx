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

extern GfxCommand *gHudDisplayList __asm__("D_8037A174");
extern u8 gHudAlpha __asm__("D_8037A170");
extern u8 gHudTextures[] __asm__("D_8037AD78");
extern u8 gHudPortraits[] __asm__("D_80382D80");
extern s32 gGameMode __asm__("D_8012578C");
extern HudRecord *gHudRecord0 __asm__("D_8037A130");
extern HudRecord *gHudRecord1 __asm__("D_8037A134");
extern HudUnit *gHudUnit0 __asm__("D_8037A120");
extern HudUnit *gHudUnit1 __asm__("D_8037A124");
extern s32 gHudUnitActive[2] __asm__("D_8037A150");
extern u16 gPortrait8X[2] __asm__("D_8014160C");
extern u16 gPortrait8Y[2] __asm__("D_80141610");
extern u16 gPortrait7X[2] __asm__("D_80141614");
extern u16 gPortrait7Y[2] __asm__("D_80141618");
extern s32 gMessageClock __asm__("D_801B4AA8");
extern s32 gWeaponIconIndex[] __asm__("D_8014165C");

extern ModeState *get_game_mode(void) __asm__("func_8007AAF4");
extern s32 game_mode_is_3_through_6(void) __asm__("func_8007C6D8");
extern HudUnit *get_unit(s16 id) __asm__("func_800A03B8");
extern HudRecord *get_entity_record(u16 index) __asm__("func_800A6688");
extern void draw_paletted_image(GfxCommand **list, u8 *texels, s32 arg2, s32 arg3, s32 width, s32 height,
                                s32 tileWidth, s32 tileHeight, s32 x, s32 y, s32 width2, s32 height2, s32 s,
                                s32 t, f32 scaleX, f32 scaleY) __asm__("func_800F3D40");
extern void draw_filled_rectangle(GfxCommand **list, s32 left, s32 top, s32 right, s32 bottom, s32 red,
                                  s32 green, s32 blue, s32 alpha) __asm__("func_800F4DFC");
extern void draw_segment_bar(s32 x, s32 y, s32 value, s32 max) __asm__("func_800FF73C");
extern void func_80100550(s32);
extern void draw_hud_level_map(s32) __asm__("func_801009E8");
extern void draw_viewport_message_pair(s32 messageId, s32 viewport, s32 viewportCount, void *customText)
    __asm__("func_80101E9C");
extern void draw_versus_stats_screen(void) __asm__("func_80103E50");
extern void select_texture_draw_entry(s32 index) __asm__("func_801054E0");
extern void set_texture_draw_position(s32 x, s32 y) __asm__("func_8010552C");
extern void set_texture_draw_color(s32 red, s32 green, s32 blue, s32 alpha) __asm__("func_8010555C");
extern void draw_number(GfxCommand **gfx, s64 value) __asm__("func_801055D4");
extern void begin_text_draw(GfxCommand **gfx) __asm__("func_8010698C");

#define HUD_OFFSET(i) (((s32 *)gHudTextures)[i])
#define HUD_PALETTE(i) ((u32)HUD_OFFSET(i) + (u32)gHudTextures)
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

void draw_two_player_hud(void) __asm__("func_800F8120");

void draw_two_player_hud(void) {
    u16 slot0;
    u16 slot1;
    u16 ammo0;
    u16 ammo1;
    u16 height0;
    u16 height1;
    u8 anyActive;
    u16 i;
    HudRecord *rec;
    HudItem *item;
    u8 x;
    s32 icon;
    u8 shade;

    rec = gHudRecord0 = get_entity_record(0);
    height0 = 0;
    height1 = 0;
    gHudUnit0 = get_unit(rec->unitId);
    gHudUnitActive[0] = gHudUnit0 != NULL && gHudRecord0->state == 1;
    rec = gHudRecord1 = get_entity_record(1);
    gHudUnit1 = get_unit(rec->unitId);
    gHudUnitActive[1] = gHudUnit1 != NULL && gHudRecord1->state == 1;
    anyActive = 0;
    if (gHudUnitActive[0] != 0 || gHudUnitActive[1] != 0) {
        anyActive = 1;
    }
    ammo0 = 0;
    slot0 = 0;
    ammo1 = 0;
    slot1 = 0;
    if (gGameMode == 7) {
        draw_versus_stats_screen();
        return;
    }
    for (i = 0; i < 2; i++) {
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
                draw_paletted_image(&gHudDisplayList, gHudPortraits + PORTRAIT_OFFSET(7) + 0x200, 2, 1, 0x64, 0x26,
                                    0x20, 0x20, gPortrait7X[i], gPortrait7Y[i], 0x64, 0x26, 0, 0, 1.0f,
                                    1.0f);
            } else {
                GFX_WORDS(gHudDisplayList++, 0xFD100000, (u32)(gHudPortraits + PORTRAIT_OFFSET(8)));
                GFX_WORDS(gHudDisplayList++, 0xE8000000, 0);
                GFX_WORDS(gHudDisplayList++, 0xF5000100, 0x07000000);
                GFX_WORDS(gHudDisplayList++, 0xE6000000, 0);
                GFX_WORDS(gHudDisplayList++, 0xF0000000, 0x073FC000);
                GFX_WORDS(gHudDisplayList++, 0xE7000000, 0);
                draw_paletted_image(&gHudDisplayList, gHudPortraits + PORTRAIT_OFFSET(8) + 0x200, 2, 1, 0x86, 0x26,
                                    0x20, 0x20, gPortrait8X[i], gPortrait8Y[i], 0x86, 0x26, 0, 0, 1.0f,
                                    1.0f);
            }
        } else {
            rec = get_entity_record(i);
            if (rec->message != 0) {
                draw_viewport_message_pair(rec->message, i, 1, rec);
                if (gMessageClock > rec->messageTime) {
                    rec->message = 0;
                }
            }
        }
    }
    if (anyActive) {
        HUD_COMBINE(gHudAlpha | 0xFFFFFF00);
        if (gHudUnitActive[0]) {
            x = 0;
            for (item = gHudUnit0->items; item != NULL; item = item->next) {
                rec = get_entity_record(item->owner);
                icon = rec->iconIndex + 13;
                HUD_LOAD_SMALL(icon);
                HUD_RECT(0xE4000000 | (GFX_COORD(0x139 - x) << 12) | GFX_COORD(0x31),
                         (GFX_COORD(0x119 - x) << 12) | GFX_COORD(0x11));
                x += 10;
            }
        }
        if (gHudUnitActive[1]) {
            x = 0;
            for (item = gHudUnit1->items; item != NULL; item = item->next) {
                rec = get_entity_record(item->owner);
                icon = rec->iconIndex + 13;
                HUD_LOAD_SMALL(icon);
                HUD_RECT(0xE4000000 | (GFX_COORD(0x139 - x) << 12) | GFX_COORD(0x9F),
                         (GFX_COORD(0x119 - x) << 12) | GFX_COORD(0x7F));
                x += 10;
            }
        }
        func_80100550(2);
        if (get_game_mode()->mode != 0 && get_game_mode()->mode != 9 && get_game_mode()->mode != 7) {
            if (anyActive) {
                GFX_WORDS(gHudDisplayList++, 0xFC119623, 0xFF2FFFFF);
                GFX_WORDS(gHudDisplayList++, 0xBA000E02, 0x8000);
                GFX_WORDS(gHudDisplayList++, 0xB900031D, 0x504240);
                HUD_LOAD_WIDE(21);
                GFX_WORDS(gHudDisplayList++, 0xFA000101,
                          (gHudRecord0->color[0] << 24) | (gHudRecord0->color[1] << 16) |
                              (gHudRecord0->color[2] << 8) | gHudAlpha);
                if (gHudUnitActive[0]) {
                    HUD_RECT(0xE44A4088, 0x003DC044);
                }
                GFX_WORDS(gHudDisplayList++, 0xFA000101,
                          (gHudRecord1->color[0] << 24) | (gHudRecord1->color[1] << 16) |
                              (gHudRecord1->color[2] << 8) | gHudAlpha);
                if (gHudUnitActive[1]) {
                    HUD_RECT(0xE44A4240, 0x003DC1FC);
                }
            }
            begin_text_draw(&gHudDisplayList);
            select_texture_draw_entry(0);
            set_texture_draw_color(0xAA, 0xAA, 0xAA, 0xFF);
            if (gHudUnitActive[0]) {
                s32 kills;

                set_texture_draw_position(0x10B, 0x16);
                kills = gHudRecord0->unk3A;
                draw_number(&gHudDisplayList,
                            game_mode_is_3_through_6() ? kills : gHudRecord0->unk22 + kills);
            }
            if (gHudUnitActive[1]) {
                s32 kills;

                set_texture_draw_position(0x10B, 0x84);
                kills = gHudRecord1->unk3A;
                draw_number(&gHudDisplayList,
                            game_mode_is_3_through_6() ? kills : gHudRecord1->unk22 + kills);
            }
        }
        HUD_LOAD_WIDE(4);
        if (gHudUnitActive[0]) {
            s32 top;

            slot0 = gHudUnit0->weaponSlot;
            height0 = 0x10;
            ammo0 = gHudUnit0->ammo[slot0];
            if (slot0 != 0) {
                height0 = 0x29;
            }
            top = 0x74 - height0;
            draw_filled_rectangle(&gHudDisplayList, 0xF9, top, 0x30, height0, 0x32, 0x32, 0x32, 0xD2);
            HUD_COMBINE(gHudAlpha | 0xFFFFFF00);
            HUD_RECT(0xE44A41D0, GFX_COORD(top) | 0x3E4000);
        }
        if (gHudUnitActive[1]) {
            s32 top;

            slot1 = gHudUnit1->weaponSlot;
            height1 = 0x10;
            ammo1 = gHudUnit1->ammo[slot1];
            if (slot1 != 0) {
                height1 = 0x29;
            }
            top = 0xE0 - height1;
            draw_filled_rectangle(&gHudDisplayList, 0xF9, top, 0x30, height1, 0x32, 0x32, 0x32, 0xD2);
            HUD_COMBINE(gHudAlpha | 0xFFFFFF00);
            HUD_RECT(0xE44A4380, GFX_COORD(top) | 0x3E4000);
        }
        select_texture_draw_entry(0);
        if (gHudUnitActive[0] && slot0 != 0) {
            shade = gHudUnit0->secondaryLit ? 0xFF : 0x40;

            GFX_WORDS(gHudDisplayList++, 0xFA000101, (shade << 24) | (shade << 16) | (shade << 8) | gHudAlpha);
            HUD_LOAD_SMALL(gWeaponIconIndex[slot0]);
            HUD_RECT(0xE44401C0, 0x003F0170);
            begin_text_draw(&gHudDisplayList);
            set_texture_draw_position(0x11C, 0x63);
            draw_number(&gHudDisplayList, ammo0);
        }
        if (gHudUnitActive[1] && slot1 != 0) {
            shade = gHudUnit1->secondaryLit ? 0xFF : 0x40;

            GFX_WORDS(gHudDisplayList++, 0xBA000E02, 0x8000);
            GFX_WORDS(gHudDisplayList++, 0xFA000101, (shade << 24) | (shade << 16) | (shade << 8) | gHudAlpha);
            HUD_LOAD_SMALL(gWeaponIconIndex[slot1]);
            HUD_RECT(0xE4440370, 0x003F0320);
            begin_text_draw(&gHudDisplayList);
            set_texture_draw_position(0x11C, 0xCF);
            draw_number(&gHudDisplayList, ammo1);
        }
        GFX_WORDS(gHudDisplayList++, 0xFC119623, 0xFF2FFFFF);
        GFX_WORDS(gHudDisplayList++, 0xBA000E02, 0x8000);
        GFX_WORDS(gHudDisplayList++, 0xB900031D, 0x504240);
        HUD_LOAD_SMALL(18);
        if (gHudUnitActive[0]) {
            shade = gHudUnit0->primaryLit ? 0xFF : 0x40;

            GFX_WORDS(gHudDisplayList++, 0xFA000101, (shade << 24) | (shade << 16) | (shade << 8) | gHudAlpha);
            HUD_RECT(0xE4440000 | GFX_COORD(0x80 - height0), 0x3EC000 | GFX_COORD(0x78 - height0));
        }
        if (gHudUnitActive[1]) {
            shade = gHudUnit1->primaryLit ? 0xFF : 0x40;

            GFX_WORDS(gHudDisplayList++, 0xFA000101, (shade << 24) | (shade << 16) | (shade << 8) | gHudAlpha);
            HUD_RECT(0xE4440000 | GFX_COORD(0xEC - height1), 0x3EC000 | GFX_COORD(0xE4 - height1));
        }
        begin_text_draw(&gHudDisplayList);
        if (gHudUnitActive[0]) {
            set_texture_draw_position(0x11E, 0x78 - height0);
            draw_number(&gHudDisplayList, gHudUnit0->ammo[gHudUnit0->primarySlot]);
        }
        if (gHudUnitActive[1]) {
            set_texture_draw_position(0x11E, 0xE4 - height1);
            draw_number(&gHudDisplayList, gHudUnit1->ammo[gHudUnit1->primarySlot]);
        }
        if (gHudUnitActive[0]) {
            draw_segment_bar(0x7B, 0x10, gHudUnit0->health, gHudUnit0->maxHealth);
        }
        if (gHudUnitActive[1]) {
            draw_segment_bar(0x7B, 0x7E, gHudUnit1->health, gHudUnit1->maxHealth);
        }
        draw_hud_level_map(1);
    }
}
