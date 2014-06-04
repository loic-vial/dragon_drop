#ifndef EI_TOPLEVEL_H
#define EI_TOPLEVEL_H

#include "ei_widget.h"

typedef struct ei_toplevel_t
{
    ei_widget_t widget;

}
ei_toplevel_t;

void* allocfunc_toplevel();

void releasefunc_toplevel(ei_widget_t* widget);

void drawfunc_toplevel(ei_widget_t* widget, ei_surface_t surface,
                     ei_surface_t pick_surface, ei_rect_t* clipper);

void setdefaultsfunc_toplevel(ei_widget_t* widget);

void geomnotifyfunc_toplevel(ei_widget_t* widget, ei_rect_t rect);

#endif
