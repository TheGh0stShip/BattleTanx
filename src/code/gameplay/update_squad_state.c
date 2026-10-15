#include "types.h"

typedef struct SquadUnit {
    u8 value00;
    u8 value01;
    u8 pad02[0x12];
    union {
        s32 word;
        struct {
            u16 hi;
            u16 lo;
        } half;
    } value14;
    s32 value18;
    u8 pad1C[0x4E8];
    s32 value504;
} SquadUnit;

typedef struct SquadInfo {
    u8 pad00[8];
    u32 flags;
} SquadInfo;

typedef struct Squad {
    s16 ids[5];
    u8 pad0A[6];
    s32 value10;
    u8 value14;
    u8 pad15;
    u16 value16;
    s32 value18;
    u8 pad1C[4];
    s16 value20;
    u8 value22;
    u8 pad23;
    u8 value24;
    u8 pad25[0x13];
    u8 value38;
    u8 pad39;
    s16 value3A;
    u8 pad3C[2];
    s16 value3E;
    s16 value40;
    u8 pad42[2];
    u16 value44;
    u8 pad46[2];
    u8 sound48[0xA4];
    s32 valueEC;
    u8 padF0[0xB6];
    u8 value1A6;
    u8 pad1A7[0x21];
    u32 value1C8;
    u32 value1CC;
    u32 value1D0;
    u8 pad1D4[0x34];
    s32 value208;
    s32 value20C;
    u8 pad210[0xF0];
    s32 value300;
    s32 value304;
    u8 value308;
    u8 pad309[0xF];
    f32 value318;
} Squad;

extern SquadInfo *func_80096784(u16 id);
extern SquadUnit *get_unit(s16 id) __asm__("func_800A03B8");
extern s32 game_mode_is_3_through_6(void) __asm__("func_8007C6D8");
extern s32 *get_game_mode(void) __asm__("func_8007AAF4");
extern s32 get_difficulty_level(void) __asm__("func_8007AAA0");
extern void func_800A5784(Squad *squad);
extern s32 func_800A5348(Squad *squad);
extern void func_80098780(SquadUnit *unit);
extern void func_800A4A00(Squad *squad);
extern void func_80078654(void *sound, s32 id);
extern void func_800786D4(void *sound, s32 mode);
extern void func_80077E94(void *sound);
extern u32 gGameMode __asm__("D_8012578C");
extern s32 gGameTicks __asm__("D_801B4AA8");
extern s32 D_801B4AD4;
extern u8 D_80134E68;
extern s32 D_80126128[2][3];
extern s32 D_80126140[2][3];

s32 update_squad_state(Squad *squad) __asm__("func_800A3DE0");

s32 update_squad_state(Squad *squad) {
    SquadInfo *info = 0;
    SquadUnit *unit;
    s32 *table;
    u32 i;
    u16 alive;
    s32 canRespawn;

    if (squad->value1A6 == 0) {
        info = func_80096784(squad->value16);
        if (info->flags & 0x1000) {
            switch (gGameMode) {
            case 1:
            case 2:
                squad->value14 ^= 1;
                break;
            case 6:
            case 7:
                D_801B4AD4 = 0;
                break;
            }
        }
    }
    if (squad->value18 != 0) {
        alive = 0;
        if (game_mode_is_3_through_6()) {
            if (squad->value3E != 0 || squad->value40 != 0) {
                if (squad->value22 - squad->value24 < squad->value38 - 1) {
                    func_800A5784(squad);
                }
            }
        }
        canRespawn = 0;
        if (squad->value3A != 0 || squad->value308 != 0) {
            if (squad->value22 < squad->value38) {
                canRespawn = 1;
            }
        }
        if (game_mode_is_3_through_6() && squad->value1A6 == 0) {
            if (squad->value24 != 0) {
                canRespawn = 0;
            }
        }
        if (squad->value300 != 0) {
            if (squad->value300 < gGameTicks) {
                if (canRespawn) {
                    if (func_800A5348(squad) >= 0) {
                        squad->value300 = 0;
                    }
                }
            }
        } else if (canRespawn) {
            squad->value300 = gGameTicks + squad->value304;
            if (*get_game_mode() == 0 && squad->value3A <= 0) {
                squad->value304 += (s32)(squad->value318 / 100.0f * 30.0f);
                if (squad->value318 / 100.0f * 360.0f < (f32)squad->value304) {
                    squad->value304 = squad->value318 / 100.0f * 360.0f;
                }
            }
        }
        if (squad->value1A6 == 0 && squad->value14 == 0) {
            if (D_80134E68 == 0) {
                if ((info->flags & squad->value1C8) && squad->value20 != 0xFF) {
                    func_80098780(get_unit(squad->value20));
                }
            }
            if (gGameMode == 1 || gGameMode == 5) {
                if (info->flags & squad->value1D0) {
                    if (*get_game_mode() != 2) {
                        func_800A4A00(squad);
                    }
                }
                if ((info->flags & squad->value1CC) && squad->value20 != 0xFF) {
                    unit = get_unit(squad->value20);
                    if (unit->value504 == squad->valueEC) {
                        if (squad->value44 == 0) {
                            table = (get_difficulty_level() >= 3) ? D_80126140[1] : D_80126140[0];
                            func_80078654(squad->sound48, table[unit->value18]);
                            func_800786D4(squad->sound48, 2);
                            squad->value44 = 1;
                        } else {
                            table = (get_difficulty_level() >= 3) ? D_80126128[1] : D_80126128[0];
                            func_80078654(squad->sound48, table[unit->value18]);
                            func_800786D4(squad->sound48, 2);
                            squad->value44 = 0;
                        }
                    }
                }
            }
        }
        if (squad->value3A != 0 || squad->value308 != 0) {
            alive = 1;
        } else if (squad->value208 != 0 && squad->value20C != 0) {
            alive = 1;
        } else {
            for (i = 0; i < 5; i++) {
                SquadUnit *member = get_unit(squad->ids[i]);

                if (member != 0 && member->value01 != 0 && !(member->value14.half.hi & 0x100)) {
                    alive = 1;
                }
            }
        }
        squad->value18 = alive;
        if (squad->value18 == 0) {
            squad->value10 = 0;
        }
    }
    if (squad->value1A6 == 0) {
        func_80077E94(squad->sound48);
    }
    return squad->value18;
}
