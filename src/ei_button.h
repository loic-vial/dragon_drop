#ifndef EI_BUTTON_H
#define EI_BUTTON_H

#include "ei_frame.h"

typedef struct ei_button_t
{
    ei_frame_t frame;
    ei_callback_t callback;
    void* user_param;
}
ei_button_t;

void* ei_button_allocfunc();

void ei_button_releasefunc(ei_widget_t* widget);

void ei_button_setdefaultsfunc(ei_widget_t* widget);

ei_bool_t ei_button_click_down(ei_widget_t* widget, ei_event_t* event, void* user_param);

ei_bool_t ei_button_click_up(ei_widget_t* widget, ei_event_t* event, void* user_param);

#endif
