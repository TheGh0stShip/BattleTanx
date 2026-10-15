#include "types.h"

/* Initialized rodata at 0x800743A0..0x800743B4 (ROM 0x43A0..0x43B4). */
typedef struct Rodata800743A0 {
    f32 value0;
    f32 value4;
    f32 value8;
    f32 valueC;
    f32 value10;
} Rodata800743A0;

const Rodata800743A0 D_800743A0 = {
    3000.0f,
    1000.0f,
    2.14748365e+09f,
    3000.0f,
    1000.0f,
};
