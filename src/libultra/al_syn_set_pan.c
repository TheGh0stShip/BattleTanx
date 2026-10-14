/* libultra 2.0I audio/synsetpan.c: reconstructed source from decompals/ultralib e24c836
 * (src/audio/synsetpan.c). The complete object is verified byte-for-byte against the
 * BattleTanx USA Rev 0 ROM. */
#include "synthInternals.h"
#include <os_internal.h>
#include <ultraerror.h>

void alSynSetPan(ALSynth *synth, ALVoice *v, u8 pan)
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
         * set offset and pan data
         */
        update->delta  = synth->paramSamples + v->pvoice->offset;
        update->type   = AL_FILTER_SET_PAN;
        update->data.i = pan;
        update->next   = 0;

        f = v->pvoice->channelKnob;
        (*f->setParam)(f, AL_FILTER_ADD_UPDATE, update);
    }
}
