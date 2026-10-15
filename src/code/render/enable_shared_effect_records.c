#include "types.h"
/* LDSYM D_801C9170=0x801C9170 */
/* LDSYM D_802D5A46=0x802D5A46 */

extern u8 *D_801C9170;
extern s16 D_802D5A46[];

static inline void enable_indexed_render_record(s32 index) {
    s32 offset;

    if (index == -1) {
        return;
    }
    offset = index << 1;
    {
        u8 *records = *(u8 **)(D_801C9170 + 0x570);
        offset += index;
        offset <<= 2;
        records[offset] = 1;
    }
}

void enable_shared_effect_records(void) __asm__("func_80085E18");

void enable_shared_effect_records(void) {
    enable_indexed_render_record(D_802D5A46[0]);
    enable_indexed_render_record(D_802D5A46[1]);
    enable_indexed_render_record(D_802D5A46[2]);
    enable_indexed_render_record(D_802D5A46[3]);
    enable_indexed_render_record(D_802D5A46[6]);
    enable_indexed_render_record(D_802D5A46[7]);
    enable_indexed_render_record(D_802D5A46[8]);
    enable_indexed_render_record(D_802D5A46[9]);
    enable_indexed_render_record(D_802D5A46[14]);
    enable_indexed_render_record(D_802D5A46[16]);
    enable_indexed_render_record(D_802D5A46[17]);
    enable_indexed_render_record(D_802D5A46[18]);
    enable_indexed_render_record(D_802D5A46[19]);
    enable_indexed_render_record(D_802D5A46[20]);
    enable_indexed_render_record(D_802D5A46[21]);
    enable_indexed_render_record(D_802D5A46[22]);
    enable_indexed_render_record(D_802D5A46[23]);
    enable_indexed_render_record(D_802D5A46[28]);
    enable_indexed_render_record(D_802D5A46[29]);
    enable_indexed_render_record(D_802D5A46[30]);
    enable_indexed_render_record(D_802D5A46[31]);
    enable_indexed_render_record(D_802D5A46[32]);
    enable_indexed_render_record(D_802D5A46[33]);
    enable_indexed_render_record(D_802D5A46[34]);
    enable_indexed_render_record(D_802D5A46[35]);
}
