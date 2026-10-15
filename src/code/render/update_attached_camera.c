#include "types.h"

typedef struct Vec3f {
    f32 x;
    f32 y;
    f32 z;
} Vec3f;

typedef struct AnchorUnit {
    u8 pad00[0x4F4];
    s32 spinStart;
} AnchorUnit;

typedef struct CameraAnchor {
    u8 pad00[8];
    s32 handlerIndex;
    AnchorUnit *unit;
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
    u16 value8C;
    u8 pad8E[2];
    s32 value90;
    s32 value94;
    Vec3f value98;
} AttachedCamera;

typedef struct AnchorQuery {
    s32 arg;
    s32 value04;
} AnchorQuery;

typedef struct CameraHandlerEntry {
    void (*handle)(CameraAnchor *anchor, AttachedCamera *camera, s32 message, AnchorQuery *query, f32 (*matrix)[4]);
    u8 pad04[8];
} CameraHandlerEntry;

extern CameraHandlerEntry D_802C3804[];
extern u8 D_8013576B;
extern u32 gAnimationTime __asm__("D_801B4AA0");
extern void set_matrix_identity(f32 matrix[4][4]) __asm__("func_800A7650");
extern void transform_point_3x4(f32 matrix[4][4], Vec3f *input, Vec3f *output) __asm__("func_800A7D10");
extern void rotate_vector_3x3(f32 matrix[4][4], Vec3f *input, Vec3f *output) __asm__("func_800A7C7C");
extern void get_matrix_segment(f32 matrix[4][4], f32 out[4][4], Vec3f *start, Vec3f *end) __asm__("func_800A8034");
extern void look_at_matrix(f32 mf[4][4], f32 eyeX, f32 eyeY, f32 eyeZ, f32 atX, f32 atY, f32 atZ,
                           f32 upX, f32 upY, f32 upZ) __asm__("func_80113460");
extern void clamp_target_to_segment_hit(void *source, f32 *target, f32 *out, f32 *origin, f32 *fraction)
    __asm__("func_80077C78");
extern f32 angle_sin(u16 angle) __asm__("func_800F3AE0");
extern f32 angle_cos(u16 angle) __asm__("func_800F3B40");
extern s32 radians_to_angle(f32 radians) __asm__("func_800F3BE4");
extern s32 get_trail_effect_kind(void) __asm__("func_800ECB98");
extern void spawn_effect_kind_26(Vec3f *position, s32 variant) __asm__("func_800ED8C0");
extern float sqrtf(float);

void update_attached_camera(AttachedCamera *c) __asm__("func_80077E94");

