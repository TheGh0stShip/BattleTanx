#include "allocated_matrix_command.h"

u32 push_allocated_matrix_secondary(s32 source, s32 flags) __asm__("func_8007ECE8");

u32 push_allocated_matrix_secondary(s32 source, s32 flags)
{
    u32 matrix = 0;
    u32 cursor;
    u32 *command;
    MatrixCommandState *state;

    state = gMatrixCommandState;
    do {
        cursor = state->matrixCursor;
        if (cursor >= (u32)(((MatrixPoolBank *)((state->bank * sizeof(MatrixPoolBank)) + (u32)state + 0x90))->limit + 0xC000)) {
            break;
        }
        convert_float_matrix(source, cursor);
        command = state->secondaryList;
        state->secondaryList = command + 2;
        command[0] = ((flags & 0xFF) << 16) | 0x01000040;
        command[1] = state->matrixCursor - 0x80000000U;
        matrix = state->matrixCursor;
        state->matrixCursor = matrix + 0x40;
    } while (0);
    return matrix;
}
