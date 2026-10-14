#include "types.h"

typedef struct YawTransform44 {
    f32 m[12];
    s32 value30;
    s32 value34;
    s32 value38;
    s32 value3C;
    s32 value40;
} YawTransform44;

typedef struct MatrixBuffer {
    u8 bytes[0x40];
} MatrixBuffer;

typedef struct QueryPos {
    f32 value00;
    f32 value04;
} QueryPos;

typedef struct RotatingRecord {
    u8 pad00[0xC];
    f32 value0C;
    f32 value10;
    f32 value14;
    u8 pad18[0x4];
    u16 angle1C;
    u16 angle1E;
    u8 pad20[0x4];
    u8 value24;
    u8 pad25[0x1F];
    s16 value44;
    u8 value46;
} RotatingRecord;

extern YawTransform44 D_80071B10;
extern f32 D_80071B68;
extern s16 D_802D5AB2;
extern s32 gGameTicks __asm__("D_801B4AA8");

extern void load_render_translation(void *target, void *vector) __asm__("func_800A76A0");
extern void build_render_rotation(void *target, MatrixBuffer *matrix, u16 angle) __asm__("func_800A82B8");
extern void apply_render_matrix(MatrixBuffer *matrix, void *target, u16 angle) __asm__("func_800A841C");
extern void scale_matrix_axes(void *target, f32 x, f32 y, f32 z) __asm__("func_800A823C");
extern s32 get_spawn_session(void) __asm__("func_800821C0");
extern void visit_level_points_in_radius(s32 level, s32 arg1, YawTransform44 *xf, s32 arg3, s32 arg4, QueryPos *pos) __asm__("func_80084A74");

void visit_level_points_near_rotating_record(void *arg) __asm__("func_8008DDCC");

void visit_level_points_near_rotating_record(void *arg)
{
    RotatingRecord *rec;
    QueryPos pos;
    YawTransform44 xf;
    MatrixBuffer matrix;
    s32 session;

    xf = D_80071B10;
    rec = arg;
    if (rec->value24 != 0) {
        load_render_translation(&xf, &rec->value0C);
        build_render_rotation(&xf, &matrix, ~(rec->angle1E * 6) & 0xFFFF);
        apply_render_matrix(&matrix, &xf, rec->angle1C);
        if (rec->value46 != 0 && rec->value44 >= 0) {
            scale_matrix_axes(&xf, D_80071B68, D_80071B68, D_80071B68);
        }
        session = get_spawn_session();
        pos.value04 = rec->value0C;
        pos.value00 = rec->value14;
        visit_level_points_in_radius(session, D_802D5AB2, &xf, 3, (gGameTicks / 8) % 2, &pos);
    }
}
