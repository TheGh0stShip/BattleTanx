/* libaudio 2.0I sndpgetstate.c: reconstructed from decompals/ultralib e24c836;
 * complete object verified against BattleTanx USA Rev 0. */

#include "sndp.h"

s32 alSndpGetState(ALSndPlayer *sndp)
{
    ALSoundState  *sState = sndp->sndState;

    return (sState + sndp->target)->state;
}

