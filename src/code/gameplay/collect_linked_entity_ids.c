#include "types.h"

typedef struct EntityIdLists {
    s16 initialIds[3];
    u16 initialCount;
    s16 linkedIds[15];
    u16 linkedCount;
} EntityIdLists;

extern s16 *get_linked_entity_ids(u16 id) __asm__("func_800A6688");
extern void visit_entity_id(s16 id) __asm__("func_800A03B8");

void collect_linked_entity_ids(EntityIdLists *lists, s16 id) __asm__("func_800E4D44");

void collect_linked_entity_ids(EntityIdLists *lists, s16 id)
{
    s16 linkedId;
    s16 *linkedIds;
    s32 i;
    s32 index;

    linkedIds = get_linked_entity_ids(id & 0xFFFF);
    lists->initialIds[lists->initialCount] = id;
    lists->initialCount++;
    for (i = 0; (u32)(i & 0xFFFF) < 5U; i++) {
        index = i & 0xFFFF;
        linkedId = linkedIds[index];
        visit_entity_id(linkedId);
        lists->linkedIds[lists->linkedCount] = linkedId;
        lists->linkedCount++;
    }
}
