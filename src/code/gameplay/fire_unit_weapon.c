#include "types.h"

#define NULL ((void *) 0)

typedef struct Vec3f {
    f32 x, y, z;
} Vec3f;

typedef struct Unit {
    u8 pad0[4];
    u8 id;              /* 0x004 */
    u8 pad5[3];
    s32 flashTimer;     /* 0x008 */
    s32 shieldEnd;      /* 0x00C */
    s32 isAi;           /* 0x010 */
    u16 flags;          /* 0x014 */
    u8 pad16[2];
    u32 kind;           /* 0x018 */
    s32 health;         /* 0x01C */
    s32 maxHealth;      /* 0x020 */
    f32 x;              /* 0x024 */
    u8 pad28[4];
    f32 z;              /* 0x02C */
    u8 pad30[4];
    f32 heading;        /* 0x034 */
    u8 pad38[0x1C];
    f32 hullMtx[8];     /* 0x054 */
    f32 hullFwdX;       /* 0x074 */
    u8 pad78[4];
    f32 hullFwdZ;       /* 0x07C */
    u8 pad80[0x350];
    f32 recoil;         /* 0x3D0 */
    u8 pad3D4[0x28];
    f32 turretYaw;      /* 0x3FC */
    u8 pad400[0xC];
    f32 turretMtx[8];   /* 0x40C */
    f32 turretFwdX;     /* 0x42C */
    u8 pad430[4];
    f32 turretFwdZ;     /* 0x434 */
    u8 pad438[0x48];
    s16 ammo[18];       /* 0x480 */
    u8 pad4A4[0xC];
    s32 lastMineTime;   /* 0x4B0 */
    s32 lastFireTime;   /* 0x4B4 */
    u8 pad4B8[0x4C];
    s32 team;           /* 0x504 */
} Unit;

typedef struct Weapon {
    u32 kind;
    s32 lastTime;
    u8 side;
} Weapon;

typedef struct Player {
    u8 pad0[0x48];
    u8 sound[0x24];     /* 0x048 */
    f32 muzzleEnd[3];   /* 0x06C */
    f32 muzzleStart[3]; /* 0x078 */
    u8 pad84[0x12A];
    u8 kind;            /* 0x1AE */
    u8 pad1AF[0x15D];
    s32 boosted;        /* 0x30C */
} Player;

extern u8 D_80125EC0[];
extern u8 D_80125ED4[];
extern u8 D_80134E68;
extern u8 D_80134E69;
extern u8 D_80135760;
extern s32 D_801B4AA8;
extern u8 D_801256F0[];

extern void func_80078680(void *, void *);
extern void func_800786B0(void *, s32);
extern void func_800796F0(s32, s32);
extern s32 func_80085B4C(s32 sound, f32 x, f32 z);
extern void func_80085C68(s32 sound, f32 x, f32 z, f32 scale);
extern s32 func_8008D660(Vec3f *, Vec3f *, Vec3f *, s32, s32, s32, s32, s32, s32, s32);
extern s32 func_8008DF2C(Vec3f *, f32, s32, s32, s32, s32, s32, void *, void *, s32, s32);
extern s32 func_8008E29C(Vec3f *, Vec3f *, f32, s32, s32, s32, s32, s32, s32, s32);
extern s32 func_800A1408(s32, s32, s32, s32, Vec3f *, Vec3f *, Unit *, s32, s32);
extern void func_800A4D34(Player *, s32);
extern Player *func_800A6688(s32);
extern void func_800A7D10(f32 *mtx, Vec3f *in, Vec3f *out);
extern void func_800A8EF8(s32, s32, s32, s32);
extern s32 func_800E3460(Unit *);
extern void func_800ED8C0(Vec3f *, s32);
extern void func_800EED5C(Unit *, s32);
extern s32 func_800F0FD8(Vec3f *, s32, s32, s32, s32, s32, s32, s32);
extern s32 func_800F29F0(Vec3f *, s32, s32, s32);
extern void func_800F3344(Vec3f *, s32, s32, s32);
extern s32 func_800F3BE4(f32);
extern f32 func_800F3880(f32);
extern s32 func_8010DAA0(Vec3f *, s32);
extern void func_8010DED4(Vec3f *, Vec3f *, Vec3f *, s32, s32, s32);

