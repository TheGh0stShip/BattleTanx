#include "types.h"

#define NULL ((void *)0)

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

typedef struct Mtx44 {
    f32 m[4][4];
} Mtx44;

typedef struct Vec2 {
    f32 x;
    f32 z;
} Vec2;

typedef struct Body {
    f32 pad00[3];
    Vec2 pos;
    f32 velX;
    f32 velZ;
    f32 angle;
    f32 lift;
    Vec2 push;
    f32 pending2C;
    f32 pending30;
    Vec2 pending;
} Body;

typedef struct HitObject {
    u8 pad00[4];
    s32 serial;
    s32 kind;
} HitObject;

typedef struct Contact {
    HitObject *obj;
    f32 value4;
    u8 pad08[4];
    f32 valueC;
    u8 pad10[8];
} Contact;

typedef struct HitResult {
    s32 type;
    s32 value;
    f32 amount;
    s32 extra;
} HitResult;

typedef struct HitSource {
    f32 x;
    s32 zero;
    f32 z;
    s16 id;
    u8 pad0E[2];
    s32 kind;
    s32 owner;
    s8 audible;
} HitSource;

typedef struct HitSource2 {
    f32 value;
    u8 pad04[4];
    f32 amount;
    s16 id;
} HitSource2;

typedef struct HitDispatch {
    void (*fn)(HitObject *obj, s32 handle, s32 mode, void *src, HitResult *result);
    s32 pad04[2];
} HitDispatch;

typedef struct CollRect {
    s16 v[9];
} CollRect;

typedef struct LevelShape {
    CollRect rect;
    u8 pad12[0x16];
} LevelShape;

typedef struct Ammo {
    s32 kind;
    s32 time;
    s32 pad08;
} Ammo;

typedef struct Respawn {
    s32 a;
    s32 b;
    u16 c;
} Respawn;

typedef struct LevelQuery {
    s32 level;
} LevelQuery;

typedef union Grab {
    struct {
        f32 amount;
        f32 value;
    } f;
    s64 whole;
} Grab;

typedef struct Tank {
    u8 pad000;
    u8 alive;
    u8 pad002;
    u8 local;
    u8 owner;
    u8 pad005[3];
    s32 flash;
    s32 flashEnd;
    s32 value10;
    u16 flags;
    u8 pad016[2];
    u32 type;
    u8 pad01C[8];
    f32 posX;
    f32 posY;
    f32 posZ;
    u8 pad030[4];
    f32 angle;
    u8 pad038[4];
    f32 prevX;
    u8 pad040[4];
    f32 prevZ;
    u8 pad048[4];
    f32 prevAngle;
    u8 pad050[4];
    Mtx44 bodyMtx;
    u8 pad094[0x378 - 0x94];
    Body body;
    f32 speed;
    f32 grip;
    f32 pad3BC;
    f32 accel;
    f32 drag;
    f32 pitch;
    f32 roll;
    f32 damage;
    u8 pad3D4[4];
    f32 pitch2;
    f32 roll2;
    u8 pad3E0[0xC];
    f32 hover;
    s32 value3F0;
    s32 value3F4;
    u8 pad3F8[4];
    f32 turret;
    f32 heading;
    u8 trackL;
    u8 trackR;
    u8 trackPhaseL;
    u8 trackPhaseR;
    u8 smokeL;
    u8 smokeR;
    u8 zone;
    u8 pad40B;
    Mtx44 turretMtx;
    u8 pad44C[0x458 - 0x44C];
    s32 engineSfx;
    s32 skidSfx;
    u8 pad460[4];
    u8 bumpTimer;
    u8 pad465[3];
    Ammo primary;
    Ammo secondary;
    s16 ammoCount[16];
    u8 pad4A0[4];
    s32 level;
    u8 pad4A8[0x4C0 - 0x4A8];
    f32 prevSpeed;
    u8 pad4C4[0x4F4 - 0x4C4];
    s32 respawnTime;
    Respawn *respawn;
    HitObject *riding;
    s32 ridingSerial;
    s32 handle;
} Tank;

static const HitResult D_80072498 = { 1, 0, 0.0f, 0 };

