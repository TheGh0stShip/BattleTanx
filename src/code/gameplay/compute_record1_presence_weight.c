#include "types.h"

typedef struct ScoreNode {
    u8 pad00[0x2C];
    struct ScoreNode *next;
} ScoreNode;

typedef struct ScoreList {
    u8 pad00[0x10];
    ScoreNode *head;
} ScoreList;

typedef struct ScoreRecord {
    s16 members[5];
    u8 pad0A[0x1A5];
    u8 active;
    u8 pad1B0[0x8];
    ScoreList *list;
} ScoreRecord;

typedef struct ScoreUnit {
    u8 pad00[0x1];
    u8 enabled;
    u8 pad02[0x96];
    s32 state;
} ScoreUnit;

extern f32 D_80074734;
extern f32 D_80074738;

extern s32 get_entity_capacity(void) __asm__("func_8007AAB0");
extern ScoreUnit *get_unit(s16 id) __asm__("func_800A03B8");
extern ScoreRecord *get_entity_record(u16 index) __asm__("func_800A6688");

f32 compute_record1_presence_weight(void) __asm__("func_800E7A50");

static inline s32 entity_capacity_exceeds(s32 limit) {
    return get_entity_capacity() > limit;
}

f32 compute_record1_presence_weight(void) {
    ScoreRecord *owner;
    ScoreRecord *record;
    ScoreNode *node;
    ScoreUnit *unit;
    f32 weight;
    f32 total;
    f32 result;
    u16 i;

    weight = 0.0f;
    if (entity_capacity_exceeds(1)) {
        owner = get_entity_record(1);
        if (owner->active && owner->list != 0) {
            for (node = owner->list->head; node != 0; node = node->next) {
                weight += D_80074734;
            }
        }
    }
    total = weight;
    weight = 0.0f;
    if (!entity_capacity_exceeds(1)) {
        result = weight;
        goto done;
    }
    record = get_entity_record(1);
    for (i = 0; i < 5; i++) {
        unit = get_unit(record->members[i]);
        if (unit->enabled && unit->state != 0) {
            weight = D_80074738;
            break;
        }
    }
    result = weight;
done:
    return total + result;
}
