#include "types.h"

typedef struct CampaignWave {
    u32 kind;
    s32 level;
    u8 pad08[4];
    u8 teams[0x1C0];
    s32 value1CC;
    s32 value1D0;
    u8 pad1D4[0x40];
    u8 color[3];
    u8 pad217[9];
} CampaignWave;

typedef struct CampaignParams {
    s32 value00;
    s32 result;
    s16 value08;
} CampaignParams;

typedef struct PlayerRecord {
    u8 pad000[0x3A];
    u16 value3A;
    u8 pad03C[0x1D4];
    s32 value210;
} PlayerRecord;

extern PlayerRecord *get_entity_record(u16 index) __asm__("func_800A6688");
extern void reset_frame_event_counter(void) __asm__("func_8010D9A0");
extern void initialize_stream_workspace(void) __asm__("func_80081A50");
extern void empty_stack_frame(void) __asm__("func_800B87F4");
extern void func_8008B9E8(void);
extern void shuffle_four_slot_order(void) __asm__("func_800A30A8");
extern void clear_four_runtime_pairs(void) __asm__("func_800A3070");
extern s32 runtime_slot_is_active(s32 level, s32 a, s32 b, s32 c) __asm__("func_800E51A0");
extern s32 load_demo_recording(void) __asm__("func_800EC410");
extern s32 get_runtime_partition_stride(void) __asm__("func_800EC654");
extern u64 osGetTime(void) __asm__("func_801120A0");
extern s32 get_runtime_slot_value(void) __asm__("func_800EC3F0");
extern void func_80081AD0(s32 level, void *teams);
extern void clear_entity_pool_markers(void) __asm__("func_800A0380");
extern void func_800A5FF0(CampaignWave *wave);
extern s32 func_800EC644(void);
extern void begin_player_round_mode_8(void) __asm__("func_8007C678");
extern void apply_mode_display_rows(CampaignWave *wave) __asm__("func_8007C2A0");
extern void load_level_support_assets(void) __asm__("func_800F5960");
extern void refresh_audio_output(void) __asm__("func_80079BD4");
extern void request_audio_state_refresh(void) __asm__("func_800A8ECC");
extern void load_texture_draw_font(s32 font) __asm__("func_801053B0");
extern void set_screen_fade(s32 red, s32 green, s32 blue, s32 alpha, s32 arg4) __asm__("func_8008054C");
extern void func_80080580(s32 a, s32 b, s32 c, s32 d, s32 e);
extern void wait_for_async_io_idle(void) __asm__("func_800A8EE0");
extern void reset_runtime_pools(void) __asm__("func_800805DC");
extern void reset_halfword_slots(void) __asm__("func_8007968C");
extern void func_8007F2A0(void);
extern void init_runtime_color_record(void) __asm__("func_8007D850");
extern void reset_player_round_state(void) __asm__("func_8007FF68");
extern void draw_render_overlays(void) __asm__("func_800803A4");
extern u16 *finalize_runtime_frame(void) __asm__("func_8007D998");
extern u16 *func_80121B60(void);
extern s32 format_string(char *out, const char *format, ...) __asm__("func_8011CC84");
extern s32 debug_port_command_202(char *path, s32 mode) __asm__("func_80076D14");
extern s32 debug_port_command_404(s32 handle) __asm__("func_80076E34");
extern s32 debug_port_send_data(s32 handle, u16 *source, s32 length) __asm__("func_80076F60");
extern void update_game_clock(void) __asm__("func_8007AD2C");
extern void broadcast_effect_message_4(void) __asm__("func_8008B66C");
extern s32 func_800A42B0(PlayerRecord *record);
extern void func_80079064(void);
extern s32 gGameMode __asm__("D_8012578C");
extern u8 D_801B4AE8;
extern u8 D_80125798;
extern u8 D_80125799;
extern s32 D_801B4AA0;
extern CampaignWave *gCurrentGameState __asm__("D_801B4ABC");
extern s32 D_801B4AB8;
extern s32 gDifficultyLevel __asm__("D_801B4AB4");
extern u64 gClockFrameTime __asm__("D_801B4AC8");
extern u64 gClockPreviousTime __asm__("D_801257A0");
extern u64 gClockStartTime __asm__("D_801257A8");
extern s32 gGameTicks __asm__("D_801B4AA8");
extern f32 gClockFrameScale __asm__("D_801257B0");
extern u8 D_801B4BF8;
extern u8 D_801B4BF9;
extern u8 gRuntimeInitialized __asm__("D_80125780");
extern s32 D_80125784;

