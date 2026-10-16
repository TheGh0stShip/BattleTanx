#include "types.h"

typedef struct GfxCommand {
    u32 w0;
    u32 w1;
} GfxCommand;

#define GFX_WORDS(pkt, a, b) \
    {                         \
        GfxCommand *_g = (pkt); \
        _g->w0 = (a);         \
        _g->w1 = (b);         \
    }

typedef struct MarkerTexture {
    u8 pixels[0x10];
    s32 frame;
} MarkerTexture;

typedef struct UnitObject {
    u8 pad00;
    u8 active;
    u8 pad02[0xA];
    s32 dead;
    u8 pad10[0x14];
    f32 x;
    u8 pad28[4];
    f32 z;
} UnitObject;

typedef struct PlayerFlags {
    u8 pad00[0x14];
    u16 flags;
} PlayerFlags;

typedef struct PlayerState {
    u8 pad00[8];
    s32 eliminated;
    PlayerFlags *info;
} PlayerState;

typedef struct PlayerRecord {
    s16 units[5];
    u8 pad0A[0x6E];
    f32 x;
    u8 pad7C[4];
    f32 z;
    u8 pad84[0x68];
    PlayerState *state;
    u8 padF0[4];
    u32 dl;
    u8 padF8[0xC4];
    u8 color[3];
} PlayerRecord;

extern GfxCommand *gMenuDisplayList __asm__("D_8037A174");
extern MarkerTexture gMarkerTexture __asm__("D_8037FD80");
extern s32 gPlayerActive[] __asm__("D_8037A150");
extern u8 gLocalMarkerColor[] __asm__("D_8014160F");
extern u8 gMarkerDisplayList[] __asm__("D_01000138");
extern s32 get_difficulty_level(void) __asm__("func_8007AAA0");
extern s32 get_entity_capacity(void) __asm__("func_8007AAB0");
extern s32 func_8007C6D8(void);
extern PlayerRecord *get_entity_record(u16 index) __asm__("func_800A6688");
extern UnitObject *func_800A03B8(s16 id);
extern s32 func_8009453C(f32 *in, f32 *out, u16 player);

void draw_player_unit_markers(s32 count) __asm__("func_80100550");

void draw_player_unit_markers(s32 count)
{
    f32 in[4];
    f32 out[4];
    f32 pos[2];
    PlayerRecord *rec;
    UnitObject *obj;
    u16 i;
    u16 j;
    u16 k;
    s32 capacity;

    GFX_WORDS(gMenuDisplayList++, 0xFD700004, (u32)&gMarkerTexture.pixels[gMarkerTexture.frame]);
    GFX_WORDS(gMenuDisplayList++, 0xF5700400, 0x07080200);
    GFX_WORDS(gMenuDisplayList++, 0xE6000000, 0);
    GFX_WORDS(gMenuDisplayList++, 0xF4000000, 0x07014014);
    GFX_WORDS(gMenuDisplayList++, 0xE7000000, 0);
    GFX_WORDS(gMenuDisplayList++, 0xF5700400, 0x80200);
    GFX_WORDS(gMenuDisplayList++, 0xF2000000, 0x14014);
    GFX_WORDS(gMenuDisplayList++, 0xB900031D, 0x504240);
    GFX_WORDS(gMenuDisplayList++, 0xFC119623, 0xFF2FFFFF);
    GFX_WORDS(gMenuDisplayList++, 0xBA000E02, 0);
    get_difficulty_level();
    capacity = get_entity_capacity();
    for (i = 0; i < count; i++) {
        if (gPlayerActive[i] == 0) {
            continue;
        }
        rec = get_entity_record(i);
        if (rec->state->eliminated != 0) {
            continue;
        }
        if (!(rec->state->info->flags & 0x80)) {
            continue;
        }
        GFX_WORDS(gMenuDisplayList++, 0x06000000, rec->dl);
        pos[1] = rec->x;
        pos[0] = rec->z;
        if (func_8007C6D8()) {
            GFX_WORDS(gMenuDisplayList++, 0xFA000101,
                      (gLocalMarkerColor[0] << 24) | (gLocalMarkerColor[1] << 16) | (gLocalMarkerColor[2] << 8) | 0xFF);
        }
        for (j = 0; j < capacity; j++) {
            if (j == i) {
                continue;
            }
            rec = get_entity_record(j);
            if (!func_8007C6D8()) {
                GFX_WORDS(gMenuDisplayList++, 0xFA000101,
                          (rec->color[0] << 24) | (rec->color[1] << 16) | (rec->color[2] << 8) | 0xFF);
            }
            for (k = 0; k < 5; k++) {
                obj = func_800A03B8(rec->units[k]);
                if (obj->active == 0 || obj->dead != 0) {
                    continue;
                }
                in[0] = obj->x;
                in[1] = 50.0f;
                in[2] = obj->z;
                if (func_8009453C(in, out, i)) {
                    continue;
                }
                GFX_WORDS(gMenuDisplayList++,
                          0xE4000000 | ((((s32)out[0] + 5) * 4 & 0xFFF) << 12) | (((s32)out[1] + 5) * 4 & 0xFFF),
                          ((((s32)out[0]) * 4 & 0xFFF) << 12) | (((s32)out[1]) * 4 & 0xFFF));
                GFX_WORDS(gMenuDisplayList++, 0xB4000000, 0);
                GFX_WORDS(gMenuDisplayList++, 0xB3000000, 0x04000400);
            }
        }
    }
    GFX_WORDS(gMenuDisplayList++, 0x06000000, (u32)gMarkerDisplayList);
}

