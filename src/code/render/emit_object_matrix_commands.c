#include "types.h"

typedef struct MatrixPoolBank {
    u8 pad00[0x14];
    u32 base;
} MatrixPoolBank;

typedef struct MatrixRenderState {
    u8 pad00[0x90];
    MatrixPoolBank banks[2];
    u8 padC0[0x10];
    u16 bank;
    u8 padD2[0x6];
    u32 *altList;
    u32 *list;
    u8 padE0[0x8];
    u32 cursor;
} MatrixRenderState;

typedef struct MatrixObject {
    u8 pad00[0x40];
    u32 matrix;
} MatrixObject;

extern MatrixRenderState *D_801257D0;
extern void build_object_matrix(MatrixObject *source, u32 destination)
    __asm__("func_801146A0");

void emit_object_matrix_commands(MatrixObject *object, s32 perspectiveNorm)
    __asm__("func_8007E8EC");

void emit_object_matrix_commands(MatrixObject *object, s32 perspectiveNorm)
{
    MatrixRenderState *state = D_801257D0;
    MatrixPoolBank *bank = &state->banks[state->bank];
    u32 matrix = object->matrix;
    u32 *command;

    if (matrix == 0) {
        if (state->cursor >= bank->base + 0xC000) {
            return;
        }
        build_object_matrix(object, state->cursor);
        matrix = state->cursor;
        object->matrix = matrix;
        state->cursor += 0x40;
    }
    command = state->altList;
    state->altList = command + 2;
    command[0] = 0xBC00000E;
    command[1] = perspectiveNorm & 0xFFFF;
    command = state->altList;
    state->altList = command + 2;
    command[0] = 0x01030040;
    command[1] = matrix - 0x80000000;
}
