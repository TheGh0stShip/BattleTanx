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

typedef struct UnitState {
    u8 pad000[0x1A8];
    u16 entityIndex;
} UnitState;

typedef struct ChainContext {
    u8 pad00[0x4];
    UnitState *unit;
} ChainContext;

extern s32 get_entity_capacity(void) __asm__("func_8007AAB0");
extern ChainEntity *get_entity_record(u16 index) __asm__("func_800A6688");
extern f32 D_800747D8;
extern f32 D_800747DC;

static inline f32 entity_chain_weight(u16 index) {
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
                    total += D_800747D8;
                } while (link != 0);
                return total;
            }
        }
    }
    return total;
}

f32 ai_parameter_inverse_chain_weight(ChainContext *context) __asm__("func_800E8A48");

f32 ai_parameter_inverse_chain_weight(ChainContext *context) {
    return D_800747DC - entity_chain_weight(context->unit->entityIndex);
}
