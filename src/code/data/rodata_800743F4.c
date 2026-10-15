#include "types.h"

/* Initialized rodata at 0x800743F4..0x8007441C (ROM 0x43F4..0x441C). */
typedef struct Rodata800743F4 {
    f32 value0;
    f32 value4;
    f32 value8;
    f32 valueC;
    f32 value10;
    f32 value14;
    f32 value18;
    f32 value1C;
    f32 value20;
    f32 value24;
} Rodata800743F4;

const Rodata800743F4 D_800743F4 = {
    1000.0f,
    200.0f,
    1000.0f,
    200.0f,
    1000.0f,
    200.0f,
    1000.0f,
    200.0f,
    16000.0f,
    0.00999999978f,
};
