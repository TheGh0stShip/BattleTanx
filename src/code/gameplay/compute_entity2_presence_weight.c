#include "types.h"

typedef struct ChainLink {
    u8 pad00[0x2C];
    struct ChainLink *next;
} ChainLink;

typedef struct ChainHead {
    u8 pad00[0x10];
    ChainLink *first;
} ChainHead;

typedef struct ChainEntity {
    u8 pad000[0x1AF];
    u8 active;
    u8 pad1B0[0x8];
    ChainHead *chain;
} ChainEntity;

typedef struct EntityRecord {
    s16 members[5];
} EntityRecord;

typedef struct SquadUnit {
    u8 pad00;
    u8 active;
    u8 pad02[0x96];
    s32 value98;
} SquadUnit;

extern s32 get_entity_capacity(void) __asm__("func_8007AAB0");
extern void *get_entity_record(u16 index) __asm__("func_800A6688");
extern SquadUnit *get_unit(s16 id) __asm__("func_800A03B8");
extern f32 D_8007473C;
extern f32 D_80074740;

static inline f32 entity_chain_weight(u16 index)
{
    f32 total = 0.0f;
    ChainEntity *entity;
    ChainLink *link;

    if (index < get_entity_capacity()) {
        entity = get_entity_record(index);
        if (entity->active != 0 && entity->chain != 0) {
            link = entity->chain->first;
            if (link != 0) {
                do {
                    link = link->next;
                    total += D_8007473C;
                } while (link != 0);
                return total;
            }
        }
    }
    return total;
}

static inline f32 entity_active_member_weight(u16 index)
{
    f32 result = 0.0f;
    EntityRecord *record;
    SquadUnit *unit;
    u16 i;

    if (index >= get_entity_capacity()) {
        return result;
    }
    record = get_entity_record(index);
    for (i = 0; i < 5; i++) {
        unit = get_unit(record->members[i]);
        if (unit->active != 0 && unit->value98 != 0) {
            result = D_80074740;
            break;
        }
    }
    return result;
}

f32 compute_entity2_presence_weight(void) __asm__("func_800E7B7C");

f32 compute_entity2_presence_weight(void)
{
    return entity_chain_weight(2) + entity_active_member_weight(2);
}
