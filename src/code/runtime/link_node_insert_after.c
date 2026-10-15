typedef struct LinkNode { struct LinkNode *previous; struct LinkNode *next; } LinkNode;
void link_node_insert_after(LinkNode *node, LinkNode *inserted) __asm__("func_800AB640");
void link_node_insert_after(LinkNode *node, LinkNode *inserted)
{
    LinkNode *oldNext = node->next;
    inserted->next = oldNext;
    if (oldNext != 0) oldNext->previous = inserted;
    inserted->previous = node;
    node->next = inserted;
}
