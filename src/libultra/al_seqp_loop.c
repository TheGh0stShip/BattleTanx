/* libaudio 2.0I seqploop.c: reconstructed from decompals/ultralib e24c836;
 * complete object verified against BattleTanx USA Rev 0. */

#include <libaudio.h>

void alSeqpLoop(ALSeqPlayer *seqp, ALSeqMarker *start, ALSeqMarker *end, 
                s32 count)
{
    ALEvent       evt;

    evt.type            = AL_SEQP_LOOP_EVT;
    evt.msg.loop.start  = start;
    evt.msg.loop.end    = end;
    evt.msg.loop.count  = count;
                    
    alEvtqPostEvent(&seqp->evtq, &evt, 0);
}

