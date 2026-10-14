#include "types.h"

typedef struct AreaDef {
    u8 pad00[0x28];
} AreaDef;

extern AreaDef D_803B8254[];
extern void func_80109364(AreaDef *area, s32 a, s32 b, s32 c, s32 d);

void area_dispatch_by_index(s32 index, s32 a, s32 b, s32 c, s32 d) __asm__("func_8010770C");

void area_dispatch_by_index(s32 index, s32 a, s32 b, s32 c, s32 d) {
    if (index != -1) {
        func_80109364(&D_803B8254[index], a, b, c, d);
    }
}
