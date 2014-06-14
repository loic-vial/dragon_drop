#include "ei_button.h"
#include <stdlib.h>

void* ei_button_allocfunc()
{
    return calloc(1, sizeof(ei_button_t));
}

void ei_button_releasefunc(ei_widget_t* widget)
{
    ei_button_t* button = (ei_button_t*) widget;
    ei_unbind(ei_ev_mouse_buttonup, widget, NULL, button->callback, button->user_param);
}

void ei_button_setdefaultsfunc(ei_widget_t* widget)
{
    ei_frame_setdefaultsfunc(widget);
    ei_button_t* button = (ei_button_t*) widget;
    button->callback = NULL;
    button->user_param = NULL;
    button->frame.border_width = 3;
    button->frame.relief = ei_relief_raised;
    ei_set_initial_tags(widget);
}

ei_bool_t ei_button_click_down(ei_widget_t* widget, ei_event_t* event, void* user_param)
{
    ei_frame_t* frame = (ei_frame_t*) widget;
    frame->relief = ei_relief_sunken;
    return EI_TRUE;
}

ei_bool_t ei_button_click_up(ei_widget_t* widget, ei_event_t* event, void* user_param)
{
    ei_frame_t* frame = (ei_frame_t*) widget;
    frame->relief = ei_relief_raised;
    return EI_TRUE;
}
