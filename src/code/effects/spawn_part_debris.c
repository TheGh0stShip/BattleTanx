#include "types.h"

typedef struct Vec3f { f32 x, y, z; } Vec3f;
typedef struct DebrisMatrix { f32 m[4][4]; } DebrisMatrix;
typedef union DisplayCommand {
    struct { u8 opcode; u8 pad01; u16 value02; void *value04; } vtx;
    struct { u32 w0; u32 w1; } words;
} DisplayCommand;
typedef struct ModelSet { u8 pad000[0x580]; DisplayCommand *commands; } ModelSet;
typedef struct PartRecord { u8 pad00[0x4]; s32 index; } PartRecord;
typedef struct PartDebris {
    u8 pad00[0xC];
    Vec3f position;
    Vec3f center;
    Vec3f velocity;
    u16 angleX, angleY, angleZ;
    u16 spinX, spinY, spinZ;
    s32 value3C;
    u8 flags;
    u8 pad41[3];
    PartRecord *part;
} PartDebris;

extern PartDebris *allocate_effect(s32 group, s32 kind, s32 size) __asm__("func_8008AD10");
extern ModelSet *get_spawn_session(void) __asm__("func_800821C0");
extern void expand_vertex_bounds(f32 *max, f32 *min, void *vertices, s32 count) __asm__("func_8008F4EC");
extern u32 random_u32(void) __asm__("func_800F38F4");
extern f32 random_float_range(f32 range) __asm__("func_800F3880");
extern f32 sinf_u16(u16 angle) __asm__("func_800F3AE0");
extern f32 cosf_u16(u16 angle) __asm__("func_800F3B40");
extern void set_euler_rotation(DebrisMatrix *m, u16 yaw, u16 pitch, u16 roll) __asm__("func_800A7800");
extern void transform_point_3x4(DebrisMatrix *matrix, Vec3f *input, Vec3f *output) __asm__("func_800A7D10");
extern Vec3f D_80071C64;
extern Vec3f D_80071C70;

s32 spawn_part_debris(Vec3f *position, u16 angleX, u16 angleY, u16 angleZ, u16 spinX, u16 spinY,
                      u16 spinZ, u16 heading, u16 pitchMax, u16 pitchMin, f32 speedScale,
                      PartRecord *part, s32 value3C, u8 flags) __asm__("func_8008F6F4");

s32 spawn_part_debris(Vec3f *position, u16 angleX, u16 angleY, u16 angleZ, u16 spinX, u16 spinY,
                      u16 spinZ, u16 heading, u16 pitchMax, u16 pitchMin, f32 speedScale,
                      PartRecord *part, s32 value3C, u8 flags)
{
    Vec3f offset;
    DebrisMatrix matrix = {{{1.0f, 0.0f, 0.0f, 0.0f},
                            {0.0f, 1.0f, 0.0f, 0.0f},
                            {0.0f, 0.0f, 1.0f, 0.0f},
                            {0.0f, 0.0f, 0.0f, 1.0f}}};
    PartDebris *debris;
    u16 yaw;
    u16 pitch;

    debris = allocate_effect(1, 0x11, sizeof(PartDebris));
    if (debris == 0) {
        return -1;
    }
    debris->position = *position;
    debris->flags = flags;
    debris->spinX = spinX;
    debris->spinY = spinY;
    debris->spinZ = spinZ;
    debris->part = part;
    debris->value3C = value3C;
    if (part != 0) {
        Vec3f *center = &debris->center;
        ModelSet *set = get_spawn_session();
        Vec3f min = D_80071C64;
        Vec3f max = D_80071C70;
        DisplayCommand *cmd;
        s32 i;

        cmd = &set->commands[part->index];
        for (i = 0; cmd[i].words.w0 != 0xB8000000; i++) {
            if (cmd[i].vtx.opcode == 4) {
                expand_vertex_bounds(&max.x, &min.x, cmd[i].vtx.value04, cmd[i].vtx.value02 >> 10);
            }
        }
        center->x = (min.x + max.x) / 2.0f;
        center->y = (min.y + max.y) / 2.0f;
        center->z = (min.z + max.z) / 2.0f;
    } else {
        debris->center.x = 0.0f;
        debris->center.y = 0.0f;
        debris->center.z = 0.0f;
    }
    yaw = heading + (random_u32() & 0x1FFF) - 0x1000;
    pitch = pitchMin + random_u32() % (pitchMax - pitchMin);
    {
        register f32 lift __asm__("$f20") = sinf_u16(pitch);

        if (flags & 8) {
            debris->velocity.y = (random_float_range(0.2f) + 0.9f) * -2.0f;
            debris->velocity.x = sinf_u16(yaw) * 2.5f * (random_float_range(0.2f) + 0.9f);
            lift = cosf_u16(yaw) * 2.5f * (random_float_range(0.2f) + 0.9f);
            debris->velocity.z = lift;
        } else {
            f32 velocityScale = 8.0f;

            lift *= velocityScale;
            debris->velocity.x = lift * sinf_u16(yaw) * speedScale;
            debris->velocity.y = cosf_u16(pitch) * velocityScale;
            lift *= cosf_u16(yaw);
            lift *= speedScale;
            debris->velocity.z = lift;
        }
    }
    set_euler_rotation(&matrix, angleZ, angleY, angleX);
    transform_point_3x4(&matrix, &debris->center, &offset);
    debris->position.x += offset.x;
    debris->position.y += offset.y;
    debris->position.z += offset.z;
    debris->center.x = -debris->center.x;
    debris->center.y = -debris->center.y;
    debris->center.z = -debris->center.z;
    debris->angleX = angleX;
    debris->angleY = angleY;
    debris->angleZ = angleZ;
    if (flags & 8) {
        debris->position.y -= random_float_range(30.0f);
    }
    return 0;
}
