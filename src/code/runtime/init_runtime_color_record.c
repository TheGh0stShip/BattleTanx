#include "types.h"

typedef struct RuntimeColorSource {
    s32 unk00;
    s32 color0;
    s32 color1;
    s32 color2;
    s32 color3;
    s32 duration;
} RuntimeColorSource;

typedef struct RuntimeColorRecord {
    s32 color0;
    s32 color1;
    s32 color2;
    s32 color3;
    s32 duration;
    s16 unk14;
    s16 unk16;
    s16 unk18;
    s16 unk1A;
    s16 unk1C;
    u8 alpha0;
    u8 alpha1;
    u8 alpha2;
    u8 alpha3;
    u8 pad22[2];
    s32 unk24;
    s32 unk28;
    s16 unk2C;
} RuntimeColorRecord;

typedef struct RuntimeState {
    u8 pad00[0x90];
    RuntimeColorSource sources[2];
    u8 padC0[0x10];
    u16 sourceIndex;
    u8 padD2[2];
    s32 busy;
    RuntimeColorRecord runtimeColor;
} RuntimeState;

extern RuntimeState *gRuntimeState __asm__("D_801257C8");

void init_runtime_color_record(void) __asm__("func_8007D850");

void init_runtime_color_record(void)
{
    RuntimeState *state;
    RuntimeColorRecord *destination;
    RuntimeColorSource *source;

    state = gRuntimeState;
    destination = &state->runtimeColor;
    while (gRuntimeState->busy != 0) {
    }
    source = &state->sources[state->sourceIndex];
    destination->color0 = source->color0;
    destination->color1 = source->color1;
    destination->color2 = source->color2;
    destination->color3 = source->color3;
    destination->duration = source->duration + 0x40;
    destination->unk14 = 0;
    destination->unk16 = 0;
    destination->unk18 = 0;
    destination->unk1A = 0;
    destination->unk1C = 0;
    destination->alpha0 = 0xFF;
    destination->alpha1 = 0xFF;
    destination->alpha2 = 0xFF;
    destination->alpha3 = 0xFF;
    destination->unk24 = 0;
    destination->unk28 = 0;
    destination->unk2C = 0;
}
