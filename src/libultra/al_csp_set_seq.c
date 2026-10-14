/* libaudio 2.0I cspsetseq.c: reconstructed from decompals/ultralib e24c836;
 * complete object verified against BattleTanx USA Rev 0. */

#include <libaudio.h>

void alCSPSetSeq(ALCSPlayer *seqp, ALCSeq *seq)
{
    ALEvent evt;

    evt.type = AL_SEQP_SEQ_EVT;
    evt.msg.spseq.seq = seq;

    alEvtqPostEvent(&seqp->evtq, &evt, 0);
}

