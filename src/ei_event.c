#include "ei_event.h"
#include "ei_eventlist.h"
#include <stdlib.h>

void ei_bind(ei_eventtype_t  eventtype, ei_widget_t*  widget,
                 ei_tag_t  tag, ei_callback_t  callback, void* user_param)
{
    ei_eventlist_t* event = (ei_eventlist_t*) malloc(sizeof(ei_eventlist_t));
    event->eventtype = eventtype;
    event->widget = widget;
    event->tag = tag;
    event->callback=callback;
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

void  ei_unbind  (ei_eventtype_t  eventtype,
                  ei_widget_t*  widget,
                  ei_tag_t  tag,
                  ei_callback_t  callback,
                  void*   user_param)
{
    //ei_eventlist_t* tmp =ei_findevent( eventtype ,widget ,tag, callback,user_param);
    //tmp->previous->next=tmp->next;
    //tmp->next->previous=tmp->previous;
}


