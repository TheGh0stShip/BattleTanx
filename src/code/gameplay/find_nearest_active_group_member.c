#include "types.h"

typedef struct {
    u8 pad00[0x8];
    f32 value08;
} LinkRecord;

typedef struct {
    u8 value00;
    u8 value01;
} UnitHeader;

typedef struct {
    u8 pad00[0x8];
    s16 members[0xF];
    u16 memberCount;
} UnitGroup;

typedef struct {
    UnitGroup *group;
    u8 pad04[0x14];
    u16 unitId;
} GroupContext;

extern LinkRecord *get_link_record(s16 fromId, s16 toId) __asm__("func_800E52A0");
extern UnitHeader *get_unit(s16 id) __asm__("func_800A03B8");
extern f32 D_80074638;

s16 find_nearest_active_group_member(GroupContext *context) __asm__("func_800E3F90");

s16 find_nearest_active_group_member(GroupContext *context) {
    s16 best = 0xFF;
    UnitGroup *group = context->group;
    f32 bestDistance = D_80074638;
    u16 i = 0;
    u16 count = group->memberCount;
    s16 self = context->unitId;
    s16 *members = group->members;
    s16 other;
    LinkRecord *link;

    if (count != 0) {
        do {
            other = members[i];
            if (self != other) {
                link = get_link_record(self, other);
                if (link->value08 < bestDistance && get_unit(other)->value01 != 0) {
                    best = other;
                    bestDistance = link->value08;
                }
            }
            i++;
        } while (i < count);
    }
    return best;
}
