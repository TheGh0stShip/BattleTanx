#include "types.h"

typedef struct YawTransform44 {
    f32 m[12];
    s32 value30;
    s32 value34;
    s32 value38;
    s32 value3C;
    s32 value40;
} YawTransform44;

typedef struct QueryPos {
    f32 value00;
    f32 value04;
} QueryPos;

typedef struct HeadingRecord {
    u8 pad00[0xC];
    f32 x;
    f32 y;
    f32 z;
    u8 pad18[0x26 - 0x18];
    u16 heading;
} HeadingRecord;

extern YawTransform44 D_80074E90;
extern s16 D_802D5A7A;
extern f32 angle_sin(u16 angle) __asm__("func_800F3AE0");
extern f32 angle_cos(u16 angle) __asm__("func_800F3B40");
extern void load_render_translation(void *target, void *vector) __asm__("func_800A76A0");
extern s32 get_spawn_session(void) __asm__("func_800821C0");
extern void visit_level_points_in_radius(s32 level, s32 arg1, YawTransform44 *xf, s32 arg3, s32 arg4, QueryPos *pos) __asm__("func_80084A74");

void visit_level_points_near_heading_record(HeadingRecord *rec) __asm__("func_800F2D58");
void visit_level_points_near_heading_record(HeadingRecord *rec) {
    QueryPos pos;
    YawTransform44 xf;
    f32 sinValue;
    f32 cosValue;
    s32 session;

    xf = D_80074E90;
    sinValue = angle_sin(rec->heading);
    cosValue = angle_cos(rec->heading);
    load_render_translation(&xf, &rec->x);
    xf.m[0] = cosValue;
    xf.m[10] = cosValue;
    xf.m[8] = sinValue;
    xf.m[2] = -sinValue;
    session = get_spawn_session();
    pos.value04 = rec->x;
    pos.value00 = rec->z;
    visit_level_points_in_radius(session, D_802D5A7A, &xf, 3, 0, &pos);
}
