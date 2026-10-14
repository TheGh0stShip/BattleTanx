#include "types.h"

typedef struct TreeNode {
    u8 pad00;
    u8 popped;
    u8 pad02[2];
    u16 left;
    u16 right;
    u8 pad08[0x10];
} TreeNode;

typedef struct NodeTree {
    TreeNode nodes[1];
    u8 pad18[0x11958 - 0x18];
    u16 root;
} NodeTree;

static inline void splice_right_subtree(NodeTree *tree, u16 *parentSlot, u16 right, u16 left) {
    if (right == 0) {
        *parentSlot = left;
    } else {
        TreeNode *node = &tree->nodes[right];
        u16 *slot;

        while (*(slot = &node->left) != 0) {
            node = &tree->nodes[*slot];
        }
        *slot = left;
        *parentSlot = right;
    }
}

u16 sort_tree_pop_min_node(NodeTree *tree) __asm__("func_800DF6F4");

u16 sort_tree_pop_min_node(NodeTree *tree) {
    u16 dummy;
    u16 *slot;
    u16 *parentSlot;
    TreeNode *node;
    TreeNode *minNode;
    u16 index;
    u16 left;
    u16 right;

    index = 0;
    slot = &tree->root;
    dummy = 0;
    node = 0;
    parentSlot = &dummy;
    while (*slot != 0) {
        parentSlot = slot;
        node = &tree->nodes[*slot];
        slot = &node->left;
    }
    if (node != 0) {
        index = *parentSlot;
        minNode = &tree->nodes[index];
        right = minNode->right;
        left = minNode->left;
        splice_right_subtree(tree, parentSlot, right, left);
        minNode->popped = 1;
        minNode->right = 0;
        minNode->left = 0;
    }
    return index;
}
