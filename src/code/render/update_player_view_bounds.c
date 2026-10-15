#include "types.h"

typedef struct PlayerBounds {
    u8 pad00[0x18];
    u8 overhead;
    u8 pad19[7];
    f32 z;
    f32 x;
    u8 above;
    u8 pad29[3];
} PlayerBounds;

typedef struct BoundsSet {
    u8 pad000[0x584];
    PlayerBounds players[4];
} BoundsSet;

typedef struct CameraPose {
    u8 pad00[0x24];
    f32 atX;
    f32 atY;
    f32 atZ;
    f32 eyeX;
    f32 eyeY;
    f32 eyeZ;
} CameraPose;

extern f32 D_8012585C;
extern f32 D_800714AC;
extern f32 D_800714B0;
extern float sqrtf(float);
extern s32 get_difficulty_level(void) __asm__("func_8007AAA0");
extern void *get_entity_record(u16 index) __asm__("func_800A6688");
extern CameraPose *func_800A424C(void *record);
extern void init_effect_bounds(PlayerBounds *bounds, f32 x, f32 z, f32 dirZ, f32 dirX, f32 scale,
                               s32 player) __asm__("func_80094060");

void update_player_view_bounds(BoundsSet *set) __asm__("func_8008228C");

void update_player_view_bounds(BoundsSet *set)
{
    s32 count;
    s32 i;
    CameraPose *pose;
    f32 dx;
    f32 dz;
    f32 dy;
    f32 dist;

    count = get_difficulty_level();
    for (i = 0; i < count; i++) {
        pose = func_800A424C(get_entity_record(i));
        set->players[i].x = pose->eyeX;
        set->players[i].z = pose->eyeZ;
        dx = pose->atX - pose->eyeX;
        dz = pose->atZ - pose->eyeZ;
        dy = pose->atY - pose->eyeY;
        dist = sqrtf(dx * dx + dz * dz);
        if (dy < 0.0f ? dist < -dy : dist < dy) {
            set->players[i].overhead = 1;
        } else {
            init_effect_bounds(&set->players[i], pose->eyeX, pose->eyeZ, dz / dist, dx / dist,
                               (count != 3 || i != 0) ? D_8012585C : D_800714AC, i);
        }
        set->players[i].above = pose->eyeY > D_800714B0;
    }
}