typedef struct LevelMapImage {
    u32 romStart;
    u32 romEnd;
    s32 width;
    s32 height;
    s32 centerX;
    s32 centerY;
    f32 worldWidth;
    f32 worldDepth;
    u8 spawnPoints[4][2];
} LevelMapImage;

typedef struct MapUnit {
    u8 active;
    u8 alive;
    u8 pad02[6];
    s32 value08;
    s32 health;
    s32 value10;
    u16 flags;
    u8 pad16[0xE];
    f32 x;
    f32 y;
    f32 z;
    f32 pad30;
    f32 heading;
    u8 pad38[0x60];
    s32 value98;
    u8 pad9C[0x41C];
    s32 hitTick;
} MapUnit;

typedef struct MapPlayer {
    s16 units[5];
    u8 pad0A[0x16];
    s16 currentUnit;
    u8 pad22[0x184];
    u8 hasSquad;
    u8 pad1A7[0x11];
    s32 target;
    u8 pad1BC[3];
    u8 team;
} MapPlayer;

typedef struct GameModeInfo {
    u32 mode;
} GameModeInfo;

#define GFX_COORD(v) (((v) * 4) & 0xFFF)

extern GfxCommand *gHudDisplayList __asm__("D_8037A174");
extern u8 gLevelMapTexture[] __asm__("D_8037A178");
extern LevelMapImage gLevelMapImages[] __asm__("D_80141308");
extern s32 D_80141560[];
typedef u8 Rgb[3];

extern Rgb gTeamColors[16] __asm__("D_801415D0");
extern Rgb gMarkerColors[] __asm__("D_80141600");
extern u8 gHudMarkerTexels[] __asm__("D_80141148");
extern s32 gCurrentLevel __asm__("D_8037A160");
extern s32 D_80134E5C;
extern u8 D_80134E68;
extern u32 D_801B4AA0;
extern s32 gGameTicks __asm__("D_801B4AA8");
extern u8 D_801260A0[];

extern MapPlayer *get_map_player(u16 index) __asm__("func_800A6688");
extern MapUnit *get_unit(s16 id) __asm__("func_800A03B8");
extern GameModeInfo *get_game_mode(void) __asm__("func_8007AAF4");
extern s32 game_mode_is_3_through_6(void) __asm__("func_8007C6D8");
extern s32 func_800A6E10(s32 target);
extern void draw_fill_box(GfxCommand **gfx, s32 x, s32 y, s32 w, s32 h, s32 r, s32 g, s32 b, s32 a) __asm__("func_800F4DFC");
extern void draw_ci8_image(GfxCommand **gfx, u8 *texels, u8 *palette, s32 width, s32 height, s32 tileWidth,
                           s32 tileHeight, s32 x, s32 y, s32 width2, s32 height2, s32 s, s32 t, f32 scaleX,
                           f32 scaleY) __asm__("func_800F41C0");

void draw_hud_level_map(s32 layout) __asm__("func_801009E8");

