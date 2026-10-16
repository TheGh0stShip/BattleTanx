#include "types.h"

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
    u8 pad0E[0x12];
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

typedef void (*HitHandler)(void *object, UnitOwner *owner, s32 kind, void *query, HitReply *reply);

typedef struct HitHandlerEntry {
    HitHandler handle;
    u8 pad04[0x8];
} HitHandlerEntry;

typedef struct OwnerRecord {
    u8 pad000[0x204];
    u8 value204;
} OwnerRecord;

typedef struct DriveInput {
    f32 turn;
    f32 move;
    f32 aim;
    u8 fire;
    u8 firePressed;
    u8 special;
    u8 specialPressed;
    u8 boost;
    u8 brake;
} DriveInput;

typedef struct LinkTarget {
    u8 pad00[4];
    s32 serial;
    s32 kind;
} LinkTarget;

typedef struct Unit {
    u8 pad00;
    u8 alive;
    u8 pad02;
    u8 local;
    u8 owner;
    u8 pad05[0x3];
    s32 flash;
    s32 flashUntil;
    s32 value10;
    u16 flags;
    u8 pad16[0xE];
    f32 x;
    f32 y;
    f32 z;
    u8 pad30[0x24];
    f32 bodyMatrix[4][4];
    u8 pad94[0x2F0];
    f32 value384;
    f32 value388;
    f32 value38C;
    f32 value390;
    u8 pad394[0x20];
    f32 speed;
    u8 pad3B8[0x8];
    f32 value3C0;
    u8 pad3C4[4];
    f32 roll;
    f32 pitch;
    f32 health;
    u8 pad3D4[0x1C];
    s64 value3F0;
    u8 pad3F8[4];
    f32 turretAngle;
    f32 bodyAngle;
    u8 pad404[4];
    s8 primaryReady;
    s8 secondaryReady;
    u8 pad40A[2];
    f32 turretMatrix[4][4];
    u8 pad44C[0x10];
    s32 engineSound;
    u8 pad460[4];
    u8 impactCooldown;
    u8 pad465[3];
    s32 primaryWeapon;
    s32 primaryTime;
    u8 pad470[4];
    s32 secondaryWeapon;
    s32 secondaryTime;
    u8 pad47C[0x28];
    s32 collider;
    u8 pad4A8[0x28];
    f32 originZ;
    f32 originX;
    f32 dirZ;
    f32 dirX;
    f32 maxTravel;
    f32 travel;
    f32 velocity;
    s32 exitTime;
    s32 exitSound;
    u8 pad4F4[8];
    LinkTarget *link;
    s32 linkSerial;
    UnitOwner *ownerInfo;
} Unit;

extern u8 D_80125EC0[];
extern s32 gGameTicks __asm__("D_801B4AA8");
extern f32 D_801257B0;
extern s32 D_80135834;
extern HitHandlerEntry D_802C3804[];
extern HitReply D_80072498;

extern s32 func_800E3460(Unit *unit);
extern s32 func_800E3470(Unit *unit);
extern s32 *get_game_mode(void) __asm__("func_8007AAF4");
extern OwnerRecord *get_entity_record(u16 index) __asm__("func_800A6688");
extern s32 func_800796F0(s32 sound, s32 loop);
extern void func_800799D0(s32 handle, s16 value);
extern void func_80079A5C(s32 handle, f32 value);
extern void func_800798C0(s32 handle);
extern void func_80085B4C(s32 sound, f32 x, f32 z);
extern s32 radians_to_angle(f32 radians) __asm__("func_800F3BE4");
extern void func_801074AC(s32 collider, s32 x, s32 z, u16 angle);
extern u8 func_80107B44(s32 collider, SegmentHit *hits, s32 *count);
extern void apply_pickup(Unit *unit, s32 pickup, s32 arg2) __asm__("func_80099D90");
extern void func_800E480C(Unit *unit, s32 kind);
extern void func_80099A08(Unit *unit);
extern void set_matrix_identity(f32 matrix[4][4]) __asm__("func_800A7650");
extern void func_800A76A0(f32 matrix[4][4], f32 *position);
extern void func_800A7F3C(f32 a[4][4], f32 b[4][4], f32 out[4][4]);
extern void func_800A82B8(f32 out[4][4], f32 in[4][4], u16 angle);
extern void func_800A841C(f32 out[4][4], f32 in[4][4], u16 angle);
extern void func_800A8580(f32 out[4][4], f32 in[4][4], u16 angle);
extern void func_800987D8(Unit *unit, s32 *weapon, s32 arg2, s32 arg3);
extern void func_800A51E8(OwnerRecord *record, s32 arg1, f32 arg2);

