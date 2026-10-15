#include "types.h"

typedef struct ObjectGroup {
    u8 count;
    u8 pad01;
    u16 first;
    u8 pad04[0x14];
} ObjectGroup;

typedef struct GroupObject {
    u8 active;
    u8 pad01[3];
    u32 kind;
    u8 pad08[0x40];
    f32 x;
    f32 z;
    u8 pad50[8];
} GroupObject;

typedef struct ObjectSession {
    u8 pad000[0x564];
    ObjectGroup *groups;
    GroupObject *objects;
    u8 pad56C[0xC8];
    s32 groupCount;
} ObjectSession;

typedef struct PointEntity {
    u8 pad000[0x1AF];
    u8 pointCount;
    struct {
        f32 x;
        f32 z;
    } points[1];
    s32 firstRecord;
} PointEntity;

extern ObjectSession *get_spawn_session(void) __asm__("func_800821C0");
extern s32 get_entity_capacity(void) __asm__("func_8007AAB0");
extern PointEntity *get_entity_record(s32 index) __asm__("func_800A6688");
extern s32 create_entity_point_record(s32 index, f32 *point, ObjectSession *session,
                                      GroupObject *object) __asm__("func_800A6AB4");
extern u8 gSlotRank[] __asm__("D_801260A4");

void assign_group_object_points(void) __asm__("func_800A4B2C");

static inline s32 has_entries(s32 count)
{
    return count > 0;
}

void assign_group_object_points(void)
{
    ObjectSession *session;
    ObjectGroup *group;
    GroupObject *object;
    PointEntity *entity;
    s32 slot;
    f32 *point;
    s32 record;
    s32 i;
    s32 j;
    volatile s32 groupOffset;
    volatile u8 scratch[16];
    s32 one;

    session = get_spawn_session();
    i = 0;
    if (session->groupCount > 0) {
        one = 1;
        groupOffset = 0;
        do {
            group = (ObjectGroup *)((u8 *)session->groups + groupOffset);
            if (has_entries(group->count)) {
                j = 0;
                do {
                    object = &session->objects[group->first + j];
                    if (object->active != 0) {
                        switch (object->kind) {
                        case 11:
                            slot = gSlotRank[0];
                            break;
                        case 12:
                            slot = gSlotRank[1];
                            break;
                        case 13:
                            slot = gSlotRank[2];
                            break;
                        case 14:
                            slot = gSlotRank[3];
                            break;
                        default:
                            goto next;
                        }
                        point = &object->x;
                        if (slot < get_entity_capacity()) {
                            entity = get_entity_record(slot);
                            if (entity->pointCount != one) {
                                entity->points[entity->pointCount].z = object->z;
                                entity->points[entity->pointCount].x = object->x;
                                record = create_entity_point_record(slot, point, session, object);
                                if (entity->pointCount == 0) {
                                    entity->firstRecord = record;
                                }
                                entity->pointCount++;
                            }
                        }
                    }
next:
                    j++;
                } while (j < group->count);
            }
            groupOffset += sizeof(ObjectGroup);
            i++;
        } while (i < session->groupCount);
    }
}
