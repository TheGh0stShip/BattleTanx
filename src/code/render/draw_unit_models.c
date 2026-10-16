#include "types.h"
/* RODATA_VRAM 0x80072800 */

typedef struct MarkerTransform {
    f32 m[4][4];
    s32 flag;
} MarkerTransform;

typedef struct ChainLink {
    u8 pad00[0x2C];
    struct ChainLink *next;
} ChainLink;

typedef struct UnitOwner {
    u8 pad000[0xC];
    s32 team;
    u8 pad010[6];
    u16 slot;
    u8 pad018[0x2C];
    u16 busy;
    u8 pad046[0xA6];
    s32 target;
    u8 active;
    u8 pad0F1[0xCB];
    u8 colorR;
    u8 colorG;
    u8 colorB;
    u8 effectSlot;
} UnitOwner;

typedef struct TeamRecord {
    u8 pad00[0x3D];
    u8 emblem;
} TeamRecord;

typedef struct Unit {
    u8 pad000[4];
    u8 owner;
    u8 pad005[3];
    s32 fade;
    s32 visible;
    s32 cloaked;
    u16 flags;
    u8 pad016[2];
    u32 kind;
    s32 health;
    s32 maxHealth;
    f32 x;
    f32 y;
    f32 z;
    u8 pad030[0x24];
    f32 body[4][4];
    s32 value94;
    ChainLink *chain;
    u8 pad09C[0x2D4];
    s8 shadeMask;
    u8 pad371[0x95];
    u8 frame406;
    u8 frame407;
    u8 pad408[4];
    f32 turret[4][4];
} UnitHead;

typedef struct UnitTail {
    u8 pad000[0x44C];
    s32 value44C;
    s32 stamp;
    u8 pad454[0x14];
    s32 liftKind;
    s32 liftStart;
    u8 liftFlags;
    u8 pad471[0x93];
    s32 target;
} UnitTail;

extern UnitOwner *get_entity_record(u16 index) __asm__("func_800A6688");
extern TeamRecord *get_entity_info(s32 id) __asm__("func_800A68C0");
extern void *get_spawn_state(void) __asm__("func_800821C0");
extern s32 slots_near_quad_outside_mask(void *spawn, f32 *quad) __asm__("func_80084778");
extern void set_yaw_transform(MarkerTransform *xf, f32 x, f32 y, f32 z, u16 angle) __asm__("func_800A7744");
extern void matrix_multiply(f32 first[4][4], f32 second[4][4], f32 output[4][4]) __asm__("func_800A7F3C");
extern void handle_level_point_for_mask(void *spawn, s32 id, void *transform, s32 mode, s32 frame, u8 mask) __asm__("func_800849B0");
extern void submit_model_group(void *spawn, s32 index, void *transform, s32 layer, s32 phase, u8 mask, s32 arg6,
                               s32 arg7, void *frameOverride) __asm__("func_80082AA8");
extern void place_group_corner_shapes(void *spawn, s32 group, f32 *position, f32 scale, f32 arg4, u16 arg5,
                                      s32 arg6, s32 arg7, s32 arg8, u8 mask) __asm__("func_800830DC");
extern s32 get_view_count(void) __asm__("func_8007AAA0");
extern s32 game_mode_is_3_through_6(void) __asm__("func_8007C6D8");
extern s32 audio_restarts_disabled(void) __asm__("func_800EC644");

extern u32 gFrameCounter __asm__("D_801B4AA0");
extern s32 gGameTicks __asm__("D_801B4AA8");
extern u8 D_80135776;
extern u8 D_80125EC0[];
extern u8 D_80125808[];
extern s16 D_802D5A30[];

void draw_unit_models(void *arg0) __asm__("func_8009D4DC");

#define U(p) ((UnitHead *)(p))
#define T(p) ((UnitTail *)(p))

