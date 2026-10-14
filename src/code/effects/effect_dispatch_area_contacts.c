#include "types.h"

typedef struct AreaBox {
    s16 value00;
    s16 value02;
    s16 value04;
    s16 value06;
    s16 value08;
    s16 value0A;
    s16 value0C;
    s16 value0E;
    s16 value10;
} AreaBox;

typedef struct AreaDefinition {
    AreaBox box;
    u8 pad12[0x16];
} AreaDefinition;

typedef struct AreaObject {
    u8 pad00[0x8];
    s32 kind;
} AreaObject;

typedef struct AreaEffect {
    u8 pad00[0x18];
    s32 areaIndex;
} AreaEffect;

typedef void (*AreaObjectHandler)(AreaObject *object, AreaEffect *effect, s32 event, void *data, void *out);

typedef struct AreaObjectKind {
    u8 pad00[0x4];
    AreaObjectHandler handler;
    u8 pad08[0x4];
} AreaObjectKind;

#define AREA_QUERY_CAPACITY 32

extern AreaDefinition D_803B8254[];
extern AreaObjectKind D_802C3800[];
extern f32 D_80071EA0;

extern void func_80107A14(AreaBox *box, s32 capacity, AreaObject **results, s32 *count);

void effect_dispatch_area_contacts(AreaEffect *effect) __asm__("func_80092534");

void effect_dispatch_area_contacts(AreaEffect *effect)
{
    AreaBox box;
    AreaObject *results[AREA_QUERY_CAPACITY];
    u8 data[0x20];
    u8 out[0x10];
    s32 count;
    s32 i;
    f32 scale;

    box = D_803B8254[effect->areaIndex].box;
    scale = D_80071EA0;
    box.value06 = (s32)(box.value06 * scale);
    box.value08 = (s32)(box.value08 * scale);
    box.value0A = (s32)(box.value0A * scale);
    box.value0C = (s32)(box.value0C * scale);
    box.value0E = (s32)(box.value0E * scale);
    func_80107A14(&box, AREA_QUERY_CAPACITY, results, &count);
    for (i = 0; i < count; i++) {
        if ((u32)results[i] >= 4 && D_802C3800[results[i]->kind].handler != 0) {
            D_802C3800[results[i]->kind].handler(results[i], effect, 0, data, out);
        }
    }
}
