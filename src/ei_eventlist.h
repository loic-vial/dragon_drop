#include <stdlib.h>
#include "ei_event.h"

typedef struct ei_eventlist_t
{
    ei_eventtype_t eventtype;
    ei_widget_t*  widget;
    ei_tag_t  tag;
    ei_callback_t  callback;
   struct ei_eventlist_t* next;
      struct ei_eventlist_t* previous;
   void*   user_param;

}
ei_eventlist_t;

extern ei_eventlist_t* first_eventlist;

ei_eventlist_t* ei_findevent(ei_eventtype_t eventtype,ei_widget_t* widget,ei_tag_t tag,  ei_callback_t  callback, void*   user_param);
