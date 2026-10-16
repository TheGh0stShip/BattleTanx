#include "types.h"

typedef struct PlayerSetup {
    u16 index;
    u16 slot;
    void *model;
    void *portrait;
    void *banner;
    u8 team;
    u8 local;
    u8 pad12[0x2];
    s32 controller;
    s32 lives;
    u8 respawn;
    u8 red;
    u8 green;
    u8 blue;
    u8 color;
    u8 order;
    u8 pad22[0x2];
    s32 reserve;
    s32 value28;
    s16 bounds[4];
    s32 value34;
} PlayerSetup;

typedef struct ColorInfo {
    u8 pad00[0x3C];
    u8 color;
} ColorInfo;

typedef struct GameSetup {
    s32 type;
    u8 pad004[0x8];
    s32 controller[4];
    u8 pad01C[0x1B0];
    s32 mode;
    s32 count;
    s32 team[4];
    s32 value1E4[4];
    s32 reserve[4];
    u8 pad204[0x4];
    s32 waves;
    u16 bounds[4];
} GameSetup;

extern u8 D_01000000[];
extern u8 D_01000010[];
extern u8 D_01000020[];
extern u8 D_01000030[];
extern u8 D_01000040[];
extern u8 D_01000050[];
extern u8 D_01000060[];
extern u8 D_01000070[];
extern u8 D_01000138[];
extern u8 D_01000150[];
extern u8 D_01000168[];
extern u8 D_01000180[];
extern u8 D_01000198[];
extern u8 D_010001B0[];
extern u8 D_010001C8[];
extern u8 D_010001E0[];
extern u8 D_801260A0[];
extern u8 D_80126290[][4];
extern s32 D_801262C0[];
extern s32 D_801262D0;
extern s32 D_801262D4;
extern s32 D_80135834;
extern s32 D_802DF348;
extern u8 D_803C8880[];

#define SEGMENTED_TO_VIRTUAL(addr) ((void *)(((u32)(addr) & 0xFFFFFF) + (u32)D_803C8880))

extern u8 *func_800821C0(void);
extern s32 func_800EC644(void);
extern s32 func_800EC668(s32 index);
extern s32 func_800ECB68(s32 index);
extern s32 func_800EC3D0(void);
extern ColorInfo *func_800A68C0(s32 controller);
extern void *func_800A6688(u16 index);
extern void initialize_player_record(void *player, PlayerSetup *setup)
    __asm__("func_800A31C0");
extern u8 func_8007D1F8(GameSetup *game, s32 index);
extern void func_8010D850(void);
extern void func_800E4DF8(void);

void setup_players(GameSetup *game) __asm__("func_800A5FF0");

