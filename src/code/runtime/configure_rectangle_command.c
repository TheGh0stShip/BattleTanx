#include "types.h"

typedef struct RectangleCommand {
    s32 type;
    u8 pad04[0x4];
    f32 firstX;
    f32 firstY;
    f32 secondX;
    f32 secondY;
} RectangleCommand;

void configure_rectangle_command(RectangleCommand *command, f32 *first, f32 *second)
    __asm__("func_800E3A38");

void configure_rectangle_command(RectangleCommand *command, f32 *first, f32 *second)
{
    command->firstY = first[1];
    command->firstX = first[0];
    command->secondY = second[1];
    command->secondX = second[0];
    command->type = 7;
}
