#ifndef EI_FRAME_H
#define EI_FRAME_H

#include "ei_widget.h"

typedef struct ei_frame_t
{
    ei_widget_t widget;
    ei_color_t color;
    int border_width;
    ei_relief_t relief;
    char* text;
    ei_font_t text_font ;
    ei_color_t text_color;
    ei_anchor_t text_anchor;
    ei_surface_t img;
    ei_rect_t* img_rect;
    ei_anchor_t img_anchor;
    int corner_radius;
    ei_bool_t rounded_up;
    ei_bool_t rounded_down;
}
ei_frame_t;

void* ei_frame_allocfunc();

void ei_frame_releasefunc(ei_widget_t* widget);

void ei_frame_drawfunc(ei_widget_t* widget, ei_surface_t surface,
                      ei_surface_t pick_surface, ei_rect_t* clipper);

void ei_frame_setdefaultsfunc(ei_widget_t* widget);

#endif
