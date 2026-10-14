/* libultra (non-n) audio library layouts used by this range (o32, big-endian). */
#ifndef AUDIO_H
#define AUDIO_H
#include "ultra.h"

typedef s32 (*ALDMAproc)(s32 addr, s32 len, void *state);
typedef ALDMAproc (*ALDMANew)(void *state);
typedef void *(*ALFilterHandler)(void *, s16 *, s32, s32, void *);
typedef s32 (*ALSetParam)(void *, s32, void *);

typedef struct ALFilter_s {
    struct ALFilter_s *source; /* 0x00 */
    ALFilterHandler handler;   /* 0x04 */
    ALSetParam setParam;       /* 0x08 */
    s16 inp;                   /* 0x0C */
    s16 outp;                  /* 0x0E */
    s32 type;                  /* 0x10 */
} ALFilter;

typedef struct {
    ALFilter filter;
    s32 dramout;               /* 0x14 */
    s32 first;                 /* 0x18 */
} ALSave;

typedef struct {
    ALFilter filter;
    s32 sourceCount;           /* 0x14 */
    s32 maxSources;            /* 0x18 */
    ALFilter **sources;        /* 0x1C */
} ALMainBus, ALAuxBus;

typedef struct ALParam_s {
    struct ALParam_s *next;    /* 0x00 */
    s32 delta;                 /* 0x04 */
    s16 type;                  /* 0x08 */
    union { f32 f; s32 i; } data;          /* 0x0C */
    union { f32 f; s32 i; } moredata;      /* 0x10 */
    union { f32 f; s32 i; } stillmoredata; /* 0x14 */
    union { f32 f; s32 i; } yetstillmoredata; /* 0x18 */
} ALParam;

typedef struct {
    ALFilter filter;
    void *state;               /* 0x14 */
    f32 ratio;                 /* 0x18 */
    s32 upitch;                /* 0x1C */
    f32 delta;                 /* 0x20 */
    s32 first;                 /* 0x24 */
    ALParam *ctrlList;         /* 0x28 */
    ALParam *ctrlTail;         /* 0x2C */
    s32 motion;                /* 0x30 */
} ALResampler;

typedef struct {
    u32 start;
    u32 end;
    u32 count;
} ALRawLoop;

typedef struct {
    ALFilter filter;
    void *state;               /* 0x14 */
    void *lstate;              /* 0x18 */
    ALRawLoop loop;            /* 0x1C */
    struct ALWaveTable_s *table; /* 0x28 */
    s32 bookSize;              /* 0x2C */
    ALDMAproc dma;             /* 0x30 */
    void *dmaState;            /* 0x34 */
    s32 sample;                /* 0x38 */
    s32 lastsam;               /* 0x3C */
    s32 first;                 /* 0x40 */
    s32 memin;                 /* 0x44 */
} ALLoadFilter;

typedef struct {
    ALFilter filter;
    void *state;               /* 0x14 */
    s16 pan;                   /* 0x18 */
    s16 volume;                /* 0x1A */
    s16 cvolL;                 /* 0x1C */
    s16 cvolR;                 /* 0x1E */
    s16 dryamt;                /* 0x20 */
    s16 wetamt;                /* 0x22 */
    u16 lratl;                 /* 0x24 */
    s16 lratm;                 /* 0x26 */
    s16 ltgt;                  /* 0x28 */
    u16 rratl;                 /* 0x2A */
    s16 rratm;                 /* 0x2C */
    s16 rtgt;                  /* 0x2E */
    s32 delta;                 /* 0x30 */
    s32 segEnd;                /* 0x34 */
    s32 first;                 /* 0x38 */
    ALParam *ctrlList;         /* 0x3C */
    ALParam *ctrlTail;         /* 0x40 */
    ALFilter **sources;        /* 0x44 */
    s32 motion;                /* 0x48 */
} ALEnvMixer;

typedef struct {
    s16 fc;                    /* 0x00 */
    s16 fgain;                 /* 0x02 */
    union {
        s16 fccoef[16];
        s64 force_aligned;
    } fcvec;                   /* 0x08 */
    void *fstate;              /* 0x28 */
    s32 first;                 /* 0x2C */
} ALLowPass;

typedef struct {
    u32 input;                 /* 0x00 */
    u32 output;                /* 0x04 */
    s16 ffcoef;                /* 0x08 */
    s16 fbcoef;                /* 0x0A */
    s16 gain;                  /* 0x0C */
    f32 rsinc;                 /* 0x10 */
    f32 rsval;                 /* 0x14 */
    s32 rsdelta;               /* 0x18 */
    f32 rsgain;                /* 0x1C */
    ALLowPass *lp;             /* 0x20 */
    ALResampler *rs;           /* 0x24 */
} ALDelay;

typedef struct {
    ALFilter filter;
    s16 *base;                 /* 0x14 */
    s16 *input;                /* 0x18 */
    u32 length;                /* 0x1C */
    ALDelay *delay;            /* 0x20 */
    u8 section_count;          /* 0x24 */
    void *paramHdl;            /* 0x28 */
} ALFx;

typedef struct {
    s32 maxVVoices;
    s32 maxPVoices;
    s32 maxUpdates;
    s32 maxFXbusses;
    void *dmaproc;
    void *heap;
    s32 outputRate;            /* 0x18 */
    u8 fxType;                 /* 0x1C */
    s32 *params;               /* 0x20 */
} ALSynConfig;

typedef struct {
    u8 *base;
    u8 *cur;
    s32 len;
    s32 count;
} ALHeap;

#define AL_ADPCM 0
#define AL_RESAMPLE 1
#define AL_BUFFER 2
#define AL_SAVE 3
#define AL_ENVMIX 4
#define AL_FX 5
#define AL_AUXBUS 6
#define AL_MAINBUS 7
#define AL_STOPPED 0
#define AL_PLAYING 1

extern void alFilterNew(ALFilter *f, void *pull, void *param, s32 type);
extern void *alHeapDBAlloc(u8 *file, s32 line, ALHeap *hp, s32 num, s32 size);
#define alHeapAlloc(hp, num, size) alHeapDBAlloc(0, 0, hp, num, size)
#endif
