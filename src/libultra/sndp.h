/* libaudio 2.0I sndp.h: interface reconstructed from decompals/ultralib e24c836. */


#ifndef __SNDP__
#define __SNDP__

#include <libaudio.h>

#ifndef MIN
#define MIN(a,b) (((a)<(b))?(a):(b))
#endif

#ifndef MAX
#define MAX(a,b) (((a)>(b))?(a):(b))
#endif

#define MIN_RATIO	0.0001

typedef enum {
    AL_SNDP_PLAY_EVT,
    AL_SNDP_STOP_EVT,
    AL_SNDP_PAN_EVT,
    AL_SNDP_VOL_EVT,
    AL_SNDP_PITCH_EVT,
    AL_SNDP_API_EVT,
    AL_SNDP_DECAY_EVT,
    AL_SNDP_END_EVT,
    AL_SNDP_FX_EVT
} ALSndpMsgType;

typedef struct {
    ALVoice     voice;     
    ALSound     *sound;         /* sound referenced here */
    s16         priority;
    f32         pitch;          /* current playback pitch                    */
    s32         state;          /* play state for this sound                 */
    s16         vol;            /* volume - combined with volume from bank   */
    ALPan       pan;            /* pan - 0 = left, 127 = right               */
    u8          fxMix;          /* wet/dry mix - 0 = dry, 127 = wet          */
} ALSoundState;

typedef union {

    ALEvent             msg;

    struct {
        s16             type;
        ALSoundState    *state;
    } common;
    
    struct {
        s16             type;
        ALSoundState    *state;
        s16             vol;
    } vol;
    
    struct {
        s16             type;
        ALSoundState    *state;
        f32             pitch;
    } pitch;
    
    struct {
        s16             type;
        ALSoundState    *state;
        ALPan           pan;
    } pan;
    
    struct {
        s16             type;
        ALSoundState    *state;
        u8              mix;
    } fx;
    
} ALSndpEvent;

static  ALMicroTime     _sndpVoiceHandler(void *node);
static  void            _handleEvent(ALSndPlayer *sndp, ALSndpEvent *event);
static	void		_removeEvents(ALEventQueue *evtq, ALSoundState *state);
static	s32		_DivS32ByF32 (s32 i, f32 f);

#endif
