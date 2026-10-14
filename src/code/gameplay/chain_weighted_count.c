#include "types.h"

typedef struct ChainNode {
    u8 pad00[0x2C];
    struct ChainNode *next;
} ChainNode;

typedef struct ChainHead {
    u8 pad00[0x10];
    ChainNode *first;
} ChainHead;

typedef struct ChainOwner {
    u8 pad00[0x1AF];
    u8 value1AF;
    u8 pad1B0[0x8];
    ChainHead *value1B8;
} ChainOwner;

extern s32 func_8007AAB0(void);
extern ChainOwner *func_800A6688(s32 index);
extern f32 D_8007474C;

f32 chain_weighted_count(void) __asm__("func_800E7DD4");

f32 chain_weighted_count(void) {
    f32 total = 0.0f;
    ChainOwner *owner;
    ChainNode *node;

    if (func_8007AAB0() > 0) {
        owner = func_800A6688(0);
        if (owner->value1AF != 0 && owner->value1B8 != 0) {
            node = owner->value1B8->first;
            if (node != 0) {
                do {
                    node = node->next;
                    total += D_8007474C;
                } while (node != 0);
            }
        }
    }
    return total;
}
