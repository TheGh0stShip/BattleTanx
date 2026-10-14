#include "types.h"

typedef struct TransformTemplate {
    s32 words[17];
} TransformTemplate;

typedef struct PlacedModel {
    u8 pad00[0xC];
    s32 value0C[3];
    s32 value18[6];
    u16 value30;
    u16 value32;
    u16 value34;
    u8 pad36[0x6];
    s32 value3C;
    u8 pad40[0x4];
    s32 value44;
} PlacedModel;

extern TransformTemplate gTransformTemplate __asm__("D_80071C04");
extern s32 get_session(void) __asm__("func_800821C0");
extern void build_transform(TransformTemplate *out, void *a, void *b, u16 c, s32 d, s32 e) __asm__("func_800A86E4");
extern void submit_model(s32 session, s32 model, TransformTemplate *xf, void *b, s32 e) __asm__("func_80085978");

void draw_placed_model(PlacedModel *obj) __asm__("func_8008FC9C");

void draw_placed_model(PlacedModel *obj) {
    TransformTemplate xf = gTransformTemplate;
    s32 session;

    if (obj->value44 != 0) {
        session = get_session();
        build_transform(&xf, obj->value18, obj->value0C, obj->value34, obj->value32, obj->value30);
        submit_model(session, obj->value44, &xf, obj->value0C, obj->value3C);
    }
}
