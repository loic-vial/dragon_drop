#include "ei_widget.h"
#include "ei_button.h"
#include "ei_frame.h"
#include "ei_toplevel.h"
#include "ei_types.h"
#include "ei_event.h"
#include "hw_interface.h"
#include "ei_utils.h"
#include "ei_application.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static int current_pick_id = 1;

ei_widget_t* ei_widget_create(ei_widgetclass_name_t class_name, ei_widget_t* parent)
{
    ei_widgetclass_t* widgetclass = ei_widgetclass_from_name(class_name);
    ei_widget_t* widget = (ei_widget_t*) widgetclass->allocfunc();
    widget->wclass = widgetclass;
    widget->pick_id = current_pick_id;
    widget->pick_color = (ei_color_t*) malloc(sizeof(ei_color_t));
    widget->pick_color->red = current_pick_id % 255;
    widget->pick_color->green = (current_pick_id / 255) % 255;
    widget->pick_color->blue = (current_pick_id / 65025) % 255; // allows 16581375 different widgets
    widget->pick_color->alpha = 255;
    current_pick_id++;
    widget->parent = parent;
    widget->children_head = NULL;
    widget->children_tail = NULL;
    widget->next_sibling = NULL;
    if (parent->children_tail == NULL)
    {
        parent->children_head = widget;
        parent->children_tail = widget;
    }
    else
    {
        parent->children_tail->next_sibling = widget;
        parent->children_tail = widget;
    }
    widget->geom_params = NULL;
    widget->requested_size = ei_size_zero();
    widget->screen_location = ei_rect_zero();
    widget->content_rect = &widget->screen_location;
    widgetclass->setdefaultsfunc(widget);
    return widget;
}

void ei_widget_destroy(ei_widget_t* widget)
{

}

bool is_same_color(ei_color_t color1, ei_color_t color2)
{
    return (color1.red == color2.red &&
            color1.green == color2.green &&
            color1.blue == color2.blue &&
            color1.alpha == color2.alpha);
}

ei_widget_t* get_widget_with_pick_color(ei_widget_t* widget, ei_color_t color)
{
    if (widget == NULL) return NULL;
    if (is_same_color(*widget->pick_color, color)) return widget;
    ei_widget_t* current = widget->children_head;
    while (current != NULL)
    {
        ei_widget_t* tmp = get_widget_with_pick_color(current, color);
        if (tmp != NULL) return tmp;
        current = current->next_sibling;
    }
    return NULL;
}

extern ei_surface_t offscreen_surface;

ei_widget_t* ei_widget_pick(ei_point_t* where)
{
    uint8_t* buffer = hw_surface_get_buffer(offscreen_surface);
    ei_size_t size = hw_surface_get_size(offscreen_surface);
    buffer = &buffer[(where->x + where->y * size.width) * sizeof(ei_color_t)];
    ei_color_t color;
    int ir, ig, ib, ia;
    hw_surface_get_channel_indices(offscreen_surface, &ir, &ig, &ib, &ia);
    color.red = buffer[ir];
    color.green = buffer[ig];
    color.blue = buffer[ib];
    color.alpha = 255;
    return get_widget_with_pick_color(ei_app_root_widget(), color);
}

void ei_frame_configure(ei_widget_t* widget, ei_size_t* requested_size, const ei_color_t* color,
                        int* border_width, ei_relief_t* relief, char** text,
                        ei_font_t* text_font, ei_color_t* text_color, ei_anchor_t* text_anchor,
                        ei_surface_t* img, ei_rect_t** img_rect, ei_anchor_t* img_anchor)
{
    if (widget == NULL) return;

    ei_frame_t* frame = (ei_frame_t*) widget;

    if (requested_size != NULL)
        widget->requested_size = *requested_size;

    if (color != NULL)
        frame->color = *color ;

    if (border_width != NULL)
        frame->border_width = *border_width ;

    if (relief !=NULL)
        frame->relief = *relief ;

    if (text != NULL)
        frame->text= *text ;

    if (text_font != NULL)
        frame->text_font = *text_font;

    if (text_color !=NULL)
        frame->text_color = *text_color;

    if (text_anchor !=NULL)
        frame->text_anchor = *text_anchor;

    if (img != NULL)
        frame->img = img;

    if (img_rect != NULL)
        frame->img_rect = *img_rect;

    if (img_anchor != NULL)
        frame->img_anchor = *img_anchor;
}

void ei_button_configure(ei_widget_t* widget, ei_size_t* requested_size, const ei_color_t* color,
                         int* border_width, int* corner_radius, ei_relief_t* relief,
                         char** text, ei_font_t* text_font, ei_color_t* text_color,
                         ei_anchor_t* text_anchor, ei_surface_t* img, ei_rect_t** img_rect,
                         ei_anchor_t* img_anchor, ei_callback_t* callback, void** user_param)
{
    if (widget == NULL) return;

    ei_button_t* button = (ei_button_t*)widget;

    if (requested_size != NULL)
        widget->requested_size = *requested_size;

    if (color != NULL)
        button->color = *color;

    if (border_width != NULL)
        button->border_width = *border_width;

    if (corner_radius != NULL)
        button->corner_radius= *corner_radius;

    if (relief != NULL)
        button->relief = *relief;

    if (text != NULL)
        button->text =*text;

    if (text_font != NULL)
        button->text_font = text_font;

    if (text_color != NULL)
        button->text_color = *text_color;

    if (text_anchor != NULL)
        button->text_anchor = *text_anchor;

    if (img != NULL)
        button->img = *img;

    if (img_rect != NULL)
        button->img_rect = *img_rect;

    if (img_anchor != NULL)
        button->img_anchor = *img_anchor;

    if (callback != NULL)
    {
        button->callback = callback;
        ei_bind(ei_ev_mouse_buttonup, widget, "button", *callback, NULL);
    }

    if (user_param != NULL)
        button->user_param = user_param;

}

void ei_toplevel_configure (ei_widget_t* widget, ei_size_t* requested_size, ei_color_t* color,
                            int* border_width, char** title, ei_bool_t* closable,
                            ei_axis_set_t* resizable, ei_size_t** min_size)
{
    if (widget == NULL) return;

    ei_toplevel_t* toplevel = (ei_toplevel_t*) widget;

    if (requested_size != NULL)
        toplevel->contains->widget.requested_size = *requested_size;

    if (color != NULL)
        toplevel->color = *color;

    if (border_width != NULL)
        toplevel->border_width = *border_width;

    if (title != NULL)
        toplevel->title = *title;

    if (closable != NULL)
        toplevel->closable = *closable;

    if (resizable != NULL)
        toplevel->resizable = *resizable;

    if (min_size != NULL)
        toplevel->min_size = *min_size;
}
