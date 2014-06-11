#include "ei_event.h"
#include "ei_eventlist.h"
#include <stdlib.h>
#include <string.h>

void ei_bind(ei_eventtype_t  eventtype, ei_widget_t*  widget,
                 ei_tag_t  tag, ei_callback_t  callback, void* user_param)
{
    if (widget == NULL && tag == NULL) return;
    if (widget != NULL && tag != NULL) return;
    ei_eventlist_t* event = (ei_eventlist_t*) malloc(sizeof(ei_eventlist_t));
    event->eventtype = eventtype;
    event->widget = widget;
    event->tag = tag;
    event->callback = callback;
    event->next = NULL;
    event->previous = NULL;
    event->user_param = user_param;
    if (first_eventlist == NULL)
    {
        first_eventlist = event;
    }
    else
    {
        ei_eventlist_t* tmp;
        for (tmp = first_eventlist; tmp->next != NULL ; tmp = tmp->next);
        event->previous = tmp;
        tmp->next = event;
    }
}

void ei_unbind (ei_eventtype_t eventtype, ei_widget_t* widget, ei_tag_t tag,
                ei_callback_t callback, void* user_param)
{
    ei_eventlist_t* event = first_eventlist;
    while (event != NULL)
    {
        ei_eventlist_t* next_event = event->next;
        if (event->eventtype == eventtype &&
            event->widget == widget &&
            ((tag != NULL && event->tag != NULL && strcmp(event->tag, tag) == 0) ||
             (tag == NULL && event->tag == NULL)) &&
            event->callback == callback &&
            event->user_param == user_param)
        {
            if (event->previous != NULL)
                event->previous->next = event->next;
            if (event->next != NULL)
                event->next->previous = event->previous;
            free(event);
        }
        event = next_event;
    }
}


