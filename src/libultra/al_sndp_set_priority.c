/* libaudio 2.0I sndpsetpriority.c: reconstructed from decompals/ultralib e24c836;
 * complete object verified against BattleTanx USA Rev 0. */

#include "sndp.h"
#include <os_internal.h>
#include <ultraerror.h>

void alSndpSetPriority(ALSndPlayer *sndp, ALSndId id, u8 priority)
{
    ALSoundState  *sState = sndp->sndState;

#ifdef _DEBUG
    if ((id >= sndp->maxSounds) || (id < 0)){
        __osError(ERR_ALSNDPSETPRIORITY, 2, id, sndp->maxSounds-1);
	return;
    }
#endif

    sState[id].priority = priority;
}

