#include "types.h"

typedef struct ModelGroupRef {
    u8 lodMode;
    u8 pad01;
    u16 group;
    u8 pad04[0x8];
} ModelGroupRef;

typedef struct ModelGroup {
    u8 count;
    u8 pad01;
    u16 first;
} ModelGroup;

typedef struct ModelPart {
    u32 frame;
    u32 part;
    u16 animation;
    u8 pad0A[0x2];
} ModelPart;

typedef struct ModelEye {
    f32 z;
    f32 x;
    u8 pad08[0x24];
} ModelEye;

typedef struct ModelSession {
    u8 pad000[0x570];
    ModelGroupRef *refs;
    ModelGroup *groups;
    ModelPart *modelParts;
    u8 (*frames)[8];
    u8 (*parts)[8];
    u8 pad584[0x20];
    ModelEye eyes[4];
} ModelSession;

typedef struct ModelTransform {
    u8 pad00[0x30];
    f32 z;
    u8 pad34[0x4];
    f32 x;
} ModelTransform;

typedef struct ModelAnchor {
    u8 pad00[0x18];
    s32 z;
    s32 x;
} ModelAnchor;

extern void *func_8008067C(s32 arg0, s32 arg1, void *part);
extern s32 add_render_bucket_entry(void *frame, void *part, void *transform, void *anchor,
                                   void *animation, s32 view, s32 layer) __asm__("func_80080728");
extern u32 gAnimationTime __asm__("D_801B4AA0");

void submit_masked_model_group(ModelSession *session, s32 index, ModelTransform *transform, ModelAnchor *anchor,
                               s32 layer, s32 phase, s32 arg6, s32 arg7, s32 mask) __asm__("func_80082D60");

static inline u32 model_part_frame(u32 animation, s32 phase)
{
    u32 frame;

    if (phase >= 0) {
        frame = (animation & 0x7FF) + phase;
    } else if (phase == -1) {
        frame = (animation & 0x7FF) + gAnimationTime % (animation >> 11);
    } else {
        frame = (animation & 0x7FF) + (gAnimationTime >> 1) % (animation >> 11);
    }
    return frame;
}

void submit_masked_model_group(ModelSession *session, s32 index, ModelTransform *transform, ModelAnchor *anchor,
                               s32 layer, s32 phase, s32 arg6, s32 arg7, s32 mask)
{
    ModelGroupRef *ref;
    ModelGroup *group;
    ModelPart *modelPart;
    f32 pos[2];
    void *part;
    s32 i;
    s32 j;
    u32 animation;
    u32 frame;
    u32 time;

    if (index == -1) {
        return;
    }
    ref = &session->refs[index];
    if (transform != 0) {
        pos[1] = transform->z;
        pos[0] = transform->x;
    } else {
        pos[1] = anchor->z / 65536.0f;
        pos[0] = anchor->x / 65536.0f;
    }
    group = &session->groups[ref->group];
    if (arg7 > 0) {
        for (j = 0; j < group->count; j++) {
            modelPart = &session->modelParts[group->first + j];
            part = func_8008067C(arg6, arg7, session->parts[modelPart->part]);
            for (i = 0; i < 4; i++) {
                if ((mask >> i) & 1) {
                    modelPart = &session->modelParts[group->first + j];
                    animation = modelPart->animation;
                    if (animation == 0) {
                        add_render_bucket_entry(session->frames[modelPart->frame], part, transform, anchor, 0, i,
                                                layer);
                    } else {
                        frame = model_part_frame(animation, phase);
                        add_render_bucket_entry(session->frames[modelPart->frame], part, transform, anchor,
                                                session->frames[modelPart->frame + frame], i, layer);
                    }
                }
            }
        }
    } else {
        for (i = 0; i < 4; i++) {
            if ((mask >> i) & 1) {
                for (j = 0; j < 1; j++) {
                    modelPart = &session->modelParts[group->first + j];
                    animation = modelPart->animation;
                    if (animation == 0) {
                        add_render_bucket_entry(session->frames[modelPart->frame], session->parts[modelPart->part],
                                                transform, anchor, 0, i, layer);
                    } else {
                        frame = model_part_frame(animation, phase);
                        add_render_bucket_entry(session->frames[modelPart->frame], session->parts[modelPart->part],
                                                transform, anchor, session->frames[modelPart->frame + frame], i,
                                                layer);
                    }
                }
            }
        }
    }
}
