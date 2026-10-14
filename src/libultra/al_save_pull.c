#include "types.h"

typedef union {
    struct {
        u32 w0;
        u32 w1;
    } words;
    s64 force_align;
} Acmd;

typedef struct ALFilter_s ALFilter;
typedef Acmd *(*ALFilterHandler)(ALFilter *, s16 *, s32, s32, Acmd *);

struct ALFilter_s {
    ALFilter *source;
    ALFilterHandler handler;
    void *setParam;
    s16 inp;
    s16 outp;
    s32 type;
};

typedef struct {
    ALFilter filter;
    s32 dramout;
    s32 first;
} ALSave;

#define _SHIFTL(v, s, w) ((u32)(((u32)(v) & ((0x01 << (w)) - 1)) << (s)))
#define A_SAVEBUFF 6
#define A_SETBUFF 8
#define A_INTERLEAVE 13

#define aSetBuffer(pkt, f, i, o, c)                                                    \
    {                                                                                  \
        Acmd *_a = (Acmd *)(pkt);                                                      \
        _a->words.w0 = _SHIFTL(A_SETBUFF, 24, 8) | _SHIFTL(f, 16, 8) |               \
                       _SHIFTL(i, 0, 16);                                              \
        _a->words.w1 = _SHIFTL(o, 16, 16) | _SHIFTL(c, 0, 16);                        \
    }
#define aInterleave(pkt, l, r)                                                         \
    {                                                                                  \
        Acmd *_a = (Acmd *)(pkt);                                                      \
        _a->words.w0 = _SHIFTL(A_INTERLEAVE, 24, 8);                                  \
        _a->words.w1 = _SHIFTL(l, 16, 16) | _SHIFTL(r, 0, 16);                        \
    }
#define aSaveBuffer(pkt, s)                                                            \
    {                                                                                  \
        Acmd *_a = (Acmd *)(pkt);                                                      \
        _a->words.w0 = _SHIFTL(A_SAVEBUFF, 24, 8);                                    \
        _a->words.w1 = (u32)(s);                                                       \
    }

Acmd *alSavePull(ALSave *filter, s16 *outp, s32 outCount, s32 sampleOffset, Acmd *p)
{
    Acmd *ptr;

    ptr = filter->filter.source->handler(filter->filter.source, outp, outCount,
                                         sampleOffset, p);
    aSetBuffer(ptr++, 0, 0, 0, outCount << 1);
    aInterleave(ptr++, 0x440, 0x580);
    aSetBuffer(ptr++, 0, 0, 0, outCount << 2);
    aSaveBuffer(ptr++, filter->dramout);
    return ptr;
}
