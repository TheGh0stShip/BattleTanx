#include "types.h"
/* RODATA_VRAM 0x80072BE0 */
/* LDSYM D_80125FB0=0x80125FB0 */
/* LDSYM D_80126000=0x80126000 */
/* LDSYM D_80126018=0x80126018 */
/* LDSYM D_80126038=0x80126038 */
/* LDSYM D_801B4AA8=0x801B4AA8 */
/* LDSYM D_802D5A30=0x802D5A30 */
/* LDSYM func_800821C0=0x800821C0 */
/* LDSYM func_8008488C=0x8008488C */
/* LDSYM func_800849B0=0x800849B0 */
/* LDSYM func_80084CC4=0x80084CC4 */
/* LDSYM func_800A6688=0x800A6688 */
/* LDSYM func_800A7744=0x800A7744 */
/* LDSYM func_800A7F3C=0x800A7F3C */
/* LDSYM func_800A823C=0x800A823C */

typedef struct MarkerTransform {
    f32 m[4][4];
    s32 flag;
} MarkerTransform;

typedef struct MarkerVec3 {
    f32 x;
    f32 y;
    f32 z;
} MarkerVec3;

typedef struct CratePlayer {
    u8 pad000[0x1BF];
    u8 effectSlot;
    u8 pad1C0[0x180];
    s16 boostTime[8];
} CratePlayer;

typedef struct Crate {
    u8 pad00[0xC];
    u8 flags;
    u8 team;
    u8 pad0E[2];
    u8 pad10[2];
    u16 owner;
    u32 kind;
    u16 angle;
    u8 pad1A[2];
    f32 z;
    f32 x;
    u8 pad24[4];
    s32 boostStart;
    u8 pad2C[4];
    u8 squash;
} Crate;

extern CratePlayer *get_entity_record(u16 index) __asm__("func_800A6688");
extern void *get_spawn_session(void) __asm__("func_800821C0");
extern void set_yaw_transform(MarkerTransform *xf, f32 x, f32 y, f32 z, u16 angle) __asm__("func_800A7744");
extern void scale_transform(MarkerTransform *xf, f32 x, f32 y, f32 z) __asm__("func_800A823C");
extern u8 func_8008488C(void *session, f32 x, f32 z, f32 scale);
extern void func_800849B0(void *session, s16 id, MarkerTransform *transform, s32 mode, s32 frame, s32 shade);
extern void func_80084CC4(void *session, s16 id, MarkerTransform *transform, s32 zero, s32 mode, s32 frame,
                          f32 *position, f32 scale);
extern void matrix_multiply(f32 first[4][4], f32 second[4][4], f32 output[4][4]) __asm__("func_800A7F3C");
extern s32 D_80125FB0[];
extern s32 D_80126000[];
extern f32 D_80126018[];
extern f32 D_80126038[];
extern s16 D_802D5A30[];
extern s32 gGameTicks __asm__("D_801B4AA8");

void draw_bonus_crate(void *arg0) __asm__("func_800A0CE0");

void draw_bonus_crate(void *arg0) {
    Crate *crate = arg0;
    MarkerTransform transform = { { { 1.0f, 0.0f, 0.0f, 0.0f },
                                    { 0.0f, 1.0f, 0.0f, 0.0f },
                                    { 0.0f, 0.0f, 1.0f, 0.0f },
                                    { 0.0f, 0.0f, 0.0f, 1.0f } },
                                  0 };
    CratePlayer *player;
    void *session;
    u32 kind;
    f32 scale;
    f32 size;

    player = get_entity_record(crate->owner);
    if (crate->flags & 8) {
        return;
    }
    kind = crate->kind;
    session = get_spawn_session();
    scale = D_80126038[kind];
    if (crate->squash != 0) {
        set_yaw_transform(&transform, crate->x, 0.0f, crate->z, crate->angle + (crate->squash << 6));
        scale_transform(&transform, scale, scale * (256.0f - crate->squash) / 256.0f, scale);
        scale *= 80.0f;
        func_800849B0(session, D_802D5A30[D_80125FB0[kind]], &transform, 4, player->effectSlot,
                      func_8008488C(session, crate->x, crate->z, scale));
    } else {
        set_yaw_transform(&transform, crate->x, 0.0f, crate->z, crate->angle);
        scale_transform(&transform, scale, scale, scale);
        size = 80.0f;
        func_80084CC4(session, D_802D5A30[D_80125FB0[kind]], &transform, 0, 3, player->effectSlot, &crate->z,
                      scale * size);
        if (D_80126000[kind] != 0) {
            s32 start = crate->boostStart;
            s32 duration = player->boostTime[crate->kind];

            if (gGameTicks < start + duration) {
                f32 lift[4][4] = { { 1.0f, 0.0f, 0.0f, 0.0f },
                                   { 0.0f, 1.0f, 0.0f, 0.0f },
                                   { 0.0f, 0.0f, 1.0f, 0.0f },
                                   { 0.0f, 0.0f, 0.0f, 1.0f } };
                MarkerTransform lifted;

                lifted.flag = 0;
                lift[3][2] = -scale * D_80126018[kind] * (start + duration - gGameTicks) / duration;
                matrix_multiply(lift, transform.m, lifted.m);
                if (crate->flags & 2) {
                    size = scale * 80.0f;
                    func_80084CC4(session, D_802D5A30[D_80126000[kind]], &transform, 0, 3, player->effectSlot,
                                  &crate->z, size);
                    func_80084CC4(session, D_802D5A30[D_80126000[kind] + 1], &lifted, 0, 3, player->effectSlot,
                                  &crate->z, size);
                } else {
                    size = scale * 80.0f;
                    func_80084CC4(session, D_802D5A30[D_80126000[kind]], &lifted, 0, 3, player->effectSlot,
                                  &crate->z, size);
                    func_80084CC4(session, D_802D5A30[D_80126000[kind] + 1], &transform, 0, 3, player->effectSlot,
                                  &crate->z, size);
                }
            } else {
                func_80084CC4(session, D_802D5A30[D_80126000[kind]], &transform, 0, 3, player->effectSlot,
                              &crate->z, size);
                func_80084CC4(session, D_802D5A30[D_80126000[kind] + 1], &transform, 0, 3, player->effectSlot,
                              &crate->z, size);
            }
        }
    }
}
