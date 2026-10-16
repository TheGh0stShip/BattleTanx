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
    u8 pad3E[0x181];
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
extern HudRecord *gHudRecord __asm__("D_8037A130");
extern HudUnit *gHudUnit __asm__("D_8037A120");
extern s32 gHudUnitActive __asm__("D_8037A150");
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
extern void draw_segment_bar(s32 x, s32 y, s32 value, s32 max) __asm__("func_800FF73C");
extern void func_80100550(s32);
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

void draw_player_hud(void) __asm__("func_800F6934");

void draw_player_hud(void) {
    s32 timeBonus;
    HudRecord *rec;
    s32 ammo;
    HudUnit *unit;
    s32 kills;

    rec = get_entity_record(0);
    gHudRecord = rec;
    unit = gHudUnit = get_unit(rec->unitId);
    gHudUnitActive = gHudUnit != NULL && gHudRecord->state == 1;
    if (gGameMode == 6 && get_game_mode()->mode == 7 && rec->state == 2) {
        s32 timeLeft = 0x5A - D_801B4AD4;

        draw_value_text_with_notice(timeLeft, (get_game_mode()->wave - 5) / 3 + 1);
    } else if (gGameMode == 7) {
        if (game_mode_is_3_through_6()) {
            s32 timeLeft;
            s32 score;
            s32 elapsed;
            s32 bonus;
            s32 adjusted;
            s32 kills;
            s32 unk34;
            s32 unk30;
            s32 dead;
            s32 team;
            s32 unk0C;

            rec = get_entity_record(0);
            timeLeft = 0x7D0 - D_801B4AD4;
            score = rec->unk28;
            elapsed = gElapsedTicks;
            bonus = get_match_time_bonus(&timeBonus);
            adjusted = rec->unk210 - bonus;
            kills = rec->unk3C + 1;
            unk34 = rec->unk34;
            unk30 = rec->unk30;
            dead = rec->state == 2;
            if (get_game_mode()->unk04 == 0x10) {
                team = -1;
            } else {
                team = D_80142DEC[get_game_mode()->team + 1].unk00;
            }
            unk0C = rec->unk0C;
            func_800D20E4(timeLeft, adjusted, score, elapsed, timeBonus, bonus, kills, unk34, unk30, dead, team,
                          unk0C);
        } else if (get_game_mode()->mode == 7) {
            if (get_entity_record(0)->state != 2) {
                s32 timeLeft = 0x7D0 - D_801B4AD4;
                s32 wave = (get_game_mode()->wave - 5) / 3 + 1;
                s32 next = D_801B4AD8 + 1;
                s32 total = D_801B4AE4;
                s32 teamA = D_80142DEC[get_game_mode()->team + 1].unk00;
                s32 teamB = D_80142DEC[get_game_mode()->team + 1].unk08;

                func_800D3E28(timeLeft, wave, next, total, teamA, get_entity_record(0)->unk210, teamB);
            }
        } else {
            draw_player_stats_screen();
        }
        return;
    }
    if (rec->state == 0 || rec->state == 2) {
        if (get_game_mode()->mode != 7) {
            GFX_WORDS(gHudDisplayList++, 0xE7000000, 0);
            GFX_WORDS(gHudDisplayList++, 0xBA001402, 0);
            GFX_WORDS(gHudDisplayList++, 0xB900031D, 0x504240);
            GFX_WORDS(gHudDisplayList++, 0xFCFFFFFF, 0xFFFCF279);
            GFX_WORDS(gHudDisplayList++, 0xBA001301, 0);
            GFX_WORDS(gHudDisplayList++, 0xBA001001, 0);
            GFX_WORDS(gHudDisplayList++, 0xBA000C02, 0);
            GFX_WORDS(gHudDisplayList++, 0xBA000903, 0xC00);
            GFX_WORDS(gHudDisplayList++, 0xBA000E02, 0x8000);
            if (rec->state == 0) {
                GFX_WORDS(gHudDisplayList++, 0xFD100000, (u32)(gHudPortraits + PORTRAIT_OFFSET(7)));
                GFX_WORDS(gHudDisplayList++, 0xE8000000, 0);
                GFX_WORDS(gHudDisplayList++, 0xF5000100, 0x07000000);
                GFX_WORDS(gHudDisplayList++, 0xE6000000, 0);
                GFX_WORDS(gHudDisplayList++, 0xF0000000, 0x073FC000);
                GFX_WORDS(gHudDisplayList++, 0xE7000000, 0);
                draw_paletted_image(&gHudDisplayList, gHudPortraits + PORTRAIT_OFFSET(7) + 0x200, 2, 1, 0x64, 0x26,
                                    0x20, 0x20, 0x6E, 0x56, 0x64, 0x26, 0, 0, 1.0f, 1.0f);
            } else {
                GFX_WORDS(gHudDisplayList++, 0xFD100000, (u32)(gHudPortraits + PORTRAIT_OFFSET(8)));
                GFX_WORDS(gHudDisplayList++, 0xE8000000, 0);
                GFX_WORDS(gHudDisplayList++, 0xF5000100, 0x07000000);
                GFX_WORDS(gHudDisplayList++, 0xE6000000, 0);
                GFX_WORDS(gHudDisplayList++, 0xF0000000, 0x073FC000);
                GFX_WORDS(gHudDisplayList++, 0xE7000000, 0);
                draw_paletted_image(&gHudDisplayList, gHudPortraits + PORTRAIT_OFFSET(8) + 0x200, 2, 1, 0x86, 0x26,
                                    0x20, 0x20, 0x5D, 0x56, 0x86, 0x26, 0, 0, 1.0f, 1.0f);
                if (game_mode_is_3_through_6()) {
                    begin_text_draw(&gHudDisplayList);
                    select_texture_draw_entry(4);
                    set_texture_draw_color(0xFF, 0xFF, 0xFF, 0xFF);
                    set_texture_draw_position(0, 0x96);
                    draw_text(&gHudDisplayList, gHudBannerText, 0, 0x140);
                }
            }
        }
    } else {
        if (rec->message != 0) {
            draw_viewport_message_pair(rec->message, 0, 0, rec);
            if (gMessageClock > rec->messageTime) {
                rec->message = 0;
            }
        }
        func_80100550(1);
        if (get_game_mode()->mode != 0 && get_game_mode()->mode != 9 && get_game_mode()->mode != 7) {
            HUD_COMBINE(gHudAlpha | 0xFFFFFF00);
            HUD_LOAD_WIDE(21);
            HUD_RECT(0xE4138084, 0x00070040);
            select_texture_draw_entry(0);
            begin_text_draw(&gHudDisplayList);
            set_texture_draw_color(0xAA, 0xAA, 0xAA, 0xFF);
            set_texture_draw_position(0x30, 0x15);
            kills = rec->unk3A;
            draw_number(&gHudDisplayList, game_mode_is_3_through_6() ? kills : rec->unk22 + kills);
            set_texture_draw_position(0x9C, 0x1A);
            draw_centered_text_integer(&gHudDisplayList, rec->unk210);
        } else {
            select_texture_draw_entry(0);
            begin_text_draw(&gHudDisplayList);
            set_texture_draw_color(0xAA, 0xAA, 0xAA, 0xFF);
            set_texture_draw_position(0x9C, 0x1A);
            draw_centered_text_integer(&gHudDisplayList, rec->unk210);
        }
        if (unit != NULL) {
            HudItem *item = unit->items;
            s32 x = 0;
            s32 slot;
            s32 height;

            HUD_COMBINE(gHudAlpha | 0xFFFFFF00);
            while (item != NULL) {
                rec = get_entity_record(item->owner);

                if (!game_mode_is_3_through_6()) {
                    s32 icon = rec->iconIndex + 13;

                    HUD_LOAD_SMALL(icon);
                } else if (get_game_mode()->unk04 == 0x10 && rec->unk16 != 0) {
                    HUD_LOAD_SMALL(10);
                } else {
                    HUD_LOAD_SMALL(3);
                }
                HUD_RECT(0xE4000000 | (GFX_COORD(0x125 - x) << 12) | GFX_COORD(0xDC),
                         (GFX_COORD(0x105 - x) << 12) | GFX_COORD(0xBC));
                item = item->next;
                x += 10;
            }
            slot = unit->weaponSlot;
            ammo = unit->ammo[slot];
            height = 0x10;
            if (slot != 0) {
                height = 0x29;
            }
            draw_filled_rectangle(&gHudDisplayList, 0xF4, 0x10, 0x30, height, 0x32, 0x32, 0x32, 0xD2);
            HUD_COMBINE(gHudAlpha | 0xFFFFFF00);
            HUD_LOAD_WIDE(4);
            HUD_RECT(0xE4000000 | (GFX_COORD(0x124) << 12) | GFX_COORD(height + 0x10),
                     (GFX_COORD(0xF4) << 12) | GFX_COORD(0x10));
            if (slot != 0) {
                s32 shade = (u8)(unit->secondaryLit ? 0xFF : 0) | 0x40;

                GFX_WORDS(gHudDisplayList++, 0xFA000101, (shade << 24) | (shade << 16) | (shade << 8) | gHudAlpha);
                HUD_LOAD_SMALL(gWeaponIconIndex[slot]);
                HUD_RECT(0xE442C0D4, 0x003DC084);
                begin_text_draw(&gHudDisplayList);
                set_texture_draw_position(0x117, 0x28);
                draw_number(&gHudDisplayList, ammo);
            }
            {
                s32 shade = (u8)(unit->primaryLit ? 0xFF : 0) | 0x40;

                HUD_COMBINE((shade << 24) | (shade << 16) | (shade << 8) | gHudAlpha);
            }
            HUD_LOAD_SMALL(18);
            HUD_RECT(0xE4430070, 0x003DC050);
            begin_text_draw(&gHudDisplayList);
            set_texture_draw_position(0x11A, 0x14);
            draw_number(&gHudDisplayList, unit->ammo[unit->primarySlot]);
            draw_segment_bar(0x7B, 0x10, unit->health, unit->maxHealth);
        }
        draw_hud_level_map(0);
    }
}
