#include "types.h"

typedef struct Vec3f {
    f32 x;
    f32 y;
    f32 z;
} Vec3f;

typedef struct CameraAnchor {
    u8 pad00[8];
    s32 handlerIndex;
} CameraAnchor;

typedef struct AttachedCamera {
    u8 pad00[8];
    s32 kind;
    Vec3f *eyeOffset;
    Vec3f *eyeOffsetCopy;
    u8 value14;
    u8 pad15[3];
    CameraAnchor *anchor;
    s32 anchorArg;
    f32 value20;
    Vec3f at;
    Vec3f eye;
    Vec3f up;
    f32 view[4][4];
    u8 pad88[4];
    s16 value8C;
    u8 pad8E[2];
    s32 value90;
} AttachedCamera;

typedef struct AnchorQuery {
    s32 arg;
    s32 value04;
} AnchorQuery;

typedef struct CameraHandlerEntry {
    void (*handle)(CameraAnchor *anchor, AttachedCamera *camera, s32 message, AnchorQuery *query, f32 (*matrix)[4]);
    u8 pad04[8];
} CameraHandlerEntry;

extern f32 D_80071070;
extern CameraHandlerEntry D_802C3804[];
extern void set_matrix_identity(f32 matrix[4][4]) __asm__("func_800A7650");
extern void transform_point_3x4(f32 matrix[4][4], Vec3f *input, Vec3f *output) __asm__("func_800A7D10");
extern void look_at_matrix(f32 mf[4][4], f32 eyeX, f32 eyeY, f32 eyeZ, f32 atX, f32 atY, f32 atZ,
                           f32 upX, f32 upY, f32 upZ) __asm__("func_80113460");

void init_attached_camera(AttachedCamera *camera, Vec3f *offsets, CameraAnchor *anchor, s32 anchorArg) __asm__("func_80077B10");

void init_attached_camera(AttachedCamera *camera, Vec3f *offsets, CameraAnchor *anchor, s32 anchorArg)
{
    AnchorQuery query;
    f32 matrix[4][4];
    f32 one;
    Vec3f *eye;
    Vec3f *at;

    one = D_80071070;
    camera->kind = 0x25;
    camera->value14 = 0x40;
    camera->eyeOffset = offsets;
    camera->eyeOffsetCopy = offsets;
    camera->anchor = anchor;
    camera->anchorArg = anchorArg;
    camera->value90 = -1;
    camera->value20 = one;
    set_matrix_identity(matrix);
    query.arg = anchorArg;
    query.value04 = 0;
    eye = &camera->eye;
    at = &camera->at;
    if (D_802C3804[anchor->handlerIndex].handle != 0) {
        D_802C3804[anchor->handlerIndex].handle(anchor, camera, 1, &query, matrix);
    }
    transform_point_3x4(matrix, &offsets[0], eye);
    transform_point_3x4(matrix, &offsets[1], at);
    camera->up.x = 0.0f;
    camera->up.y = one;
    camera->up.z = 0.0f;
    camera->value8C = 0;
    look_at_matrix(camera->view, camera->eye.x, camera->eye.y, camera->eye.z, camera->at.x, camera->at.y,
                   camera->at.z, camera->up.x, camera->up.y, camera->up.z);
}
