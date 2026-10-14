#include "types.h"

typedef struct PoolNode {
    u8 pad00;
    u8 inUse;
    u8 pad02[0x2];
    u16 next;
    u16 children;
    u8 pad08[0x10];
} PoolNode;

PoolNode *take_free_pool_node(PoolNode *pool, u16 *freeHead) __asm__("func_800DF58C");

PoolNode *take_free_pool_node(PoolNode *pool, u16 *freeHead) {
    PoolNode *node;
    PoolNode *tail;
    u16 children;
    u16 next;

    node = &pool[*freeHead];
    children = node->children;
    next = node->next;
    if (children == 0) {
        *freeHead = next;
    } else {
        u16 *link;
        tail = &pool[children];
        while (*(link = &tail->next) != 0) {
            tail = &pool[*link];
        }
        *link = next;
        *freeHead = children;
    }
    node->inUse = 1;
    node->children = 0;
    node->next = 0;
    return node;
}