void draw_hud_level_map(s32 layout)
{
    f32 pos[3];
    Rgb *teamColors[4];
    s32 count;
    s32 left;
    s32 showOthers;
    s32 top;
    s32 map;
    u16 i;
    u16 j;
    MapPlayer *player;
    MapUnit *unit;
    Rgb *color;
    Rgb *drawColor;
    u16 angle;
    s32 since;
    u32 mode;

    teamColors[0] = &gTeamColors[0];
    teamColors[1] = &gTeamColors[4];
    showOthers = 1;
    teamColors[2] = &gTeamColors[8];
    teamColors[3] = &gTeamColors[12];
    map = D_80141560[gCurrentLevel];
    switch (layout) {
    case 0:
        left = 0x19;
        top = 0xDB - gLevelMapImages[map].height;
        break;
    case 1:
        left = 0x19;
        top = (0xF0 - gLevelMapImages[map].height) / 2;
        break;
    case 2:
    default:
        left = (0x140 - gLevelMapImages[map].width) / 2;
        top = (0xF0 - gLevelMapImages[map].height) / 2;
        break;
    }
    if (map != 0) {
        GFX_WORDS(gHudDisplayList++, 0xE7000000, 0);
        GFX_WORDS(gHudDisplayList++, 0xBA001402, 0);
        GFX_WORDS(gHudDisplayList++, 0xB900031D, 0x00504240);
        GFX_WORDS(gHudDisplayList++, 0xFC119623, 0xFF2FFFFF);
        GFX_WORDS(gHudDisplayList++, 0xBA001301, 0);
        GFX_WORDS(gHudDisplayList++, 0xBA001001, 0);
        GFX_WORDS(gHudDisplayList++, 0xBA000C02, 0);
        GFX_WORDS(gHudDisplayList++, 0xBA000903, 0xC00);
        GFX_WORDS(gHudDisplayList++, 0xBA000E02, 0x8000);
        GFX_WORDS(gHudDisplayList++, 0xFA000101, 0xFFFFFFBE);
        GFX_WORDS(gHudDisplayList++, 0xFD100000, (u32)gLevelMapTexture);
        GFX_WORDS(gHudDisplayList++, 0xE8000000, 0);
        GFX_WORDS(gHudDisplayList++, 0xF5000100, 0x07000000);
        GFX_WORDS(gHudDisplayList++, 0xE6000000, 0);
        GFX_WORDS(gHudDisplayList++, 0xF0000000, 0x0703C000);
        GFX_WORDS(gHudDisplayList++, 0xE7000000, 0);
        draw_ci8_image(&gHudDisplayList, gLevelMapTexture + 0x20, gLevelMapTexture, gLevelMapImages[map].width,
                       gLevelMapImages[map].height, 0x20, 0x20, left, top, gLevelMapImages[map].width,
                       gLevelMapImages[map].height, 0, 0, 1.0f, 1.0f);
    } else {
        GFX_WORDS(gHudDisplayList++, 0xE7000000, 0);
        GFX_WORDS(gHudDisplayList++, 0xBA001402, 0);
        GFX_WORDS(gHudDisplayList++, 0xB900031D, 0x00504240);
        GFX_WORDS(gHudDisplayList++, 0xFCFFFFFF, 0xFFFCF279);
        GFX_WORDS(gHudDisplayList++, 0xBA001301, 0);
        GFX_WORDS(gHudDisplayList++, 0xBA001001, 0);
        GFX_WORDS(gHudDisplayList++, 0xBA000C02, 0);
        GFX_WORDS(gHudDisplayList++, 0xBA000903, 0xC00);
        GFX_WORDS(gHudDisplayList++, 0xBA000E02, 0);
        draw_fill_box(&gHudDisplayList, left, top, gLevelMapImages[0].width, gLevelMapImages[0].height, 0x20, 0x20,
                      0x20, 0x80);
    }
    count = get_entity_capacity();
    if (map != 0) {
        GFX_WORDS(gHudDisplayList++, 0xB900031D, 0x0F0A4000);
        GFX_WORDS(gHudDisplayList++, 0xFCFFFFFF, 0xFFFCF279);
        mode = get_game_mode()->mode;
        if (mode == 0 || mode == 3 || mode == 6 || mode == 4) {
        for (i = 0; i < count; i++) {
            player = get_map_player(i);
            if (D_80134E5C == 0) {
                color = &gMarkerColors[0];
                if (player->hasSquad) {
                    color = &gMarkerColors[1];
                }
            } else {
                color = teamColors[player->team]++;
            }
            if (player->target != 0
                && (func_800A6E10(player->target) == 0 || ((D_801B4AA0 >> 3) & 3) != 0)) {
                draw_fill_box(&gHudDisplayList,
                              left + gLevelMapImages[map].spawnPoints[D_801260A0[i]][0],
                              top + gLevelMapImages[map].spawnPoints[D_801260A0[i]][1], 4, 4, (*color)[0],
                              (*color)[1], (*color)[2], 0xFF);
            }
        }
        }
    }
    teamColors[0] = &gTeamColors[0];
    teamColors[1] = &gTeamColors[4];
    teamColors[2] = &gTeamColors[8];
    teamColors[3] = &gTeamColors[12];
    if (game_mode_is_3_through_6()) {
        unit = get_unit(get_map_player(0)->currentUnit);
        if (unit != 0) {
            showOthers = unit->flags & 0x80;
        } else {
            showOthers = 0;
        }
    }
    GFX_WORDS(gHudDisplayList++, 0xFD700000, (u32)gHudMarkerTexels);
    GFX_WORDS(gHudDisplayList++, 0xF5700000, 0x07000200);
    GFX_WORDS(gHudDisplayList++, 0xE6000000, 0);
    GFX_WORDS(gHudDisplayList++, 0xF3000000, 0x070DF800);
    GFX_WORDS(gHudDisplayList++, 0xE7000000, 0);
    GFX_WORDS(gHudDisplayList++, 0xF5680200, 0x200);
    GFX_WORDS(gHudDisplayList++, 0xF2000000, 0x0001C0DC);
    GFX_WORDS(gHudDisplayList++, 0xB900031D, 0x00504240);
    GFX_WORDS(gHudDisplayList++, 0xFC119623, 0xFF2FFFFF);
    GFX_WORDS(gHudDisplayList++, 0xBA000E02, 0);
    for (i = 0; i < count; i++) {
        player = get_map_player(i);
        if (D_80134E5C == 0) {
            color = &gMarkerColors[0];
            if (player->hasSquad) {
                color = &gMarkerColors[1];
            }
        } else {
            color = teamColors[player->team]++;
        }
        if (player->hasSquad) {
            for (j = 0; j < 5; j++) {
                unit = get_unit(player->units[j]);
                if (!unit->active || !unit->alive) {
                    continue;
                }
                if (unit->value98 != 0 && !(D_801B4AA0 & 3)) {
                    GFX_WORDS(gHudDisplayList++, 0xB900031D, 0x00504240);
                    GFX_WORDS(gHudDisplayList++, 0xFC119623, 0xFF2FFFFF);
                    GFX_WORDS(gHudDisplayList++, 0xBA000E02, 0);
                    if (gLevelMapImages[map].worldWidth < 0.0f) {
                        pos[0] = (gLevelMapImages[map].width / 2) * (unit->z / gLevelMapImages[map].worldWidth);
                        pos[2] = (gLevelMapImages[map].height / 2) * (unit->x / gLevelMapImages[map].worldDepth);
                        angle = (u32)(unit->heading * 182.04444444) + 0x5000;
                    } else {
                        pos[0] = (gLevelMapImages[map].width / 2) * (unit->x / gLevelMapImages[map].worldWidth);
                        pos[2] = (gLevelMapImages[map].height / 2) * (unit->z / gLevelMapImages[map].worldDepth);
                        angle = (u32)(unit->heading * 182.04444444) - 0x7000;
                    }
                    GFX_WORDS(gHudDisplayList++, 0xFA000101, ((*color)[0] << 24) | ((*color)[1] << 16) | ((*color)[2] << 8) | 0xFF);
                    GFX_WORDS(gHudDisplayList++,
                              0xE4000000
                                  | (GFX_COORD((s32)((f32)(left + gLevelMapImages[map].centerX) + pos[0]) + 4) << 12)
                                  | GFX_COORD((s32)((f32)(top + gLevelMapImages[map].centerY) + pos[2] - 3.0f) + 7),
                              (GFX_COORD((s32)((f32)(left + gLevelMapImages[map].centerX) + pos[0]) - 3) << 12)
                                  | GFX_COORD((s32)((f32)(top + gLevelMapImages[map].centerY) + pos[2] - 3.0f)));
                    GFX_WORDS(gHudDisplayList++, 0xB4000000, ((angle >> 13) * 0xE0) & 0xFFFF);
                    GFX_WORDS(gHudDisplayList++, 0xB3000000, 0x04000400);
                } else if (unit->value98 == 0 && showOthers) {
                    if (gLevelMapImages[map].worldWidth < 0.0f) {
                        pos[0] = (gLevelMapImages[map].width / 2) * (unit->z / gLevelMapImages[map].worldWidth);
                        pos[2] = (gLevelMapImages[map].height / 2) * (unit->x / gLevelMapImages[map].worldDepth);
                    } else {
                        pos[0] = (gLevelMapImages[map].width / 2) * (unit->x / gLevelMapImages[map].worldWidth);
                        pos[2] = (gLevelMapImages[map].height / 2) * (unit->z / gLevelMapImages[map].worldDepth);
                    }
                    draw_fill_box(&gHudDisplayList, (s32)((f32)(left + gLevelMapImages[map].centerX) + pos[0]) - 1,
                                  (s32)((f32)(top + gLevelMapImages[map].centerY) + pos[2] - 1.0f), 2, 2, (*color)[0],
                                  (*color)[1], (*color)[2], 0xFF);
                }
            }
        } else {
            for (j = 0; j < 5; j++) {
                unit = get_unit(player->units[j]);
                if (!unit->active || !unit->alive) {
                    continue;
                }
                if (unit->value98 != 0 && (D_801B4AA0 & 3)) {
                    continue;
                }
                drawColor = color;
                if (player->units[j] == player->currentUnit) {
                    if (unit->health > 0 && get_difficulty_level() != 1 && unit->value08 == 0
                        && unit->value98 == 0 && D_80134E68 == 0) {
                        continue;
                    }
                    if (unit->value10 != 0 && (D_801B4AA0 & 0x1F)) {
                        continue;
                    }
                    GFX_WORDS(gHudDisplayList++, 0xB900031D, 0x00504240);
                    GFX_WORDS(gHudDisplayList++, 0xFC119623, 0xFF2FFFFF);
                    GFX_WORDS(gHudDisplayList++, 0xBA000E02, 0);
                    if (gLevelMapImages[map].worldWidth < 0.0f) {
                        pos[0] = (gLevelMapImages[map].width / 2) * (unit->z / gLevelMapImages[map].worldWidth);
                        pos[2] = (gLevelMapImages[map].height / 2) * (unit->x / gLevelMapImages[map].worldDepth);
                        angle = (u32)(unit->heading * 182.04444444) + 0x5000;
                    } else {
                        pos[0] = (gLevelMapImages[map].width / 2) * (unit->x / gLevelMapImages[map].worldWidth);
                        pos[2] = (gLevelMapImages[map].height / 2) * (unit->z / gLevelMapImages[map].worldDepth);
                        angle = (u32)(unit->heading * 182.04444444) - 0x7000;
                    }
                    GFX_WORDS(gHudDisplayList++, 0xFA000101, ((*color)[0] << 24) | ((*color)[1] << 16) | ((*color)[2] << 8) | 0xFF);
                    GFX_WORDS(gHudDisplayList++,
                              0xE4000000
                                  | (GFX_COORD((s32)((f32)(left + gLevelMapImages[map].centerX) + pos[0]) + 4) << 12)
                                  | GFX_COORD((s32)((f32)(top + gLevelMapImages[map].centerY) + pos[2] - 3.0f) + 7),
                              (GFX_COORD((s32)((f32)(left + gLevelMapImages[map].centerX) + pos[0]) - 3) << 12)
                                  | GFX_COORD((s32)((f32)(top + gLevelMapImages[map].centerY) + pos[2] - 3.0f)));
                    GFX_WORDS(gHudDisplayList++, 0xB4000000, ((angle >> 13) * 0xE0) & 0xFFFF);
                    GFX_WORDS(gHudDisplayList++, 0xB3000000, 0x04000400);
                } else {
                    since = gGameTicks - unit->hitTick;
                    if (game_mode_is_3_through_6() && since < 0x1E) {
                        if (since & 2) {
                            continue;
                        }
                        drawColor = &gMarkerColors[2];
                    }
                    if (gLevelMapImages[map].worldWidth < 0.0f) {
                        pos[0] = (gLevelMapImages[map].width / 2) * (unit->z / gLevelMapImages[map].worldWidth);
                        pos[2] = (gLevelMapImages[map].height / 2) * (unit->x / gLevelMapImages[map].worldDepth);
                    } else {
                        pos[0] = (gLevelMapImages[map].width / 2) * (unit->x / gLevelMapImages[map].worldWidth);
                        pos[2] = (gLevelMapImages[map].height / 2) * (unit->z / gLevelMapImages[map].worldDepth);
                    }
                    draw_fill_box(&gHudDisplayList, (s32)((f32)(left + gLevelMapImages[map].centerX) + pos[0]) - 1,
                                  (s32)((f32)(top + gLevelMapImages[map].centerY) + pos[2] - 1.0f), 2, 2,
                                  (*drawColor)[0], (*drawColor)[1], (*drawColor)[2], 0xFF);
                }
            }
        }
    }
}
