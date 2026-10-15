#include "types.h"

typedef struct NearbyUnit {
    u8 pad00;
    u8 active;
    u8 pad02[0x12];
    u16 flags;
    u8 pad16[0xE];
    f32 position[3];
    u8 pad30[0x316];
    u16 slot;
} NearbyUnit;

typedef struct UnitIdList {
    u8 pad00[8];
    s16 ids[15];
    u16 count;
} UnitIdList;

extern NearbyUnit *get_unit(s16 id) __asm__("func_800A03B8");
extern s32 ai_member_status_is_1(NearbyUnit *unit) __asm__("func_800E3470");
extern f32 approx_xz_distance(f32 *a, f32 *b) __asm__("func_800E0D54");
extern f32 D_800743A0;
extern f32 D_800743A4;

void count_nearby_units_by_slot(u8 *counts, NearbyUnit *self, UnitIdList *list) __asm__("func_800DED28");
void count_nearby_units_by_slot(u8 *counts, NearbyUnit *self, UnitIdList *list) {
    s32 i;

    for (i = 0; i < list->count; i++) {
        NearbyUnit *unit = get_unit(list->ids[i]);
        f32 distance;
        u16 score;
        u16 slot;

        if (unit->active == 0) {
            continue;
        }
        if (unit == self) {
            continue;
        }
        if (unit->flags & 4) {
            continue;
        }
        if (ai_member_status_is_1(unit) != 0) {
            continue;
        }
        distance = approx_xz_distance(self->position, unit->position);
        if (distance > D_800743A0) {
            continue;
        }
        score = 4 - (u32)(distance / D_800743A4);
        slot = unit->slot;
        if (score == 0) {
            counts[slot] = 0;
        } else {
            counts[slot]++;
        }
    }
}
