typedef struct ALLink {
    struct ALLink *next;
    struct ALLink *previous;
} ALLink;

void alUnlink(ALLink *element)
{
    if (element->next != 0) {
        element->next->previous = element->previous;
    }
    if (element->previous != 0) {
        element->previous->next = element->next;
    }
}

void alLink(ALLink *element, ALLink *after)
{
    element->next = after->next;
    element->previous = after;
    if (after->next != 0) {
        after->next->previous = element;
    }
    after->next = element;
}
