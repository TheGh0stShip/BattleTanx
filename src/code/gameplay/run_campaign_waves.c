#include "types.h"

typedef struct CampaignWave {
    s32 kind;
    s32 id;
    s32 value08;
    s32 value0C;
    u8 pad10[0x1C0];
    s32 value1D0;
    u8 pad1D4[0x10];
    s32 value1E4;
    u8 pad1E8[0x24];
    u16 value20C;
    u8 pad20E[9];
    u8 value217;
    u8 pad218[8];
} CampaignWave;

typedef struct CampaignParams {
    s32 value00;
    s32 result;
    s16 value08;
    u8 pad0A[0x26];
} CampaignParams;

typedef struct FrontendSession {
    u8 pad00[8];
    s32 value08;
} FrontendSession;

typedef struct SessionState {
    u8 pad00[0x10];
    s32 value10;
} SessionState;

typedef struct EntityRecord {
    u8 pad00[0x210];
    s32 value210;
} EntityRecord;

extern s32 run_state_loop_after_sequence_reset(s32 state) __asm__("func_8007C58C");
extern void play_endurance_wave(CampaignWave *wave, CampaignParams *params)
    __asm__("func_8007B9E4");
extern EntityRecord *get_entity_record(u16 index) __asm__("func_800A6688");
extern void func_800D0828(s32 id, s32 value, s32 session, s32 offset, s32 flag, void *buffer);
extern CampaignWave gOpponentWaves[17] __asm__("D_80142DE8");
extern u8 gFrontendState __asm__("D_801B4AE0");
extern FrontendSession D_801B4AB0;
extern CampaignWave *gCurrentGameState __asm__("D_801B4ABC");
extern s32 D_801B4AD0;
extern s32 D_801B4AD4;
extern s32 gGameMode __asm__("D_8012578C");
extern u8 D_80125798;
extern u8 D_8012579B;
extern u8 D_80134E64;
extern u8 D_80134E68;
extern SessionState *D_80134E78;
extern u8 D_803283B8;
extern u8 D_803282A8[];

void run_campaign_waves(s32 index, s32 id, s32 offset, s16 bonus) __asm__("func_8007B280");

void run_campaign_waves(s32 index, s32 id, s32 offset, s16 bonus) {
    CampaignWave wave;
    CampaignParams params = { 0 };
    s32 i;
    FrontendSession *session;

    gFrontendState = 2;
    session = &D_801B4AB0;
    gCurrentGameState = &wave;
    D_80134E68 = 0;
    if (id != -1) {
        index = -1;
        for (i = 0; i < 17; i++) {
            if (gOpponentWaves[i].id == id) {
                index = i;
            }
        }
    }
    if (index == -1) {
        return;
    }
    D_801B4AD0 = index;
    params.value08 = bonus;
    params.value00 = offset;
    do {
        switch (D_801B4AD0) {
        case 0:
            if (run_state_loop_after_sequence_reset(15) < 0) {
                gFrontendState = 2;
                return;
            }
            break;
        case 5:
            run_state_loop_after_sequence_reset(16);
            break;
        case 9:
            run_state_loop_after_sequence_reset(17);
            break;
        case 13:
            run_state_loop_after_sequence_reset(18);
            break;
        }
        gFrontendState = 2;
        wave = gOpponentWaves[D_801B4AD0];
        session->value08 = wave.value1D0;
        wave.value20C += params.value08;
        wave.value1E4 += params.value00;
        wave.value217 = D_80134E64;
        if (wave.kind != 7) {
            wave.value0C = D_80134E78->value10;
        }
        gGameMode = 9;
        D_801B4AD4 = 1;
        play_endurance_wave(&wave, &params);
        if (D_80125798 != 0) {
            return;
        }
        if (params.result == 0 && wave.kind != 7) {
            return;
        }
        D_801B4AD0++;
        if (D_8012579B != 0) {
            func_800D0828(gOpponentWaves[D_801B4AD0].id, get_entity_record(0)->value210, D_80134E78->value10,
                          params.value08, D_803283B8, D_803282A8);
        }
    } while (D_801B4AD0 < 17);
    gFrontendState = 19;
}
