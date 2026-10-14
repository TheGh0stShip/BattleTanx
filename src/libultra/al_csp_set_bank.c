/* libaudio 2.0I cspsetbank.c: reconstructed from decompals/ultralib e24c836;
 * complete object verified against BattleTanx USA Rev 0. */

#include <libaudio.h>

void alCSPSetBank(ALCSPlayer *seqp, ALBank *b)
{
    ALEvent evt;

    evt.type = AL_SEQP_BANK_EVT;
    evt.msg.spbank.bank = b;

    alEvtqPostEvent(&seqp->evtq, &evt, 0);
}

