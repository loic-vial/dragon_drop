#include "ei_widgetclass.h"
#include <stdio.h>
#include <stdlib.h>
#include "ei_frame.h"

ei_widgetclass_t first_class;

void ei_widgetclass_register		(ei_widgetclass_t* widgetclass)
{
    ei_widgetclass_t tmp=first_class;
   /* while(tmp.next /= NULL)
    {
       tmp=first_class.next;
    }
    tmp.next=widgetclass;*/
}

ei_widgetclass_t*	ei_widgetclass_from_name	(ei_widgetclass_name_t name)
{
    NULL;
}

void			ei_frame_register_class 	()
{
    ei_widgetclass_t frame;
    strcpy(frame.name,"frame");
    frame.allocfunc=&allocfunc_frame;
    frame.releasefunc=&releasefunc_frame;
    frame.drawfunc=&drawfunc_frame;
    frame.setdefaultsfunc=&setdefaultsfunc_frame;
    frame.geomnotifyfunc=&geomnotifyfunc_frame;
    frame.next = NULL;
    ei_widgetclass_register(&frame);
}

void			ei_button_register_class 	()
{
    NULL;
}

void			ei_toplevel_register_class 	()
{
    NULL;
}
