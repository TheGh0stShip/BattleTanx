#include "types.h"

/* RODATA_VRAM 0x800713D0 */

typedef struct GameModeInfo {
    s32 kind;
    s32 value04;
    u8 pad08[0x200];
    s32 value208;
} GameModeInfo;

typedef struct PlayerRecord {
    u8 pad00[0x10];
    s32 value10;
    u16 value14;
    u16 controller;
    s32 value18;
    u8 pad1C[0x18A];
    u8 value1A6;
    u8 pad1A7[7];
    u8 team;
} PlayerRecord;

typedef struct PlayerInput {
    u8 pad00[4];
    u32 pressed;
} PlayerInput;

extern u32 D_8012578C;
extern s8 D_80125799;
extern s8 D_8012579B;
extern s32 D_80126714;
extern s32 D_80134E5C;
extern u8 D_80134E64;
extern s32 D_801416EC;
extern s32 D_801B4AA8;
extern s32 D_801B4AAC;
extern s32 D_801B4AC0;
extern s32 D_801B4AD4;
extern s32 D_801B4ADC;
extern s8 D_80327B44;

extern s32 get_entity_capacity(void) __asm__("func_8007AAB0");
extern GameModeInfo *get_game_mode(void) __asm__("func_8007AAF4");
extern s32 game_mode_is_3_through_6(void) __asm__("func_8007C6D8");
extern void func_8007D2A0(s32 value);
extern s32 func_8007D384(void *buffer);
extern void func_8008B2C8(s32 mode);
extern PlayerInput *read_player_controller(s32 player) __asm__("func_80096784");
extern s32 read_player_menu_directions(s32 player, s32 ignoreCButtons) __asm__("func_80096920");
extern void func_80097B7C(void);
extern s32 func_800A3DE0(PlayerRecord *record);
extern s32 func_800A42B0(PlayerRecord *record);
extern void func_800A42BC(PlayerRecord *record, s32 value);
extern s32 func_800A42C4(PlayerRecord *record);
extern void func_800A5050(PlayerRecord *record);
extern void func_800A52AC(PlayerRecord *record, char *line1, char *line2, f32 scale);
extern void func_800A5AA4(s32 player, s32 value);
extern PlayerRecord *get_entity_record(u16 index) __asm__("func_800A6688");
extern void func_800A66C0(void);
extern s32 func_800A6798(void);
extern void stop_all_rumble_paks(void) __asm__("func_800A9010");
extern s32 func_800A933C(void);
extern void func_800A93C8(void);
extern void func_800DDC3C(void);
extern s32 audio_restarts_disabled(void) __asm__("func_800EC644");
extern s32 func_800EC8C4(void);
extern void func_800ECB34(void);
extern void func_8010D984(void);
extern s32 format_string(char *dst, char *fmt, ...) __asm__("func_8011CC84");
extern void update_attached_camera(void *camera) __asm__("func_80077E94");

s32 update_match_state(void) __asm__("func_8007F2A0");