s32 play_campaign_wave(CampaignWave *wave, CampaignParams *params) __asm__("func_8007BD24");

s32 play_campaign_wave(CampaignWave *wave, CampaignParams *params)
{
    CampaignWave backup;
    char path[0x20];
    s32 mode = gGameMode;
    PlayerRecord *record;
    PlayerRecord *player;
    s32 keep;
    s32 result;
    u16 *frame;
    s32 handle;
    s32 i;
    s32 demoKind;
    u16 n;
    u64 now;

    backup = *wave;
    player = get_entity_record(0);
    keep = player->value210;
    reset_frame_event_counter();
restart:
    gGameMode = mode;
    D_801B4AE8 = 1;
    backup.color[0] = wave->color[0];
    backup.color[1] = wave->color[1];
    backup.color[2] = wave->color[2];
    *wave = backup;
    player->value210 = keep;
    D_80125799 = 0;
    D_801B4AA0 = 0;
    gCurrentGameState = wave;
    initialize_stream_workspace();
    empty_stack_frame();
    func_8008B9E8();
    if (wave->kind < 3) {
        shuffle_four_slot_order();
    } else if (wave->kind == 9) {
        shuffle_four_slot_order();
    } else {
        clear_four_runtime_pairs();
    }
    runtime_slot_is_active(wave->level, -1, wave->value1D0, wave->value1CC);
    demoKind = 8;
    if (wave->kind == demoKind) {
        result = load_demo_recording();
        if (result < 0) {
            return result;
        }
        result = get_runtime_partition_stride();
        D_801B4AB8 = result;
        wave->value1D0 = result;
        gDifficultyLevel = 1;
        wave->value1CC = 1;
    }
    now = osGetTime();
    gClockStartTime = now;
    gClockPreviousTime = now;
    gClockFrameTime = now;
    gGameTicks = 0;
    gClockFrameScale = 1.0f;
    if (wave->kind == demoKind) {
        result = get_runtime_slot_value();
    } else {
        result = wave->level;
    }
    func_80081AD0(result, wave->teams);
    clear_entity_pool_markers();
    func_800A5FF0(wave);
    if (func_800EC644()) {
        begin_player_round_mode_8();
    } else {
        apply_mode_display_rows(wave);
    }
    load_level_support_assets();
    if (wave->kind != 8) {
        refresh_audio_output();
    }
    D_80125798 = 0;
    request_audio_state_refresh();
    now = osGetTime();
    gClockStartTime = now;
    gClockPreviousTime = now;
    gClockFrameTime = now;
    gGameTicks = 0;
    D_801B4BF9 = 1;
    D_801B4BF8 = 0;
    gClockFrameScale = 1.0f;
    load_texture_draw_font(0);
    while (gGameMode != 0 && D_80125798 == 0) {
        set_screen_fade(0, 0, 0, 0, 0);
        func_80080580(0, 0, 0, 0, 0);
        func_80080580(0, 0, 0, 0, 1);
        func_80080580(0, 0, 0, 0, 2);
        func_80080580(0, 0, 0, 0, 3);
        wait_for_async_io_idle();
        reset_runtime_pools();
        reset_halfword_slots();
        func_8007F2A0();
        request_audio_state_refresh();
        init_runtime_color_record();
        reset_player_round_state();
        draw_render_overlays();
        frame = finalize_runtime_frame();
        if (gRuntimeInitialized) {
            while (frame != func_80121B60()) {
            }
            format_string(path, "d:\\bs64\\screenshot%d.raw", D_80125784++);
            handle = debug_port_command_202(path, 1);
            for (i = 0; i < 0x12C00; i++) {
                frame[i] >>= 1;
            }
            debug_port_send_data(handle, frame, 0x25800);
            debug_port_command_404(handle);
            gRuntimeInitialized = 0;
        }
        D_801B4AA0++;
        update_game_clock();
    }
    broadcast_effect_message_4();
    for (n = 0; n < 4; n++) {
        record = get_entity_record(n);
        params[n].value00 = record->value210;
        params[n].result = func_800A42B0(record) == 2;
        params[n].value08 = record->value3A;
    }
    func_80079064();
    if (D_80125799 != 0) {
        goto restart;
    }
}
