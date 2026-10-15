#include "types.h"

typedef struct ObjectBounds {
    u8 pad00[0x10];
    f32 *anchor;
    u8 pad14[0x4];
    s32 kind;
    f32 minX;
    f32 minZ;
    f32 maxX;
    f32 maxZ;
} ObjectBounds;

typedef struct ObjectRecord {
    u8 pad000[0x1AE];
    u8 group;
    u8 linked;
    f32 x;
    f32 z;
    ObjectBounds *bounds;
} ObjectRecord;

typedef struct ObjectGroup {
    u16 members[3];
    u16 count;
    u8 pad08[0x4A];
} ObjectGroup;

extern ObjectRecord *get_entity_record(u16 index) __asm__("func_800A6688");
extern f32 ai_horizontal_length(f32 *offset) __asm__("func_800E0BC4");
extern ObjectGroup gObjectGroups[] __asm__("D_8033A980");
extern f32 gObjectCenterDivisor __asm__("D_80074628");
extern f32 gObjectCenterOffsetScale __asm__("D_8007462C");

ObjectBounds *ai_find_object_position(u16 id, f32 *point, s32 useCenter)
    __asm__("func_800E377C");

ObjectBounds *ai_find_object_position(u16 id, f32 *point, s32 useCenter)
{
    ObjectRecord *record = 0;
    ObjectBounds *bounds = 0;
    ObjectGroup *group;
    u16 i;
    f32 position[2];
    f32 center[2];
    f32 offset[2];
    f32 scale;
    f32 *anchor;

    if (id != 0xFF) {
        record = get_entity_record(id);
        if (record->linked == 0) {
            group = &gObjectGroups[record->group];
            for (i = 0; i < group->count; i++) {
                record = get_entity_record(group->members[i]);
                if (record->linked != 0) {
                    break;
                }
            }
            if (record->linked == 0) {
                goto resolved;
            }
        }
        bounds = record->bounds;
    }
resolved:
    if (bounds == 0) {
        if (point != 0) {
            point[1] = point[0] = 0.0f;
        }
        return bounds;
    } else if (point != 0) {
        if (bounds->kind >= 2 || useCenter == 0) {
            anchor = bounds->anchor;
            if (anchor != 0) {
                point[1] = anchor[8];
                point[0] = anchor[7];
            } else {
                point[1] = record->z;
                point[0] = record->x;
            }
        } else {
            position[1] = record->z;
            position[0] = record->x;
            center[1] = (bounds->minZ + bounds->maxZ) / gObjectCenterDivisor;
            center[0] = (bounds->minX + bounds->maxX) / gObjectCenterDivisor;
            offset[1] = center[1] - position[1];
            offset[0] = center[0] - position[0];
            scale = gObjectCenterOffsetScale / ai_horizontal_length(offset);
            offset[1] *= scale;
            offset[0] *= scale;
            point[1] = center[1] + offset[1];
            point[0] = center[0] + offset[0];
        }
    }
    return bounds;
}
