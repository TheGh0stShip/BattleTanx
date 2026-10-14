#include "types.h"

typedef struct RenderMatrixState {
    f32 m[4][4];
    s32 flag;
} RenderMatrixState;

typedef struct FlashingRecord {
    u8 pad00[0xC];
    s32 value0C;
    s32 value10;
    u8 pad14[0x8];
    s32 value1C;
} FlashingRecord;

extern void *get_secondary_runtime_resource(void) __asm__("func_800821C0");
extern void func_80084CC4(void *resource, s16 id, RenderMatrixState *matrix, s32 zero, s32 mode, s32 frame, void *position, f32 scale);
extern void submit_render_record(RenderMatrixState *target, s32 value14, s32 zero, s32 value10, u16 flags)
    __asm__("func_800A7744");
extern RenderMatrixState D_800755D0;
extern f32 D_80075614;
extern s32 gGameTicks __asm__("D_801B4AA8");
extern s16 D_802D5ACA;

void render_record_flashing_model(FlashingRecord *record) __asm__("func_8010D9B0");

void render_record_flashing_model(FlashingRecord *record) {
    RenderMatrixState matrix = D_800755D0;

    if (record->value1C == 0) {
        submit_render_record(&matrix, record->value10, 0, record->value0C, 0);
        func_80084CC4(get_secondary_runtime_resource(), D_802D5ACA, &matrix, 0, 3, (gGameTicks / 8) % 2, &record->value0C, D_80075614);
    }
}
