#ifndef ALLOCATED_MATRIX_COMMAND_H
#define ALLOCATED_MATRIX_COMMAND_H

#include "types.h"

typedef struct MatrixPoolBank {
    u8 pad00[0x14];
    s32 limit;
} MatrixPoolBank;

typedef struct MatrixCommandState {
    u8 pad00[0x90];
    MatrixPoolBank banks[2];
    u8 padC0[0x10];
    u16 bank;
    u8 padD2[0x6];
    u32 *primaryList;
    u32 *secondaryList;
    u8 padE0[0x8];
    u32 matrixCursor;
} MatrixCommandState;

extern MatrixCommandState *gMatrixCommandState __asm__("D_801257D0");
extern void convert_float_matrix(s32 source, u32 destination) __asm__("func_801146A0");

#endif
