#include "types.h"

typedef struct Matrix4f {
    f32 m[4][4];
} Matrix4f;

typedef struct Vec3f {
    f32 x;
    f32 y;
    f32 z;
} Vec3f;

typedef struct MatrixSlot {
    u32 address;
    u32 pad04;
    Matrix4f matrix;
} MatrixSlot;

typedef struct DrawItem {
    void *displayList;
    Vec3f position;
    f32 scaleX;
    f32 scaleY;
    u16 angle;
    u8 pad1A[2];
    struct DrawItem *next;
} DrawItem;

typedef struct DrawBucket {
    void *displayList;
    DrawItem *items[4];
    struct DrawBucket *next;
} DrawBucket;

typedef struct RenderRecord {
    u8 pad00[0x14];
    u32 matrixBase;
} RenderRecord;

typedef struct RenderFrameRecord {
    u8 pad00[0x10];
    u32 matrixCursor;
} RenderFrameRecord;

extern DrawBucket *D_801C2EC0[][32];

extern RenderRecord *get_current_render_record(void) __asm__("func_8007F00C");
extern RenderFrameRecord *get_render_frame_record(void) __asm__("func_8007F030");
extern s32 get_difficulty_level(void) __asm__("func_8007AAA0");
extern void append_display_list_call_0(void *list) __asm__("func_8007EEF8");
extern void *get_entity_record(u16 index) __asm__("func_800A6688");
extern u8 *func_800A424C(void *record);
extern void *func_800A42A4(void *record);
extern void func_8007E8EC(u8 *arg0, u16 arg1);
extern void set_matrix_identity(Matrix4f *matrix) __asm__("func_800A7650");
extern void build_render_rotation(Matrix4f *src, Matrix4f *dst, u16 angle) __asm__("func_800A82B8");
extern void transform_point_3x4(void *matrix, Vec3f *input, Vec3f *output) __asm__("func_800A7D10");
extern void load_render_translation(Matrix4f *target, Vec3f *vector) __asm__("func_800A76A0");
extern void guMtxF2L(Matrix4f *src, u32 dst) __asm__("func_801146A0");
extern void load_matrix_list_a(u32 address, s32 params) __asm__("func_8007EB64");

void draw_bucket_items(s32 bucket, u8 *arg1, u16 *arg2) __asm__("func_80080C60");

void draw_bucket_items(s32 bucket, u8 *arg1, u16 *arg2) {
    Matrix4f matrix;
    MatrixSlot local;
    Vec3f position;
    s32 lastOwner;
    s32 ownerCount;
    s32 index;
    RenderRecord *record;
    u8 *entity;
    RenderFrameRecord *frame;
    DrawBucket *node;
    DrawItem *item;
    s32 owner;
    void *stats;

    lastOwner = -1;
    record = get_current_render_record();
    frame = get_render_frame_record();
    entity = 0;
    ownerCount = get_difficulty_level();
    for (index = 0; index < 32; index++) {
        for (node = D_801C2EC0[bucket][index]; node != 0; node = node->next) {
            append_display_list_call_0(node->displayList);
            for (owner = 0; owner < ownerCount; owner++) {
                for (item = node->items[owner]; item != 0; item = item->next) {
                    if (owner != lastOwner) {
                        stats = get_entity_record(owner);
                        entity = func_800A424C(stats);
                        append_display_list_call_0(func_800A42A4(stats));
                        lastOwner = owner;
                        func_8007E8EC(arg1 + owner * 0x44, arg2[owner]);
                    }
                    set_matrix_identity(&local.matrix);
                    local.address = 0;
                    local.matrix.m[0][0] = item->scaleX;
                    local.matrix.m[1][1] = item->scaleY;
                    if (item->angle != 0) {
                        build_render_rotation(&local.matrix, &matrix, item->angle);
                    } else {
                        matrix = local.matrix;
                    }
                    transform_point_3x4(entity + 0x48, &item->position, &position);
                    load_render_translation(&matrix, &position);
                    if (frame->matrixCursor >= record->matrixBase + 0xC000) {
                        return;
                    }
                    guMtxF2L(&matrix, frame->matrixCursor);
                    local.address = frame->matrixCursor;
                    frame->matrixCursor += 0x40;
                    load_matrix_list_a(local.address, 2);
                    append_display_list_call_0(item->displayList);
                }
            }
        }
    }
}
