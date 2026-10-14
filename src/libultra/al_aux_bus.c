/* IDOFLAGS: -O3 -mips2 */
#include "audio.h"
#include "abi.h"

#define AL_AUX_L_OUT 0x6C0
#define AL_AUX_R_OUT 0x800
#define AL_FILTER_ADD_SOURCE 2

typedef Acmd *(*ALCmdHandler)(void *, s16 *, s32, s32, Acmd *);

Acmd *alAuxBusPull(void *filter, s16 *outp, s32 outCount, s32 sampleOffset, Acmd *p)
{
    Acmd *ptr = p;
    ALAuxBus *m = (ALAuxBus *)filter;
    ALFilter **sources = m->sources;
    s32 i;

    aClearBuffer(ptr++, AL_AUX_L_OUT, outCount << 1);
    aClearBuffer(ptr++, AL_AUX_R_OUT, outCount << 1);

    for (i = 0; i < m->sourceCount; i++)
        ptr = ((ALCmdHandler)sources[i]->handler)(sources[i], outp, outCount, sampleOffset, ptr);
    return ptr;
}

s32 alAuxBusParam(void *filter, s32 paramID, void *param)
{
    ALAuxBus *m = (ALAuxBus *)filter;
    ALFilter **sources = m->sources;

    switch (paramID) {
    case AL_FILTER_ADD_SOURCE:
        sources[m->sourceCount++] = (ALFilter *)param;
        break;
    default:
        break;
    }
    return 0;
}
