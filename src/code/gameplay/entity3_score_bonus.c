#include "types.h"

typedef struct ChainNode {
    u8 pad00[0x2C];
    struct ChainNode *next;
} ChainNode;

typedef struct ChainHead {
    u8 pad00[0x10];
    ChainNode *first;
} ChainHead;

typedef struct ScoreEntity {
    s16 units[5];
    u8 pad0A[0x1AF - 0xA];
    u8 value1AF;
    u8 pad1B0[0x1B8 - 0x1B0];
    ChainHead *chain;
} ScoreEntity;

typedef struct ScoreUnit {
    u8 value00;
    u8 value01;
    u8 pad02[0x98 - 0x2];
    s32 value98;
} ScoreUnit;

extern f32 D_80074744;
extern f32 D_80074748;
extern s32 get_entity_capacity(void) __asm__("func_8007AAB0");
extern ScoreEntity *get_entity_record(u16 index) __asm__("func_800A6688");
extern ScoreUnit *get_unit(s16 id) __asm__("func_800A03B8");

static inline f32 chain_score(u16 index) {
    f32 sum = 0.0f;
    ScoreEntity *entity;
    ChainNode *node;

    if (index < get_entity_capacity()) {
        entity = get_entity_record(index);
        if (entity->value1AF != 0 && entity->chain != 0 && (node = entity->chain->first) != 0) {
            do {
                sum += D_80074744;
                node = node->next;
            } while (node != 0);
        }
    }
    return sum;
}

static inline f32 unit_score(u16 index) {
    f32 result = 0.0f;
    ScoreEntity *entity;
    ScoreUnit *unit;
    u16 i;

    if (index >= get_entity_capacity()) {
        return result;
    }
    entity = get_entity_record(index);
    for (i = 0; i < 5; i++) {
        unit = get_unit(entity->units[i]);
        if (unit->value01 != 0 && unit->value98 != 0) {
            result = D_80074748;
            break;
        }
    }
    return result;
}

f32 entity3_score_bonus(void) __asm__("func_800E7CA8");
f32 entity3_score_bonus(void) {
    f32 total;

    total = chain_score(3);
    total += unit_score(3);
    return total;
}