extern s32 D_801B4AA0;
extern s32 D_801B4AA8;
extern u8 D_80125EC0[];
extern f32 D_801257B0;
extern f32 D_802D8150;
extern f32 D_802D8154;
extern LevelShape D_803B8254[];
extern HitDispatch D_802C3804[];
extern u8 D_80134E68;
extern s32 D_80135834;
extern f32 D_80125F94[];

extern s32 func_8009FEE0(Tank *tank, s32 a, s32 b, u16 c);
extern s32 func_800E3460(Tank *tank);
extern s32 func_800E3470(Tank *tank);
extern void func_800F2E50(s32 r, s32 g, s32 b, s32 a, s32 player);
extern void func_80097C64(Body *body, f32 rate);
extern void func_80109354(CollRect *rect, s32 x, s32 z, u16 angle);
extern u8 func_80107F14(s32 level, CollRect *rect, u8 zone, f32 *normal, HitObject **hit);
extern u8 func_80108B68(CollRect *rect, s32 level, u8 zone, f32 *slide, f32 *out, f32 *pos, f32 *normal, HitObject **hit);
extern void func_801074AC(s32 level, s32 x, s32 z, u16 angle);
extern s16 func_8009FD94(Tank *tank, Body *body);
extern void func_800E4660(Tank *tank, HitObject *obj, s32 mode, void *arg);
extern s32 func_800796F0(s32 sfx, s32 loop);
extern void func_800799D0(s32 handle, s16 volume);
extern void func_80079A5C(s32 handle, f32 pitch);
extern void func_800798C0(s32 handle);
extern void func_800A8EF8(u8 player, s32 a, s32 b, s32 c);
extern u8 func_80107B44(s32 level, Contact *contacts, s32 *count);
extern void func_80099D90(Tank *tank, s32 value, s32 flag);
extern void func_800983E0(Tank *tank, s32 value, f32 amount, s32 flag);
extern u8 *func_800A6688(u8 player);
extern void func_80099A08(Tank *tank);
extern void func_800A7650(Mtx44 *m);
extern void func_800A82B8(Mtx44 *dst, Mtx44 *src, u16 angle);
extern void func_800A8580(Mtx44 *dst, Mtx44 *src, u16 angle);
extern void func_800A841C(Mtx44 *dst, Mtx44 *src, u16 angle);
extern void func_800A76A0(Mtx44 *m, f32 *pos);
extern void func_800A7F3C(Mtx44 *a, Mtx44 *b, Mtx44 *out);
extern void func_800987D8(Tank *tank, Ammo *ammo, u8 pressed, s32 flag);
extern u8 *func_80096784(u8 player);

void update_tank_drive(Tank *tank, DriveInput *input, s32 mode) __asm__("func_8009A354");

