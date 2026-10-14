/* libaudio 2.0I cspstop.c: reconstructed from decompals/ultralib e24c836;
 * complete object verified against BattleTanx USA Rev 0. */

#include <libaudio.h>

void alCSPStop(ALCSPlayer *seqp)
{
    ALEvent     evt;

    evt.type = AL_SEQP_STOPPING_EVT;                    
    alEvtqPostEvent(&seqp->evtq, &evt, 0);
}

