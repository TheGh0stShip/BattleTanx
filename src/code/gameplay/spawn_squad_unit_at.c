#include "types.h"

typedef struct AreaBox {
    s16 value00;
    s16 value02;
    s16 value04;
    s16 value06;
    s16 value08;
    s16 value0A;
    s16 value0C;
    s16 value0E;
    s16 value10;
} AreaBox;

typedef struct SquadUnit {
    u8 pad00[0xC];
    u8 flags;
    u8 team;
    u8 value0E;
    u8 pad0F;
    s32 value10;
    s32 kind;
    s16 value18;
    u8 pad1A[0x2];
    f32 x;
    f32 z;
    s32 motion;
    s32 value28;
    u16 value2C;
    u8 pad2E[0x2];
    u8 value30;
    u8 serial;
    u8 value32;
    u8 value33;
    s32 value34;
} SquadUnit;

extern void func_80109268(AreaBox *box, s32 x, s32 y, s32 minA, s32 maxA, s32 minB, s32 maxB, s32 flags);
extern u8 func_80107A14(AreaBox *box, s32 capacity, void **results, s32 *count);
extern SquadUnit *allocate_effect(s32 group, s32 kind, s32 size) __asm__("func_8008AD10");
extern void func_800A1170(SquadUnit *unit);
extern s32 create_effect_motion(SquadUnit *owner, s32 x, s32 y, s32 minX, s32 maxX, s32 minY, s32 maxY,
                                s32 mode, s32 flags) __asm__("func_80106D18");
extern u16 D_80126010[];
extern f32 D_80126038[];
extern u8 D_8012607C;
extern f32 D_80072C88;
extern f32 D_80072C8C;
extern f32 D_80072C90;

static inline s32 area_is_clear(f32 *pos, s32 kind, AreaBox *box, void **results, s32 *count)
{
    f32 half = D_80126038[kind] * 45.0f;

    func_80109268(box, pos[1], pos[0], -half, half, -half, half, 0);
    return !func_80107A14(box, 16, results, count);
}

s32 spawn_squad_unit_at(u8 team, s32 value10, s32 kind, s16 value18, f32 *pos, s32 unused,
                        s32 checkArea, u8 flagged, u8 value33) __asm__("func_800A1408");

s32 spawn_squad_unit_at(u8 team, s32 value10, s32 kind, s16 value18, f32 *pos, s32 unused,
                        s32 checkArea, u8 flagged, u8 value33)
{
    void *results[16];
    AreaBox box;
    s32 count;
    SquadUnit *unit;
    f32 size;

    if (checkArea) {
        if (!area_is_clear(pos, kind, &box, results, &count)) {
            return -1;
        }
        {
            void *results2[16];
            AreaBox box2;
            s32 count2;

            if (!area_is_clear(pos, kind, &box2, results2, &count2)) {
                return -1;
            }
        }
    }
    unit = allocate_effect(1, 0x1B, 0x3C);
    if (unit == 0) {
        return -1;
    }
    unit->serial = D_8012607C;
    D_8012607C = (D_8012607C + 1) % 16;
    unit->value32 = 0;
    unit->team = team;
    unit->value10 = value10;
    unit->kind = kind;
    unit->z = pos[1];
    unit->x = pos[0];
    unit->value18 = value18;
    unit->value28 = 0;
    unit->flags = 0;
    unit->value33 = value33;
    unit->value2C = D_80126010[unit->kind];
    unit->value30 = 0xFF;
    func_800A1170(unit);
    size = D_80126038[kind];
    unit->motion = create_effect_motion(unit, unit->z, unit->x, size * -45.0f, size * 45.0f, size * -45.0f,
                                        size * 45.0f, 0xD6, 0);
    if (flagged) {
        unit->flags |= 4;
    }
    unit->value34 = -1;
    unit->value0E = 0;
    return 0;
}
