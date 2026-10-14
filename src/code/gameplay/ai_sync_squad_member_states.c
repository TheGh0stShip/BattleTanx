#include "types.h"

typedef struct SquadUnit {
    u8 pad00;
    u8 alive;
    u8 pad02[0x96];
    s32 value98;
    u8 pad9C[0xCC - 0x9C];
    s32 valueCC;
    u8 padD0[0x4];
    s32 valueD4;
} SquadUnit;

typedef struct UnitQuery {
    u8 pad00[0x10];
    s32 value10;
    u8 pad14[0x34];
} UnitQuery;

extern s16 *ai_get_squad_member_ids(u16 slot) __asm__("func_800A6688");
extern SquadUnit *get_unit(s16 id) __asm__("func_800A03B8");
extern s32 entity_state_is_one(SquadUnit *unit) __asm__("func_800E3470");
extern void func_800E9894(UnitQuery *query, s16 id);
extern void func_800EA1FC(UnitQuery *query, s32 arg1);
extern void func_800EA1B8(s32 arg0, s32 arg1);

void ai_sync_squad_member_states(u16 slot) __asm__("func_800E4820");

void ai_sync_squad_member_states(u16 slot)
{
    s16 *members = ai_get_squad_member_ids(slot);
    UnitQuery query;
    SquadUnit *unit;
    s16 id;
    u16 i;

    for (i = 0; i < 5; i++) {
        id = members[i];
        unit = get_unit(id);
        if (unit->alive == 0) {
            continue;
        }
        if (entity_state_is_one(unit)) {
            continue;
        }
        if (unit->value98 == 0) {
            if (unit->valueCC != 0 && unit->valueD4 == 16) {
                func_800E9894(&query, id);
                func_800EA1FC(&query, 0);
            }
        } else if (unit->valueCC != 0 && unit->valueD4 != 16) {
            func_800E9894(&query, id);
            func_800EA1FC(&query, 0);
            func_800EA1B8(query.value10, 16);
        }
    }
}
