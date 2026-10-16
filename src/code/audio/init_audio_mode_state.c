#include "types.h"

typedef void (*AudioHandler)(void);

typedef struct AudioModeState {
    s32 mode;
    u8 *currentValue;
    s32 value08;
    u8 *values[5];
    s32 value24;
    s32 value28;
    u8 *bufferEnd;
    u8 *bufferStart;
} AudioModeState;

extern AudioModeState gAudioModeState __asm__("D_803275F0");
extern AudioHandler gAudioHandlersA[21] __asm__("D_80327620");
extern s32 gAudioHandlersReady __asm__("D_80327674");
extern AudioHandler gAudioHandlersB[21] __asm__("D_80327678");
extern s32 gAudioBufferSize __asm__("D_803276CC");
extern u8 *gAudioBuffer2 __asm__("D_803276D0");
extern s32 D_803276D8;
extern u8 *D_801B4AA4;
extern u8 D_803DA800[];
extern u8 D_B02D2790[];
extern u8 D_B02E2CD0[];

extern s32 select_audio_mode(u32 mode) __asm__("func_800AB95C");
extern void rom_dma_read(u32 romAddress, void *destination, u32 size) __asm__("func_80077930");
extern s32 lzari_decode(u32 sourceSize, u8 *source, u32 destinationSize, u8 *destination) __asm__("func_800F4F60");

extern void func_800ABFA0(void);
extern void func_800C5B90(void);
extern void func_800C5C60(void);
extern void func_800C8210(void);
extern void func_800C83D4(void);
extern void func_800CA980(void);
extern void func_800CAA04(void);
extern void func_800CC470(void);
extern void func_800CC4E4(void);
extern void func_800CE4B0(void);
extern void func_800CE554(void);
extern void func_800D44CC(void);
extern void func_800D455C(void);
extern void func_800D9080(void);
extern void func_800D9134(void);
extern void func_800DADBC(void);
extern void draw_code_entry_screen(void) __asm__("func_800DAE30");

void init_audio_mode_state(void) __asm__("func_800AB690");

void init_audio_mode_state(void)
{
    s32 i;
    u32 size;

    gAudioBufferSize = 0xF8240;
    gAudioModeState.mode = 1;
    gAudioModeState.value24 = 0;
    D_803276D8 = 0;
    gAudioModeState.value08 = 0;
    gAudioModeState.value28 = 0;
    gAudioModeState.bufferStart = D_801B4AA4;
    gAudioModeState.values[0] = D_801B4AA4;
    gAudioModeState.bufferEnd = D_801B4AA4 + 0xF8240;
    gAudioModeState.values[1] = D_801B4AA4 + 0x24DD8;
    gAudioModeState.values[2] = D_801B4AA4 + 0x5F758;
    gAudioModeState.values[3] = D_801B4AA4 + 0x9A0D8;
    gAudioModeState.values[4] = D_801B4AA4 + 0xAD958;
    gAudioModeState.currentValue = gAudioModeState.values[1];
    gAudioBuffer2 = D_801B4AA4 + 0xC5240;
    for (i = 0; i < 21; i++) {
        gAudioHandlersB[i] = func_800ABFA0;
        gAudioHandlersA[i] = func_800ABFA0;
    }
    gAudioHandlersB[2] = func_800CA980;
    gAudioHandlersA[2] = func_800CAA04;
    gAudioHandlersB[5] = func_800CC470;
    gAudioHandlersA[5] = func_800CC4E4;
    gAudioHandlersB[3] = func_800C5B90;
    gAudioHandlersA[3] = func_800C5C60;
    gAudioHandlersB[3] = func_800C8210;
    gAudioHandlersA[3] = func_800C83D4;
    gAudioHandlersB[9] = func_800DADBC;
    gAudioHandlersA[9] = draw_code_entry_screen;
    gAudioHandlersB[10] = func_800CE4B0;
    gAudioHandlersA[10] = func_800CE554;
    gAudioHandlersB[6] = func_800D44CC;
    gAudioHandlersA[6] = func_800D455C;
    gAudioHandlersB[8] = func_800D9080;
    gAudioHandlersA[8] = func_800D9134;
    gAudioHandlersReady = 1;
    select_audio_mode(0);
    size = D_B02E2CD0 - D_B02D2790;
    rom_dma_read((u32)D_B02D2790, D_803DA800, size);
    lzari_decode(size, D_803DA800, 0x25800, gAudioModeState.currentValue);
    select_audio_mode(1);
}
