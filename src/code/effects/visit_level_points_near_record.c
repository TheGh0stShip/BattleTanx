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

typedef struct EffectRecord {
    u8 pad00[0xC];
    s32 value0C;
    s32 value10;
    s32 value14;
    u8 pad18[0x10];
    u16 value28;
    u8 pad2A[4];
    s16 value2E;
} EffectRecord;

typedef struct EffectRecordF {
    u8 pad00[0xC];
    f32 value0C;
    s32 value10;
    f32 value14;
} EffectRecordF;

extern YawTransform44 D_80071B10;
extern s16 D_802D5A78;
extern void set_yaw_transform(YawTransform44 *xf, s32 x, s32 y, s32 z, u16 angle) __asm__("func_800A7744");
extern s32 get_spawn_session(void) __asm__("func_800821C0");
extern void visit_level_points_in_radius(s32 level, s32 arg1, YawTransform44 *xf, s32 arg3, s32 arg4, QueryPos *pos) __asm__("func_80084A74");

void visit_level_points_near_record(EffectRecord *rec) __asm__("func_8008D588");

void visit_level_points_near_record(EffectRecord *rec)
{
    QueryPos pos;
    s32 session;
    YawTransform44 xf;

    xf = D_80071B10;
    if (rec->value2E == 1) {
        set_yaw_transform(&xf, rec->value0C, rec->value10, rec->value14, rec->value28);
        session = get_spawn_session();
        pos.value04 = ((EffectRecordF *)rec)->value0C;
        pos.value00 = ((EffectRecordF *)rec)->value14;
        visit_level_points_in_radius(session, D_802D5A78, &xf, 3, 0, &pos);
    }
}
