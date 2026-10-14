#include "types.h"

typedef struct PlayerInput {
    s8 stickX;
    s8 stickY;
    u8 pad02[0x2];
    u32 held;
    u32 pressed;
    u32 released;
} PlayerInput;

extern void start_graphics_thread(s32 id, s32 priority, u8 viMode, u8 retraceCount, s32 recordValue)
    __asm__("func_80078E30");
extern void start_worker_thread_20(void) __asm__("func_8007961C");
extern void reset_player_input_flags(s32 unused) __asm__("func_8007963C");
extern void func_8007D4E8(void);
extern void func_800865E0(void);
extern PlayerInput *read_player_controller(s32 player) __asm__("func_80096784");
extern void func_800A8940(void);
extern void request_audio_state_refresh(void) __asm__("func_800A8ECC");
extern void wait_for_async_io_idle(void) __asm__("func_800A8EE0");
extern void func_800D05DC(void);
extern void func_800D4410(void);
extern void set_runtime_selection(s32 selection) __asm__("func_800F3A14");
extern u64 osGetTime(void) __asm__("func_801120A0");

extern s32 osTvType __asm__("D_80000300");
extern s32 gControllerCount __asm__("D_80126714");
extern u8 gLoadingState __asm__("D_80134E75");
extern u8 *D_801B4AA4;
extern u8 D_801B4AE0;
extern u8 D_8012579D;
extern u8 D_801C9190[];

void initialize_runtime_state(void) __asm__("func_8007AB04");

void initialize_runtime_state(void)
{
    PlayerInput *input;

    D_801B4AA4 = D_801C9190;
    start_worker_thread_20();
    reset_player_input_flags(5);
    func_8007D4E8();
    func_800A8940();
    if (osTvType == 2) {
        start_graphics_thread(3, 0x1E, 0x1E, 1, 2);
    } else {
        start_graphics_thread(3, 0x1E, 2, 1, 2);
    }
    func_800865E0();
    func_800D4410();
    func_800D05DC();
    set_runtime_selection(osGetTime());
    request_audio_state_refresh();
    wait_for_async_io_idle();
    input = read_player_controller(0);
    if (gControllerCount == 0) {
        D_801B4AE0 = 0xE;
    } else if (input->pressed & 0x1000) {
        D_801B4AE0 = 0xA;
        gLoadingState = 0;
    } else {
        D_801B4AE0 = 0;
    }
    D_8012579D = 0;
}
