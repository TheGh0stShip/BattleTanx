#include "types.h"

/* Initialized rodata at 0x8007470C..0x80074714 (ROM 0x470C..0x4714). */
typedef struct Rodata8007470C {
    f32 value0;
    f32 value4;
} Rodata8007470C;

const Rodata8007470C D_8007470C = {
    1.0f,
    1800.0f,
};
