#include "ei_button.h"
#include "ei_utils.h"
#include "ei_utils_2.h"
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

    if (button->text != NULL)
    {
        ei_size_t text_size;
        hw_text_compute_size(button->text, button->text_font, &text_size.width, &text_size.height);
        ei_point_t top_left_corner = ei_position_from_anchor(widget->screen_location.top_left,
                                                             widget->screen_location.size,
                                                             text_size,
                                                             button->text_anchor);

        ei_draw_text(surface, &top_left_corner, button->text, button->text_font, &button->text_color, clipper);
    }
    //tracé de l'image

    if (button->img != NULL)
    {
        ei_size_t size = button->img_rect->size;

        ei_point_t top_left_corner = ei_position_from_anchor(widget->screen_location.top_left,
                                                             widget->screen_location.size,
                                                             size,
                                                             button->img_anchor);

        hw_surface_lock(*button->img);
        ei_rect_t rect_1;

        if(button->img_rect->size.height < clipper->size.height && button->img_rect->size.width < clipper->size.width)
        {

            if(button->img_rect->size.height < button->widget.screen_location.size.height && button->img_rect->size.width < button->widget.screen_location.size.width)
            {
                rect_1 = ei_rect(top_left_corner, button->img_rect->size);
            }

            else
            {
                rect_1 = ei_rect(button->widget.screen_location.top_left, button->widget.screen_location.size);
            }
        }
        else
        {

            if ( clipper->size.height<button->widget.screen_location.size.height)
            {
                rect_1.size.height = clipper->size.height;
            }
            else  rect_1.size.height =button->widget.screen_location.size.height;

            if ( clipper->size.width<button->widget.screen_location.size.width)
            {
                rect_1.size.width = clipper->size.width;
            }
            else  rect_1.size.width =button->widget.screen_location.size.width;
            rect_1.top_left=widget->screen_location.top_left;
        }
        if (clipper->size.width + button->widget.parent->screen_location.top_left.x>top_left_corner.x ||clipper->size.height + button->widget.parent->screen_location.top_left.y>top_left_corner.y)
        {
            if (clipper->size.width + button->widget.parent->screen_location.top_left.x < top_left_corner.x +button->img_rect->size.width)
            {
                rect_1.size.width=clipper->size.width + button->widget.parent->screen_location.top_left.x-top_left_corner.x;
            }
            if (clipper->size.height + button->widget.parent->screen_location.top_left.y< top_left_corner.y+button->img_rect->size.height)
            {
                rect_1.size.height=clipper->size.height + button->widget.parent->screen_location.top_left.y-top_left_corner.y;
            }
ei_rect_t rect_2;
rect_2.size=rect_1.size;
rect_2.top_left.x=button->img_rect->top_left.x;
rect_2.top_left.y=button->img_rect->top_left.y;
            ei_copy_surface(surface, &rect_1, *button->img,&rect_2, EI_TRUE);
        }
        hw_surface_unlock(*button->img);
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
