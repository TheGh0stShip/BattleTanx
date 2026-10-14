#include "types.h"

typedef struct Vec2f {
    f32 x;
    f32 y;
} Vec2f;

typedef struct EntityPointRecords {
    u8 pad000[0x1AF];
    u8 pointCount;
    Vec2f points[1];
    s32 firstRecord;
} EntityPointRecords;

extern s32 get_entity_capacity(void) __asm__("func_8007AAB0");
extern EntityPointRecords *get_entity_by_index(u16 index) __asm__("func_800A6688");
extern s32 create_entity_point_record(u8 index, Vec2f *point, s32 arg2, s32 arg3)
    __asm__("func_800A6AB4");

void append_entity_point_record(s32 index, Vec2f *point, s32 arg2, s32 arg3) __asm__("func_800A4A64");

void append_entity_point_record(s32 index, Vec2f *point, s32 arg2, s32 arg3)
{
    EntityPointRecords *entity;
    s32 record;

    if (index < get_entity_capacity()) {
        entity = get_entity_by_index(index & 0xFFFF);
        if (entity->pointCount != 1) {
            entity->points[entity->pointCount].y = point->y;
            entity->points[entity->pointCount].x = point->x;
            record = create_entity_point_record(index & 0xFF, point, arg2, arg3);
            if (entity->pointCount == 0) {
                entity->firstRecord = record;
            }
            entity->pointCount++;
        }
    }
}
