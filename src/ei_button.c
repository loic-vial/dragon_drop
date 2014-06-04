#include "ei_button.h"
#include "ei_utils.h"
#include <stdlib.h>

void* allocfunc_button()
{
    return calloc(1, sizeof(ei_button_t));
}

void releasefunc_button(ei_widget_t* widget)
{
    free(widget);
}

void drawfunc_button(ei_widget_t* widget, ei_surface_t surface,
                     ei_surface_t pick_surface, ei_rect_t* clipper)
{
    ei_button_t* button = (ei_button_t*)widget;
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

    ei_draw_polygon(surface, &first_point, button->color, clipper);

    ei_anchor_t anchor = button->text_anchor;
    if (anchor == ei_anc_northwest)
    {

    }
    else
    {
        int text_width, text_height;
        hw_text_compute_size(button->text, button->text_font, &text_width, &text_height);
        ei_size_t widget_size = widget->screen_location.size;
        ei_point_t top_left_corner = widget->screen_location.top_left;
        top_left_corner.x += widget_size.width / 2;
        top_left_corner.y += widget_size.height / 2;
        top_left_corner.x -= text_width / 2;
        top_left_corner.y -= text_height / 2;

        ei_draw_text(surface, &top_left_corner, button->text, button->text_font, &button->text_color, clipper);
    }

    ei_draw_polygon(pick_surface, &first_point,*widget->pick_color, clipper);
}

void setdefaultsfunc_button(ei_widget_t* widget)
{
    ei_button_t* button = (ei_button_t*) widget;
    button->color = ei_default_background_color;
    button->border_width = 0;
    button->corner_radius = 0;
    button->relief = ei_relief_none;
    button->text = NULL;
    button->text_font = ei_default_font;
    button->text_color = ei_font_default_color;
    button->text_anchor = ei_anc_center;
    button->img = NULL;
    button->img_rect = NULL;
    button->img_anchor = ei_anc_center;
    button->callback = NULL;
    button->user_param = NULL;
}

void geomnotifyfunc_button(ei_widget_t* widget, ei_rect_t rect)
{

}
