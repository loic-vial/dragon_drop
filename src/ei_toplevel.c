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
    ei_toplevel_t* toplevel = (ei_toplevel_t*)widget;
    ei_linked_point_t first_point;
    ei_linked_point_t second_point;
    ei_linked_point_t third_point;
    ei_linked_point_t fourth_point;
    first_point.point = widget->screen_location.top_left;
    first_point.next = &second_point;
    second_point.point = widget->screen_location.top_left;
    second_point.point.x += widget->screen_location.size.width;
    second_point.next = &third_point;
    third_point.point = second_point.point;
    third_point.point.y += widget->screen_location.size.height;
    third_point.next = &fourth_point;
    fourth_point.point = first_point.point;
    fourth_point.point.y += widget->screen_location.size.height;
    fourth_point.next = NULL;

    ei_draw_polygon(surface, &first_point, toplevel->color, clipper);
    ei_draw_polygon(pick_surface, &first_point, *widget->pick_color, clipper);
}

void setdefaultsfunc_toplevel(ei_widget_t* widget)
{
    ei_toplevel_t* toplevel = (ei_toplevel_t*) widget;
    toplevel->requested_size.width=320;
    toplevel->requested_size.height=420;
    toplevel->color=ei_default_background_color;
    toplevel->border_width=4;
    toplevel->title="Toplevel";
    toplevel->closable=EI_TRUE;
    toplevel->resizable=ei_axis_both;
    toplevel->min_size=malloc(sizeof(ei_size_t));
    toplevel->min_size->width=160;
    toplevel->min_size->height=120;
}

void geomnotifyfunc_toplevel(ei_widget_t* widget, ei_rect_t rect)
{

}