void update_rail_unit_control(Unit *u, DriveInput *in) __asm__("func_8009BBC0");

void update_rail_unit_control(Unit *u, DriveInput *in)
{
    f32 a[4][4];
    f32 b[4][4];
    f32 t[4][4];
    SegmentHit hits[32];
    f32 scratch[4][4];
    s32 count;
    s32 i;
    s32 blocked;
    s32 bumpKind;
    f32 dt;
    f32 one;
    f32 hundred;
    f32 scale;
    f32 aim;
    f32 limit;
    f32 accel;
    f32 cap;
    f32 oldTravel;
    f32 prev[2];
    f32 f;
    s32 command;
    s64 stick;

    blocked = 0;
    bumpKind = 0;
    if (u->impactCooldown != 0) {
        u->impactCooldown--;
    }
    if (u->alive == 0) {
        return;
    }
    if (u->flash > 0) {
        u->flash -= 0x20;
        if (u->flash < 0) {
            u->flash = 0;
        }
    }
    if (u->flashUntil < gGameTicks) {
        u->flashUntil = 0;
        u->value10 = 0;
    } else if (u->flashUntil - 7 < gGameTicks) {
        u->flash = (gGameTicks - u->flashUntil) << 5;
    }
    if (in->boost != 0 && func_800E3460(u) == 0 && *get_game_mode() != 7) {
        if (u->exitTime == 0) {
            u->exitTime = gGameTicks;
        } else if (u->exitTime + 60 < gGameTicks) {
            if (get_entity_record(u->owner)->value204 == 0) {
                u->bodyAngle = u->turretAngle;
            }
            u->flags &= ~4;
            u->value384 = u->x;
            u->value388 = u->z;
        } else if (u->exitTime + 5 < gGameTicks && u->exitSound == -1) {
            u->exitSound = func_800796F0(0x15, 0);
        }
    } else {
        if (u->exitSound != -1) {
            func_800799D0(u->exitSound, 0);
            u->exitSound = -1;
        }
        u->exitTime = 0;
    }
    u->primaryReady = 0;
    if (u->primaryTime + D_80125EC0[u->primaryWeapon] < gGameTicks) {
        u->primaryReady = 1;
    }
    u->secondaryReady = 0;
    if (u->secondaryTime + D_80125EC0[u->secondaryWeapon] < gGameTicks) {
        u->secondaryReady = 1;
    }
    one = 1.0f;
    dt = D_801257B0 * 0.15;
    hundred = 100.0f;
    aim = -in->aim * hundred;
    if (one < dt) {
        dt = one;
    }
    if (dt < 0.1f) {
        dt = 0.1f;
    }
    u->value3F0 = stick;
    u->turretAngle -= aim * u->value3C0 * dt * 1.98f;
    if (*get_game_mode() == 7) {
        scale = 1.4f;
    } else {
        scale = one;
    }
    limit = scale * 26.5f;
    accel = ((-limit * in->move) / hundred - u->velocity) / (4.0f / scale);
    cap = scale * 8.06f;
    if (cap < accel) {
        accel = cap;
    } else if (accel < -cap) {
        accel = -cap;
    }
    u->velocity += accel;
    if (limit < u->velocity) {
        u->velocity = limit;
    }
    if (u->velocity < -limit) {
        u->velocity = -limit;
    }
    oldTravel = u->travel;
    u->travel = oldTravel + u->velocity;
    if (u->travel < 0.0f) {
        if (u->velocity < -15.899999999999999) {
            func_80085B4C(0x17, u->x, u->z);
        }
        u->travel = 0.0f;
        u->velocity = -u->velocity / 0.82f;
    }
    if (u->travel > u->maxTravel) {
        if (15.899999999999999 < u->velocity) {
            func_80085B4C(0x17, u->x, u->z);
        }
        u->travel = u->maxTravel;
        u->velocity = -u->velocity / 0.82f;
    }
    prev[1] = u->x;
    prev[0] = u->z;
    u->x = u->originX + u->dirX * u->travel;
    u->z = u->originZ + u->dirZ * u->travel;
    u->y = 0.0f;
    func_801074AC(u->collider, u->x, u->z, (u16)(u->bodyAngle * 182.04445f));
    if (func_80107B44(u->collider, hits, &count)) {
        HitReply reply = D_80072498;
        HitQuery query;

        for (i = 0; i < count; i++) {
            if ((u32)hits[i].object >= 4) {
                u16 angle;

                if (u->dirX < 0.0f) {
                    angle = -radians_to_angle(u->dirZ);
                } else {
                    angle = radians_to_angle(u->dirZ);
                }
                query.angle = (u->velocity >= 0.0f) ? angle : angle + 0x8000;
                query.x = hits[i].x;
                query.z = hits[i].z;
                if (D_802C3804[hits[i].object->kind].handle != 0) {
                    D_802C3804[hits[i].object->kind].handle(hits[i].object, u->ownerInfo, 0, &query, &reply);
                }
                switch (reply.status) {
                case 0:
                    blocked = 1;
                    bumpKind = 1;
                    break;
                case 4:
                    f = u->value38C;
                    if (f < 0.0f) {
                        f = -f;
                    }
                    if (!(0.1f < f)) {
                        if (u->value390 < 0.0f) {
                            if (0.1f < -u->value390) {
                                goto hurt;
                            }
                        } else if (0.1f < u->value390) {
                            goto hurt;
                        }
                        break;
                    }
                hurt:
                    u->health -= 1.2f;
                    break;
                case 5:
                    u->health -= 6.0;
                    break;
                case 3:
                    apply_pickup(u, reply.value04, 1);
                    break;
                }
            } else {
                blocked = 1;
                bumpKind = 2;
                if (u->impactCooldown == 0 && 0.3 < u->speed && func_800E3470(u) != 0) {
                    command = func_800796F0(0x11, 0);
                    if (u->speed < 0.5f) {
                        func_800799D0(command, 2.0f * u->speed * 28672.0f);
                    }
                    u->impactCooldown = 0x20;
                }
            }
            scratch[1][1] = 0;
            scratch[1][2] = 0;
            u->velocity = 0.0f;
        }
    }
    if (blocked) {
        u->x = prev[1];
        u->z = prev[0];
        u->travel = oldTravel;
        func_801074AC(u->collider, u->x, u->z, (u16)(u->bodyAngle * 182.04445f));
        func_800E480C(u, bumpKind);
        u->velocity = 0.0f;
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
    if (in->fire != 0) {
        func_800987D8(u, &u->primaryWeapon, in->firePressed, 0);
    }
    if (in->special != 0) {
        func_800987D8(u, &u->secondaryWeapon, in->specialPressed, 0);
    }
    if (u->local != 0 && (D_80135834 == 0 || func_800E3470(u) != 0)) {
        f32 v = u->velocity;
        f32 vol;

        if (v < 0.0f) {
            vol = -v / 21.2f;
        } else {
            vol = v / 21.2f;
        }
        if (1.0 < vol) {
            vol = 1.0f;
        }
        if (0.1 < vol) {
            if (u->engineSound == -1) {
                u->engineSound = func_800796F0(0x18, 1);
            }
            func_80079A5C(u->engineSound, vol + 0.8f);
            func_800799D0(u->engineSound, vol * 28672.0f);
            goto link;
        }
    }
    if (u->engineSound != -1) {
        func_800798C0(u->engineSound);
        u->engineSound = -1;
    }
link:
    if (u->link != 0) {
        if (u->link->serial != u->linkSerial) {
            u->link = 0;
        } else {
            s32 collider[1];

            collider[0] = u->collider;

            if (D_802C3804[u->link->kind].handle != 0) {
                D_802C3804[u->link->kind].handle(u->link, u->ownerInfo, 5, collider, 0);
            }
        }
    }
    if (!(u->flags & 4)) {
        if (u->engineSound != -1) {
            func_800798C0(u->engineSound);
            u->engineSound = -1;
        }
        func_800A51E8(get_entity_record(u->owner), 0x24, 3.0f);
    }
}
