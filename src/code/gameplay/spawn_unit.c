#include "types.h"

/* RODATA_VRAM 0x80072150 */
/* LDSYM D_80125EF0=0x80125EF0 */
/* LDSYM D_80125EFC=0x80125EFC */
/* LDSYM D_80125F08=0x80125F08 */
/* LDSYM D_80125F18=0x80125F18 */
/* LDSYM D_80125F24=0x80125F24 */
/* LDSYM D_80125FA0=0x80125FA0 */
/* LDSYM D_801260A0=0x801260A0 */
/* LDSYM D_80135761=0x80135761 */
/* LDSYM D_80135765=0x80135765 */
/* LDSYM D_8013576A=0x8013576A */
/* LDSYM D_80135834=0x80135834 */
/* LDSYM D_801B4AA8=0x801B4AA8 */
/* LDSYM func_800A03B8=0x800A03B8 */
/* LDSYM func_800A6688=0x800A6688 */
/* LDSYM func_800A68C0=0x800A68C0 */
/* LDSYM func_8008AE18=0x8008AE18 */
/* LDSYM func_800EC700=0x800EC700 */
/* LDSYM func_800821C0=0x800821C0 */
/* LDSYM func_8007AAF4=0x8007AAF4 */
/* LDSYM func_8007C6D8=0x8007C6D8 */
/* LDSYM func_800F3BE4=0x800F3BE4 */
/* LDSYM func_80097C24=0x80097C24 */
/* LDSYM func_800A7650=0x800A7650 */
/* LDSYM func_800A7964=0x800A7964 */
/* LDSYM func_800A76A0=0x800A76A0 */
/* LDSYM func_80106D18=0x80106D18 */
/* LDSYM func_800E4104=0x800E4104 */
/* LDSYM func_8009A22C=0x8009A22C */
/* LDSYM sqrtf=0x8011D190 */



typedef struct Vec3 {
    f32 x;
    f32 y;
    f32 z;
} Vec3;

typedef struct UnitMatrix {
    s32 words[17];
} UnitMatrix;

typedef struct SpawnedUnit {
    u8 active;
    u8 visible;
    u8 enabled;
    u8 primary;
    u8 player;
    u8 team;
    u8 pad006[0x2];
    s32 value08;
    s32 value0C;
    s32 value10;
    u16 flags;
    u8 pad016[0x2];
    u32 kind;
    s32 health;
    s32 maxHealth;
    Vec3 pos;
    f32 value30;
    f32 heading;
    f32 value38;
    u8 pad03C[0x18];
    UnitMatrix matrix;
    s32 value98;
    u8 pad09C[0x2B4];
    u8 value350;
    u8 pad351[0x1F];
    u8 value370;
    u8 pad371[0x3];
    s32 value374;
    f32 value378;
    f32 value37C;
    f32 value380;
    f32 value384;
    f32 value388;
    u8 pad38C[0x8];
    f32 value394;
    u8 pad398[0x1C];
    s32 value3B4;
    f32 value3B8;
    f32 value3BC;
    f32 value3C0;
    f32 value3C4;
    s32 value3C8[10];
    s64 value3F0;
    f32 value3F8;
    f32 value3FC;
    f32 value400;
    u8 value404;
    u8 value405;
    u8 value406;
    u8 value407;
    u8 pad408[0x2];
    u8 value40A;
    u8 pad40B[0x1];
    UnitMatrix savedMatrix;
    s32 value450;
    s32 value454;
    s32 value458;
    s32 value45C;
    s32 value460;
    u8 value464;
    u8 pad465[0x3];
    s32 value468;
    s32 value46C;
    u8 pad470[0x4];
    s32 value474;
    s32 value478;
    u8 pad47C[0x4];
    s16 ammo[17];
    u8 pad4A2[0x2];
    s32 value4A4;
    f32 value4A8;
    u8 pad4AC[0x4];
    s32 value4B0;
    s32 value4B4;
    s32 value4B8;
    u8 pad4BC[0x14];
    f32 railX;
    f32 railZ;
    f32 railDirX;
    f32 railDirZ;
    f32 railLength;
    f32 railPos;
    s32 value4E8;
    s32 value4EC;
    s32 value4F0;
    s32 value4F4;
    u8 pad4F8[0x4];
    s32 value4FC;
    u8 pad500[0x4];
    void *effect;
} SpawnedUnit;

