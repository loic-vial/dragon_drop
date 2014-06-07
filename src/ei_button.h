#ifndef EI_BUTTON_H
#define EI_BUTTON_H

#include "ei_widget.h"
#include "ei_frame.h"

typedef struct ei_button_t
{
    ei_frame_t frame;
    int corner_radius;
    ei_callback_t callback;
    void* user_param;
}
ei_button_t;

void* allocfunc_button();

void releasefunc_button(ei_widget_t* widget);

void drawfunc_button(ei_widget_t* widget, ei_surface_t surface,
                     ei_surface_t pick_surface, ei_rect_t* clipper);

void setdefaultsfunc_button (ei_widget_t* widget);

void geomnotifyfunc_button (ei_widget_t* widget, ei_rect_t rect);

#endif
