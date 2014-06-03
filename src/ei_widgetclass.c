#include "ei_widgetclass.h"
#include <stdio.h>
#include <stdlib.h>
#include "ei_frame.h"
#include <string.h>

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
    NULL;
}

void ei_toplevel_register_class()
{
    NULL;
}
