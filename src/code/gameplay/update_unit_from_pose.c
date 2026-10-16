#include "types.h"

/* RODATA_VRAM 0x8007273C */

typedef struct HitObject {
    u8 pad00[0x8];
    s32 kind;
} HitObject;

typedef struct SegmentHit {
    HitObject *object;
    f32 x;
    f32 y;
    f32 z;
    u8 pad10[0x8];
} SegmentHit;

typedef struct HitQuery {
    f32 x;
    f32 y;
    f32 z;
    s16 angle;
} HitQuery;

typedef struct HitReply {
    u32 status;
    s32 value04;
    s32 value08;
    s32 value0C;
} HitReply;

typedef struct UnitOwner {
    u8 pad00[0x12];
    u16 controller;
} UnitOwner;

typedef void (*HitHandler)(HitObject *object, UnitOwner *owner, s32 kind, HitQuery *query, HitReply *reply);

typedef struct HitHandlerEntry {
    HitHandler handle;
    u8 pad04[0x8];
} HitHandlerEntry;

typedef struct UnitPose {
    f32 x;
    f32 z;
    u16 angle;
    u16 turret;
} UnitPose;

typedef struct Unit {
    u8 pad00;
    u8 alive;
    u8 pad02[0x12];
    u16 flags;
    u8 pad16[2];
    s32 value18;
    u8 pad1C[8];
    f32 x;
    f32 y;
    f32 z;
    u8 pad30[4];
    f32 heading;
    u8 pad38[0x1C];
    f32 bodyMatrix[4][4];
    u8 pad94[0x2F8];
    f32 value38C;
    f32 value390;
    u8 pad394[0x20];
    f32 speed;
    u8 pad3B8[0x10];
    f32 roll;
    f32 pitch;
    f32 health;
    u8 pad3D4[0x28];
    f32 turretAngle;
    f32 bodyAngle;
    u8 leftSpeed;
    u8 rightSpeed;
    u8 leftTrack;
    u8 rightTrack;
    s8 primaryReady;
    s8 secondaryReady;
    u8 pad40A[2];
    f32 turretMatrix[4][4];
    u8 pad44C[0xC];
    s32 engineSound;
    s32 skidSound;
    u8 pad460[4];
    u8 impactCooldown;
    u8 pad465[3];
    s32 primaryWeapon;
    s32 primaryTime;
    u8 pad470[4];
    s32 secondaryWeapon;
    s32 secondaryTime;
    u8 pad47C[8];
    s16 value484;
    s16 value486;
    u8 pad488[4];
    s16 value48C;
    u8 pad48E[6];
    s16 value494;
    u8 pad496[0xE];
    s32 collider;
    u8 pad4A8[0x5C];
    UnitOwner *owner;
} Unit;

extern u8 D_80125EC0[];
extern s32 gGameTicks __asm__("D_801B4AA8");
extern HitHandlerEntry D_802C3804[];
extern HitReply D_80072498;

extern f32 angle_sin(u16 angle) __asm__("func_800F3AE0");
extern f32 angle_cos(u16 angle) __asm__("func_800F3B40");
extern s32 radians_to_angle(f32 radians) __asm__("func_800F3BE4");
extern void func_801074AC(s32 collider, s32 x, s32 z, u16 angle);
extern u8 func_80107B44(s32 collider, SegmentHit *hits, s32 *count);
extern void apply_pickup(Unit *unit, s32 pickup, s32 arg2) __asm__("func_80099D90");
extern s32 func_800E3470(Unit *unit);
extern s32 func_800796F0(s32 sound, s32 loop);
extern void func_800799D0(s32 handle, s16 value);
extern void func_80079A5C(s32 handle, f32 value);
extern void func_800798C0(s32 handle);
extern void func_80099A08(Unit *unit);
extern void set_matrix_identity(f32 matrix[4][4]) __asm__("func_800A7650");
extern void func_800A76A0(f32 matrix[4][4], f32 *position);
extern void func_800A7F3C(f32 a[4][4], f32 b[4][4], f32 out[4][4]);
extern void func_800A82B8(f32 out[4][4], f32 in[4][4], u16 angle);
extern void func_800A841C(f32 out[4][4], f32 in[4][4], u16 angle);
extern void func_800A8580(f32 out[4][4], f32 in[4][4], u16 angle);
extern s32 func_800EC738(u16 controller);
extern void func_800987D8(Unit *unit, s32 *weapon, s32 arg2, s32 arg3);
extern void func_8009EDD0(Unit *unit);
extern void destroy_unit(Unit *unit, u32 killer, s32 spawnWreck) __asm__("func_80097DD0");

void update_unit_from_pose(Unit *u, UnitPose *pose) __asm__("func_8009CA6C");

