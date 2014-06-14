#ifndef EI_EVENTLIST_H
#define EI_EVENTLIST_H

#include "ei_event.h"

typedef struct ei_eventlist_t
{
    ei_eventtype_t eventtype;
    ei_widget_t* widget;
    ei_tag_t tag;
    ei_callback_t callback;
    void* user_param;
    struct ei_eventlist_t* next;
    struct ei_eventlist_t* previous;
}
ei_eventlist_t;

extern ei_eventlist_t* first_event;

#endif