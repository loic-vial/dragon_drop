#include "ei_toplevel.h"
#include "ei_toplevel_banner.h"
#include "ei_toplevel_resize.h"
#include <string.h>
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
    frameclass->allocfunc = &ei_frame_allocfunc;
    frameclass->releasefunc = &ei_frame_releasefunc;
    frameclass->drawfunc = &ei_frame_drawfunc;
    frameclass->setdefaultsfunc = &ei_frame_setdefaultsfunc;
    frameclass->geomnotifyfunc = NULL;
    frameclass->next = NULL;
    ei_widgetclass_register(frameclass);
}

void ei_button_register_class()
{
    ei_widgetclass_t* buttonclass = (ei_widgetclass_t*) malloc(sizeof(ei_widgetclass_t));
    strcpy(buttonclass->name, "button");
    buttonclass->allocfunc = &ei_button_allocfunc;
    buttonclass->releasefunc = &ei_button_releasefunc;
    buttonclass->drawfunc = &ei_frame_drawfunc;
    buttonclass->setdefaultsfunc = &ei_button_setdefaultsfunc;
    buttonclass->geomnotifyfunc = NULL;
    buttonclass->next = NULL;
    ei_widgetclass_register(buttonclass);
    ei_bind(ei_ev_mouse_buttondown, NULL, "button", ei_button_click_down, NULL);
    ei_bind(ei_ev_mouse_buttonup, NULL, "button", ei_button_click_up, NULL);
}

void ei_toplevel_register_class()
{
    ei_widgetclass_t* toplevelclass = (ei_widgetclass_t*) malloc(sizeof(ei_widgetclass_t));
    strcpy(toplevelclass->name, "toplevel");
    toplevelclass->allocfunc = &ei_toplevel_allocfunc;
    toplevelclass->releasefunc = &ei_toplevel_releasefunc;
    toplevelclass->drawfunc = &ei_frame_drawfunc;
    toplevelclass->setdefaultsfunc = &ei_toplevel_setdefaultsfunc;
    toplevelclass->geomnotifyfunc = NULL;
    toplevelclass->next = NULL;
    ei_widgetclass_register(toplevelclass);
    ei_banner_register_class();
    ei_resize_register_class();
}
