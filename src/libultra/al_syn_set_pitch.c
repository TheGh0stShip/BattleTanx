/* libultra 2.0I audio/synsetpitch.c: reconstructed source from decompals/ultralib e24c836
 * (src/audio/synsetpitch.c). The complete object is verified byte-for-byte against the
 * BattleTanx USA Rev 0 ROM. */
#include "synthInternals.h"
#include <os_internal.h>
#include <ultraerror.h>

void alSynSetPitch(ALSynth *synth, ALVoice *v, f32 pitch)
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
         * set offset and pitch data
         */
        update->delta  = synth->paramSamples + v->pvoice->offset;
        update->type   = AL_FILTER_SET_PITCH;
        update->data.f = pitch;
        update->next   = 0;

        f = v->pvoice->channelKnob;
        (*f->setParam)(f, AL_FILTER_ADD_UPDATE, update);
    }
}
