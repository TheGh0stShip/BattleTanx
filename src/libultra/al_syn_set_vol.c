/* libultra 2.0I audio/synsetvol.c: reconstructed source from decompals/ultralib e24c836
 * (src/audio/synsetvol.c). The complete object is verified byte-for-byte against the
 * BattleTanx USA Rev 0 ROM. */
#include "synthInternals.h"
#include <os_internal.h>
#include <ultraerror.h>

void alSynSetVol(ALSynth *synth, ALVoice *v, s16 volume, ALMicroTime t)
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
         * set offset and volume data
         */
        update->delta           = synth->paramSamples + v->pvoice->offset;
        update->type            = AL_FILTER_SET_VOLUME;
        update->data.i          = volume;
        update->moredata.i      = _timeToSamples(synth, t);
        update->next            = 0;

        f = v->pvoice->channelKnob;
        (*f->setParam)(f, AL_FILTER_ADD_UPDATE, update);
    }
}
