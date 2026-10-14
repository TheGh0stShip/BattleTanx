#include "types.h"

typedef struct ListNode {
    u8 pad00[0x2C];
    struct ListNode *next;
} ListNode;

s32 func_800A6E10(void *value)
{
    ListNode *node = *(ListNode **)((u8 *)value + 0x10);
    s32 count = 0;

    while (node != 0) {
        node = node->next;
        count++;
    }
    return count;
}