void fire_unit_weapon(Unit *unit, Weapon *weapon, u8 trigger, s8 force) __asm__("func_800987D8");

void fire_unit_weapon(Unit *unit, Weapon *weapon, u8 trigger, s8 force) {
    u32 kind;
    u32 next;
    s32 delay;
    s32 angle1, angle11, angle2, angle4, angle6;
    Vec3f dir1;
    f32 vel1[2];
    Vec3f off1, pos1, dir11;
    f32 vel[2];
    Vec3f off11, pos11, dir2, off2, pos2, dir4;
    f32 a[4];
    f32 spread[2];
    Vec3f off4, pos4;
    f32 b[2];
    Vec3f dir5, off5, pos5, dir6, off6, pos6;
    f32 v[4];
    Vec3f off13, pos13;
    f32 w[4];
    Player *player;
    f32 speed4, speed1, speed11, speed2, side, t, h1, h, r;
    s32 isLocal1, isLocal5, shot, yaw, i;
    static const Vec3f sZeroOffset = {0.0f, 0.0f, 0.0f};

    if ((D_80125ED4[weapon->kind] == 0) & (trigger == 0)) {
        return;
    }
    if (D_80134E68 != 0) {
        if (weapon->kind >= 4) {
            delay = 20;
        } else {
            delay = D_80125EC0[weapon->kind];
        }
    } else if ((unit->flags & 4) && weapon->kind == 3) {
        delay = (u8) (D_80125EC0[3] / 3);
    } else {
        delay = D_80125EC0[weapon->kind];
    }
    if (((weapon->lastTime + delay < D_801B4AA8) | (force != 0))
        && unit->ammo[weapon->kind] > 0) {
        switch (weapon->kind) {
        case 16:
            unit->health += (s32) ((f32) unit->maxHealth * 0.3f);
            if (unit->maxHealth < unit->health) {
                unit->health = unit->maxHealth;
            }
            break;
        case 1:
        case 3: {
            off1.x = 0.0f;
            off1.z = 45.0f;
            off1.y = 36.0f;
            func_800A7D10(unit->turretMtx, &off1, &pos1);
            speed1 = 110.0f;
            unit->recoil += -2.5;
            dir1.x = pos1.x;
            dir1.y = pos1.y;
            dir1.z = pos1.z;
                {
                vel1[1] = unit->turretFwdX * speed1;
                vel1[0] = unit->turretFwdZ * speed1;
                if (unit->turretFwdX < 0.0f) {
                    angle1 = -func_800F3BE4(unit->turretFwdZ);
                } else {
                    angle1 = func_800F3BE4(unit->turretFwdZ);
                }
                isLocal1 = func_800E3460(unit) == 0;
                if (func_8008E29C(&dir1, (Vec3f *) vel1, speed1, angle1 & 0xFFFF, unit->id,
                                  unit->kind == 2 ? 0x28 : 0x11, 0, 0xF, unit->team, isLocal1) < 0) {
                    goto done;
                }
            }
            if (func_800E3460(unit) == 0) {
                func_800796F0(weapon->kind == 1 ? 1 : 0x16, 0);
            } else {
                func_80085C68(weapon->kind == 1 ? 1 : 0x16, unit->x, unit->z, 1.2f);
            }
            func_800EED5C(unit, 0x1D);
            if (unit->isAi == 0) {
                unit->flashTimer = 0xF0;
            }
            unit->lastFireTime = D_801B4AA8;
            if (func_800E3460(unit) == 0) {
                func_800A8EF8(unit->id, 5, 5, 0);
            }
            break;
        }
        case 11: {
            player = func_800A6688(unit->id);
            if (unit->kind == 1) {
                off11.x = 0.0f;
                off11.z = 19.0f;
                off11.y = 25.0f;
            } else {
                off11.x = 0.0f;
                off11.z = 45.0f;
                off11.y = 36.0f;
            }
            func_800A7D10(unit->turretMtx, &off11, &pos11);
            unit->recoil += -2.5;
            speed11 = 40.0f;
            if (player->boosted == 0) {
                speed11 = 30.0f;
            }
            dir11.x = pos11.x;
            dir11.y = pos11.y;
            dir11.z = pos11.z;
            vel[1] = unit->turretFwdX * speed11;
            vel[0] = unit->turretFwdZ * speed11;
            if (unit->turretFwdX < 0.0f) {
                angle11 = -func_800F3BE4(unit->turretFwdZ);
            } else {
                angle11 = func_800F3BE4(unit->turretFwdZ);
            }
            if (func_800E3460(unit) != 0) {
                shot = func_8008DF2C(&dir11, speed11, angle11 & 0xFFFF, unit->id, 0x28, 0x10, 0, NULL, NULL,
                                     unit->team, 0);
            } else {
                shot = func_8008DF2C(&dir11, speed11, angle11 & 0xFFFF, unit->id, 0x28, 0x10, 1,
                                     player->muzzleStart, player->muzzleEnd, unit->team,
                                     (unit->flags & 0x2000) ? unit->ammo[11] : 0);
            }
            if (shot != 0) {
                func_80085B4C(0xA, unit->x, unit->z);
                func_800EED5C(unit, 0x1D);
                if (unit->isAi == 0) {
                    unit->flashTimer = 0xF0;
                }
                unit->lastFireTime = D_801B4AA8;
                if (unit->flags & 0x2000) {
                    unit->ammo[11] = 1;
                }
                if (func_800E3460(unit) == 0) {
                    func_800A4D34(player, shot);
                    func_80078680(player->sound, D_801256F0);
                    func_800786B0(player->sound, shot + 0x28);
                }
            }
            break;
        }
        case 2: {
            off2.z = 19.0f;
            off2.y = 25.0f;
            side = -11.1f;
            if (weapon->side & 1) {
                side = 11.1f;
            }
            off2.x = side;
            weapon->side ^= 1;
            func_800A7D10(unit->hullMtx, &off2, &pos2);
            speed2 = 110.0f;
            unit->recoil += -2.0;
            dir2.x = pos2.x;
            dir2.y = pos2.y;
            dir2.z = pos2.z;
            vel[1] = unit->hullFwdX * speed2;
            vel[0] = unit->hullFwdZ * speed2;
            if (unit->hullFwdX < 0.0f) {
                angle2 = -func_800F3BE4(unit->hullFwdZ);
            } else {
                angle2 = func_800F3BE4(unit->hullFwdZ);
            }
            if (func_8008E29C(&dir2, (Vec3f *) vel, speed2, angle2 & 0xFFFF, unit->id, 2, 1, 0,
                              unit->team, func_800E3460(unit) == 0) >= 0) {
                func_80085B4C(0x22, unit->x, unit->z);
                if (unit->isAi == 0) {
                    unit->flashTimer = 0xF0;
                }
                unit->lastFireTime = D_801B4AA8;
            }
            break;
        }
        case 4: {
            if (unit->kind == 1) {
                off4.x = 0.0f;
                off4.z = 19.0f;
                off4.y = 25.0f;
            } else {
                off4.x = 0.0f;
                off4.z = 45.0f;
                off4.y = 36.0f;
            }
            func_800A7D10(unit->turretMtx, &off4, &pos4);
            unit->recoil += 3.0;
            dir4.x = pos4.x;
            dir4.y = pos4.y;
            dir4.z = pos4.z;
            speed4 = 50.0f;
            a[1] = unit->turretFwdX * speed4;
            a[0] = unit->turretFwdZ * speed4;
            a[2] = -a[1];
            a[3] = a[0];
            if (unit->turretFwdX < 0.0f) {
                angle4 = -func_800F3BE4(unit->turretFwdZ);
            } else {
                angle4 = func_800F3BE4(unit->turretFwdZ);
            }
            if (unit->flags & 0x2000) {
                for (i = 0; i < 3; i++) {
                    t = func_800F3880(6.0f) - 3.0f;
                    b[1] = a[1] + (a[3] * t) / 10.0f;
                    b[0] = a[0] + (a[2] * t) / 10.0f;
                    spread[1] = (-a[3] * t) / 200.0f;
                    spread[0] = (-a[2] * t) / 200.0f;
                    if (func_8008D660(&dir4, (Vec3f *) b, (Vec3f *) spread, angle4 & 0xFFFF, unit->id,
                                      0xE, 0, 0x10, unit->team, func_800E3460(unit) == 0) >= 0
                        && i == 0) {
                        func_80085B4C(0xA, unit->x, unit->z);
                        weapon->lastTime = D_801B4AA8;
                        if (unit->isAi == 0) {
                            unit->flashTimer = 0xF0;
                        }
                        unit->lastFireTime = D_801B4AA8;
                    }
                }
            } else {
                s32 ang = angle4 & 0xFFFF;

                spread[1] = 0.0f;
                spread[0] = 0.0f;
                func_8008D660(&dir4, (Vec3f *) a, (Vec3f *) spread, ang, unit->id, 0xE, 0, 0x10,
                              unit->team, func_800E3460(unit) == 0);
                a[1] += a[3] / 10.0f;
                a[0] += a[2] / 10.0f;
                spread[1] = -a[3] / 200.0f;
                spread[0] = -a[2] / 200.0f;
                if (func_8008D660(&dir4, (Vec3f *) a, (Vec3f *) spread, ang, unit->id, 0xE, 0, 0x10,
                                  unit->team, func_800E3460(unit) == 0) >= 0) {
                    func_80085B4C(0xA, unit->x, unit->z);
                    weapon->lastTime = D_801B4AA8;
                    if (unit->isAi == 0) {
                        unit->flashTimer = 0xF0;
                    }
                    unit->lastFireTime = D_801B4AA8;
                }
                a[1] -= a[3] / 5.0f;
                a[0] -= a[2] / 5.0f;
                spread[1] = a[3] / 200.0f;
                spread[0] = a[2] / 200.0f;
                func_8008D660(&dir4, (Vec3f *) a, (Vec3f *) spread, angle4 & 0xFFFF, unit->id, 0xE, 0,
                              0x10, unit->team, func_800E3460(unit) == 0);
            }
            break;
        }
        case 5:
        case 10: {
            if (unit->kind == 1) {
                off5.x = 0.0f;
                off5.z = 19.0f;
                off5.y = 25.0f;
            } else {
                off5.x = 0.0f;
                off5.z = 45.0f;
                off5.y = 36.0f;
            }
            func_800A7D10(unit->turretMtx, &off5, &pos5);
            dir5.x = pos5.x;
            dir5.y = pos5.y;
            dir5.z = pos5.z;
            yaw = (u32) (unit->turretYaw * 182.04445f);
            isLocal5 = func_800E3460(unit) == 0;
            if (func_800F0FD8(&dir5, yaw & 0xFFFF, unit->id, weapon->kind == 5 ? 0x12 : 8, 0x26,
                              (unit->flags & 0x2000) ? 0x16 : 4, unit->team, isLocal5) == 0) {
                func_80085B4C(9, unit->x, unit->z);
                if (unit->isAi == 0) {
                    unit->flashTimer = 0xF0;
                }
                unit->lastFireTime = D_801B4AA8;
            }
            if (unit->flags & 0x2000) {
                unit->ammo[5] = 1;
            }
            break;
        }
        case 6:
        case 7: {
            off6.x = 0.0f;
            off6.z = 45.0f;
            off6.y = 36.0f;
            func_800A7D10(unit->turretMtx, &off6, &pos6);
            dir6.x = pos6.x;
            dir6.y = pos6.y;
            dir6.z = pos6.z;
            if (unit->turretFwdX < 0.0f) {
                angle6 = -func_800F3BE4(unit->turretFwdZ);
            } else {
                angle6 = func_800F3BE4(unit->turretFwdZ);
            }
            switch (weapon->kind) {
            case 6:
                if (func_800F29F0(&dir6, angle6 & 0xFFFF, unit->id, unit->team) >= 0) {
                    func_800796F0(0x2D, 0);
                }
                break;
            case 7:
                func_800F3344(&dir6, angle6 & 0xFFFF, unit->id, unit->team);
                break;
            }
            break;
        }
        case 12:
            if (unit->flags & 0x2000) {

                v[1] = -unit->hullFwdX * 100.0f;
                v[0] = -unit->hullFwdZ * 100.0f;
                v[2] = -v[1];
                v[3] = v[0];
                a[3] = unit->x;
                a[2] = unit->z;
                func_8010DED4((Vec3f *) &a[2], (Vec3f *) &v[0], (Vec3f *) &v[2], unit->id, 0, 0);
                unit->ammo[12] = 1;
            } else {

                b[1] = unit->x;
                b[0] = unit->z;
                if (func_8010DAA0((Vec3f *) b, unit->id) < 0) {
                    return;
                }
                func_80085B4C(0x19, unit->x, unit->z);
            }
            break;
        case 13: {
            off13 = sZeroOffset;

            if (unit->flags & 0x2000) {
                w[1] = -unit->hullFwdX * 100.0f;
                w[0] = -unit->hullFwdZ * 100.0f;
                w[2] = -w[1];
                w[3] = w[0];
                v[3] = unit->x;
                v[2] = unit->z;
                h1 = unit->heading * 182.04445f + 32768.0f;
                func_8010DED4((Vec3f *) &v[2], (Vec3f *) w, (Vec3f *) &w[2], unit->id,
                              (u32) h1 & 0xFFFF, 1);
                unit->ammo[13] = 1;
                break;
            }
            switch (unit->kind) {
            case 1:
                off13.z = -82.0f;
                break;
            case 0:
            case 2:
                off13.z = -145.0f;
                break;
            }
            func_800A7D10(unit->hullMtx, &off13, &pos13);
            a[3] = pos13.x;
            a[2] = pos13.z;
            v[1] = unit->x;
            v[0] = unit->z;
            player = func_800A6688(unit->id);
            h = unit->heading * 182.04445f + 32768.0f;
            if (func_800A1408(player->kind, unit->id, 0, (u32) h & 0xFFFF,
                              (Vec3f *) &a[2], (Vec3f *) v, unit, 0, 0) < 0) {
                return;
            }
            break;
        }
        case 14: {
            r = 90.0f;

            w[1] = 50.0f;
            w[0] = unit->x + r;
            w[2] = unit->z;
            func_800ED8C0((Vec3f *) w, 0x11);
            w[0] = unit->x - r;
            func_800ED8C0((Vec3f *) w, 0x11);
            w[2] = unit->z + r;
            w[0] = unit->x;
            func_800ED8C0((Vec3f *) w, 0x11);
            w[2] = unit->z - r;
            func_800ED8C0((Vec3f *) w, 0x11);
            unit->lastMineTime = D_801B4AA8;
            break;
        }
        case 15:
            if (unit->shieldEnd == 0) {
                unit->shieldEnd = D_801B4AA8 + 900;
            } else {
                unit->shieldEnd += 900;
            }
            unit->flashTimer = 0xF0;
            break;
        }
    done:
        weapon->lastTime = D_801B4AA8;
        if (D_80134E68 != 0) {
            if (weapon->kind >= 4) {
                unit->ammo[weapon->kind]--;
            }
        } else if (func_800E3460(unit) == 0) {
            if (weapon->kind >= 4
                || (D_80135760 == 0 && D_80134E69 == 0 && !(unit->flags & 0x40))) {
                unit->ammo[weapon->kind]--;
            }
        }
        if (unit->ammo[weapon->kind] == 0 && weapon->kind >= 4) {
            /* Weapon exhausted: advance to the next stocked special weapon. */
            unit->flags &= ~0x2000;
            kind = weapon->kind;
            next = kind + 1;
            if (next == 17) {
                next = 4;
            }
            while (unit->ammo[next] == 0) {
                if (next == kind) {
                    goto none;
                }
                next++;
                if (next == 17) {
                    next = 4;
                }
            }
            if (next == weapon->kind) {
            none:
                weapon->kind = 0;
            } else {
                weapon->kind = next;
            }
        }
    } else if ((unit->ammo[weapon->kind] == 0) & (trigger != 0)) {
        if (func_800E3460(unit) == 0) {
            func_80085B4C(0x20, unit->x, unit->z);
        }
    }
}
