#include "types.h"

typedef struct PointRecordPos {
    f32 x;
    f32 y;
} PointRecordPos;

typedef struct PointRecordOwner {
    u8 pad00[0x50];
    u16 flags;
} PointRecordOwner;

typedef struct PointLink {
    u8 pad00[0x28];
    struct PointRecord *record;
} PointLink;

typedef struct PointRecord {
    u8 pad00[0xC];
    u8 index;
    u8 pad0D[0x3];
    PointLink *link;
    PointRecordOwner *owner;
    s32 value18;
    f32 value1C;
    f32 value20;
    f32 value24;
    f32 value28;
} PointRecord;

typedef struct AreaCorners {
    f32 value00[4];
    f32 value10;
    f32 value14;
    f32 value18;
    f32 value1C;
} AreaCorners;

extern PointRecord *allocate_effect(s32 group, s32 kind, s32 size) __asm__("func_8008AD10");
extern PointLink *spawn_effect_kind_15(u8 value, PointRecordPos *position) __asm__("func_800A6958");
extern s32 create_effect_motion(PointRecord *owner, s32 x, s32 y, s32 minX, s32 maxX, s32 minY,
                                s32 maxY, s32 mode, s32 flags) __asm__("func_80106D18");
extern s32 *get_game_mode(void) __asm__("func_8007AAF4");
extern void area_box_corners(s32 index, AreaCorners *out) __asm__("func_80108E74");

PointRecord *create_entity_point_record(u8 index, PointRecordPos *point, s32 arg2,
                                        PointRecordOwner *owner) __asm__("func_800A6AB4");

PointRecord *create_entity_point_record(u8 index, PointRecordPos *point, s32 arg2,
                                        PointRecordOwner *owner)
{
    AreaCorners corners;
    PointRecord *record;
    PointLink *link;
    s32 motion;

    record = allocate_effect(0, 0x14, 0x2C);
    if (record == 0) {
        return 0;
    }
    record->index = index;
    motion = create_effect_motion(record, point->y, point->x, -0xC3, 0xC3, -0xC3, 0xC3, 2,
                                  owner->flags);
    if (*get_game_mode() == 6 && index == 0) {
        record->link = 0;
    } else {
        link = spawn_effect_kind_15(index, point);
        record->link = link;
        link->record = record;
    }
    record->owner = owner;
    record->value18 = 0;
    area_box_corners(motion, &corners);
    record->value20 = corners.value14;
    record->value1C = corners.value10;
    record->value28 = corners.value1C;
    record->value24 = corners.value18;
    return record;
}
