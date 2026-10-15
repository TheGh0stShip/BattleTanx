#include "types.h"

/* Initialized rodata at 0x800745D0..0x800745F4 (ROM 0x45D0..0x45F4). */
typedef struct Rodata800745D0 {
    f32 value0;
    f32 value4;
    f32 value8;
    f32 valueC;
    f32 value10;
    f32 value14;
    f32 value18;
    f32 value1C;
    f32 value20;
} Rodata800745D0;

const Rodata800745D0 D_800745D0 = {
    16000.0f,
    16000.0f,
    40.0f,
    1.0f,
    2.0f,
    1.0f,
    200.0f,
    80.0f,
    16.0f,
};
