#include "os_thread.h"

void __osDequeueThread(OSThread **queue, OSThread *thread)
{
    register OSThread **link = queue;
    register OSThread *current = *link;

    while (current != 0) {
        if (current == thread) {
            *link = thread->next;
            return;
        }
        link = &current->next;
        current = *link;
    }
}
