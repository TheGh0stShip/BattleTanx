#include "types.h"

/* One F3D display-list command: opcode in the top byte of w0. */
typedef struct {
    u32 w0;
    u32 w1;
} DisplayCommand;

#define DL_OPCODE_VTX 0x04
#define DL_END_DL_WORD 0xB8000000

void offset_display_list_vertex_addresses(DisplayCommand *list, s32 count, s32 offset)
    __asm__("func_80085290");

/* Adds offset to the address word of each G_VTX command until G_ENDDL. */
void offset_display_list_vertex_addresses(DisplayCommand *list, s32 count, s32 offset) {
    s32 i;

    for (i = 0; i < count; i++) {
        if (list[i].w0 == DL_END_DL_WORD) {
            break;
        }
        if (*(u8 *)&list[i] == DL_OPCODE_VTX) {
            list[i].w1 += offset;
        }
    }
}