s32 update_match_state(void)
{
    u8 teams[4];
    char line1[32];
    char line2[32];
    char line3[32];
    char line4[32];
    u8 buffer[24];
    register PlayerRecord *record __asm__("$16");
    s32 count;
    register u16 i __asm__("$17");
    s32 alive;
    s32 teamCount;
    s32 buttons;
    s32 pressed;
    s32 j;
    s32 next;

    count = get_entity_capacity();
    switch (D_8012578C) {
    case 0:
        return 1;
    case 9:
        func_800A66C0();
        for (i = 0; i < count; i++) {
            func_800A3DE0(get_entity_record(i));
        }
        if (D_801B4AD4 != 0) {
            if (func_800A933C() != 0) {
                D_8012578C = 3;
                D_801B4AD4 = 0xFF;
                return 0;
            }
            D_801B4AD4 = 0;
            return 0;
        }
        for (i = 0; i < D_80126714; i++) {
            if (read_player_menu_directions(i, 0) & 0x10) {
                goto state3;
            }
        }
        break;
    case 10:
        func_800A66C0();
        for (i = 0; i < count; i++) {
            func_800A3DE0(get_entity_record(i));
        }
        if (D_801B4AD4 != 0) {
            if (func_800A933C() == 0) {
                D_801B4AD4 = 0;
                return 0;
            }
            D_8012578C = 4;
            D_801B4AD4 = D_801B4AC0 * 5;
            return 0;
        }
        for (i = 0; i < D_80126714; i++) {
            if (read_player_menu_directions(i, 0) & 0x10) {
                goto state4;
            }
        }
        break;
    case 3:
        func_800A66C0();
        for (i = 0; i < count; i++) {
            func_800A3DE0(get_entity_record(i));
        }
        buttons = read_player_menu_directions(0, 0);
        D_801B4AD4 -= 4;
        if (D_801B4AD4 < 0) {
            D_801B4AD4 = 0;
        }
        if (buttons != 0) {
            D_8012578C = 4;
            D_801B4AD4 = D_801B4AC0 * 5;
            return 0;
        }
        break;
    case 4:
        func_800A66C0();
        for (i = 0; i < count; i++) {
            func_800A3DE0(get_entity_record(i));
        }
        if (--D_801B4AD4 <= 0) {
            if (get_game_mode()->kind == 7) {
                format_string(line1, "KILL %d TANKS", get_game_mode()->value208);
                format_string(line2, "POINTS X %d", (get_game_mode()->value208 - 5) / 3 + 1);
                func_800A52AC(get_entity_record(0), line1, line2, 3.0f);
            }
            if (audio_restarts_disabled() == 0) {
                func_8007D2A0(get_game_mode()->value04);
            }
            D_8012578C = 1;
            D_801B4ADC = D_801B4AA8;
            return 0;
        }
        break;
    case 8:
        func_800A66C0();
        func_8008B2C8(0);
        for (i = 0; i < 4; i++) {
            if (read_player_controller(get_entity_record(i)->controller)->pressed & 0x9000) {
                func_800ECB34();
                D_80327B44 = 1;
            }
        }
        update_attached_camera((u8 *)get_entity_record(0) + 0x48);
        if (func_800EC8C4() < 0) {
            goto reset;
        }
        return 0;
    case 1:
        func_800DDC3C();
        func_800A66C0();
        func_8008B2C8(0);
        for (i = 0; i < 4; i++) {
            teams[i] = 0;
        }
        alive = 0;
        teamCount = 0;
        for (i = 0; i < count; i++) {
            record = get_entity_record(i);
            if (func_800A3DE0(record) != 0) {
                alive += record->value1A6 == 0;
                if (teams[record->team] == 0) {
                    teams[record->team] = 1;
                    teamCount++;
                }
            }
        }
        for (i = 0; i < count; i++) {
            if (func_800A42C4(get_entity_record(i)) != 0) {
                D_801416EC = 0;
                D_8012578C = 2;
                stop_all_rumble_paks();
            }
        }
        switch (get_game_mode()->kind) {
        case 0:
            if (func_800A6798() < 0) {
                return 0;
            }
            for (i = 0; i < count; i++) {
                PlayerRecord *player = get_entity_record(i);

                if (player->value1A6 == 0) {
                    func_800A5050(player);
                }
            }
            goto end6;
        case 9:
            for (i = 0; i < count; i++) {
                if (get_entity_record(i)->value10 == 2) {
                    D_8012578C = 5;
                    D_801B4AD4 = 90;
                }
            }
            break;
        case 4:
            record = get_entity_record(0);
            if (record->value10 == 2) {
                stop_all_rumble_paks();
                D_8012578C = 6;
                D_801B4AD4 = 90;
            }
            if (teams[0] == 0) {
                D_8012578C = 5;
                record->value10 = 0;
                D_801B4AD4 = 90;
                return 0;
            }
            break;
        case 2:
        case 5:
        case 7:
            if ((teamCount < 2) | (alive == 0)) {
                next = 5;
                goto set_state;
            }
            break;
        case 3:
        case 6:
            if (func_800A6798() >= 0 || get_entity_record(0)->value18 == 0) {
                for (i = 0; i < count; i++) {
                    record = get_entity_record(i);
                    if (teamCount == 1) {
                        if (record->value18 != 0) {
                            func_800A42BC(record, 2);
                        } else {
                            func_800A42BC(record, 0);
                        }
                    }
                    if (record->value1A6 == 0) {
                        func_800A5050(record);
                    }
                }
                goto end6;
            }
            break;
        }
        break;
    case 2:
        func_80097B7C();
        func_800A66C0();
        func_8008B2C8(1);
        for (i = 0; i < count; i++) {
            func_800A3DE0(get_entity_record(i));
        }
        D_8012578C = 1;
        for (i = 0; i < count; i++) {
            if (func_800A42C4(get_entity_record(i)) != 0) {
                D_8012578C = 2;
            }
        }
        break;
    case 5:
        func_800A66C0();
        func_8008B2C8(0);
        for (i = 0; i < count; i++) {
            func_800A3DE0(get_entity_record(i));
        }
        if (--D_801B4AD4 <= 0) {
            for (i = 0; i < count; i++) {
                record = get_entity_record(i);
                if (get_game_mode()->kind == 9) {
                    if (func_800A42B0(record) == 1) {
                        func_800A42BC(record, 0);
                    }
                } else if (func_800A42B0(record) == 1) {
                    func_800A42BC(record, 2);
                }
                if (record->value1A6 == 0) {
                    func_800A5050(record);
                }
                if (i == 0 && get_game_mode()->kind == 7) {
                    s32 playerState = func_800A42B0(record);

                    if (playerState != 0) {
                        if (playerState == 2) {
                            if (get_game_mode()->value208 >= 11) {
                                format_string(line3, "EXTRA TANK!");
                                format_string(line4, "KEEP IT UP");
                            } else {
                                format_string(line3, "YOU KILLED %d TANKS", get_game_mode()->value208);
                                format_string(line4, "BUT YOU'RE NOT DONE YET");
                            }
                            func_800A52AC(get_entity_record(0), line3, line4, 3.0f);
                        }
                    }
                }
            }
        end6:
            stop_all_rumble_paks();
            next = 6;
        set_state:
            D_8012578C = next;
            D_801B4AD4 = 90;
            return 0;
        }
        break;
    case 6:
        func_800A66C0();
        func_8008B2C8(2);
        for (i = 0; i < count; i++) {
            func_800A3DE0(get_entity_record(i));
        }
        if (--D_801B4AD4 <= 0) {
            D_801B4AAC = D_801B4AA8 - D_801B4ADC;
            if (get_game_mode()->kind == 7 && get_entity_record(0)->value10 == 2) {
                goto reset;
            }
            if (game_mode_is_3_through_6() != 0 && get_entity_record(0)->value10 == 2) {
                func_800A5AA4(0, func_8007D384(buffer));
            }
            D_8012578C = 7;
            D_801B4AD4 = 2000;
            return 0;
        }
        break;
    state3:
        D_8012578C = 3;
        D_801B4AD4 = 0xFF;
        goto notify;
    state4:
        D_8012578C = 4;
        D_801B4AD4 = D_801B4AC0 * 5;
    notify:
        func_800A93C8();
        return 0;
    clear799:
        D_80125799 = 0;
    reset:
        D_8012578C = 0;
        return 0;
    set799:
        D_80125799 = 1;
        goto reset;
    case 7:
        if (--D_801B4AD4 < 0) {
            D_801B4AD4 = 0;
        }
        func_800A66C0();
        func_8008B2C8(2);
        for (i = 0; i < count; i++) {
            func_800A3DE0(get_entity_record(i));
        }
        for (j = 0; j < D_80126714; j++) {
            pressed = read_player_menu_directions(j, 0);
            if (D_80134E5C == 0) {
                if (get_game_mode()->kind == 7) {
                    if (func_800A42B0(get_entity_record(0)) == 2) {
                        buttons = pressed & 0x30;
                    } else {
                        if (func_800A42B0(get_entity_record(0)) != 0) {
                            continue;
                        }
                        buttons = pressed & 0x10;
                        if (pressed & 0x20) {
                            D_8012579B = 1;
                            D_8012578C = 0;
                        }
                    }
                } else if (func_800A42B0(get_entity_record(0)) == 2) {
                    if (get_game_mode()->value04 != 0x10) {
                        if (pressed & 0x20) {
                            D_8012579B = 1;
                            D_8012578C = 0;
                        }
                    }
                    buttons = pressed & 0x10;
                } else {
                    if (func_800A42B0(get_entity_record(0)) != 0) {
                        continue;
                    }
                    if (pressed & 0x10) {
                        D_8012579B = 0;
                        D_80125799 = 1;
                        if (D_80134E64 == 0) {
                            func_8010D984();
                        }
                        D_8012578C = 0;
                    }
                    buttons = pressed & 0x20;
                }
                if (buttons != 0) {
                    D_8012579B = 0;
                    D_8012578C = 0;
                }
            } else {
                if (pressed & 0x20) {
                    goto clear799;
                }
                if (pressed & 0x10) {
                    goto set799;
                }
            }
        }
        break;
    }
    return 0;
}
