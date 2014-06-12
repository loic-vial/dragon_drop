#include "ei_button.h"
#include "ei_utils.h"
#include "ei_utils_2.h"
#include "ei_event.h"
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
    ei_linked_tag_t* tag = ei_initial_tag_t( widget);
    button->frame.tag = tag;
    button->frame.relief = ei_relief_raised;
}

ei_bool_t ei_button_click_down(ei_widget_t* widget, ei_event_t* event, void* user_param)
{
    ei_frame_t* frame = (ei_frame_t*) widget;
    frame->relief = ei_relief_sunken;
    return EI_FALSE;
}

ei_bool_t ei_button_click_up(ei_widget_t* widget, ei_event_t* event, void* user_param)
{
    ei_frame_t* frame = (ei_frame_t*) widget;
    frame->relief = ei_relief_raised;
    return EI_FALSE;
}
