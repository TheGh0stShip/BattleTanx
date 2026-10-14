#include "types.h"

typedef struct LookAtCamera {
    u8 pad00[0x24];
    f32 atX;
    f32 atY;
    f32 atZ;
    f32 eyeX;
    f32 eyeY;
    f32 eyeZ;
    u8 pad3C[0xC];
    f32 viewMatrix[4][4];
    s32 value88;
} LookAtCamera;

extern void look_at_matrix(f32 mf[4][4], f32 eyeX, f32 eyeY, f32 eyeZ, f32 atX, f32 atY, f32 atZ,
                           f32 upX, f32 upY, f32 upZ) __asm__("func_80113460");
extern f32 D_800710B4; /* 1.0f */

void set_camera_look_at(LookAtCamera *camera, f32 eyeX, f32 eyeY, f32 eyeZ, f32 atX, f32 atY, f32 atZ) __asm__("func_80078764");

void set_camera_look_at(LookAtCamera *camera, f32 eyeX, f32 eyeY, f32 eyeZ, f32 atX, f32 atY, f32 atZ) {
    look_at_matrix(camera->viewMatrix, eyeX, eyeY, eyeZ, atX, atY, atZ, 0.0f, D_800710B4, 0.0f);
    camera->value88 = 0;
    camera->eyeX = eyeX;
    camera->eyeY = eyeY;
    camera->eyeZ = eyeZ;
    camera->atX = atX;
    camera->atY = atY;
    camera->atZ = atZ;
}
