#include "types.h"

typedef struct ListNode {
    u8 pad00[0x2C];
    struct ListNode *next;
} ListNode;

typedef struct OwnerNodeList {
    u8 pad00[0x10];
    ListNode *head;
} OwnerNodeList;

typedef struct OwnerRecord {
    s16 unitIds[0xD7];
    u8 value1AE;
    u8 value1AF;
    u8 pad1B0[0x8];
    OwnerNodeList *list;
} OwnerRecord;

typedef struct WeightUnit {
    u8 value00;
    u8 value01;
    u8 pad02[0x96];
    s32 value98;
} WeightUnit;

extern s32 get_entity_capacity(void) __asm__("func_8007AAB0");
extern OwnerRecord *get_entity_record(u16 index) __asm__("func_800A6688");
extern WeightUnit *get_unit(s16 id) __asm__("func_800A03B8");
extern f32 gOwnerListNodeWeight __asm__("D_8007472C");
extern f32 gOwnerActiveUnitWeight __asm__("D_80074730");

f32 get_owner_list_and_unit_weight(void) __asm__("func_800E7934");

f32 get_owner_list_and_unit_weight(void) {
    f32 weight = 0.0f;
    f32 listWeight;
    OwnerRecord *owner;
    OwnerRecord *unitOwner;
    f32 unitWeight;
    ListNode *node;
    WeightUnit *unit;
    u16 i;

    if (get_entity_capacity() > 0) {
        owner = get_entity_record(0);
        if (owner->value1AF != 0 && owner->list != 0) {
            node = owner->list->head;
            if (node != 0) {
                do {
                    node = node->next;
                    weight += gOwnerListNodeWeight;
                } while (node != 0);
            }
        }
    }
    listWeight = weight;

    weight = 0.0f;
    if (get_entity_capacity() <= 0) {
        unitWeight = weight;
    } else {
        unitOwner = get_entity_record(0);
        for (i = 0; i < 5; i++) {
            unit = get_unit(unitOwner->unitIds[i]);
            if (unit->value01 != 0 && unit->value98 != 0) {
                weight = gOwnerActiveUnitWeight;
                break;
            }
        }
        unitWeight = weight;
    }
    return listWeight + unitWeight;
}
