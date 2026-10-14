#include "types.h"

typedef struct AudioBuffer {
    struct AudioBuffer *value00;
    u8 pad04[0x44];
    s16 value48;
    u8 pad4A[2];
    struct AudioBuffer *value4C;
} AudioBuffer;

extern void *alHeapDBAlloc(u8 *file, s32 line, void *heap, s32 num, s32 size) __asm__("func_80112140");
extern u8 gAudioHeap[] __asm__("D_80150340");
extern void *D_80152EF0[2];
extern s32 D_80152EF8;
extern AudioBuffer *D_801B4A48[3];

void allocate_audio_buffers(void) __asm__("func_8007A26C");

void allocate_audio_buffers(void) {
    u32 i;
    AudioBuffer *b;

    for (i = 0; i < 2; i++) {
        D_80152EF0[i] = alHeapDBAlloc(0, 0, gAudioHeap, 1, 0x8000);
    }
    for (i = 0; i < 3; i++) {
        D_801B4A48[i] = alHeapDBAlloc(0, 0, gAudioHeap, 1, 0x50);
        D_801B4A48[i]->value48 = 2;
        b = D_801B4A48[i];
        b->value4C = b;
        D_801B4A48[i]->value00 = alHeapDBAlloc(0, 0, gAudioHeap, 1, D_80152EF8 * 4);
    }
}
