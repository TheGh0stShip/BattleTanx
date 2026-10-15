#include "types.h"

typedef struct AreaBox {
    u8 data[0x18];
} AreaBox;

typedef struct SpawnPoint {
    f32 x;
    f32 y;
    u16 angle;
    u8 pad0A[0x6];
    u8 kind;
    u8 pad11[0x3];
    s32 lastUsed;
} SpawnPoint;

typedef struct SpawnGroup {
    SpawnPoint points[5];
} SpawnGroup;

typedef struct SpawnSession {
    u8 pad000[0x370];
    s32 pointCounts[4];
    SpawnGroup groups[1];
} SpawnSession;

typedef struct SpawnPlacement {
    f32 x;
    f32 y;
    u16 angle;
} SpawnPlacement;

typedef struct AreaObject {
    u8 pad00[0x8];
    s32 kind;
} AreaObject;

typedef struct SquadUnit {
    u8 pad00;
    u8 active;
} SquadUnit;

typedef struct Squad {
    s16 members[5];
    u8 pad0A[0xC];
    u16 group;
    u8 pad18[0x26];
    s16 respawns[2];
} Squad;

typedef void (*AreaObjectCallback)(AreaObject *object, s32 a1, s32 a2, s32 a3, s32 a4);

extern SpawnSession *get_spawn_session(void) __asm__("func_800821C0");
extern void build_area_box_by_shape(f32 x, f32 y, u16 flags, u32 shape, AreaBox *box, f32 scale)
    __asm__("func_80096E80");
extern u8 find_objects_in_area(AreaBox *box, s32 capacity, AreaObject **results, s32 *count)
    __asm__("func_80107A14");
extern SquadUnit *get_unit(s16 id) __asm__("func_800A03B8");
extern void spawn_unit_at_placement(s16 unit, s32 owner, SpawnPlacement *placement, s32 shape, u8 kind,
                                    u8 option, u8 force) __asm__("func_8009FA70");
typedef struct AreaHandlerEntry {
    s32 value00;
    void (*handler)(AreaObject *object, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
    s32 value08;
} AreaHandlerEntry;

extern AreaHandlerEntry D_802C3800[];
extern s32 D_801B4AA8;

s32 respawn_squad_member(Squad *squad) __asm__("func_800A5784");

s32 respawn_squad_member(Squad *squad) {
    s32 shape;
    SpawnSession *session = get_spawn_session();
    AreaBox box;
    AreaObject *hits[16];
    SpawnPlacement placement;
    SpawnPlacement *spawn;
    s32 count;
    SpawnPoint *point;
    s32 i;
    s32 j;
    u8 clear;
    u8 kind;

    shape = squad->respawns[0] == 0;
    for (i = 1; i < session->pointCounts[squad->group]; i++) {
        point = &session->groups[squad->group].points[i];
        if (point->lastUsed > D_801B4AA8 - 360) {
            continue;
        }
        clear = 1;
        spawn = &placement;
        placement.x = point->x;
        placement.y = point->y;
        placement.angle = point->angle;
        kind = point->kind;
        build_area_box_by_shape(placement.x, placement.y, placement.angle, shape, &box, 1.0f);
        if (find_objects_in_area(&box, 16, hits, &count)) {
            for (j = 0; j < count; j++) {
                if ((u32)hits[j] >= 4) {
                    if (hits[j]->kind == 0x1A) {
                        if (D_802C3800[0x1A].handler != 0) {
                            D_802C3800[0x1A].handler(hits[j], 0, 4, 0, 0);
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

found:
    for (j = 0; j < 5; j++) {
        if (!get_unit(squad->members[j])->active) {
            spawn_unit_at_placement(squad->members[j], squad->group, spawn, shape, kind, 1, 1);
            point->lastUsed = D_801B4AA8;
            if (squad->respawns[shape] > 0) {
                squad->respawns[shape]--;
            }
            return 0;
        }
    }
    return -1;
}
