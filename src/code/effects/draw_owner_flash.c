#include "types.h"

typedef struct ParticleColor {
    u8 red;
    u8 green;
    u8 blue;
    u8 alpha;
} ParticleColor;

typedef struct ParticleGfx {
    u32 w0;
    u32 w1;
} ParticleGfx;

typedef struct FlashMatrix {
    f32 m[16];
    s32 flag;
} FlashMatrix;

typedef struct FlashOwner {
    u8 pad00[4];
    s32 serial;
    s32 handlerIndex;
} FlashOwner;

typedef struct OwnerFlash {
    u8 pad00[0xC];
    f32 position[3];
    u16 angle;
    u8 pad1A[2];
    FlashOwner *owner;
    s32 serial;
    s32 frame;
} OwnerFlash;

typedef void (*FlashHandler)(FlashOwner *owner, OwnerFlash *flash, s32 kind, s32 arg3, f32 *offset);

typedef struct FlashHandlerEntry {
    u8 pad00[4];
    FlashHandler handle;
    u8 pad08[4];
} FlashHandlerEntry;

extern FlashHandlerEntry D_802C3800[];
extern s16 D_802D5AB6;
extern ParticleColor D_80139600;
extern ParticleColor D_80139604;
extern ParticleColor D_80139608;

extern void lerp_color(ParticleColor *out, ParticleColor *from, ParticleColor *to, f32 t) __asm__("func_800AB24C");
extern void load_render_translation(FlashMatrix *matrix, f32 *vector) __asm__("func_800A76A0");
extern void build_render_rotation(FlashMatrix *target, f32 *matrix, u16 angle) __asm__("func_800A82B8");
extern void apply_render_matrix(f32 *matrix, FlashMatrix *target, u16 angle) __asm__("func_800A841C");
extern void scale_matrix_axes(FlashMatrix *matrix, f32 x, f32 y, f32 z) __asm__("func_800A823C");
extern s32 get_spawn_session(void) __asm__("func_800821C0");
extern void dispatch_nearby_sector_mask(s32 table, s32 a1, FlashMatrix *a2, s32 a3, s32 a4, s32 a5,
                                        ParticleGfx *a6, s32 a7, f32 *pos, f32 radius) __asm__("func_80084DF4");

void draw_owner_flash(OwnerFlash *flash) __asm__("func_800F26B4");

void draw_owner_flash(OwnerFlash *flash) {
    f32 point[2];
    f32 position[3];
    ParticleColor primary;
    ParticleColor environment;
    f32 offset[3];
    FlashMatrix transform = { { 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
                                0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f }, 0 };
    f32 rotation[16];
    ParticleGfx gfx[2];
    f32 t;
    f32 scale;
    OwnerFlash *self;
    s32 session;

    self = flash;
    if (self->serial != self->owner->serial) {
        self->frame = 16;
        return;
    }
    transform.flag = 0;
    if (D_802C3800[self->owner->handlerIndex].handle != 0) {
        D_802C3800[self->owner->handlerIndex].handle(self->owner, self, 6, 0, offset);
    }
    position[0] = offset[0] + self->position[0];
    position[1] = offset[1] + self->position[1];
    position[2] = offset[2] + self->position[2];
    if (self->frame >= 7) {
        t = (self->frame - 6) / 10.0f;
        scale = (1.0f - t) * 48.0f;
        lerp_color(&primary, &D_80139604, &D_80139608, t);
        lerp_color(&environment, &D_80139604, &D_80139608, t);
    } else {
        t = self->frame / 6.0f;
        scale = t * 48.0f;
        lerp_color(&primary, &D_80139600, &D_80139604, t);
        lerp_color(&environment, &D_80139600, &D_80139604, t);
    }
    load_render_translation(&transform, position);
    build_render_rotation(&transform, rotation, self->frame * 1820.4445f);
    apply_render_matrix(rotation, &transform, self->angle);
    scale_matrix_axes(&transform, scale, scale, scale);
    session = get_spawn_session();
    point[1] = position[0];
    point[0] = position[2];
    gfx[0].w0 = 0xFA000000;
    gfx[0].w1 = (environment.red << 24) | (environment.green << 16) | (environment.blue << 8) | environment.alpha;
    gfx[1].w0 = 0xFB000000;
    gfx[1].w1 = (primary.red << 24) | (primary.green << 16) | (primary.blue << 8) | primary.alpha;
    dispatch_nearby_sector_mask(session, D_802D5AB6, &transform, 0, 4, 0, gfx, 2, point, scale);
    self->frame++;
}
