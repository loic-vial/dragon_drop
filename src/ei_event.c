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
    for (ei_eventlist_t* tmp = first_eventlist ; tmp != NULL ; tmp = tmp->next)
    {
        if (tmp->eventtype == eventtype &&
            tmp->widget == widget &&
            ((tag != NULL && tmp->tag != NULL && strcmp(tmp->tag, tag) == 0) ||
             (tag == NULL && tmp->tag == NULL)) &&
            tmp->callback == callback &&
            tmp->user_param == user_param)
        {
            if (tmp->previous != NULL)
                tmp->previous->next = tmp->next;
            if (tmp->next != NULL)
                tmp->next->previous = tmp->previous;
        }
    }
}


