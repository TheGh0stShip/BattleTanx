#include "types.h"

typedef struct UnitLink {
    u8 pad00[0x4];
    u8 active;
    u8 pad05[0x3];
    f32 distance;
} UnitLink;

typedef struct LinkTeam {
    u8 pad00[0x8];
    s16 members[15];
    u16 memberCount;
    u8 pad28[0x2A];
} LinkTeam;

typedef struct LinkUnit {
    u8 pad000[0x4];
    u8 ownerId;
    u8 pad005[0x354];
    u8 nearestMember;
} LinkUnit;

typedef struct LinkOwner {
    u8 pad000[0x1AE];
    u8 teamIndex;
} LinkOwner;

extern u8 D_8033B450[][20];
extern UnitLink D_8033AAE8[];
extern LinkTeam D_8033A980[];
extern f32 D_80074658;

extern LinkUnit *get_unit(s16 id) __asm__("func_800A03B8");
extern LinkOwner *get_entity_record(u16 index) __asm__("func_800A6688");

void select_nearest_linked_member(s16 id) __asm__("func_800E5DE4");

static inline UnitLink *get_unit_link(s16 fromId, s16 toId) {
    if (fromId < toId) {
        return &D_8033AAE8[D_8033B450[fromId][toId]];
    }
    if (toId < fromId) {
        return &D_8033AAE8[D_8033B450[toId][fromId]];
    }
    return 0;
}

void select_nearest_linked_member(s16 id) {
    LinkUnit *unit;
    LinkTeam *team;
    UnitLink *link;
    f32 best;
    s16 nearest;
    s16 other;
    u16 i;
    s16 *members;

    unit = get_unit(id);
    team = &D_8033A980[get_entity_record(unit->ownerId)->teamIndex];
    nearest = 0xFF;
    best = D_80074658;
    members = team->members;
    for (i = 0; i < team->memberCount; i++) {
        other = members[i];
        if (id != other) {
            link = get_unit_link(id, other);
            if (link->active && link->distance < best) {
                best = link->distance;
                nearest = other;
            }
        }
    }
    unit->nearestMember = nearest;
}
