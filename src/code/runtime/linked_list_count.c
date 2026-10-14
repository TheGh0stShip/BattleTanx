#include "types.h"

typedef struct ListNode {
    u8 pad00[0x2C];
    struct ListNode *next;
} ListNode;

typedef struct List {
    u8 pad00[0x10];
    ListNode *head;
} List;

s32 linked_list_count(List *list) __asm__("func_800A6E10");

s32 linked_list_count(List *list)
{
    ListNode *node = list->head;
    s32 count = 0;

    while (node != 0) {
        node = node->next;
        count++;
    }
    return count;
}