typedef struct UnitSpawn {
    u8 primary;
    u8 pad01;
    u16 player;
    Vec3 pos;
    u16 angle;
    u8 fromMarker;
    u8 pad13;
    u16 marker;
    u8 selectable;
    u8 pad17;
    s32 kind;
    u16 flags;
    u8 value1E;
    u8 pad1F;
} UnitSpawn;

typedef struct UnitEffect {
    u8 pad00[0xC];
    SpawnedUnit *unit;
    u8 pad10;
    u8 fromMarker;
    u16 marker;
} UnitEffect;

typedef struct OwnerRecord {
    u8 pad000[0xC];
    s32 controller;
    u8 pad010[0x6];
    u16 index;
    u8 pad018[0xA];
    u8 units;
    u8 flags23;
    u8 pad024[0x182];
    u8 local;
    u8 pad1A7[0x7];
    u8 team;
} OwnerRecord;

typedef struct ControllerInfo {
    u8 pad00[0x40];
    s32 weaponA;
    s32 weaponB;
} ControllerInfo;

typedef struct MarkerPoint {
    f32 x;
    f32 z;
    u16 heading;
    u16 turret;
} MarkerPoint;

typedef struct RailZone {
    u8 active;
    u8 pad01[0x3];
    f32 x0;
    f32 z0;
    f32 x1;
    f32 z1;
} RailZone;

typedef struct RailSession {
    u8 pad000[0xC8];
    RailZone zones[4];
} RailSession;

typedef struct GameModeInfo {
    u32 mode;
} GameModeInfo;

extern u8 D_801260A0[];
extern f32 D_80125EF0[3];
extern f32 D_80125EFC[3];
extern f32 D_80125F08[3];
extern f32 D_80125F18[3];
extern f32 D_80125F24[3];
extern s32 D_80125FA0;
extern s32 D_801B4AA8;
extern u8 D_80135761;
extern u8 D_80135765;
extern u8 D_8013576A;
extern s32 D_80135834;

extern SpawnedUnit *func_800A03B8(s16 index);
extern OwnerRecord *func_800A6688(u16 index);
extern ControllerInfo *func_800A68C0(s32 controller);
extern UnitEffect *func_8008AE18(s32 group, s32 kind, s32 arg2);
extern MarkerPoint *func_800EC700(u16 marker);
extern RailSession *func_800821C0(void);
extern GameModeInfo *get_game_mode(void) __asm__("func_8007AAF4");
extern s32 func_8007C6D8(void);
extern s32 func_800F3BE4(f32 x);
extern void func_80097C24(f32 *physics);
extern void func_800A7650(UnitMatrix *m);
extern void func_800A7964(UnitMatrix *m, f32 *rotation);
extern void func_800A76A0(UnitMatrix *m, Vec3 *pos);
extern s32 func_80106D18(void *effect, s32 x, s32 z, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7, s32 heading);
extern void func_800E4104(s16 unit, s32 hidden, s32 arg2);
extern void func_8009A22C(SpawnedUnit *unit, s32 weapon);
extern f32 sqrtf(f32 x);

s32 spawn_unit(s16 index, UnitSpawn *spawn) __asm__("func_80097038");

