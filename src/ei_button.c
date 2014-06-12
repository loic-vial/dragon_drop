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
}

