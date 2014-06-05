#ifndef EI_TOPLEVEL_H
#define EI_TOPLEVEL_H

#include "ei_types.h"
#include "ei_widget.h"

typedef struct ei_toplevel_t
{
    ei_widget_t widget;
    ei_size_t		requested_size;
    ei_color_t		color;
    int			border_width;
    char*			title;
    ei_bool_t		closable;
    ei_axis_set_t		resizable;
    ei_size_t*		min_size;

}
ei_toplevel_t;

void* allocfunc_toplevel();

void releasefunc_toplevel(ei_widget_t* widget);

void drawfunc_toplevel(ei_widget_t* widget, ei_surface_t surface,
                       ei_surface_t pick_surface, ei_rect_t* clipper);

void setdefaultsfunc_toplevel(ei_widget_t* widget);

void geomnotifyfunc_toplevel(ei_widget_t* widget, ei_rect_t rect);

#endif
