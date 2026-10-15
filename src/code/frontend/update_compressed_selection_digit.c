#include "types.h"

extern s32 read_controller_buttons(s32 controller, s32 repeat) __asm__("func_80096920");
extern void load_selected_resource_bundle(void) __asm__("func_800C80E0");
extern s32 gCompressedSelectionDigits[] __asm__("D_80134010");
extern u8 gCompressedSelectionAllowOne __asm__("D_80135773");
extern s32 gCompressedSelectionDigitIndex __asm__("D_80327EE8");
extern s32 gCompressedSelectionDirection __asm__("D_80327EF0");

s32 update_compressed_selection_digit(void) __asm__("func_800C7FC0");

s32 update_compressed_selection_digit(void)
{
    s32 buttons;
    s32 result;
    s32 delta;
    s32 left;
    s32 right;
    s32 digit;
    s32 masked;
    u16 held;

    buttons = read_controller_buttons(0, 0);
    result = 0;
    held = buttons;
    if (buttons & 1) {
        gCompressedSelectionDirection = -gCompressedSelectionDirection;
    }
    if (buttons & 8) {
        gCompressedSelectionDirection = -gCompressedSelectionDirection;
    }
    left = (buttons & 2) > 0;
    right = (buttons & 4) > 0;
    delta = right - left;
    gCompressedSelectionDigits[gCompressedSelectionDigitIndex] += delta;
    if (gCompressedSelectionAllowOne == 0 &&
        gCompressedSelectionDigits[gCompressedSelectionDigitIndex] == 1) {
        gCompressedSelectionDigits[gCompressedSelectionDigitIndex] = delta + 1;
    }
    digit = gCompressedSelectionDigits[gCompressedSelectionDigitIndex];
    if (digit < 0) {
        digit = 9;
    }
    masked = -(digit < 10) & digit;
    gCompressedSelectionDigits[gCompressedSelectionDigitIndex] = masked;
    load_selected_resource_bundle();
    if (held & 0x50) {
        result = 1;
    }
    if (held & 0x20) {
        result = 2;
    }
    return result;
}
