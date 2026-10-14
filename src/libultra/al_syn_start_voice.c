/* libultra 2.0I audio/synstartvoice.c: reconstructed source from decompals/ultralib e24c836
 * (src/audio/synstartvoice.c). The complete object is verified byte-for-byte against the
 * BattleTanx USA Rev 0 ROM. */
#include "synthInternals.h"
#include <os_internal.h>
#include <ultraerror.h>

void alSynStartVoice(ALSynth *synth, ALVoice *v, ALWaveTable *table)
{
    ALStartParam  *update;
    ALFilter *f;

    if (v->pvoice) {

        update = (ALStartParam *)__allocParam();
        ALFailIf(update == 0, ERR_ALSYN_NO_UPDATE);

        /*
         * send the start message to the motion control filter
         */
        update->delta  = synth->paramSamples + v->pvoice->offset;
        update->type   = AL_FILTER_START_VOICE;
        update->wave   = table;
        update->next   = 0;
        update->unity  = v->unityPitch;

        f = v->pvoice->channelKnob;
        (*f->setParam)(f, AL_FILTER_ADD_UPDATE, update);
    }
}
