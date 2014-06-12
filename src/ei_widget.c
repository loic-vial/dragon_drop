#include "ei_widget.h"
#include "ei_button.h"
#include "ei_frame.h"
#include "ei_toplevel.h"
#include "ei_types.h"
#include "ei_event.h"
#include "hw_interface.h"
#include "ei_utils.h"
#include "ei_application.h"
#include "ei_geometrymanager.h"
#include "ei_placer.h"
#include "ei_utils_2.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

static int current_pick_id = 0;

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

    if (parent != NULL && parent->children_tail == NULL)
    {
        parent->children_head = widget;
        parent->children_tail = widget;
    }
    else if (parent != NULL)
    {
        parent->children_tail->next_sibling = widget;
        parent->children_tail = widget;
    }
    widget->geom_params = NULL;
    widget->requested_size = ei_size_zero();
    widget->screen_location = ei_rect_zero();
    widget->content_rect = &widget->screen_location;
    widgetclass->setdefaultsfunc(widget);

    if (parent != NULL)
    {
        if (strcmp(parent->wclass->name,"toplevel") == 0 &&
                strcmp(widget->wclass->name,"banner") != 0 &&
                strcmp(widget->wclass->name,"resize") != 0)
        {
            ei_widget_t* resize;
            resize=parent->children_head;
            while(resize != NULL && strcmp(resize->wclass->name,"resize")!=0)
            {
                resize=resize->next_sibling;
            }
            if (resize != NULL)
            {
                ei_tail(resize);
            }
        }
    }
    return widget;
}