s32 spawn_unit(s16 index, UnitSpawn *spawn)
{
    SpawnedUnit *u;
    OwnerRecord *owner;
    ControllerInfo *info;
    UnitEffect *effect;
    MarkerPoint *point;
    RailSession *session;
    RailZone *zone;
    f32 dz;
    f32 dx;
    f32 len;
    s32 angle;
    u32 turret;
    s32 i;

    u = func_800A03B8(index);
    owner = func_800A6688(spawn->player);
    info = func_800A68C0(owner->controller);
    effect = func_8008AE18(1, 0, 0x14);
    if (effect == 0) {
        return -1;
    }
    u->effect = effect;
    effect->unit = u;
    effect->fromMarker = spawn->fromMarker;
    effect->marker = spawn->marker;
    u->value40A = 0x80;
    u->active = 1;
    u->visible = 1;
    u->enabled = 1;
    u->primary = spawn->primary;
    u->player = spawn->player;
    u->team = owner->team;
    u->kind = spawn->kind;
    u->flags = spawn->flags;
    u->value3F0 = 0;
    u->value370 = 0;
    u->value30 = u->value38 = 0.0f;
    if (effect->fromMarker) {
        point = func_800EC700(effect->marker);
        u->pos.x = point->x;
        u->pos.z = point->z;
        u->pos.y = 0.0f;
        u->value400 = u->heading = point->heading * (360.0 / 65536);
        u->value3FC = point->turret * (360.0 / 65536);
    } else {
        u->pos = spawn->pos;
        u->value3FC = u->heading = spawn->angle * (360.0 / 65536);
        u->value400 = u->heading;
    }
    u->value450 = 0;
    u->value3F8 = u->heading;
    if (u->kind == 2) {
        session = func_800821C0();
        if ((!u->primary || owner->local || get_game_mode()->mode == 7) &&
            session->zones[D_801260A0[u->player]].active != 0) {
            if (owner->flags23 & 2) {
            } else if (get_game_mode()->mode != 9 && get_game_mode()->mode != 2) {
                u->flags |= 0x804;
                owner->flags23 |= 2;
                u->railZ = session->zones[D_801260A0[u->player]].z0;
                u->railX = session->zones[D_801260A0[u->player]].x0;
                dz = session->zones[D_801260A0[u->player]].z1 - session->zones[D_801260A0[u->player]].z0;
                dx = session->zones[D_801260A0[u->player]].x1 - session->zones[D_801260A0[u->player]].x0;
                len = sqrtf(dz * dz + dx * dx);
                u->railDirZ = dz / len;
                u->railDirX = dx / len;
                u->railLength = len;
                u->railPos = (u->pos.x - u->railZ) * u->railDirZ + (u->pos.z - u->railX) * u->railDirX;
                if (u->railPos < 0.0f) {
                    u->railPos = 0.0f;
                }
                if (u->railPos > u->railLength) {
                    u->railPos = u->railLength;
                }
                u->pos.x = u->railZ + u->railPos * u->railDirZ;
                u->pos.z = u->railX + u->railPos * u->railDirX;
                if (u->railDirZ < 0.0f) {
                    angle = -func_800F3BE4(u->railDirX);
                } else {
                    angle = func_800F3BE4(u->railDirX);
                }
                u->value3FC = u->heading = ((u16)angle + 0xC000) * (360.0 / 65536);
                u->value400 = u->heading;
                u->value3F8 = u->heading;
                u->value4E8 = 0;
                u->value4EC = 0;
                u->value4F0 = -1;
            }
        }
    }
    u->value3C8[0] = 0;
    u->value3C8[1] = 0;
    u->value3C8[2] = 0;
    u->value3C8[3] = 0;
    u->value3C8[4] = 0;
    u->value3C8[5] = 0;
    u->value3C8[6] = 0;
    u->value3C8[7] = 0;
    u->value3C8[8] = 0;
    u->value3C8[9] = 0;
    u->value3B4 = 0;
    func_80097C24(&u->value378);
    switch (u->kind) {
    case 1:
        u->maxHealth = 30;
        u->value3B8 = D_80125F18[0];
        u->value378 = 1.0f / D_80125F24[0];
        u->value37C = 1.0f / (D_80125F24[0] / 12.0f * 6554.0f);
        u->value380 = 1.0f;
        u->value3BC = D_80125EFC[0];
        u->value3C0 = D_80125EF0[0];
        u->value3C4 = D_80125F08[0];
        break;
    case 0:
        u->maxHealth = 100;
        u->value3B8 = D_80125F18[1];
        u->value378 = 1.0f / D_80125F24[1];
        u->value37C = 1.0f / (D_80125F24[1] / 12.0f * 6554.0f);
        u->value380 = 1.0f;
        u->value3BC = D_80125EFC[1];
        u->value3C0 = D_80125EF0[1];
        u->value3C4 = D_80125F08[1];
        break;
    case 2:
        u->maxHealth = 200;
        u->value3B8 = D_80125F18[2];
        u->value378 = 1.0f / D_80125F24[2];
        u->value37C = 1.0f / (D_80125F24[2] / 12.0f * 6554.0f);
        u->value380 = 1.0f;
        u->value3BC = D_80125EFC[2];
        u->value3C0 = D_80125EF0[2];
        u->value3C4 = D_80125F08[2];
        break;
    }
    if (owner->local && func_8007C6D8() && u->kind == 2) {
        if (u->flags & 4) {
            u->maxHealth = u->maxHealth * 2;
        } else {
            u->maxHealth = u->maxHealth + (u->maxHealth >> 1);
        }
    }
    u->health = u->maxHealth;
    u->value4B0 = -1000;
    u->value4B4 = -1000;
    u->value4B8 = -1000;
    u->value454 = 0;
    u->value460 = -1;
    u->value458 = -1;
    u->value45C = -1;
    u->value464 = 0;
    u->value406 = 0;
    u->value407 = 0;
    u->value404 = 0;
    u->value405 = 0;
    func_800A7650(&u->matrix);
    func_800A7964(&u->matrix, &u->value30);
    func_800A76A0(&u->matrix, &u->pos);
    u->matrix.words[16] = 0;
    u->savedMatrix = u->matrix;
    u->value474 = 0;
    u->value478 = -1000;
    u->value384 = u->pos.x;
    u->value388 = u->pos.z;
    u->value394 = u->heading;
    for (i = 0; i < 17; i++) {
        u->ammo[i] = 0;
    }
    if (D_80135765 != 0) {
        s32 ammo50 = 50;
        u->value474 = 5;
        u->ammo[6] = 1;
        u->ammo[12] = 60;
        u->ammo[13] = 3;
        u->ammo[11] = u->ammo[4] = u->ammo[5] = ammo50;
        u->ammo[7] = 99;
    }
    u->value0C = 0;
    if (D_8013576A != 0 && u->primary && u->player == 0) {
        u->value0C = 1000000;
    }
    u->value10 = 0;
    u->value4A8 = 1.0f;
    turret = u->value400 * 182.04444444;
    switch (u->kind) {
    case 1:
        u->value468 = 2;
        u->value46C = -1000;
        u->ammo[2] = 150;
        u->value4A4 = func_80106D18(u->effect, u->pos.x, u->pos.z, -0x1A, 0x1A, -0x26, 0x1A, 0x4D6, turret & 0xFFFF);
        u->value98 = 0;
        break;
    case 0:
        u->value468 = 1;
        u->value46C = -1000;
        u->ammo[1] = 70;
        u->value4A4 = func_80106D18(u->effect, u->pos.x, u->pos.z, -0x23, 0x23, -0x49, 0x51, 0x4D6, turret & 0xFFFF);
        u->value98 = 0;
        break;
    case 2:
        u->value468 = 3;
        u->value46C = -1000;
        u->ammo[3] = 70;
        u->value4A4 = func_80106D18(u->effect, u->pos.x, u->pos.z, -0x3C, 0x3C, -0x4B, 0x51, 0x4D6, turret & 0xFFFF);
        u->value98 = 0;
        break;
    default:
        u->value98 = 0;
        break;
    }
    u->value4FC = 0;
    if (effect->fromMarker == 0 && D_80135834 != 0) {
        func_800E4104(index, spawn->selectable == 0, spawn->value1E);
    } else {
        u->value350 = 0;
        u->value40A = 0x10;
    }
    if (D_80125FA0 == 0) {
        D_80125FA0 = 1;
    }
    if (u->flags & 0x1000) {
        u->value08 = 0;
        u->value0C = D_801B4AA8 + 60;
    }
    if (D_80135761 != 0) {
        u->flags |= 0x80;
    }
    u->value374 = info->weaponA;
    switch (get_game_mode()->mode) {
    case 3:
    case 4:
    case 5:
    case 6:
        if (owner->index == 0 && owner->controller != 9) {
            func_8009A22C(u, info->weaponA);
            func_8009A22C(u, info->weaponB);
        }
        break;
    case 0:
    case 1:
    case 2:
    case 9:
        if ((owner->flags23 & 4) && !(u->flags & 0x100)) {
            owner->flags23 &= ~4;
        } else {
            func_8009A22C(u, info->weaponA);
            func_8009A22C(u, info->weaponB);
        }
        break;
    }
    u->value4F4 = 0;
    owner->units++;
    return 0;
}