void update_unit_from_pose(Unit *u, UnitPose *pose)
{
    f32 a[4][4];
    f32 b[4][4];
    f32 t[4][4];
    SegmentHit hits[16];
    s32 count;
    s32 i;
    s32 command;
    f32 turn;
    f32 x;
    f32 z;
    f32 forward;
    f32 s;
    f32 f;

    if (u->alive == 0) {
        return;
    }
    u->primaryReady = 0;
    if (u->primaryTime + D_80125EC0[u->primaryWeapon] < gGameTicks) {
        u->primaryReady = 1;
    }
    u->secondaryReady = 0;
    if (u->secondaryTime + D_80125EC0[u->secondaryWeapon] < gGameTicks) {
        u->secondaryReady = 1;
    }
    turn = pose->angle * (360.0f / 65536.0f) - u->heading;
    x = pose->x;
    z = pose->z;
    if (turn < -180.0f) {
        turn += 360.0f;
    }
    if (180.0f < turn) {
        turn -= 360.0f;
    }
    s = angle_sin((u16)(u->heading * 182.04445f));
    forward = (s * (x - u->x) + angle_cos((u16)(u->heading * 182.04445f)) * (z - u->z)) * 13.0f;
    turn *= 1.0f / 180.0f;
    u->leftSpeed = (s32)(forward + turn);
    u->rightSpeed = (s32)(forward - turn);
    u->leftTrack += u->leftSpeed;
    u->rightTrack += u->rightSpeed;
    u->x = pose->x;
    u->z = pose->z;
    u->heading = pose->angle * (360.0f / 65536.0f);
    u->bodyAngle = u->heading;
    u->turretAngle = pose->turret * (360.0f / 65536.0f);
    func_801074AC(u->collider, u->x, u->z, (u16)(u->heading * 182.04445f));
    if (func_80107B44(u->collider, hits, &count)) {
        HitReply reply = D_80072498;
        HitQuery query;
        register SegmentHit *hit __asm__("$16") = hits;

        for (i = 0; i < count; i++) {
            if ((u32)hit->object >= 4) {
                if (u->bodyMatrix[2][0] < 0.0f) {
                    query.angle = -radians_to_angle(u->bodyMatrix[2][2]);
                } else {
                    query.angle = radians_to_angle(u->bodyMatrix[2][2]);
                }
                query.x = hit->x;
                query.z = hit->z;
                if (D_802C3804[hit->object->kind].handle != 0) {
                    D_802C3804[hit->object->kind].handle(hit->object, u->owner, 0, &query, &reply);
                }
                switch (reply.status) {
                case 3:
                    apply_pickup(u, reply.value04, 1);
                    if (u->value48C != 0) {
                        u->secondaryWeapon = 10;
                        u->value494 = 1;
                    }
                    break;
                case 4:
                    f = u->value38C;
                    if (f < 0.0f) {
                        f = -f;
                    }
                    if (!(0.1f < f)) {
                        if (u->value390 < 0.0f) {
                            if (!(0.1f < -u->value390)) {
                                break;
                            }
                        } else if (!(0.1f < u->value390)) {
                            break;
                        }
                    }
                    u->health -= 1.2f;
                    break;
                case 5:
                    u->health -= 6.0;
                    break;
                }
            } else if (u->impactCooldown == 0 && 0.3 < u->speed && func_800E3470(u) != 0) {
                command = func_800796F0(0x11, 0);
                if (u->speed < 0.5f) {
                    func_800799D0(command, 2.0f * u->speed * 28672.0f);
                }
                u->impactCooldown = 0x20;
            }
            hit++;
        }
    }
    func_80099A08(u);
    set_matrix_identity(a);
    set_matrix_identity(b);
    func_800A82B8(b, a, (u16)(u->pitch * 182.04445f));
    func_800A8580(a, b, (u16)(u->roll * 182.04445f));
    func_800A841C(b, a, (u16)(u->bodyAngle * 182.04445f));
    set_matrix_identity(t);
    func_800A76A0(t, &u->x);
    func_800A7F3C(a, t, u->bodyMatrix);
    set_matrix_identity(a);
    set_matrix_identity(b);
    func_800A82B8(b, a, (u16)(u->pitch * 182.04445f));
    func_800A8580(a, b, (u16)(u->roll * 182.04445f));
    func_800A841C(b, a, (u16)(u->turretAngle * 182.04445f));
    set_matrix_identity(t);
    func_800A76A0(t, &u->x);
    func_800A7F3C(a, t, u->turretMatrix);
    command = func_800EC738(u->owner->controller);
    if (command & 0x80) {
        apply_pickup(u, command & ~0x80, 0);
        if (u->value48C != 0) {
            u->secondaryWeapon = 10;
            u->value494 = 1;
        }
    } else {
        switch (command) {
        case 1:
            func_800987D8(u, &u->primaryWeapon, 1, 1);
            break;
        case 2:
            func_800987D8(u, &u->secondaryWeapon, 1, 1);
            break;
        case 3:
            u->flags |= 1;
            break;
        case 4:
            u->flags |= 2;
            break;
        case 6:
            func_8009EDD0(u);
            destroy_unit(u, -1, 0);
            break;
        case 5:
            u->value18 = 2;
            u->primaryWeapon = 3;
            u->value486 = 100;
            break;
        case 7:
            u->value18 = 1;
            u->primaryWeapon = 2;
            u->value484 = 500;
            break;
        case 8:
            u->flags |= 0x4000;
            break;
        case 9:
            u->flags &= ~0x4000;
            break;
        }
    }
    if (u->flags & 0x4000) {
        func_800987D8(u, &u->primaryWeapon, 0, 0);
    }
    if (u->owner->controller == 0) {
        if (u->engineSound == -1) {
            u->engineSound = func_800796F0(0x10, 1);
        }
        func_80079A5C(u->engineSound, u->speed + 0.8f);
        func_800799D0(u->engineSound, 0x3800);
        if (0.5 < u->speed) {
            if (u->skidSound == -1) {
                u->skidSound = func_800796F0(0x12, 1);
            }
            func_800799D0(u->skidSound, 2.0f * (u->speed - 0.5f) * 28672.0f);
            return;
        }
        if (u->skidSound != -1) {
            func_800798C0(u->skidSound);
            u->skidSound = -1;
        }
    }
}
