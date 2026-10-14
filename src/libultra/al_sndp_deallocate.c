/* libaudio 2.0I sndpdeallocate.c: reconstructed from decompals/ultralib e24c836;
 * complete object verified against BattleTanx USA Rev 0. */

#include "sndp.h"
#include <os_internal.h>
#include <ultraerror.h>

void alSndpDeallocate(ALSndPlayer *sndp, ALSndId id)
{
    ALSoundState  *sState = sndp->sndState;

    ALFailIf((sState + id)->state != AL_STOPPED, ERR_ALSNDPDEALLOCATE);

    sState[id].sound = 0;
    if (sndp->target == id) /* if we are deleting the target sound */
        sndp->target = -1;      
}

