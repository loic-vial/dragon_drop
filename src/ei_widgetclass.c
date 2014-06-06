#include "ei_widgetclass.h"
#include "ei_frame.h"
#include "ei_button.h"
#include "ei_toplevel.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

ei_widgetclass_t* first_class = NULL;

void ei_widgetclass_register (ei_widgetclass_t* widgetclass)
{
    if (first_class == NULL)
    {
        first_class = widgetclass;
    }
    else
    {
        ei_widgetclass_t* tmp;
        for (tmp = first_class ; tmp->next != NULL ; tmp = tmp->next);
        tmp->next = widgetclass;
    }
}

ei_widgetclass_t* ei_widgetclass_from_name(ei_widgetclass_name_t name)
{
    for (ei_widgetclass_t* tmp = first_class ; tmp != NULL ; tmp = tmp->next)
    {
        if (strcmp(name, tmp->name) == 0)
        {
            return tmp;
        }
    }
    return NULL;
}

void ei_frame_register_class()
{
    ei_widgetclass_t* frameclass = (ei_widgetclass_t*) malloc(sizeof(ei_widgetclass_t));
    strcpy(frameclass->name, "frame");
    frameclass->allocfunc = &allocfunc_frame;
    frameclass->releasefunc = &releasefunc_frame;
    frameclass->drawfunc = &drawfunc_frame;
    frameclass->setdefaultsfunc = &setdefaultsfunc_frame;
    frameclass->geomnotifyfunc = &geomnotifyfunc_frame;
    frameclass->next = NULL;
    ei_widgetclass_register(frameclass);
}

void ei_button_register_class()
{
    ei_widgetclass_t* buttonclass = (ei_widgetclass_t*) malloc(sizeof(ei_widgetclass_t));
    strcpy(buttonclass->name, "button");
    buttonclass->allocfunc = &allocfunc_button;
    buttonclass->releasefunc = &releasefunc_button;
    buttonclass->drawfunc = &drawfunc_button;
    buttonclass->setdefaultsfunc = &setdefaultsfunc_button;
    buttonclass->geomnotifyfunc = &geomnotifyfunc_button;
    buttonclass->next = NULL;
    ei_widgetclass_register(buttonclass);
}

void ei_toplevel_register_class()
{
    ei_widgetclass_t* toplevelclass = (ei_widgetclass_t*) malloc(sizeof(ei_widgetclass_t));
    strcpy(toplevelclass->name, "toplevel");
    toplevelclass->allocfunc = &allocfunc_toplevel;
    toplevelclass->releasefunc = &releasefunc_toplevel;
    toplevelclass->drawfunc = &drawfunc_toplevel;
    toplevelclass->setdefaultsfunc = &setdefaultsfunc_toplevel;
    toplevelclass->geomnotifyfunc = &geomnotifyfunc_toplevel;
    toplevelclass->next = NULL;
    ei_widgetclass_register(toplevelclass);
    ei_callback_t drag_start = ei_toplevel_drag_start_callback;
    ei_bind(ei_ev_mouse_buttondown, NULL, "banner", drag_start, NULL);
}