void draw_unit_models(void *arg0) {
    s32 layer = 1;
    UnitOwner *owner;
    TeamRecord *team;
    void *spawn;
    s32 *override = 0;
    s32 overrideCount = 0;
    u8 *overrideTable = 0;
    u32 effect;
    s32 ghost = 0;
    s8 mask;
    f32 quad[4][2];
    s32 dl[2];
    f32 pos[3];
    s32 id;

    owner = get_entity_record(U(arg0)->owner);
    team = get_entity_info(owner->team);
    effect = owner->effectSlot;
    if (T(arg0)->stamp != gFrameCounter) {
        U(arg0)->value94 = 0;
        T(arg0)->value44C = 0;
        T(arg0)->stamp = gFrameCounter;
    }
    quad[0][1] = U(arg0)->x - 80.0f;
    quad[0][0] = U(arg0)->z - 80.0f;
    quad[1][1] = U(arg0)->x - 80.0f;
    quad[1][0] = U(arg0)->z + 80.0f;
    quad[2][1] = U(arg0)->x + 80.0f;
    quad[2][0] = U(arg0)->z + 80.0f;
    quad[3][1] = U(arg0)->x + 80.0f;
    quad[3][0] = U(arg0)->z - 80.0f;
    spawn = get_spawn_state();
    mask = slots_near_quad_outside_mask(spawn, quad[0]);
    U(arg0)->shadeMask = mask;
    if (U(arg0)->visible != 0 && (U(arg0)->chain == 0 || U(arg0)->cloaked != 0)) {
        ghost = 1;
    }
    if (U(arg0)->chain != 0) {
        ChainLink *link = U(arg0)->chain;
        s8 linkMask = mask & ~(1 << U(arg0)->owner);

        switch (U(arg0)->kind) {
        case 1:
            pos[0] = U(arg0)->x + 0.0f;
            pos[1] = U(arg0)->y + 50.0f;
            pos[2] = U(arg0)->z + 0.0f;
            break;
        case 0:
            pos[0] = U(arg0)->x + 0.0f;
            pos[1] = U(arg0)->y + 50.0f;
            pos[2] = U(arg0)->z + 0.0f;
            break;
        case 2:
            pos[0] = U(arg0)->x + 0.0f;
            pos[1] = U(arg0)->y + 100.0f;
            pos[2] = U(arg0)->z + 0.0f;
            break;
        }
        while (link != 0) {
            {
                if (D_80135776 != 0) {
                    MarkerTransform xf = { { { 1.0f, 0.0f, 0.0f, 0.0f },
                                             { 0.0f, 1.0f, 0.0f, 0.0f },
                                             { 0.0f, 0.0f, 1.0f, 0.0f },
                                             { 0.0f, 0.0f, 0.0f, 1.0f } },
                                           0 };

                    set_yaw_transform(&xf, pos[0], pos[1], pos[2], (gFrameCounter % 30) * 0x888);
                    handle_level_point_for_mask(spawn, D_802D5A30[0x18], &xf, 0, 0, linkMask);
                } else {
                    place_group_corner_shapes(spawn, D_802D5A30[0x3E], pos, 1.0f, 1.0f, 0, 0, 0, 0, linkMask);
                }
                pos[2] += -20.0;
                link = link->next;
            }
        }
    }
    if (ghost) {
        if (U(arg0)->fade != 0) {
            dl[0] = 0xFA000000;
            dl[1] = (owner->colorR << 24) | (owner->colorG << 16) | (owner->colorB << 8) | ((u8 *)arg0)[0xB];
        } else if (U(arg0)->owner < get_view_count()) {
            dl[0] = 0xFA000000;
            dl[1] = (owner->colorR << 24) | (owner->colorG << 16) | (owner->colorB << 8) | 0x18;
            mask = 1 << U(arg0)->owner;
        } else {
            return;
        }
        override = dl;
        overrideCount = 1;
        overrideTable = D_80125808;
        layer = 4;
    }
    switch (U(arg0)->kind) {
    case 1:
        if (!ghost) {
            handle_level_point_for_mask(spawn, D_802D5A30[0x53], U(arg0)->body, 5, 0, mask);
        }
        if (U(arg0)->maxHealth / 2 < U(arg0)->health) {
            if ((team->emblem != 0xFF) & !ghost) {
                handle_level_point_for_mask(spawn, D_802D5A30[0x6D + team->emblem], U(arg0)->body, 2, 0, mask);
            }
            submit_model_group(spawn, D_802D5A30[0x1A], U(arg0)->body, layer, U(arg0)->frame406 >> 4, mask,
                               (s32)override, overrideCount, overrideTable);
            submit_model_group(spawn, D_802D5A30[0x1B], U(arg0)->body, layer, U(arg0)->frame407 >> 4, mask,
                               (s32)override, overrideCount, overrideTable);
            submit_model_group(spawn, D_802D5A30[0x19], U(arg0)->body, layer, effect, mask, (s32)override,
                               overrideCount, overrideTable);
            {
                s32 start = T(arg0)->liftStart;
                s32 duration = D_80125EC0[T(arg0)->liftKind];

                if (gGameTicks < start + duration) {
                    f32 lift[4][4] = { { 1.0f, 0.0f, 0.0f, 0.0f },
                                       { 0.0f, 1.0f, 0.0f, 0.0f },
                                       { 0.0f, 0.0f, 1.0f, 0.0f },
                                       { 0.0f, 0.0f, 0.0f, 1.0f } };
                    MarkerTransform lifted;

                    lifted.flag = 0;
                    lift[3][2] = (start + duration - gGameTicks) * -10.0f / duration;
                    matrix_multiply(lift, U(arg0)->body, lifted.m);
                    if (T(arg0)->liftFlags & 1) {
                        submit_model_group(spawn, D_802D5A30[0x1C], U(arg0)->body, layer, effect, mask,
                                           (s32)override, overrideCount, overrideTable);
                        submit_model_group(spawn, D_802D5A30[0x1D], &lifted, layer, effect, mask,
                                           (s32)override, overrideCount, overrideTable);
                    } else {
                        submit_model_group(spawn, D_802D5A30[0x1D], U(arg0)->body, layer, effect, mask,
                                           (s32)override, overrideCount, overrideTable);
                        submit_model_group(spawn, D_802D5A30[0x1C], &lifted, layer, effect, mask,
                                           (s32)override, overrideCount, overrideTable);
                    }
                } else {
                    submit_model_group(spawn, D_802D5A30[0x1C], U(arg0)->body, layer, effect, mask,
                                       (s32)override, overrideCount, overrideTable);
                    submit_model_group(spawn, D_802D5A30[0x1D], U(arg0)->body, layer, effect, mask,
                                       (s32)override, overrideCount, overrideTable);
                }
            }
        } else if (U(arg0)->health > 0) {
            if ((team->emblem != 0xFF) & !ghost) {
                handle_level_point_for_mask(spawn, D_802D5A30[0x95 + team->emblem], U(arg0)->body, 2, 0, mask);
            }
            submit_model_group(spawn, D_802D5A30[0x1A], U(arg0)->body, layer, U(arg0)->frame406 >> 4, mask,
                               (s32)override, overrideCount, overrideTable);
            submit_model_group(spawn, D_802D5A30[0x1B], U(arg0)->body, layer, U(arg0)->frame407 >> 4, mask,
                               (s32)override, overrideCount, overrideTable);
            submit_model_group(spawn, D_802D5A30[0x21], U(arg0)->body, layer, effect, mask, (s32)override,
                               overrideCount, overrideTable);
            submit_model_group(spawn, D_802D5A30[0x22], U(arg0)->body, layer, effect, mask, (s32)override,
                               overrideCount, overrideTable);
            submit_model_group(spawn, D_802D5A30[0x1E], U(arg0)->body, layer, effect, mask, (s32)override,
                               overrideCount, overrideTable);
        }
        return;
    case 2:
        if (!ghost) {
            f32 at[3];

            handle_level_point_for_mask(spawn, D_802D5A30[0x54], U(arg0)->body, 5, 0, mask);
            at[0] = U(arg0)->x + 0.0f;
            at[1] = U(arg0)->y + 100.0f;
            at[2] = U(arg0)->z + 0.0f;
            if (game_mode_is_3_through_6() != 0 && U(arg0)->owner != 0 && (U(arg0)->flags & 4)) {
                place_group_corner_shapes(spawn, D_802D5A30[0x61], at, 1.0f, 1.0f, 0, 0, 0, 0, mask);
                place_group_corner_shapes(spawn, D_802D5A30[0x62], at,
                                          (f32)U(arg0)->health / (f32)U(arg0)->maxHealth, 1.0f, 0, 0, 0, 0, mask);
            }
        }
        if (U(arg0)->maxHealth / 2 < U(arg0)->health) {
            s8 m;

            if ((team->emblem != 0xFF) & !ghost) {
                handle_level_point_for_mask(spawn, D_802D5A30[0x77 + team->emblem], U(arg0)->turret, 2, 0, mask);
            }
            submit_model_group(spawn, D_802D5A30[0x29], U(arg0)->turret, layer, effect, mask, (s32)override,
                               overrideCount, overrideTable);
            m = mask;
            if (owner->target == T(arg0)->target && owner->active != 0 && owner->busy == 0) {
                m = mask & ~(1 << owner->slot);
            }
            submit_model_group(spawn, D_802D5A30[0x27], U(arg0)->body, layer, U(arg0)->frame406 >> 4, m,
                               (s32)override, overrideCount, overrideTable);
            submit_model_group(spawn, D_802D5A30[0x28], U(arg0)->body, layer, U(arg0)->frame407 >> 4, m,
                               (s32)override, overrideCount, overrideTable);
            submit_model_group(spawn, D_802D5A30[0x2A], U(arg0)->body, layer, effect, m, (s32)override,
                               overrideCount, overrideTable);
        } else if (U(arg0)->health > 0) {
            s8 m;

            submit_model_group(spawn, D_802D5A30[0x2D], U(arg0)->turret, layer, effect, mask, (s32)override,
                               overrideCount, overrideTable);
            m = mask;
            if (owner->target == T(arg0)->target && owner->active != 0 && owner->busy == 0) {
                m = mask & ~(1 << owner->slot);
            }
            submit_model_group(spawn, D_802D5A30[0x2B], U(arg0)->body, layer, U(arg0)->frame406 >> 4, m,
                               (s32)override, overrideCount, overrideTable);
            submit_model_group(spawn, D_802D5A30[0x2C], U(arg0)->body, layer, U(arg0)->frame407 >> 4, m,
                               (s32)override, overrideCount, overrideTable);
            submit_model_group(spawn, D_802D5A30[0x2E], U(arg0)->body, layer, effect, m, (s32)override,
                               overrideCount, overrideTable);
        }
        break;
    default:
        if (!ghost) {
            handle_level_point_for_mask(spawn, D_802D5A30[0x52], U(arg0)->body, 5, 0, mask);
        }
        if (U(arg0)->maxHealth / 2 < U(arg0)->health) {
            if ((team->emblem != 0xFF) & !ghost) {
                handle_level_point_for_mask(spawn, D_802D5A30[0x81 + team->emblem], U(arg0)->turret, 2, 0, mask);
                handle_level_point_for_mask(spawn, D_802D5A30[0x63 + team->emblem], U(arg0)->body, 2, 0, mask);
            }
            submit_model_group(spawn, D_802D5A30[0xB], U(arg0)->body, layer, U(arg0)->frame406 >> 4, mask,
                               (s32)override, overrideCount, overrideTable);
            submit_model_group(spawn, D_802D5A30[0xC], U(arg0)->body, layer, U(arg0)->frame407 >> 4, mask,
                               (s32)override, overrideCount, overrideTable);
            submit_model_group(spawn, D_802D5A30[0xD], U(arg0)->turret, layer, effect, mask, (s32)override,
                               overrideCount, overrideTable);
            submit_model_group(spawn, D_802D5A30[0xE], U(arg0)->body, layer, effect, mask, (s32)override,
                               overrideCount, overrideTable);
        } else if (U(arg0)->health > 0) {
            if ((team->emblem != 0xFF) & !ghost) {
                handle_level_point_for_mask(spawn, D_802D5A30[0xA9 + team->emblem], U(arg0)->turret, 2, 0, mask);
                handle_level_point_for_mask(spawn, D_802D5A30[0x8B + team->emblem], U(arg0)->body, 2, 0, mask);
            }
            submit_model_group(spawn, D_802D5A30[0xB], U(arg0)->body, layer, U(arg0)->frame406 >> 4, mask,
                               (s32)override, overrideCount, overrideTable);
            submit_model_group(spawn, D_802D5A30[0xC], U(arg0)->body, layer, U(arg0)->frame407 >> 4, mask,
                               (s32)override, overrideCount, overrideTable);
            submit_model_group(spawn, D_802D5A30[0x13], U(arg0)->turret, layer, effect, mask, (s32)override,
                               overrideCount, overrideTable);
            submit_model_group(spawn, D_802D5A30[0x14], U(arg0)->body, layer, effect, mask, (s32)override,
                               overrideCount, overrideTable);
        }
        if (audio_restarts_disabled() != 0) {
            handle_level_point_for_mask(spawn, D_802D5A30[0xB5], U(arg0)->turret, 1, 0, mask);
            handle_level_point_for_mask(spawn, D_802D5A30[0xB4], U(arg0)->body, 1, 0, mask);
        }
        break;
    }
}
