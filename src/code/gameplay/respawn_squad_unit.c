#include "types.h"

typedef struct AreaBox {
    s16 bounds[12];
} AreaBox;

typedef struct AreaObject {
    u8 pad00[8];
    s32 kind;
} AreaObject;

typedef struct SpawnPos {
    f32 x;
    f32 z;
    u16 angle;
} SpawnPos;

typedef struct SquadSpawn {
    f32 x;
    f32 z;
    u16 angle;
    u8 pad0A[6];
    u8 orient;
    u8 pad11[7];
} SquadSpawn;

typedef struct SpawnSession {
    u8 pad000[0x280];
    SpawnPos teamSpawns[8][5];
} SpawnSession;

typedef struct SpawnSessionB {
    u8 pad000[0x370];
    s32 squadSpawnCount[4];
    SquadSpawn squadSpawns[4][5];
} SpawnSessionB;

typedef struct TeamList {
    u8 count;
    u8 pad01[3];
    s32 teams[1];
} TeamList;

typedef struct SquadUnit {
    u8 value00;
    u8 value01;
} SquadUnit;

typedef struct Squad {
    s16 ids[5];
    u8 pad0A[2];
    s32 value0C;
    u8 pad10[6];
    u16 value16;
    u8 pad18[0xC];
    u8 value24;
    u8 pad25[0x15];
    s16 value3A;
    u8 pad3C[0x16A];
    u8 value1A6;
    u8 pad1A7[0x162];
    u8 value309;
} Squad;

typedef void (*AreaHandler)(AreaObject *object, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

extern void *get_spawn_session(void) __asm__("func_800821C0");
extern TeamList *func_800A68C0(s32 id);
extern s32 *get_game_mode(void) __asm__("func_8007AAF4");
extern void func_80096E80(f32 x, f32 z, u16 angle, s32 team, AreaBox *box, f32 scale);
extern u8 find_objects_in_area(AreaBox *box, s32 capacity, AreaObject **results, s32 *count)
    __asm__("func_80107A14");
extern u32 next_random_u32(void) __asm__("func_800F38F4");
extern SquadUnit *get_unit(s16 id) __asm__("func_800A03B8");
extern void func_8009FA70(s16 id, u16 squad, void *spawn, s32 team, s32 orient, s32 arg5, s32 arg6);
typedef struct AreaHandlerEntry {
    s32 value00;
    AreaHandler handler;
    s32 value08;
} AreaHandlerEntry;

extern AreaHandlerEntry D_802C3800[];
extern u8 D_801260A0[];
extern u8 D_80135772;

s32 respawn_squad_unit(Squad *squad) __asm__("func_800A5348");

s32 respawn_squad_unit(Squad *squad) {
    SpawnSessionB *session = get_spawn_session();
    TeamList *list;
    void *spawn = 0;
    u8 orient = 0;
    AreaBox box;
    AreaObject *results[16];
    SpawnPos pos;
    s32 count;
    s32 team;
    s32 index;
    s32 offset;
    s32 i;
    s32 j;
    u8 clear;

    list = func_800A68C0(squad->value0C);
    do {
        index = squad->value309;
        team = list->teams[index];
        squad->value309 = (index + 1) % list->count;
    } while (team == 2 && squad->value309 == 0);
    switch ((u32)*get_game_mode()) {
    case 3:
    case 4:
    case 5:
    case 6:
        for (i = 0; i < session->squadSpawnCount[squad->value16]; i++) {
            SquadSpawn *entry = &session->squadSpawns[squad->value16][i];

            spawn = &pos;
            pos.x = entry->x;
            pos.z = entry->z;
            pos.angle = entry->angle;
            orient = entry->orient;
            clear = 1;
            func_80096E80(pos.x, pos.z, pos.angle, team, &box, 1.0f);
            if (find_objects_in_area(&box, 16, results, &count)) {
                for (j = 0; j < count; j++) {
                    if ((u32)results[j] >= 4) {
                        if (results[j]->kind == 0x1A) {
                            if (D_802C3800[0x1A].handler != 0) {
                                D_802C3800[0x1A].handler(results[j], 0, 4, 0, 0);
                            }
                        } else {
                            clear = 0;
                        }
                    }
                }
            }
            if (clear) {
                break;
            }
        }
        break;
    default:
        offset = next_random_u32() % 5;
        for (i = 0; i < 5; i++) {
            SpawnPos *entry = &((SpawnSession *)session)->teamSpawns[D_801260A0[squad->value16]][(i + offset) % 5];

            spawn = entry;
            clear = 1;
            func_80096E80(entry->x, entry->z, entry->angle, team, &box, 1.0f);
            if (find_objects_in_area(&box, 16, results, &count)) {
                for (j = 0; j < count; j++) {
                    if ((u32)results[j] >= 4) {
                        if (results[j]->kind == 0x1A) {
                            if (D_802C3800[0x1A].handler != 0) {
                                D_802C3800[0x1A].handler(results[j], 0, 4, 0, 0);
                            }
                        } else {
                            clear = 0;
                        }
                    }
                }
            }
            if (clear) {
                goto found;
            }
        }
        return -1;
    }
found:
    for (j = 0; j < 5; j++) {
        if (get_unit(squad->ids[j])->value01 == 0) {
            func_8009FA70(squad->ids[j], squad->value16, spawn, team, orient, 0, 0);
            if (squad->value3A > 0) {
                if (D_80135772 == 0 || squad->value16 != 0) {
                    squad->value3A--;
                }
            }
            if (squad->value1A6 == 0) {
                squad->value24 = 1;
            }
            return 0;
        }
    }
    return -1;
}
