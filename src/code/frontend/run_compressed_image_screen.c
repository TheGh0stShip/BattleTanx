#include "types.h"

typedef struct DisplayCommand {
    u32 w0;
    u32 w1;
} DisplayCommand;

extern void rom_dma_read(u8 *romAddress, u8 *destination, s32 size) __asm__("func_80077930");
extern void reset_halfword_slots(void) __asm__("func_8007968C");
extern void func_8007D850(void);
extern void func_8007D998(void);
extern void append_display_list_call_0(u8 *list, u8 *base) __asm__("func_8007EEF8");
extern void request_audio_state_refresh(void) __asm__("func_800A8ECC");
extern void wait_for_async_io_idle(void) __asm__("func_800A8EE0");
extern void func_800DAE30(s32 index);
extern s32 func_800DCCC0(void);
extern void lzari_decode(s32 sourceSize, u8 *source, s32 destinationSize, s32 destination)
    __asm__("func_800F4F60");
extern void load_texture_draw_font(s32 font) __asm__("func_801053B0");

extern s32 gResourceTarget __asm__("D_803275F4");
extern u8 *gDisplayListBase __asm__("D_803276D0");
extern DisplayCommand *gFrameDisplayList __asm__("D_803276D4");
extern s32 gDisplayListIndex __asm__("D_803276D8");
extern u8 D_803DA800[];
extern u8 D_B04AC150[];
extern u8 D_B04AD7E0[];

static inline s32 load_rom_span(u8 *start, u8 *end, u8 *dst) {
    s32 size = end - start;

    rom_dma_read(start, dst, size);
    return size;
}

s32 run_compressed_image_screen(void) __asm__("func_800DC93C");

s32 run_compressed_image_screen(void) {
    s32 size;
    u8 done;

    size = load_rom_span(D_B04AC150, D_B04AD7E0, D_803DA800);
    lzari_decode(size, D_803DA800, 0x25800, gResourceTarget);
    load_texture_draw_font(1);
    do {
        DisplayCommand *cmd;

        request_audio_state_refresh();
        wait_for_async_io_idle();
        done = func_800DCCC0();
        func_8007D850();
        gFrameDisplayList = (DisplayCommand *)(gDisplayListBase + gDisplayListIndex * 0x11000);
        func_800DAE30(gDisplayListIndex);
        cmd = gFrameDisplayList++;
        cmd->w0 = 0xB8000000;
        cmd->w1 = 0;
        append_display_list_call_0(gDisplayListBase + gDisplayListIndex * 0x11000, gDisplayListBase);
        gDisplayListIndex = (gDisplayListIndex + 1 < 3) ? gDisplayListIndex + 1 : 0;
        reset_halfword_slots();
        func_8007D998();
    } while (!done);
    return 2;
}
