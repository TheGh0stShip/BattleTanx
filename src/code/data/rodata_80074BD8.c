#include "types.h"

/* Initialized rodata at 0x80074BD8..0x80074BE8 (ROM 0x4BD8..0x4BE8). */
typedef struct Rodata80074BD8 {
    f32 value0;
    f32 value4;
    f32 value8;
    f32 valueC;
} Rodata80074BD8;

const Rodata80074BD8 D_80074BD8 = {
    1024.0f,
    275.0f,
    95.0f,
    40.0f,
};
