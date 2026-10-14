#include "types.h"

typedef struct DisplayCommand {
    u32 w0;
    u32 w1;
} DisplayCommand;

typedef struct ScreenState {
    u8 pad00[0x10];
    s32 value10;
} ScreenState;

extern void rom_dma_read(u8 *romAddress, u8 *destination, s32 size) __asm__("func_80077930");
extern void reset_halfword_slots(void) __asm__("func_8007968C");
extern void func_8007D850(void);
extern void func_8007D998(void);
extern void append_display_list_call_0(u8 *list, u8 *base) __asm__("func_8007EEF8");
extern void request_audio_state_refresh(void) __asm__("func_800A8ECC");
extern void wait_for_async_io_idle(void) __asm__("func_800A8EE0");
extern void func_800C5C60(f32 value);
extern s32 func_800C7FC0(void);
extern void func_800C80E0(void);
extern void func_800D05DC(void);
extern void lzari_decode(s32 sourceSize, u8 *source, s32 destinationSize, s32 destination)
    __asm__("func_800F4F60");
extern void load_texture_draw_font(s32 font) __asm__("func_801053B0");

extern s32 gResourceTarget __asm__("D_803275F4");
extern u8 *gDisplayListBase __asm__("D_803276D0");
extern DisplayCommand *gFrameDisplayList __asm__("D_803276D4");
extern s32 gDisplayListIndex __asm__("D_803276D8");
extern s32 gControllerSlotCount __asm__("D_80134E58");
extern f32 D_800735F0;
extern s32 D_80133FE4[];
extern s32 D_80134010[];
extern s32 D_80134020[];
extern s32 D_80134E5C;
extern ScreenState *D_80134E78;
extern u8 D_80135767;
extern s32 D_80327ED0;
extern s32 D_80327ED4;
extern s32 D_80327ED8;
extern s8 D_80327EDC;
extern s32 D_80327EE0;
extern s32 D_80327EE4;
extern s32 D_80327EE8;
extern s32 D_80327EEC;
extern s32 D_80327EF0;
extern u8 D_803DA800[];
extern u8 D_B03D6940[];
extern u8 D_B03DC430[];

static inline s32 load_rom_span(u8 *start, u8 *end, u8 *dst) {
    s32 size = end - start;

    rom_dma_read(start, dst, size);
    return size;
}

s32 run_compressed_selection_screen(void) __asm__("func_800C7D74");

s32 run_compressed_selection_screen(void)
{
    s32 size;
    s32 i;
    u8 result;

    D_80327ED8 = -1;
    D_80327EE4 = -1;
    D_80327EEC = 0xFF;
    D_80327ED0 = 0;
    D_80327ED4 = 0;
    D_80327EDC = 0;
    D_80327EE0 = 0;
    D_80327EE8 = 0;
    D_80327EF0 = 0xF;
    size = load_rom_span(D_B03D6940, D_B03DC430, D_803DA800);
    lzari_decode(size, D_803DA800, 0x25800, gResourceTarget);
    func_800C80E0();
    load_texture_draw_font(1);
    do {
        DisplayCommand *cmd;

        request_audio_state_refresh();
        wait_for_async_io_idle();
        result = func_800C7FC0();
        func_8007D850();
        gFrameDisplayList = (DisplayCommand *)(gDisplayListBase + gDisplayListIndex * 0x11000);
        func_800C5C60(D_800735F0);
        cmd = gFrameDisplayList++;
        cmd->w0 = 0xB8000000;
        cmd->w1 = 0;
        append_display_list_call_0(gDisplayListBase + gDisplayListIndex * 0x11000, gDisplayListBase);
        gDisplayListIndex = (gDisplayListIndex + 1 < 3) ? gDisplayListIndex + 1 : 0;
        reset_halfword_slots();
        func_8007D998();
    } while (!result);

    for (i = 0; i < 4; i++) {
        D_80134020[i] = D_80133FE4[D_80134010[i]];
    }
    if (result == 1) {
        if (gControllerSlotCount == result && D_80134E5C == 0) {
            func_800D05DC();
            D_80134E78->value10 = D_80134020[0];
            if (D_80135767 != 0) {
                return 8;
            }
        }
        return 0xB;
    }
    return 2;
}
