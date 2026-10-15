#include "types.h"

typedef struct YawTransform44 {
    f32 m[12];
    s32 value30;
    s32 value34;
    s32 value38;
    s32 value3C;
    s32 value40;
} YawTransform44;

typedef struct ScaleMatrix {
    f32 m[16];
} ScaleMatrix;

typedef struct PointXZ {
    f32 x;
    f32 z;
} PointXZ;

typedef struct SweepRecord {
    u8 pad00[0xC];
    f32 value0C;
    f32 value10;
    f32 value14;
    u16 angle18;
    u8 pad1A[0x2];
    f32 length1C;
} SweepRecord;

extern ScaleMatrix D_80074D28;
extern YawTransform44 D_80074D68;
extern s16 D_802D5A44;

extern void load_render_translation(void *target, void *vector) __asm__("func_800A76A0");
extern void apply_render_matrix(ScaleMatrix *matrix, void *target, u16 angle) __asm__("func_800A841C");
extern s32 get_spawn_session(void) __asm__("func_800821C0");
extern f32 angle_sin(u16 angle) __asm__("func_800F3AE0");
extern f32 angle_cos(u16 angle) __asm__("func_800F3B40");
extern void notify_listeners_near_points(s32 session, s32 arg1, YawTransform44 *xf, s32 arg3, s32 arg4,
                                         PointXZ *points, s32 count) __asm__("func_8008463C");

void notify_listeners_along_sweep(SweepRecord *rec) __asm__("func_800F0E4C");

void notify_listeners_along_sweep(SweepRecord *rec) {
    PointXZ origin;
    ScaleMatrix matrix;
    YawTransform44 xf;
    PointXZ points[4];
    s32 session;

    matrix = D_80074D28;
    xf = D_80074D68;
    matrix.m[10] = rec->length1C;
    apply_render_matrix(&matrix, &xf, rec->angle18);
    load_render_translation(&xf, &rec->value0C);
    session = get_spawn_session();
    origin.z = rec->value0C;
    origin.x = rec->value14;
    points[0].z = rec->value0C;
    points[0].x = rec->value14;
    points[2].z = rec->value0C + angle_sin(rec->angle18) * rec->length1C;
    points[2].x = rec->value14 + angle_cos(rec->angle18) * rec->length1C;
    points[1].z = points[0].z;
    points[3].z = points[2].z;
    points[3].x = points[0].x;
    points[1].x = points[2].x;
    notify_listeners_near_points(session, D_802D5A44, &xf, 3, 0, points, 4);
}
