typedef struct LinkNode { struct LinkNode *previous; struct LinkNode *next; } LinkNode;
void link_node_remove(LinkNode *node) __asm__("func_800AB65C");
void link_node_remove(LinkNode *node)
{
    if (node->previous != 0) node->previous->next = node->next;
    if (node->next != 0) node->next->previous = node->previous;
    node->next = 0;
    node->previous = 0;
}
