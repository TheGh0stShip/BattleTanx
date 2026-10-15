#include "types.h"

typedef struct DisplayCommand {
    u32 w0;
    u32 w1;
} DisplayCommand;

typedef struct ScreenState {
    u8 pad00[0x8];
    u8 value08;
} ScreenState;

extern void rom_dma_read(u8 *romAddress, u8 *destination, s32 size) __asm__("func_80077930");
extern void reset_halfword_slots(void) __asm__("func_8007968C");
extern void func_8007D850(void);
extern void func_8007D998(void);
extern void append_display_list_call_0(u8 *list, u8 *base) __asm__("func_8007EEF8");
extern void request_audio_state_refresh(void) __asm__("func_800A8ECC");
extern void wait_for_async_io_idle(void) __asm__("func_800A8EE0");
extern void func_800D68D0(void);
extern void func_800D9134(f32 value);
extern u8 func_800DAC4C(void);
extern void lzari_decode(s32 sourceSize, u8 *source, s32 destinationSize, s32 destination)
    __asm__("func_800F4F60");
extern void load_texture_draw_font(s32 font) __asm__("func_801053B0");

extern s32 gResourceTarget __asm__("D_803275F4");
extern u8 *gDisplayListBase __asm__("D_803276D0");
extern DisplayCommand *gFrameDisplayList __asm__("D_803276D4");
extern s32 gDisplayListIndex __asm__("D_803276D8");
extern s32 gControllerSlotCount __asm__("D_80134E58");
extern f32 D_8007419C;
extern s32 D_80134020[];
extern s32 D_80134E5C;
extern ScreenState *D_80134E78;
extern s32 D_80135674;
extern u8 D_80135767;
extern s32 D_803283C4;
extern s32 D_80328400[];
extern s32 D_80328410;
extern u8 D_803DA800[];
extern u8 D_B03DFD10[];
extern u8 D_B03EA970[];

static inline s32 load_rom_span(u8 *start, u8 *end, u8 *dst) {
    s32 size = end - start;

    rom_dma_read(start, dst, size);
    return size;
}

s32 run_team_select_screen(void) __asm__("func_800DA9B4");

s32 run_team_select_screen(void)
{
    s32 size;
    s32 i;
    s32 j;
    s32 kind;
    u8 result;

    size = load_rom_span(D_B03DFD10, D_B03EA970, D_803DA800);
    lzari_decode(size, D_803DA800, 0x25800, gResourceTarget);
    load_texture_draw_font(1);
    result = 0;
    if (D_80134E5C == 0) {
        D_80328410 = 0x1C;
    } else {
        D_80328410 = (gControllerSlotCount >= 3) ? 6 : 8;
    }
    while (result == 0) {
        DisplayCommand *cmd;

        request_audio_state_refresh();
        wait_for_async_io_idle();
        result = func_800DAC4C();
        func_8007D850();
        gFrameDisplayList = (DisplayCommand *)(gDisplayListBase + gDisplayListIndex * 0x11000);
        func_800D9134(D_8007419C);
        cmd = gFrameDisplayList++;
        cmd->w0 = 0xB8000000;
        cmd->w1 = 0;
        append_display_list_call_0(gDisplayListBase + gDisplayListIndex * 0x11000, gDisplayListBase);
        gDisplayListIndex = (gDisplayListIndex + 1 < 3) ? gDisplayListIndex + 1 : 0;
        reset_halfword_slots();
        func_8007D998();
    }
    if (result == 1) {
        if (D_80134E5C == 0) {
            func_800D68D0();
            if (D_80135767 != 0) {
                D_80134E78->value08 = D_80135674;
            }
        } else {
            for (i = 0; i < D_803283C4; i++) {
                kind = D_80328400[i];
                if (kind == 4) {
                    j = i + 1;
                    j += D_80328400[j] == 4;
                    D_80328400[i] = D_80328400[j];
                    D_80134020[i] = D_80134020[j];
                    D_80328400[j] = kind;
                }
            }
        }
        return 0xB;
    }
    return (D_80134E5C == 4) ? 7 : 4;
}