void update_tank_drive(Tank *tank, DriveInput *input, s32 mode) {
    Mtx44 m0;
    Mtx44 m1;
    Mtx44 m2;
    Contact contacts[32];
    Body saved;
    f32 out[2];
    f32 normal[2];
    f32 pos[2];
    f32 slide[4];
    CollRect rect;
    Vec2 newPos;
    HitObject *hit;
    s32 contactCount;
    f32 rate;
    f32 fwd;
    f32 side;
    u8 brake;
    f32 startTurret;
    f32 startHeading;
    f32 turnLeft;
    f32 turnExtra;
    f32 delta;
    s32 pass;
    LevelQuery query;
    s32 stale3F0;
    s32 stale3F4;
    s32 i;
    s32 j;

    if (input->turn > 200.0f) {
        input->turn = 200.0f;
    }
    if (input->turn < -200.0f) {
        input->turn = -200.0f;
    }

    if (tank->respawnTime != 0) {
        if (tank->respawnTime == D_801B4AA0 - 30) {
            tank->respawnTime = 0;
        } else if (tank->respawnTime == D_801B4AA0 - 15) {
            s32 found = 0;

            i = 0;
            do {
                if (func_8009FEE0(tank, tank->respawn[i].a, tank->respawn[i].b, tank->respawn[i].c) >= 0) {
                    found = 1;
                    if (func_800E3460(tank) == 0) {
                        func_800F2E50(0xFF, 0xFF, 0xFF, 0xC, tank->owner);
                    }
                }
                i++;
            } while (i < 5 && !found);
            if (!found) {
                tank->respawnTime = 0;
            }
        }
    }

    if (tank->bumpTimer != 0) {
        tank->bumpTimer--;
    }
    if (tank->flash > 0) {
        tank->flash -= 0x20;
        if (tank->flash < 0) {
            tank->flash = 0;
        }
    }
    if (tank->flashEnd < D_801B4AA8) {
        tank->flashEnd = 0;
        tank->value10 = 0;
    } else if (tank->flashEnd - 7 < D_801B4AA8) {
        tank->flash = (D_801B4AA8 - tank->flashEnd) << 5;
    }

    if (tank->alive == 0) {
        return;
    }

    tank->smokeL = 0;
    tank->smokeR = 0;
    if (tank->primary.time + D_80125EC0[tank->primary.kind] < D_801B4AA8) {
        tank->smokeL = 1;
    }
    if (tank->secondary.time + D_80125EC0[tank->secondary.kind] < D_801B4AA8) {
        tank->smokeR = 1;
    }

    rate = D_801257B0 * 0.15;
    rate = (rate > 0.9f) ? 0.9f : rate;
    rate = (rate < 0.1f) ? 0.1f : rate;

    tank->value3F0 = stale3F0;
    tank->value3F4 = stale3F4;
    tank->trackPhaseL += tank->trackL;
    tank->trackPhaseR += tank->trackR;
    tank->body.pending2C = tank->body.pending30;
    tank->body.push = tank->body.pending;
    tank->body.pending30 = 0.0f;
    tank->body.pending.x = 0.0f;
    tank->body.pending.z = 0.0f;

    if (tank->body.velX < 5.0f && tank->body.velZ < 5.0f) {
        input->move *= 1.5;
    }

    startTurret = tank->turret;
    startHeading = tank->heading;
    brake = input->brake;

    if (mode == 1) {
        delta = input->move * tank->accel * rate;
        tank->turret = startTurret - delta;
        while (tank->turret > 360.0f) {
            tank->turret -= 360.0f;
        }
        while (tank->turret < 0.0f) {
            tank->turret += 360.0f;
        }
        if (tank->type == 1) {
            tank->heading = tank->turret;
        }
        if (brake == 0) {
            f32 step;

            delta = tank->turret - tank->heading;
            if (delta > 180.0f) {
                delta -= 360.0f;
            }
            if (delta < -180.0f) {
                delta += 360.0f;
            }
            step = delta * delta / 200.0f;
            if (input->turn < 0.0f) {
                step = step * -input->turn / 80.0f;
            } else {
                step = step * input->turn / 80.0f;
            }
            if (step > 4.0f) {
                step = 4.0f;
            }
            if (delta < 0.0f) {
                tank->heading -= step;
            } else {
                tank->heading += step;
            }
        }
    } else {
        if (mode == 2) {
            input->move /= 2.0f;
        } else if (mode == 3) {
            input->aim /= 2.0f;
        }
        delta = input->move * tank->accel * rate;
        tank->heading -= delta;
        tank->turret -= delta;
        if (tank->type != 1) {
            delta = input->aim * tank->accel * rate;
            tank->turret += delta;
        }
    }

    tank->trackL = (s32)(-input->turn / 2.0f + input->move / 800.0f);
    tank->trackR = (s32)(-input->turn / 2.0f - input->move / 800.0f);
    tank->body.push.x += tank->grip * input->turn * tank->bodyMtx.m[2][0];
    tank->body.push.z += tank->grip * input->turn * tank->bodyMtx.m[2][2];
    D_802D8150 = tank->body.velX * tank->bodyMtx.m[2][0] + tank->body.velZ * tank->bodyMtx.m[2][2];
    D_802D8154 = tank->body.velX * tank->bodyMtx.m[2][2] + tank->body.velZ * -tank->bodyMtx.m[2][0];
    tank->body.push.x -= tank->body.velX * tank->drag;
    tank->body.push.z -= tank->body.velZ * tank->drag;

    saved = tank->body;
    turnLeft = saved.angle = tank->heading;
    func_80097C64(&saved, rate);
    pass = 0;

    if (saved.velX > 512.0f) {
        saved.velX = 512.0f;
    }
    if (saved.velX < -512.0f) {
        saved.velX = -512.0f;
    }
    if (saved.velZ > 512.0f) {
        saved.velZ = 512.0f;
    }
    if (saved.velZ < -512.0f) {
        saved.velZ = -512.0f;
    }

    if (tank->prevX == saved.pos.x && tank->prevZ == saved.pos.z && tank->prevAngle == saved.angle) {
        goto after_move;
    }
    {
        u8 blocked;

        newPos = tank->body.pos;
        slide[1] = saved.velX;
        slide[0] = saved.velZ;
        turnExtra = saved.lift;
        rect = D_803B8254[tank->level].rect;
    retry:
        blocked = 0;
        hit = NULL;
        func_80109354(&rect, newPos.x, newPos.z, (u16)(saved.angle * 182.04444444));
        if (func_80107F14(tank->level, &rect, tank->zone, normal, &hit)) {
            blocked = 1;
            if (pass == 1) {
                turnExtra = 0.0f;
                tank->heading = startHeading;
                turnLeft = 0.0f;
                if (mode != pass) {
                    tank->turret = startTurret;
                }
                pos[1] = tank->body.pos.x;
                pos[0] = tank->body.pos.z;
            }
            if (pass == 0) {
                newPos.x += normal[1] * 5.0f;
                pass = 1;
                slide[1] = 0.0f;
                newPos.z += normal[0] * 5.0f;
                slide[0] = 0.0f;
                saved.pos.x = newPos.x;
                saved.pos.z = newPos.z;
                goto retry;
            }
        }
        if (!blocked) {
            if (slide[1] != 0.0f || slide[0] != 0.0f) {
                blocked = func_80108B68(&rect, tank->level, tank->zone, slide, out, pos, normal, &hit);
                if (!blocked) {
                    goto accept;
                }
                tank->body.pos.x = tank->body.pos.x;
                tank->body.pos.z = tank->body.pos.z;
                tank->body.velX *= -0.3;
                tank->body.velZ *= -0.3;
                tank->body.velX += normal[1] * 5.0f;
                tank->body.velZ += normal[0] * 5.0f;
                turnLeft -= saved.angle;
            }
            if (!blocked) {
                goto accept;
            }
        }

        while (saved.angle > 360.0f) {
            saved.angle -= 360.0f;
        }
        while (saved.angle < 0.0f) {
            saved.angle += 360.0f;
        }
        if ((u32)hit >= 4) {
            HitSource src;
            HitResult res;

            res = D_80072498;
            src.id = func_8009FD94(tank, &saved);
            src.zero = 0;
            src.x = pos[1];
            src.z = pos[0];
            switch (tank->type) {
            case 1:
                src.kind = 10;
                break;
            case 0:
            case 2:
                src.kind = 17;
                break;
            }
            src.owner = tank->owner;
            src.audible = func_800E3460(tank) == 0;
            if (D_802C3804[hit->kind].fn != NULL) {
                D_802C3804[hit->kind].fn(hit, tank->handle, 0, &src, &res);
            }
            if (func_800E3460(tank) != 0) {
                if (hit->kind == 0x1B) {
                    func_800E4660(tank, hit, 8, pos);
                }
                if (hit->kind == 0) {
                    func_800E4660(tank, hit, 8, pos);
                }
            }
        }
        if (tank->speed > 0.2) {
            s32 sfx;

            if ((u32)hit < 4) {
                if (tank->bumpTimer == 0 && tank->speed > 0.3) {
                    if (func_800E3470(tank) != 0) {
                        sfx = 0x11;
                        goto play;
                    }
                }
            } else {
                switch (hit->kind) {
                case 6:
                    break;
                case 0:
                    if (tank->bumpTimer == 0 && tank->speed > 0.3) {
                        if (func_800E3470(tank) != 0) {
                            sfx = 0xF;
                            goto play;
                        }
                    }
                    break;
                case 16:
                    if (tank->bumpTimer == 0 && tank->speed > 0.3) {
                        if (func_800E3470(tank) != 0) {
                            sfx = 0x23;
                            goto play;
                        }
                    }
                    break;
                default:
                    if (tank->bumpTimer == 0 && tank->speed > 0.3) {
                        if (func_800E3470(tank) != 0) {
                            s32 h;

                            sfx = 0x11;

                        play:
                            h = func_800796F0(sfx, 0);
                            if (tank->speed < 0.5f) {
                                func_800799D0(h, 2.0f * tank->speed * 28672.0f);
                            }
                            tank->bumpTimer = 0x20;
                        }
                    }
                    break;
                }
            }
            if ((u32)hit < 4 || hit->kind == 5) {
                func_800A8EF8(tank->owner, 0x10, 2, 2);
            }
        goto moved;
    accept:
            tank->prevX = tank->posX;
            tank->prevZ = tank->posZ;
            tank->prevAngle = tank->angle;
            tank->body = saved;
            tank->heading = saved.angle;
            tank->posX = tank->body.pos.x;
            tank->posZ = tank->body.pos.z;
            tank->angle = tank->body.angle;
            {
                u16 angle = tank->heading * 182.04445f;

                func_801074AC(tank->level, tank->posX, tank->posZ, angle);
            }
            turnLeft -= saved.angle;
            goto moved;
        }
    }
moved:
    tank->turret = tank->turret - turnLeft + turnExtra;
    if (tank->type == 1) {
        tank->turret = tank->heading;
    }

    if (func_80107B44(tank->level, contacts, &contactCount)) {
        HitResult res;
        HitSource2 src;

        res = D_80072498;
        for (j = 0; j < contactCount; j++) {

            if ((u32)contacts[j].obj >= 4) {
                Grab grab;

                src.id = func_8009FD94(tank, &saved);
                src.value = contacts[j].value4;
                src.amount = contacts[j].valueC;
                if (D_802C3804[contacts[j].obj->kind].fn != NULL) {
                    D_802C3804[contacts[j].obj->kind].fn(contacts[j].obj, tank->handle, 0, &src, &res);
                }
                grab.f.value = src.value;
                grab.f.amount = src.amount;
                func_800E4660(tank, contacts[j].obj, 0, &grab);
                switch (res.type) {
                case 4:
                    if ((tank->body.velX < 0.0f ? -tank->body.velX : tank->body.velX) > 0.1f ||
                        (tank->body.velZ < 0.0f ? -tank->body.velZ : tank->body.velZ) > 0.1f) {
                        tank->damage -= 1.2f;
                    }
                    break;
                case 5:
                    tank->damage -= 6.0f;
                    break;
                case 3:
                    if (func_800E3460(tank) == 0) {
                        func_80099D90(tank, res.value, 1);
                    }
                    break;
                case 8:
                    func_800983E0(tank, res.value, res.amount, 0);
                    tank->damage -= res.value * 0.2f;
                    break;
                case 9:
                    *(s32 *)(func_800A6688(tank->owner) + 0x10) = 2;
                    break;
                case 10:
                    if (tank->respawnTime == 0) {
                        tank->respawnTime = D_801B4AA0;
                        tank->respawn = (Respawn *)res.value;
                    }
                    break;
                }
            }
        }
    }

    {
        f32 ax = tank->body.velX < 0.0f ? -tank->body.velX : tank->body.velX;
        f32 az = tank->body.velZ < 0.0f ? -tank->body.velZ : tank->body.velZ;

        if (ax < az) {
            tank->speed = ax * 0.75f + az;
        } else {
            tank->speed = az * 0.75f + ax;
        }
    }
    if (tank->speed > 100.0) {
        tank->speed = 1.0;
    } else {
        tank->speed = tank->speed / 100.0;
    }
    if (tank->speed - tank->prevSpeed > 0.1) {
        tank->flags |= 0x200;
    } else {
        tank->flags &= ~0x200;
    }
    tank->prevSpeed = tank->speed;

after_move:
    func_80099A08(tank);

    func_800A7650(&m0);
    func_800A7650(&m1);
    func_800A82B8(&m1, &m0, (u16)((tank->roll + tank->roll2) * 182.04445f));
    func_800A8580(&m0, &m1, (u16)((tank->pitch + tank->pitch2) * 182.04445f));
    func_800A841C(&m1, &m0, (u16)(tank->heading * 182.04445f));
    func_800A7650(&m2);
    tank->posY += tank->hover;
    func_800A76A0(&m2, &tank->posX);
    tank->posY -= tank->hover;
    func_800A7F3C(&m0, &m2, &tank->bodyMtx);

    func_800A7650(&m0);
    func_800A7650(&m1);
    func_800A82B8(&m1, &m0, (u16)((tank->roll + tank->roll2) * 182.04445f));
    func_800A8580(&m0, &m1, (u16)((tank->pitch + tank->pitch2) * 182.04445f));
    func_800A841C(&m1, &m0, (u16)(tank->turret * 182.04445f));
    func_800A7650(&m2);
    tank->posY += tank->hover;
    func_800A76A0(&m2, &tank->posX);
    tank->posY -= tank->hover;
    func_800A7F3C(&m0, &m2, &tank->turretMtx);

    tank->body.push.x = 0.0f;
    tank->body.push.z = 0.0f;
    tank->body.pending2C = 0.0f;

    if (D_80134E68 != 0) {
        if (input->fire != 0) {
            if (tank->secondary.kind != 0) {
                func_800987D8(tank, &tank->secondary, input->firePressed, 0);
            } else {
                func_800987D8(tank, &tank->primary, input->firePressed, 0);
            }
        }
    } else {
        if (input->fire != 0) {
            func_800987D8(tank, &tank->primary, input->firePressed, 0);
        }
        if ((tank->flags & 0x2000) && !(D_801B4AA0 & 3)) {
            func_800987D8(tank, &tank->secondary, 1, 1);
        }
        if (input->special != 0 && !(tank->flags & 0x2000)) {
            if (input->specialPressed != 0) {
                u8 *pad = func_80096784(tank->owner);

                if (*(u32 *)(pad + 8) & *(u32 *)(func_800A6688(tank->owner) + 0x1C8)) {
                    switch (tank->secondary.kind) {
                    case 4:
                    case 5:
                    case 11:
                    case 12:
                        if (tank->ammoCount[tank->secondary.kind] >= 0xF) {
                            tank->flags |= 0x2000;
                        }
                        break;
                    case 13:
                        if (tank->ammoCount[tank->secondary.kind] >= 6) {
                            tank->flags |= 0x2000;
                        }
                        break;
                    }
                }
            }
            func_800987D8(tank, &tank->secondary, input->specialPressed, 0);
        }
    }

    if (tank->local != 0 && (D_80135834 == 0 || func_800E3470(tank) != 0)) {
        if (tank->engineSfx == -1) {
            tank->engineSfx = func_800796F0(0x10, 1);
        }
        func_80079A5C(tank->engineSfx, (tank->speed + 0.8f) * D_80125F94[tank->type]);
        func_800799D0(tank->engineSfx, 0x3800);
        if (tank->speed > 0.5) {
            if (tank->skidSfx == -1) {
                tank->skidSfx = func_800796F0(0x12, 1);
            }
            func_800799D0(tank->skidSfx, 2.0f * (tank->speed - 0.5f) * 28672.0f);
            func_80079A5C(tank->skidSfx, D_80125F94[tank->type]);
        } else if (tank->skidSfx != -1) {
            func_800798C0(tank->skidSfx);
            tank->skidSfx = -1;
        }
    }

    if (tank->riding != NULL) {
        if (tank->riding->serial != tank->ridingSerial) {
            tank->riding = NULL;
            return;
        }
        {
            query.level = tank->level;

            if (D_802C3804[tank->riding->kind].fn != NULL) {
                D_802C3804[tank->riding->kind].fn(tank->riding, tank->handle, 5, &query, NULL);
            }
        }
    }
}
