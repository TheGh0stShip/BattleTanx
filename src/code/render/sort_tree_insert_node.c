#include "types.h"

typedef struct SortTreeNode {
    u8 value00;
    u8 value01;
    u8 pad02[2];
    u16 left;
    u16 right;
    u8 pad08[4];
    f32 key;
    u8 pad10[8];
} SortTreeNode;


void sort_tree_insert_node(SortTreeNode *nodes, u16 index) __asm__("func_800DF4E8");
void sort_tree_insert_node(SortTreeNode *nodes, u16 index) {
    u16 *link = (u16 *)((u8 *)nodes + 0x11958);
    SortTreeNode *node = &nodes[index];
    f32 key;
    u16 cur;

    node->value01 = 0;
    node->left = 0;
    node->right = 0;
    cur = *link;
    key = node->key;
    while (cur != 0) {
        SortTreeNode *other = &nodes[cur];
        if (key <= other->key) {
            link = &other->left;
        } else {
            link = &other->right;
        }
        cur = *link;
    }
    *link = index;
}
