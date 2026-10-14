/* libultra 2.0I audio/synsetfxmix.c: reconstructed source from decompals/ultralib e24c836
 * (src/audio/synsetfxmix.c). The complete object is verified byte-for-byte against the
 * BattleTanx USA Rev 0 ROM. */
#include "synthInternals.h"
#include <os_internal.h>
#include <ultraerror.h>

void alSynSetFXMix(ALSynth *synth, ALVoice *v, u8 fxmix)
{
    ALParam  *update;
    ALFilter *f;

    if (v->pvoice) {
        /*
         * get new update struct from the free list
         */
        update = __allocParam();
        ALFailIf(update == 0, ERR_ALSYN_NO_UPDATE);

        /*
         * set offset and fxmix data
         */
        update->delta  = synth->paramSamples + v->pvoice->offset;
        update->type   = AL_FILTER_SET_FXAMT;
#if BUILD_VERSION >= VERSION_J
        if (fxmix > 127) {
            fxmix = 127;
        }
	    update->data.i = fxmix;
#else
        if (fxmix < 0) { // Not possible
            update->data.i = -fxmix;
        } else {
            update->data.i = fxmix;
        }
#endif
        update->next   = 0;

        f = v->pvoice->channelKnob;
        (*f->setParam)(f, AL_FILTER_ADD_UPDATE, update);
    }
}
