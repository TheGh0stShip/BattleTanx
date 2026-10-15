#include "types.h"

typedef struct ModelView {
    u8 pad00[0x20];
    f32 z;
    f32 x;
    u8 pad28[4];
} ModelView;

typedef struct ModelSession {
    u8 pad000[0x57C];
    u8 (*frames)[8];
    u8 (*parts)[8];
    ModelView views[4];
} ModelSession;

typedef struct ModelRef {
    u32 frame;
    u32 part;
    u16 animation;
} ModelRef;

typedef struct ModelPosition {
    f32 x;
    f32 y;
    f32 z;
} ModelPosition;

extern s32 get_view_count(void) __asm__("func_8007AAA0");
extern s32 point_is_outside_view(f32 x, f32 z, ModelView *view) __asm__("func_800940AC");
extern s32 add_render_bucket_entry(void *frame, void *part, void *transform, s32 arg3,
                                   void *animation, s32 view, s32 layer) __asm__("func_80080728");
extern s32 gProximityRadiusSq __asm__("D_801C9174");
extern u32 gAnimationTime __asm__("D_801B4AA0");

void submit_model(ModelSession *session, ModelRef *model, void *transform,
                  ModelPosition *position, s32 phase) __asm__("func_80085978");

void submit_model(ModelSession *session, ModelRef *model, void *transform,
                  ModelPosition *position, s32 phase)
{
    s32 count;
    s32 i;
    u32 animation;
    u32 frame;
    u32 time;

    count = get_view_count();
    for (i = 0; i < count; i++) {
        f32 x = position->x;
        ModelView *view = &session->views[i];
        f32 z = position->z;
        f32 dx = view->x - x;
        f32 dz = view->z - z;
        s32 near = 0;

        if (dx * dx + dz * dz < (f32)gProximityRadiusSq) {
            near = 1;
        }
        if (!near) {
            continue;
        }
        if (point_is_outside_view(x, z, view) != 0) {
            continue;
        }
        animation = model->animation;
        if (animation == 0) {
            add_render_bucket_entry(session->frames[model->frame], session->parts[model->part],
                                    transform, 0, 0, i, 3);
        } else {
            if (phase >= 0) {
                frame = (animation & 0x7FF) + phase;
            } else {
                u32 period = animation >> 11;

                if (phase == -1) {
                    time = gAnimationTime;
                } else {
                    time = gAnimationTime >> 1;
                }
                frame = (animation & 0x7FF) + time % period;
            }
            add_render_bucket_entry(session->frames[model->frame], session->parts[model->part],
                                    transform, 0, session->frames[model->frame + frame], i, 3);
        }
    }
}
