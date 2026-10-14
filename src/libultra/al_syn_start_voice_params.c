/* libultra 2.0I audio/synstartvoiceparam.c: reconstructed source from decompals/ultralib e24c836
 * (src/audio/synstartvoiceparam.c). The complete object is verified byte-for-byte against the
 * BattleTanx USA Rev 0 ROM. */
#include "synthInternals.h"
#include <libaudio.h>
#include <ultraerror.h>
#include <os_internal.h>

#if BUILD_VERSION < VERSION_J
#ident "$Revision: 1.17 $"
#endif

void alSynStartVoiceParams(ALSynth *s, ALVoice *v, ALWaveTable *w,
                           f32 pitch, s16 vol, ALPan pan, u8 fxmix,
                           ALMicroTime t)
{
    ALStartParamAlt  *update;
    ALFilter    *f;

    if (v->pvoice) {
        /*
         * get new update struct from the free list
         */
        update = (ALStartParamAlt *)__allocParam();
        ALFailIf(update == 0, ERR_ALSYN_NO_UPDATE);

#if BUILD_VERSION >= VERSION_J
        if (fxmix > 127) {
            fxmix = 127;
        }
#else
        if (fxmix < 0) { // Not possible
            fxmix = -fxmix;
        }
#endif

        /*
         * set offset and fxmix data
         */
        update->delta  = s->paramSamples + v->pvoice->offset;
        update->next   = 0;
        update->type   = AL_FILTER_START_VOICE_ALT;

        update->unity  = v->unityPitch;
        update->pan    = pan;
        update->volume = vol;
        update->fxMix  = fxmix;
        update->pitch  = pitch;
        update->samples = _timeToSamples(s, t);
        update->wave    = w;

        f = v->pvoice->channelKnob;
        (*f->setParam)(f, AL_FILTER_ADD_UPDATE, update);
    }

}
