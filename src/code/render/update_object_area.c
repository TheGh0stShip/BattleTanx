#include "types.h"

typedef struct Vec3f {
    f32 x;
    f32 y;
    f32 z;
} Vec3f;

typedef struct ModelGroupEntry {
    u8 pad00[4];
    s16 minX;
    s16 minZ;
    s16 maxX;
    s16 maxZ;
} ModelGroupEntry;

typedef struct ModelSession {
    u8 pad000[0x570];
    ModelGroupEntry *groups;
} ModelSession;

typedef struct PlacedObject {
    u8 pad00[8];
    u8 transform[0x4C];
    u16 model;
} PlacedObject;

extern f32 sqrtf(f32);
extern void func_80114858(f32 matrix[4][4], void *transform);
extern void transform_point_3x4(f32 matrix[4][4], Vec3f *input, Vec3f *output) __asm__("func_800A7D10");
extern s32 cosine_to_angle(f32 cosine) __asm__("func_800F3BE4");
extern void move_effect_area(s32 handle, s32 x, s32 z, s32 radius, s32 angle, f32 *corners) __asm__("func_80106D08");

#define CORNER_LENGTH(c) sqrtf((c).x * (c).x + (c).z * (c).z)
#define MAX(a, b) ((a) > (b) ? (a) : (b))

void update_object_area(ModelSession *session, PlacedObject *object, s32 handle) __asm__("func_80085470");

void update_object_area(ModelSession *session, PlacedObject *object, s32 handle)
{
    Vec3f corners[4] = { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } };
    Vec3f world[4];
    f32 points[4][2];
    f32 matrix[4][4];
    ModelGroupEntry *group;
    f32 radius;
    s32 angle;
    s32 x;
    s32 z;
    s32 i;

    group = &session->groups[object->model];
    corners[0].x = group->minX;
    corners[0].z = group->minZ;
    corners[1].x = group->maxX;
    corners[1].z = group->minZ;
    corners[2].x = group->maxX;
    corners[2].z = group->maxZ;
    corners[3].x = group->minX;
    corners[3].z = group->maxZ;
    func_80114858(matrix, object->transform);
    for (i = 0; i < 4; i++) {
        transform_point_3x4(matrix, &corners[i], &world[i]);
        points[i][1] = world[i].x;
        points[i][0] = world[i].z;
    }
    radius = MAX(MAX(CORNER_LENGTH(corners[0]), CORNER_LENGTH(corners[1])),
                 MAX(CORNER_LENGTH(corners[2]), CORNER_LENGTH(corners[3])));
    x = matrix[3][0];
    z = matrix[3][2];
    if (matrix[2][0] < 0.0f) {
        angle = -cosine_to_angle(matrix[2][2]);
    } else {
        angle = cosine_to_angle(matrix[2][2]);
    }
    angle &= 0xFFFF;
    move_effect_area(handle, x, z, radius, angle, points[0]);
}

/* LDSYM func_800A7D10=0x800A7D10 */
/* LDSYM func_800F3BE4=0x800F3BE4 */
/* LDSYM func_80106D08=0x80106D08 */
/* LDSYM func_80114858=0x80114858 */
/* RODATA_VRAM 0x800714E8 */
/* LDSYM sqrtf=0x8011D190 */
