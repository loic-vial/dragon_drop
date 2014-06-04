#include "ei_eventlist.h"
#include <stdlib.h>
#include <string.h>

ei_eventlist_t* first_eventlist = NULL;

ei_eventlist_t* ei_findevent(ei_eventtype_t eventtype,ei_widget_t* widget,ei_tag_t tag,  ei_callback_t  callback, void*   user_param)
{
    ei_eventlist_t* tmp=first_eventlist;
    for (tmp = first_eventlist; tmp != NULL ; tmp = tmp->next)
    {
        if(tmp->eventtype==eventtype || tmp->widget == widget ||strcmp(tmp->tag,tag)==0 || tmp->callback==callback ||tmp->user_param == user_param)
        {
            return tmp;
        }
    }

    return NULL;
}

ei_eventlist_t* _ei_findevent(ei_eventtype_t eventtype)
{
    ei_eventlist_t* tmp = first_eventlist;
    for (tmp = first_eventlist ; tmp != NULL ; tmp = tmp->next)
    {
        if (tmp->eventtype==eventtype)
        {
            return tmp;
        }
    }

    return NULL;
}
