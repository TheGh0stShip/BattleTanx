#include "types.h"
typedef struct {
    u8 pad0[0x310];
    f32 value310;
    f32 value314;
} ScaleTarget;

extern ScaleTarget *get_entity_record(u16 index) __asm__("func_800A6688");
extern f32 D_800755C0;
extern f32 D_800755C4;
extern s32 D_803C4D70;

void scale_entity_records_by_counter(void) __asm__("func_8010D850");

/* Shrinks entity 0's 0x310/0x314 values (clamped) and grows entities 1-3 by 15% per counter step, capped at 100%. */
void scale_entity_records_by_counter(void) {
    f32 minv;
    f32 scale;
    s32 pct;
    u16 i;
    ScaleTarget *t;

    pct = 0;
    if (D_803C4D70 > 0) {
        pct = D_803C4D70 * 15;
        if (pct > 100) {
            pct = 100;
        }
    }
    i = 0;
    if (pct != 0) {
        scale = D_800755C0;
        minv = D_800755C4;
        do {
            t = get_entity_record(i);
            if (i == 0) {
                t->value310 = t->value310 - t->value310 * pct / scale;
                t->value314 = t->value314 - t->value314 * pct / scale;
                if (t->value310 < minv) {
                    t->value310 = minv;
                }
                if (t->value314 < minv) {
                    t->value314 = minv;
                }
            } else {
                t->value310 = t->value310 + t->value310 * pct / scale;
                t->value314 = t->value314 + t->value314 * pct / scale;
            }
            i++;
        } while (i < 4);
    }
}
