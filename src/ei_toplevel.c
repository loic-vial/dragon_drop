#include "ei_toplevel.h"
#include <stdlib.h>

void* allocfunc_toplevel()
{
    return calloc(1, sizeof(ei_toplevel_t));
}

void releasefunc_toplevel(ei_widget_t* widget)
{
    free(widget);
}

void drawfunc_toplevel(ei_widget_t* widget, ei_surface_t surface,
                       ei_surface_t pick_surface, ei_rect_t* clipper)
{

}

void setdefaultsfunc_toplevel(ei_widget_t* widget)
{

}

void geomnotifyfunc_toplevel(ei_widget_t* widget, ei_rect_t rect)
{

}
