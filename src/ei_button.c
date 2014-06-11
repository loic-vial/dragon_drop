#include "ei_button.h"
#include "ei_utils.h"
#include "ei_utils_2.h"
#include "ei_event.h"
#include <stdlib.h>

void* allocfunc_button()
{
    return calloc(1, sizeof(ei_button_t));
}

void releasefunc_button(ei_widget_t* widget)
{
    ei_button_t* button = (ei_button_t*) widget;
    ei_unbind(ei_ev_mouse_buttonup, widget, NULL, button->callback, button->user_param);
}

void drawfunc_button(ei_widget_t* widget, ei_surface_t surface,
                     ei_surface_t pick_surface, ei_rect_t* clipper)
{
    drawfunc_frame(widget, surface, pick_surface, clipper);
}

void setdefaultsfunc_button(ei_widget_t* widget)
{
    setdefaultsfunc_frame(widget);
    ei_button_t* button = (ei_button_t*) widget;
    button->callback = NULL;
    button->user_param = NULL;
}

void geomnotifyfunc_button(ei_widget_t* widget, ei_rect_t rect)
{

}