void ei_widget_destroy(ei_widget_t* widget)
{

    ei_widget_t* child = widget->children_head;
    while (child != NULL)
    {
        ei_widget_t* next_child = child->next_sibling;
        ei_widget_destroy(child);
        child = next_child;
    }
    if (widget->parent->children_head == widget)
    {
        widget->parent->children_head = widget->next_sibling;
    }
    else
    {
        for (ei_widget_t* child = widget->parent->children_head ; child != NULL ; child = child->next_sibling)
        {
            for (ei_widget_t* child = widget->parent->children_head ; child != NULL ; child = child->next_sibling)
            {
                if (child->next_sibling == widget)
                {
                    child->next_sibling = widget->next_sibling;
                }
                if (widget == widget->parent->children_tail)
                {
                    widget->parent->children_tail=child;
                }
            }
        }
        widget->wclass->releasefunc(widget);
    }

    ei_geometrymanager_unmap(widget);
    widget->wclass->releasefunc(widget);
    free(widget->pick_color);
    free(widget);
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

void recompute_frame_requested_size(ei_frame_t* frame)
{
    ei_widget_t* widget = &frame->widget;
    if (frame->img != NULL)
    {
        if (frame->img_rect == NULL)
        {
            ei_size_t size = hw_surface_get_size(frame->img);
            widget->requested_size.width = size.width > widget->requested_size.width ?
                        size.width : widget->requested_size.width;
            widget->requested_size.height = size.height > widget->requested_size.height ?
                        size.height : widget->requested_size.height;
        }
        else
        {
            widget->requested_size.width = frame->img_rect->size.width > widget->requested_size.width ?
                        frame->img_rect->size.width : widget->requested_size.width;
            widget->requested_size.height = frame->img_rect->size.height > widget->requested_size.height ?
                        frame->img_rect->size.height : widget->requested_size.height;
        }
    }
    else if (frame->text != NULL)
    {
        int width, height;
        hw_text_compute_size(frame->text, frame->text_font, &width, &height);
        widget->requested_size.width = width > widget->requested_size.width ? width : widget->requested_size.width;
        widget->requested_size.height = height > widget->requested_size.height ? height : widget->requested_size.height;
    }
}

void ei_frame_configure(ei_widget_t* widget, ei_size_t* requested_size, const ei_color_t* color,
                        int* border_width, ei_relief_t* relief, char** text,
                        ei_font_t* text_font, ei_color_t* text_color, ei_anchor_t* text_anchor,
                        ei_surface_t* img, ei_rect_t** img_rect, ei_anchor_t* img_anchor)
{
    if (widget == NULL) return;

    ei_frame_t* frame = (ei_frame_t*) widget;
    ei_bool_t need_recompute_requested_size = EI_FALSE;

    if (requested_size != NULL)
        widget->requested_size = *requested_size;

    if (color != NULL)
        frame->color = *color ;

    if (border_width != NULL)
        frame->border_width = *border_width ;

    if (relief !=NULL)
        frame->relief = *relief ;

    if (text_font != NULL)
    {
        frame->text_font = *text_font;
        need_recompute_requested_size = EI_TRUE;
    }

    if (text != NULL && strcmp(*text, "") != 0)
    {
        frame->text = *text;
        need_recompute_requested_size = EI_TRUE;
    }

    if (text_color !=NULL)
        frame->text_color = *text_color;

    if (text_anchor !=NULL)
        frame->text_anchor = *text_anchor;

    if (img != NULL)
    {
        frame->img = *img;
        frame->text = NULL;
        need_recompute_requested_size = EI_TRUE;
    }

    if (img_rect != NULL)
    {
        if (frame->img_rect != NULL)
        {
            free(frame->img_rect);
        }
        if (*img_rect != NULL)
        {
            frame->img_rect = (ei_rect_t*) malloc(sizeof(ei_rect_t));
            *frame->img_rect = **img_rect;
        }
        else
        {
            frame->img_rect = NULL;
        }
        need_recompute_requested_size = EI_TRUE;
    }

    if (img_anchor != NULL)
        frame->img_anchor = *img_anchor;

    if (need_recompute_requested_size)
        recompute_frame_requested_size(frame);
}

void ei_button_configure(ei_widget_t* widget, ei_size_t* requested_size, const ei_color_t* color,
                         int* border_width, int* corner_radius, ei_relief_t* relief,
                         char** text, ei_font_t* text_font, ei_color_t* text_color,
                         ei_anchor_t* text_anchor, ei_surface_t* img, ei_rect_t** img_rect,
                         ei_anchor_t* img_anchor, ei_callback_t* callback, void** user_param)
{
    if (widget == NULL) return;

    ei_frame_configure(widget, requested_size, color, border_width, relief, text, text_font,
                       text_color, text_anchor, img, img_rect, img_anchor);

    ei_button_t* button = (ei_button_t*) widget;

    if (corner_radius != NULL)
    {
        button->frame.corner_radius = *corner_radius;
    }

    if (user_param != NULL || callback != NULL)
    {
        ei_unbind(ei_ev_mouse_buttonup, widget, NULL, button->callback, button->user_param);

        if (user_param != NULL)
        {
            button->user_param = *user_param;
        }

        if (callback != NULL)
        {
            button->callback = *callback;
        }

        ei_bind(ei_ev_mouse_buttonup, widget, NULL, button->callback, button->user_param);
    }
}

void ei_toplevel_configure (ei_widget_t* widget, ei_size_t* requested_size, ei_color_t* color,
                            int* border_width, char** title, ei_bool_t* closable,
                            ei_axis_set_t* resizable, ei_size_t** min_size)
{
    if (widget == NULL) return;

    ei_toplevel_t* toplevel = (ei_toplevel_t*) widget;

    if (requested_size != NULL)
        toplevel->frame.widget.requested_size = *requested_size;

    if (color != NULL)
        toplevel->frame.color = *color;

    if (border_width != NULL)
        toplevel->frame.border_width = *border_width;

    if (title != NULL)
    {
        toplevel->title = *title;
        toplevel->border->text=*title;
    }

    if (closable != NULL)
    {
        toplevel->closable = *closable;

        if (toplevel->closable)
        {
            ei_anchor_t resize_button_anchor = ei_anc_west;
            int resize_button_x = 4;
            ei_place(&toplevel->close_button->frame.widget, &resize_button_anchor,
                     &resize_button_x, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
        }
        else
        {
            ei_releasefunc_placer(&toplevel->close_button->frame.widget);
        }
    }

    if (resizable != NULL)
    {
        toplevel->resizable = *resizable;

        if(toplevel->resizable != ei_axis_none)
        {
            ei_anchor_t resize_button_anchor = ei_anc_southeast;
            int resize_button_x = 8;
            ei_place(&toplevel->resize_button->frame.widget, &resize_button_anchor,
                     &resize_button_x, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
        }
        else
        {
            ei_releasefunc_placer(&toplevel->resize_button->frame.widget);
        }
    }

    if (min_size != NULL)
    {
        if (toplevel->min_size != NULL)
        {
            free(toplevel->min_size);
        }
        if (*min_size != NULL)
        {
            toplevel->min_size = (ei_size_t*) malloc(sizeof(ei_size_t));
            *toplevel->min_size = **min_size;
        }
        else
        {
            toplevel->min_size = NULL;
        }
    }
}
