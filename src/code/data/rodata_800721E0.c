#include "types.h"

/* Initialized rodata at 0x800721E0..0x80072234 (ROM 0x21E0..0x2234). */
typedef struct Rodata800721E0 {
    char text0[8];
    char text8[16];
    char text18[12];
    char text24[16];
    f32 value34;
    f32 value38;
    f32 value3C;
    f32 value40;
    f32 value44;
    f32 value48;
    f32 value4C;
    f32 value50;
} Rodata800721E0;

const Rodata800721E0 D_800721E0 = {
    "1 ENEMY\000",
    "TANK REMAINS\000\000\000\000",
    "%d ENEMY\000\000\000\000",
    "TANKS REMAIN\000\000\000\000",
    182.044449f,
    2.14748365e+09f,
    182.044449f,
    2.14748365e+09f,
    182.044449f,
    2.14748365e+09f,
    100.0f,
    1.5f,
};
