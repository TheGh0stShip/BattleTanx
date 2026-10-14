#include "types.h"

typedef struct ChainNode {
    u8 pad00[0x2C];
    struct ChainNode *next;
} ChainNode;

typedef struct ChainList {
    u8 pad00[0x10];
    ChainNode *head;
} ChainList;

typedef struct ChainEntity {
    u8 pad00[0x1AF];
    u8 value1AF;
    u8 pad1B0[8];
    ChainList *value1B8;
} ChainEntity;

extern s32 get_entity_capacity(void) __asm__("func_8007AAB0");
extern ChainEntity *get_entity_record(s32 index) __asm__("func_800A6688");
extern f32 D_80074750;

f32 sum_entity1_chain_weight(void) __asm__("func_800E7E50");

f32 sum_entity1_chain_weight(void) {
    f32 total = 0.0f;
    ChainEntity *entity;
    ChainNode *node;
    s32 index = 1;

    if (get_entity_capacity() > index) {
        entity = get_entity_record(index);
        if (entity->value1AF != 0 && entity->value1B8 != 0) {
            for (node = entity->value1B8->head; node != 0; node = node->next) {
                total += D_80074750;
            }
        }
    }
    return total;
}
