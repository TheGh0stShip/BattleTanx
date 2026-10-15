#include "types.h"

typedef struct Unit {
    u8 pad00;
    u8 active;
    u8 pad02[0x22];
    f32 x;
    u8 pad28[0x4];
    f32 z;
} Unit;

typedef struct Squad {
    s16 unitIds[5];
    u8 pad0A[0x1A4];
    u8 team;
} Squad;

typedef struct UnitSearch {
    u8 pad00[0xD];
    u8 team;
    u8 pad0E[0xE];
    f32 z;
    f32 x;
    u8 pad24[0xA];
    s16 nearestUnit;
} UnitSearch;

extern s32 get_entity_capacity(void) __asm__("func_8007AAB0");
extern Squad *get_entity_record(u16 index) __asm__("func_800A6688");
extern Unit *get_unit(s16 id) __asm__("func_800A03B8");
extern s32 unit_is_targetable(Unit *unit) __asm__("func_8009FB8C");
extern f32 gMaximumDistanceSquared __asm__("D_80072C78");
extern f32 gEnemySearchRangeScale __asm__("D_80072C7C");
extern s32 gEnemySearchRange __asm__("D_80125858");

void find_nearest_enemy_unit(UnitSearch *search) __asm__("func_800A1170");

void find_nearest_enemy_unit(UnitSearch *search)
{
    f32 best = gMaximumDistanceSquared;
    s32 count = get_entity_capacity();
    s32 nearest = 0xFF;
    u16 i;

    for (i = 0; i < count; i++) {
        Squad *squad = get_entity_record(i);
        s32 slot;

        if (squad->team == search->team) {
            continue;
        }
        for (slot = 0; slot < 5; slot++) {
            Unit *unit = get_unit(squad->unitIds[slot]);

            if (unit->active != 0 && unit_is_targetable(unit) != 0) {
                f32 dx = unit->x - search->x;
                f32 dz = unit->z - search->z;
                f32 distance = dx * dx + dz * dz;

                if (distance < best) {
                    best = distance;
                    nearest = squad->unitIds[slot];
                }
            }
        }
    }
    if ((f32)(s32)((f32)(gEnemySearchRange * gEnemySearchRange) *
                   gEnemySearchRangeScale) < best) {
        search->nearestUnit = 0xFF;
    } else {
        search->nearestUnit = nearest;
    }
}
