#include "types.h"

typedef struct TransformRecord {
    u8 pad00[0xC];
    u8 vector0C[0x10];
    u16 angle1C;
    u16 angle1E;
} TransformRecord;

typedef struct MatrixBuffer {
    u8 bytes[0x40];
} MatrixBuffer;

extern void load_render_translation(void *target, void *vector) __asm__("func_800A76A0");
extern void build_render_rotation(void *target, MatrixBuffer *matrix, u16 angle) __asm__("func_800A82B8");
extern void apply_render_matrix(MatrixBuffer *matrix, void *target, u16 angle) __asm__("func_800A841C");

void apply_record_transform(TransformRecord *record, s32 unused1, s32 unused2, void *target)
    __asm__("func_8008E1BC");

void apply_record_transform(TransformRecord *record, s32 unused1, s32 unused2, void *target)
{
    MatrixBuffer matrix;

    load_render_translation(target, record->vector0C);
    build_render_rotation(target, &matrix, ~(record->angle1E * 3) & 0xFFFF);
    apply_render_matrix(&matrix, target, record->angle1C);
}
