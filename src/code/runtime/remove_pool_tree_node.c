#include "types.h"

/* 0x18-byte pool node; index 0 is the null link. */
typedef struct PoolTreeNode {
    u8 pad00;
    u8 value01;
    u8 pad02[0x2];
    u16 left;
    u16 right;
    u8 pad08[0x4];
    f32 key;
    u8 pad10[0x8];
} PoolTreeNode;

/* The root link sits directly after 0xBB9 nodes (offset 0x11958). */
typedef struct PoolTree {
    PoolTreeNode nodes[0xBB9];
    u16 root;
} PoolTree;

s32 remove_pool_tree_node(PoolTree *tree, u16 id) __asm__("func_800DF60C");

/*
 * Unlinks node id from the key-ordered tree, attaching its left subtree to the
 * leftmost node of its right subtree. Returns 1 when the node was found.
 */
s32 remove_pool_tree_node(PoolTree *tree, u16 id) {
    s32 removed = 0;
    u16 *link = &tree->root;
    f32 key = tree->nodes[id].key;

    for (;;) {
        u16 index = *link;

        if (index == id) {
            PoolTreeNode *node = &tree->nodes[index];
            u16 right = node->right;
            u16 left = node->left;

            if (right == 0) {
                *link = left;
            } else {
                u16 *slot;
                PoolTreeNode *last = &tree->nodes[right];

                while (*(slot = &last->left) != 0) {
                    last = &tree->nodes[*slot];
                }
                *slot = left;
                *link = right;
            }
            removed = 1;
            node->value01 = 1;
            node->right = 0;
            node->left = 0;
            break;
        }
        if (index == 0) {
            break;
        }
        if (key <= tree->nodes[index].key) {
            link = &tree->nodes[index].left;
        } else {
            link = &tree->nodes[index].right;
        }
    }
    return removed;
}
