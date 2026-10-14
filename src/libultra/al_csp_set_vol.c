/* libaudio 2.0I cspsetvol.c: reconstructed from decompals/ultralib e24c836;
 * complete object verified against BattleTanx USA Rev 0. */

#include <libaudio.h>

void alCSPSetVol(ALCSPlayer *seqp, s16 vol)
{
    ALEvent       evt;

    evt.type            = AL_SEQP_VOL_EVT;
    evt.msg.spvol.vol   = vol;
    
    alEvtqPostEvent(&seqp->evtq, &evt, 0);
}

