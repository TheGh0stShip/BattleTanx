#include "types.h"

typedef struct PlacementGroup {
    u8 pad00[2];
    u16 set;
    u8 pad04[8];
} PlacementGroup;

typedef struct PlacementSet {
    u8 count;
    u8 pad01;
    u16 first;
} PlacementSet;

typedef struct PlacementPoint {
    s32 shape;
    s32 record;
    u8 pad08[4];
} PlacementPoint;

typedef struct PlacementRecord {
    u8 data[8];
} PlacementRecord;

typedef struct PlacementSession {
    u8 pad000[0x570];
    PlacementGroup *groups;
    PlacementSet *sets;
    PlacementPoint *points;
    PlacementRecord *shapes;
    PlacementRecord *records;
} PlacementSession;

extern void *func_8008067C(s32 arg0, s32 arg1, PlacementRecord *record);
extern void func_80080910(PlacementRecord *shape, void *record, f32 *position, f32 scale, f32 arg4, u16 arg5,
                          s32 corner, s32 arg7);

void place_group_corner_shapes(PlacementSession *session, s32 group, f32 *position, f32 scale, f32 arg4, u16 arg5, s32 arg6,
       s32 arg7, s32 arg8, u8 mask) __asm__("func_800830DC");

void place_group_corner_shapes(PlacementSession *session, s32 group, f32 *position, f32 scale, f32 arg4, u16 arg5, s32 arg6,
       s32 arg7, s32 arg8, u8 mask) {
    PlacementSet *set;
    PlacementGroup *pg;
    PlacementPoint *point;
    void *record;
    f32 xz[2];
    s32 i;
    s32 corner;

    if (group == -1) {
        return;
    }
    pg = &session->groups[group];
    xz[1] = position[0];
    xz[0] = position[2];
    set = &session->sets[pg->set];
    if (arg7 > 0) {
        for (i = 0; i < set->count; i++) {
            point = &session->points[set->first + i];
            record = func_8008067C(arg6, arg7, &session->records[point->record]);
            for (corner = 0; corner < 4; corner++) {
                if ((mask >> corner) & 1) {
                    point = &session->points[set->first + i];
                    func_80080910(&session->shapes[point->shape], record, position, scale, arg4, arg5, corner,
                                  arg8);
                }
            }
        }
    } else {
        for (corner = 0; corner < 4; corner++) {
            if ((mask >> corner) & 1) {
                for (i = 0; i < set->count; i++) {
                    point = &session->points[set->first + i];
                    func_80080910(&session->shapes[point->shape], &session->records[point->record], position,
                                  scale, arg4, arg5, corner, arg8);
                }
            }
        }
    }
}