void update_attached_camera(AttachedCamera *c)
{
    AnchorQuery q;
    f32 m[4][4];
    Vec3f ofs;
    Vec3f tgt;
    Vec3f a;
    Vec3f pa;
    Vec3f b;
    Vec3f pb;
    Vec3f eye;
    f32 origin[2];
    Vec3f up = { 0.0f, 1.0f, 0.0f };
    Vec3f pofs;
    Vec3f ptgt;
    f32 t;
    Vec3f *peye = &c->eye;
    Vec3f *pat = &c->at;
    Vec3f *pup = &c->up;
    f32 k;
    f32 dx;
    f32 dz;
    f32 dy;
    f32 len;
    s32 angle;
    s32 start;

    c->value20 += 0.05f;
    if (1.0f < c->value20) {
        c->value20 = 1.0f;
    }
    ofs.x = c->eyeOffset[0].x * c->value20;
    k = 50.0f;
    ofs.y = (c->eyeOffset[0].y - k) * c->value20 + k;
    ofs.z = c->eyeOffset[0].z * c->value20;
    tgt = c->eyeOffset[1];
    set_matrix_identity(m);
    q.arg = c->anchorArg;
    q.value04 = 0;
    if (D_802C3804[c->anchor->handlerIndex].handle != 0) {
        D_802C3804[c->anchor->handlerIndex].handle(c->anchor, c, 1, &q, m);
    }
    if (c->anchorArg == 3) {
        get_matrix_segment(m, c->view, peye, pat);
    } else {
        if (c->value14 == 64) {
            transform_point_3x4(m, &ofs, &eye);
            transform_point_3x4(m, &tgt, pat);
        } else {
            pofs.x = c->eyeOffsetCopy[0].x * c->value20;
            pofs.y = (c->eyeOffsetCopy[0].y - k) * c->value20 + k;
            pofs.z = c->eyeOffsetCopy[0].z * c->value20;
            ptgt = c->eyeOffsetCopy[1];
            transform_point_3x4(m, &ofs, &a);
            transform_point_3x4(m, &tgt, &b);
            transform_point_3x4(m, &pofs, &pa);
            transform_point_3x4(m, &ptgt, &pb);
            eye.x = pa.x + (a.x - pa.x) * c->value14 / 64.0f;
            eye.y = pa.y + (a.y - pa.y) * c->value14 / 64.0f;
            eye.z = pa.z + (a.z - pa.z) * c->value14 / 64.0f;
            c->at.x = pb.x + (b.x - pb.x) * c->value14 / 64.0f;
            c->at.y = pb.y + (b.y - pb.y) * c->value14 / 64.0f;
            c->at.z = pb.z + (b.z - pb.z) * c->value14 / 64.0f;
            c->value14 += 4;
            if (c->value14 > 64) {
                c->value14 = 64;
            }
        }
        origin[1] = m[3][0];
        origin[0] = m[3][2];
        clamp_target_to_segment_hit(c, &eye.x, &peye->x, origin, &t);
        c->value20 *= t;
        peye->x = origin[1] + (peye->x - origin[1]) * 0.8f;
        peye->z = origin[0] + (peye->z - origin[0]) * 0.8f;
        if (D_8013576B != 0) {
            f32 ax = pat->x - peye->x;
            f32 az = pat->z - peye->z;
            f32 d = sqrtf(ax * ax + az * az);
            f32 nx = ax / d;
            f32 nz = az / d;

            if (nx < 0.0f) {
                angle = -radians_to_angle(nz);
            } else {
                angle = radians_to_angle(nz);
            }
            pup->x = -nz * angle_sin(c->value8C + angle);
            pup->z = nx * angle_sin(c->value8C + angle);
            pup->y = angle_cos(c->value8C + angle);
            c->value8C += 0x400;
        } else if (c->anchor->handlerIndex == 0 && (start = c->anchor->unit->spinStart) != 0) {
            f32 ax = pat->x - peye->x;
            f32 az = pat->z - peye->z;
            f32 d;
            f32 nx;
            f32 nz;

            angle = ((gAnimationTime - start) * 0xFFFF) / 30;
            d = sqrtf(ax * ax + az * az);
            nx = ax / d;
            nz = az / d;
            pup->x = -nz * angle_sin(angle);
            pup->z = angle_sin(angle) * nx;
            pup->y = angle_cos(angle);
        } else {
            rotate_vector_3x3(m, &up, pup);
        }
        look_at_matrix(c->view, peye->x, peye->y, peye->z, pat->x, pat->y, pat->z, pup->x, pup->y, pup->z);
    }
    if (c->value90 != -1) {
        f32 seg[4][4];
        Vec3f p0;
        Vec3f p1;

        q.arg = c->anchorArg;
        q.value04 = 15;
        if (D_802C3804[c->anchor->handlerIndex].handle != 0) {
            D_802C3804[c->anchor->handlerIndex].handle(c->anchor, c, 1, &q, m);
        }
        get_matrix_segment(m, seg, &p0, &p1);
        dx = p1.x - p0.x;
        dy = p1.y - p0.y;
        dz = p1.z - p0.z;
        len = sqrtf(dx * dx + dy * dy + dz * dz);
        pofs.x = p0.x + dx / len * 40.0f;
        pofs.y = p0.y + dy / len * 40.0f;
        pofs.z = p0.z + dz / len * 40.0f;
        dx = pofs.x - c->value98.x;
        dy = pofs.y - c->value98.y;
        dz = pofs.z - c->value98.z;
        if (900.0f < dx * dx + dy * dy + dz * dz || c->value94 - c->value90 >= 30) {
            spawn_effect_kind_26(&pofs, get_trail_effect_kind());
            c->value90 = c->value94;
            c->value98.x = pofs.x;
            c->value98.y = pofs.y;
            c->value98.z = pofs.z;
        }
        c->value94++;
    }
}
