/* libultra 2.0I audio/synfreevoice.c: reconstructed source from decompals/ultralib e24c836
 * (src/audio/synfreevoice.c). The complete object is verified byte-for-byte against the
 * BattleTanx USA Rev 0 ROM. */
#include <ultraerror.h>
#include <os_internal.h>
#include "synthInternals.h"

#include <os.h>

void alSynFreeVoice(ALSynth *drvr, ALVoice *voice)
{
    ALFilter *f;
    ALFreeParam *update;

    if (voice->pvoice) {

        if (voice->pvoice->offset) { /* if voice was stolen */
            update = (ALFreeParam *)__allocParam();
            ALFailIf(update == 0, ERR_ALSYN_NO_UPDATE);

            /*
             * set voice data
             */
            update->delta  = drvr->paramSamples + voice->pvoice->offset;
            update->type   = AL_FILTER_FREE_VOICE;
            update->pvoice = voice->pvoice;

            f = voice->pvoice->channelKnob;
            (*f->setParam)(f, AL_FILTER_ADD_UPDATE, update);
        } else {
            _freePVoice(drvr, voice->pvoice);
        }

        voice->pvoice = 0;

    }
}
