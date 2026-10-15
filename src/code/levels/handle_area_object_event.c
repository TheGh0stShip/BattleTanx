#include "types.h"

typedef struct AreaRect {
    s16 value00;
    s16 x;
    s16 y;
    s16 value06;
    s16 value08;
    s16 value0A;
    s16 value0C;
    s16 value0E;
    u16 value10;
} AreaRect;

typedef struct AreaRecord {
    AreaRect rect;
    u8 pad12[0x28 - 0x12];
} AreaRecord;

typedef struct AreaObject {
    u8 pad00[0x10];
    f32 y;
    f32 x;
    s32 value18;
    s32 area;
} AreaObject;

extern AreaRecord D_803B8254[];
extern f32 D_80074E04;
extern void func_801074AC(s32 area, s32 x, s32 y, u16 value) __asm__("func_801074AC");
extern void func_80109364(AreaRecord *record, s32 a, s32 b, s32 c, s32 d) __asm__("func_80109364");
extern void reflect_heading_off_zone_box(void *zone, s32 kind, void *mover, s32 result) __asm__("func_800F2270");

void handle_area_object_event(AreaObject *obj, s32 arg1, u32 event, s32 *data, s32 arg4) __asm__("func_800F2478");

void handle_area_object_event(AreaObject *obj, s32 arg1, u32 event, s32 *data, s32 arg4) {
    AreaRect rect;

    switch (event) {
        case 0:
            reflect_heading_off_zone_box(obj, arg1, data, arg4);
            break;
        case 5:
            rect = D_803B8254[*data].rect;
            obj->x = rect.x;
            obj->y = rect.y;
            func_801074AC(obj->area, rect.x, rect.y, rect.value10);
            func_80109364(&D_803B8254[obj->area], rect.value06 * D_80074E04, rect.value08 * D_80074E04,
                          rect.value0A * D_80074E04, rect.value0C * D_80074E04);
            break;
        case 4:
            obj->value18 = 0;
            break;
    }
}