void setup_players(GameSetup *game)
{
    PlayerSetup setup;
    u8 *session;
    s32 waves;
    u16 i;
    s32 j;

    D_801262D0 = 0;
    session = func_800821C0();
    D_802DF348 = game->count;
    waves = 0;
    if (func_800EC644() != 0) {
        for (i = 0; i < game->count; i++) {
            setup.lives = func_800EC668(i);
            setup.index = i;
            setup.order = i;
            setup.slot = i * 5;
            setup.model = 0;
            setup.team = i;
            setup.controller = func_800ECB68(i);
            if (i == 0) {
                setup.banner = func_800EC3D0() ? D_010001E0 : D_01000138;
                setup.portrait = func_800EC3D0() ? SEGMENTED_TO_VIRTUAL(D_01000070) : SEGMENTED_TO_VIRTUAL(D_01000000);
            } else {
                setup.banner = 0;
                setup.portrait = 0;
            }
            setup.local = 0;
            setup.color = func_800A68C0(setup.controller)->color;
            setup.red = D_80126290[setup.color][0];
            setup.green = D_80126290[setup.color][1];
            setup.blue = D_80126290[setup.color][2];
            initialize_player_record(func_800A6688(i), &setup);
        }
    } else {
        for (j = 0; j < game->count; j++) {
            setup.index = j;
            setup.team = game->team[j];
            setup.order = j;
            setup.slot = j * 5;
            setup.model = session + 0x280 + D_801260A0[j] * 60;
            setup.value28 = game->value1E4[j];
            setup.value34 = D_801262C0[j];
            switch (game->mode) {
            case 1:
                if (j == 0) {
                    setup.banner = D_01000138;
                    setup.local = 0;
                    setup.portrait = SEGMENTED_TO_VIRTUAL(D_01000000);
                } else {
                    setup.banner = 0;
                    setup.portrait = 0;
                    setup.local = 1;
                }
                break;
            case 2:
                switch (j) {
                case 0:
                    setup.banner = D_01000150;
                    setup.local = 0;
                    setup.portrait = SEGMENTED_TO_VIRTUAL(D_01000010);
                    break;
                case 1:
                    setup.banner = D_01000168;
                    setup.portrait = SEGMENTED_TO_VIRTUAL(D_01000020);
                    setup.local = 0;
                    break;
                default:
                    setup.banner = 0;
                    setup.local = 1;
                    setup.portrait = 0;
                    break;
                }
                break;
            case 3:
                switch (j) {
                case 0:
                    setup.banner = D_01000150;
                    setup.local = 0;
                    setup.portrait = SEGMENTED_TO_VIRTUAL(D_01000010);
                    break;
                case 1:
                    setup.banner = D_010001B0;
                    setup.local = 0;
                    setup.portrait = SEGMENTED_TO_VIRTUAL(D_01000050);
                    break;
                case 2:
                    setup.banner = D_010001C8;
                    setup.local = 0;
                    setup.portrait = SEGMENTED_TO_VIRTUAL(D_01000060);
                    break;
                default:
                    setup.banner = 0;
                    setup.local = 1;
                    setup.portrait = 0;
                    break;
                }
                break;
            case 4:
                switch (j) {
                case 0:
                    setup.banner = D_01000180;
                    setup.portrait = SEGMENTED_TO_VIRTUAL(D_01000030);
                    setup.local = 0;
                    break;
                case 1:
                    setup.portrait = SEGMENTED_TO_VIRTUAL(D_01000040);
                    setup.banner = D_01000198;
                    setup.local = 0;
                    break;
                case 2:
                    setup.banner = D_010001B0;
                    setup.local = 0;
                    setup.portrait = SEGMENTED_TO_VIRTUAL(D_01000050);
                    break;
                case 3:
                    setup.banner = D_010001C8;
                    setup.local = 0;
                    setup.portrait = SEGMENTED_TO_VIRTUAL(D_01000060);
                    break;
                default:
                    setup.portrait = 0;
                    setup.banner = 0;
                    setup.local = 1;
                    break;
                }
                break;
            }
            setup.controller = game->controller[j];
            setup.lives = 5;
            setup.color = func_8007D1F8(game, setup.index);
            setup.red = D_80126290[setup.color][0];
            setup.green = D_80126290[setup.color][1];
            setup.blue = D_80126290[setup.color][2];
            setup.reserve = game->reserve[j];
            setup.respawn = 0;
            setup.bounds[0] = 0;
            setup.bounds[1] = 0;
            setup.bounds[2] = 0;
            setup.bounds[3] = 0;
            switch (game->type) {
            case 7:
                switch (j) {
                case 1:
                    waves = game->waves / 3 + (game->waves % 3 > 0);
                    break;
                case 2:
                    waves = game->waves / 3 + (game->waves % 3 >= 2);
                    break;
                case 3:
                    waves = game->waves / 3;
                    break;
                }
                if (j != 0) {
                    if (waves < 4) {
                        setup.lives = waves;
                        setup.reserve = 0;
                    } else {
                        setup.lives = 3;
                        setup.reserve = waves - 3;
                    }
                }
                break;
            case 0:
                setup.lives = 2;
                setup.respawn = 1;
                break;
            case 9:
                setup.lives = 1;
                setup.respawn = 1;
                break;
            case 3:
            case 4:
            case 5:
            case 6:
                if (j == 0) {
                    setup.lives = 1;
                    setup.respawn = 0;
                    setup.bounds[0] = game->bounds[0];
                    setup.bounds[1] = game->bounds[1];
                    setup.bounds[2] = game->bounds[2];
                    setup.bounds[3] = game->bounds[3];
                } else {
                    setup.lives = 5;
                    setup.respawn = 0;
                }
                break;
            }
            initialize_player_record(func_800A6688(j), &setup);
        }
        func_8010D850();
        if (D_80135834 != 0) {
            func_800E4DF8();
        }
    }
    if (D_801262D4 == 0) {
        D_801262D4 = 1;
    }
}
