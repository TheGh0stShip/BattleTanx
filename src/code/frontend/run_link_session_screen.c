#include "types.h"

typedef struct DisplayCommand {
    u32 w0;
    u32 w1;
} DisplayCommand;

extern void rom_dma_read(u32 romAddress, void *destination, u32 size) __asm__("func_80077930");
extern s32 lzari_decode(u32 sourceSize, u8 *source, u32 destinationSize, u8 *destination)
    __asm__("func_800F4F60");
extern void load_texture_draw_font(s32 font) __asm__("func_801053B0");
extern void reset_halfword_slots(void) __asm__("func_8007968C");
extern void func_8007D850(void);
extern void func_8007D998(void);
extern void append_display_list_call_0(u8 *list, u8 *base) __asm__("func_8007EEF8");
extern void request_audio_state_refresh(void) __asm__("func_800A8ECC");
extern void wait_for_async_io_idle(void) __asm__("func_800A8EE0");
extern void func_800CE554(void);
extern void func_800CF374(void);
extern u8 func_800CF4C0(void);
extern s32 func_800CF454(void);
extern void func_800D05DC(void);
extern s32 func_800D0B0C(void);
extern u8 gResourceScratch[] __asm__("D_803DA800");
extern u8 *gResourceTarget __asm__("D_803275F4");
extern u8 gBundle4B1300Start[] __asm__("D_B04B1300");
extern u8 gBundle4B1300End[] __asm__("D_B04B3280");
extern u8 *gDisplayListBase __asm__("D_803276D0");
extern DisplayCommand *gFrameDisplayList __asm__("D_803276D4");
extern s32 gDisplayListIndex __asm__("D_803276D8");
extern u8 D_80134E75;
extern s32 D_80328150;
extern s32 D_80328154;
extern u8 D_80328158;
extern u8 D_80328159;
extern u8 D_8032815A;
extern s32 D_8032815C;
extern s32 D_80328160;
extern s32 D_80328164;
extern s32 D_80328168;
extern s32 D_8032816C;
extern s32 D_80328170;

static inline void load_resource_bundle_4B1300(void) {
    u32 size = gBundle4B1300End - gBundle4B1300Start;

    rom_dma_read((u32)gBundle4B1300Start, gResourceScratch, size);
    lzari_decode(size, gResourceScratch, 0x25800, gResourceTarget);
    load_texture_draw_font(1);
    D_80328150 = 0;
    D_80328158 = 0;
    D_80328159 = 0;
    D_8032815A = 0;
    D_80328154 = 0;
    D_80328170 = 0;
}

s32 run_link_session_screen(void) __asm__("func_800CEE2C");

s32 run_link_session_screen(void) {
    u8 result = 0;
    s8 back;
    s8 next;

    load_resource_bundle_4B1300();
    next = 10;
    back = 10;
    switch (D_80134E75) {
    case 0:
        func_800CF374();
        back = 0;
        if (D_8032815C == 0) {
            return 0;
        }
        if (D_80328160 != 0) {
            switch (D_80328160) {
            case 4:
                D_80328170 = 8;
                break;
            case 10:
                D_80328170 = 9;
                break;
            case 11:
                D_80328170 = 8;
                break;
            case 1:
                D_80328170 = 2;
                break;
            case 2:
                D_80328170 = 0;
                next = 0;
                break;
            }
        } else {
            D_80328170 = 0;
            next = 0;
        }
        break;
    case 1:
        func_800CF374();
        back = 2;
        if (D_8032815C == 0) {
            D_80328170 = 3;
            break;
        }
        if (D_80328160 != 0) {
            switch (D_80328160) {
            case 2:
                D_80328170 = 10;
                break;
            case 4:
                D_80328170 = 8;
                break;
            case 10:
                D_80328170 = 9;
                break;
            case 11:
                D_80328170 = 8;
                break;
            case 1:
                D_80328170 = 2;
                break;
            }
        } else {
            D_8032816C = func_800CF454();
            if (D_8032816C != -1) {
                return 2;
            }
            if (D_80328164 > 0x100 && D_80328168 < 16) {
                func_800D05DC();
                D_80328170 = 6;
            } else {
                D_80328170 = 1;
            }
        }
        break;
    case 2:
        back = 2;
        if (D_8032815C == 0) {
            D_80328170 = 2;
            break;
        }
        if (D_80328160 != 0) {
            switch (D_80328160) {
            case 2:
                D_80328170 = 10;
                break;
            case 10:
                D_80328170 = 9;
                break;
            case 4:
                D_80328170 = 8;
                break;
            case 11:
                D_80328170 = 8;
                break;
            case -69:
                D_80328170 = 11;
                break;
            case 1:
                D_80328170 = 2;
                break;
            }
        } else {
            D_8032816C = func_800CF454();
            if (D_8032816C != -1) {
                return func_800D0B0C() == 0 ? 11 : 10;
            }
            if (D_80328164 > 0x100 && D_80328168 < 16) {
                func_800D05DC();
                D_80328170 = 6;
            } else {
                D_80328170 = 1;
            }
        }
        break;
    case 3:
        back = 3;
        if (D_8032815C == 0) {
            D_80328170 = 2;
            break;
        }
        if (D_80328160 != 0) {
            switch (D_80328160) {
            case 2:
                D_80328170 = 10;
                break;
            case 10:
                D_80328170 = 9;
                break;
            case 4:
                D_80328170 = 8;
                break;
            case 11:
                D_80328170 = 8;
                break;
            case -69:
                D_80328170 = 11;
                break;
            case 1:
                D_80328170 = 2;
                break;
            }
        } else {
            D_8032816C = func_800CF454();
            if (D_8032816C != -1) {
                D_80328170 = 7;
            } else if (D_80328164 > 0x100 && D_80328168 < 16) {
                D_80328170 = 6;
            } else {
                D_80328170 = 1;
            }
        }
        break;
    }
    while (!result) {
        DisplayCommand *cmd;

        request_audio_state_refresh();
        wait_for_async_io_idle();
        result = func_800CF4C0();
        func_8007D850();
        gFrameDisplayList = (DisplayCommand *)(gDisplayListBase + gDisplayListIndex * 0x11000);
        func_800CE554();
        cmd = gFrameDisplayList++;
        cmd->w0 = 0xB8000000;
        cmd->w1 = 0;
        append_display_list_call_0(gDisplayListBase + gDisplayListIndex * 0x11000, gDisplayListBase);
        gDisplayListIndex = (gDisplayListIndex + 1 < 3) ? gDisplayListIndex + 1 : 0;
        reset_halfword_slots();
        func_8007D998();
    }
    switch (result) {
    case 1:
        return next;
    case 5:
        return 10;
    case 3:
        return 11;
    case 4:
        return back;
    }
    return next;
}
