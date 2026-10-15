#include "types.h"

typedef struct ModelGroupRef {
    u8 pad00[0x2];
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

typedef struct ModelSession {
    u8 pad000[0x570];
    ModelGroupRef *refs;
    ModelGroup *groups;
    ModelPart *modelParts;
    u8 (*frames)[8];
    u8 (*parts)[8];
} ModelSession;

extern s32 get_view_count(void) __asm__("func_8007AAA0");
extern void *func_8008067C(s32 arg0, s32 arg1, void *part);
extern s32 add_render_bucket_entry(void *frame, void *part, void *transform, s32 arg3,
                                   void *animation, s32 view, s32 layer) __asm__("func_80080728");
extern void handle_level_point(ModelSession *session, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5,
                               s32 index) __asm__("func_800824E4");
extern u32 gAnimationTime __asm__("D_801B4AA0");

void submit_model_group(ModelSession *session, s32 index, void *transform, s32 layer, s32 phase, u8 mask,
                        s32 arg6, s32 arg7, void *frameOverride) __asm__("func_80082AA8");

void submit_model_group(ModelSession *session, s32 index, void *transform, s32 layer, s32 phase, u8 mask,
                        s32 arg6, s32 arg7, void *frameOverride)
{
    ModelGroup *group;
    ModelGroupRef *groupRef;
    ModelPart *modelPart;
    void *part;
    s32 count;
    s32 i;
    s32 j;
    u32 frame;

    count = get_view_count();
    if (index == -1) {
        return;
    }
    if (mask == 0) {
        return;
    }
    if (arg6 == 0) {
        if (arg6 < count) {
            for (i = 0; i < count; i++) {
                if ((mask >> i) & 1) {
                    handle_level_point(session, index, (s32)transform, 0, layer, phase, i);
                }
            }
        }
        return;
    }
    groupRef = &session->refs[index];
    group = &session->groups[groupRef->group];
    for (j = 0; j < group->count; j++) {
        modelPart = &session->modelParts[group->first + j];
        if (arg7 != 0) {
            part = func_8008067C(arg6, arg7, session->parts[modelPart->part]);
        } else {
            part = session->parts[modelPart->part];
        }
        for (i = 0; i < count; i++) {
            if (!((mask >> i) & 1)) {
                continue;
            }
            if (frameOverride != 0) {
                add_render_bucket_entry(frameOverride, part, transform, 0, 0, i, layer);
            } else {
                u32 animation = modelPart->animation;

                if (animation == 0) {
                    add_render_bucket_entry(session->frames[modelPart->frame], part, transform, 0, 0, i, layer);
                } else {
                    if (phase >= 0) {
                        frame = (animation & 0x7FF) + phase;
                    } else if (phase == -1) {
                        frame = (animation & 0x7FF) + gAnimationTime % (u32)(animation >> 11);
                    } else {
                        frame = (animation & 0x7FF) + (gAnimationTime >> 1) % (u32)(animation >> 11);
                    }
                    add_render_bucket_entry(session->frames[modelPart->frame], part, transform, 0,
                                            session->frames[modelPart->frame + frame], i, layer);
                }
            }
        }
    }
}
