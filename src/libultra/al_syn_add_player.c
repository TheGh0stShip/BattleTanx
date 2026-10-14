/* libultra 2.0I audio/synaddplayer.c: reconstructed source from decompals/ultralib e24c836
 * (src/audio/synaddplayer.c). The complete object is verified byte-for-byte against the
 * BattleTanx USA Rev 0 ROM. */
#include "synthInternals.h"
#include <os_internal.h>

void alSynAddPlayer(ALSynth *drvr, ALPlayer *client)
{
    OSIntMask mask = osSetIntMask(OS_IM_NONE);

    client->samplesLeft = drvr->curSamples;
    client->next = drvr->head;
    drvr->head   = client;

    osSetIntMask(mask);
}
