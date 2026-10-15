#include "types.h"

typedef struct ObjectSegmentDraw {
    u8 pad00[0xC];
    s32 value0C;
    s32 value10;
    u16 startAngle;
    u16 endAngle;
    u16 segmentCount;
    u8 pad1A[0xA];
    s16 modelIndex;
} ObjectSegmentDraw;

extern void matrix_identity(f32 *matrix) __asm__("func_800A7650");
extern void matrix_build_segment(f32 *matrix, s32 value10, s32 zero, s32 value0C,
                                 u16 angle) __asm__("func_800A7744");
extern void matrix_apply_segment_count(f32 *input, f32 *output, u16 count)
    __asm__("func_800A8580");
extern void matrix_apply_angle(f32 *input, f32 *output, u16 angle) __asm__("func_800A841C");
extern s32 get_render_context(void) __asm__("func_800821C0");
extern void draw_object_segment(s32 context, s16 modelIndex, f32 *matrix, s32 mode,
                                s32 zero, void *position) __asm__("func_80084A74");

void draw_transformed_object_segment(ObjectSegmentDraw *object) __asm__("func_800EF380");

void draw_transformed_object_segment(ObjectSegmentDraw *object)
{
    f32 matrix0[16];
    f32 matrix1[16];
    f32 matrix2[16];
    volatile s32 unused;
    s32 angle;

    if (object->segmentCount != 0) {
        unused = 0;
        matrix_identity(matrix0);
        angle = object->startAngle - object->endAngle;
        if (angle < 0) {
            angle = object->endAngle - object->startAngle;
        }
        matrix_build_segment(matrix0, object->value10, 0, object->value0C, angle & 0xFFFF);
        matrix_apply_segment_count(matrix0, matrix1, object->segmentCount);
        matrix_apply_angle(matrix1, matrix2, object->endAngle);
        draw_object_segment(get_render_context(), object->modelIndex, matrix2, 3, 0,
                            &object->value0C);
    }
}
