#include "types.h"

typedef struct OSMesgQueue {
    void *waiting_to_send;
    void *waiting_to_receive;
    s32 valid_count;
    s32 first;
    s32 message_count;
    void *messages;
} OSMesgQueue;

extern u8 D_801460F0[];

void osCreateMesgQueue(OSMesgQueue *queue, void *messages, s32 message_count)
{
    queue->waiting_to_send = D_801460F0;
    queue->waiting_to_receive = D_801460F0;
    queue->valid_count = 0;
    queue->first = 0;
    queue->message_count = message_count;
    queue->messages = messages;
}
