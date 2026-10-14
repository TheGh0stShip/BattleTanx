/* libaudio 2.0I sndpplay.c: reconstructed from decompals/ultralib e24c836;
 * complete object verified against BattleTanx USA Rev 0. */

#include "sndp.h"
#include <os_internal.h>
#include <ultraerror.h>

void alSndpPlay(ALSndPlayer *sndp)
{
    ALSndpEvent evt;
    ALSoundState  *sState = sndp->sndState;

    ALFailIf((sState + sndp->target)->state != AL_STOPPED, ERR_ALSNDPPLAY);
                                  
    evt.common.type = AL_SNDP_PLAY_EVT;
    evt.common.state = &sState[sndp->target];
    alEvtqPostEvent(&sndp->evtq, (ALEvent *)&evt, 0);
}

