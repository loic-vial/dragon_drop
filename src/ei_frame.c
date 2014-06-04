#include "ei_frame.h"
#include "ei_utils.h"
#include <stdlib.h>


void* allocfunc_frame()
{
    return calloc(1, sizeof(ei_frame_t));
}

void releasefunc_frame(ei_widget_t* widget)
{
    free(widget);
}

void drawfunc_frame(ei_widget_t* widget, ei_surface_t surface,
                    ei_surface_t pick_surface, ei_rect_t* clipper)
{
    hw_surface_lock(surface);
    ei_frame_t* frame = (ei_frame_t*)widget;
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

    ei_draw_polygon(surface, &first_point, frame->color, clipper);
    hw_surface_unlock(surface);
}

void setdefaultsfunc_frame(ei_widget_t* widget)
{
    ei_frame_t* frame = (ei_frame_t*) widget;
    frame->color = ei_default_background_color;
    frame->border_width = 0;
    frame->relief = ei_relief_none;
    frame->text = NULL;
    frame->text_font = ei_default_font;
    frame->text_color = ei_font_default_color;
    frame->text_anchor = ei_anc_center;
    frame->img = NULL;
    frame->img_rect = NULL;
    frame->img_anchor = ei_anc_center;
}

void geomnotifyfunc_frame(ei_widget_t* widget, ei_rect_t rect)
{

}
