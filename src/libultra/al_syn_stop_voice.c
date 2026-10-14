/* libultra 2.0I audio/synstopvoice.c: reconstructed source from decompals/ultralib e24c836
 * (src/audio/synstopvoice.c). The complete object is verified byte-for-byte against the
 * BattleTanx USA Rev 0 ROM. */
#include "synthInternals.h"
#include <os_internal.h>
#include <ultraerror.h>


void alSynStopVoice(ALSynth *synth, ALVoice *v)
{
    ALParam  *update;
    ALFilter *f;

    if (v->pvoice) {

        update = __allocParam();
        ALFailIf(update == 0, ERR_ALSYN_NO_UPDATE);

        update->delta  = synth->paramSamples + v->pvoice->offset;
        update->type   = AL_FILTER_STOP_VOICE;
        update->next   = 0;

        f = v->pvoice->channelKnob;
        (*f->setParam)(f, AL_FILTER_ADD_UPDATE, update);
    }
}
