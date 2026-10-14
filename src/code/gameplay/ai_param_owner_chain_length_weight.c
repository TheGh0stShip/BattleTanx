#include "types.h"

typedef struct ChainNode {
    u8 pad00[0x2C];
    struct ChainNode *next;
} ChainNode;

typedef struct {
    u8 pad00[0x10];
    ChainNode *head;
} ChainList;

typedef struct {
    u8 pad00[0x1AF];
    u8 active;
    u8 pad1B0[0x8];
    ChainList *list;
} OwnerRecord;

typedef struct {
    u8 pad00[0x1A8];
    u16 ownerIndex;
} AiMember;

typedef struct {
    u8 pad00[0x4];
    AiMember *member;
} AiParamContext;

extern s32 get_entity_capacity(void) __asm__("func_8007AAB0");
extern OwnerRecord *get_entity_record(u16 index) __asm__("func_800A6688");
extern f32 gChainNodeWeight __asm__("D_800747D4");

f32 ai_param_owner_chain_length_weight(AiParamContext *context) __asm__("func_800E89B8");

f32 ai_param_owner_chain_length_weight(AiParamContext *context) {
    f32 total = 0.0f;
    s32 index = context->member->ownerIndex;
    OwnerRecord *owner;
    ChainNode *node;

    if (index < get_entity_capacity()) {
        owner = get_entity_record(index);
        if (owner->active != 0 && owner->list != 0) {
            node = owner->list->head;
            if (node != 0) {
                do {
                    node = node->next;
                    total += gChainNodeWeight;
                } while (node != 0);
            }
        }
    }
    return total;
}
