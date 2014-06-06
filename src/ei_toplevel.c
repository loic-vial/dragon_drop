#include "ei_toplevel.h"
#include "ei_types.h"
#include "ei_widget.h"
#include "ei_widgetclass.h"
#include "ei_geometrymanager.h"
#include "hw_interface.h"
#include "ei_event.h"
#include "ei_utils.h"
#include "ei_utils_2.h"
#include "ei_placer.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

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
    drawfunc_frame(widget, surface, pick_surface, clipper);
}

static ei_bool_t destroy_widget(ei_widget_t* widget, ei_event_t* event, void* user_param)
{
    ei_widget_destroy(widget->parent->parent);
    return true;
}

static bool is_dragging = false;
static ei_point_t drag_mouse_position;
static bool is_resizing = false;
static ei_point_t resize_mouse_position;

static ei_bool_t drag_start(ei_widget_t* widget, ei_event_t* event, void* user_param)
{
    if (!is_dragging)
    {
        drag_mouse_position.x = event->param.mouse.where.x;
        drag_mouse_position.y = event->param.mouse.where.y;
        is_dragging = true;
    }
    return true;
}

static ei_bool_t drag(ei_widget_t* widget, ei_event_t* event, void* user_param)
{
    ei_widget_t* toplevel = (ei_widget_t*) user_param;
    if (is_dragging)
    {
        if (strcmp(toplevel->geom_params->manager->name, "placer") == 0)
        {
            ei_placer_geometry_param_t* placer = (ei_placer_geometry_param_t*) toplevel->geom_params;
            ei_point_t diff_position = ei_point_sub(event->param.mouse.where, drag_mouse_position);
            placer->x += diff_position.x;
            placer->y += diff_position.y;
            drag_mouse_position = event->param.mouse.where;
        }
    }
    return true;
}

static ei_bool_t drag_stop(ei_widget_t* widget, ei_event_t* event, void* user_param)
{
    drag(widget, event, user_param);
    if (is_dragging)
    {
        is_dragging = false;
    }
    return true;
}

static ei_bool_t resize_start(ei_widget_t* widget, ei_event_t* event, void* user_param)
{
    if (!is_resizing)
    {
        resize_mouse_position.x = event->param.mouse.where.x;
        resize_mouse_position.y = event->param.mouse.where.y;
        is_resizing = true;
    }
    return true;
}

static ei_bool_t resize(ei_widget_t* widget, ei_event_t* event, void* user_param)
{
    ei_widget_t* toplevel = (ei_widget_t*) user_param;
    if (is_resizing)
    {
        if (strcmp(toplevel->geom_params->manager->name, "placer") == 0)
        {
            ei_placer_geometry_param_t* placer = (ei_placer_geometry_param_t*) toplevel->geom_params;
            ei_point_t diff_position = ei_point_sub(event->param.mouse.where, resize_mouse_position);
            placer->width += diff_position.x;
            toplevel->requested_size.width += diff_position.x;
            placer->height += diff_position.y;
            toplevel->requested_size.height += diff_position.y;
            resize_mouse_position = event->param.mouse.where;
        }
    }
    return true;
}

static ei_bool_t resize_stop(ei_widget_t* widget, ei_event_t* event, void* user_param)
{
    resize(widget, event, user_param);
    if (is_resizing)
    {
        is_resizing = false;
    }
    return true;
}

void setdefaultsfunc_toplevel(ei_widget_t* widget)
{
    setdefaultsfunc_frame(widget);
    ei_toplevel_t* toplevel = (ei_toplevel_t*) widget;

    toplevel->frame.widget.requested_size.width = 320;
    toplevel->frame.widget.requested_size.height = 240;
    toplevel->frame.color = ei_default_background_color;
    toplevel->frame.border_width = 4;
    toplevel->title = "Toplevel";
    toplevel->closable = EI_TRUE;
    toplevel->resizable = ei_axis_both;
    toplevel->min_size = malloc(sizeof(ei_size_t));
    toplevel->min_size->width = 160;
    toplevel->min_size->height = 120;

    toplevel->border=(ei_frame_t*) ei_widget_create("frame", &toplevel->frame.widget);
    toplevel->border->text = "Toplevel";

    toplevel->border->widget.requested_size.height = 20;
    ei_font_t border_font = hw_text_font_create("misc/font.ttf",ei_style_normal, 18);
    ei_color_t border_color = ei_color(0, 0, 0, 255);
    ei_color_t border_text_color = ei_color(255, 255, 255, 255);

    ei_frame_configure(&toplevel->border->widget, NULL, &border_color,
                       &toplevel->frame.border_width, NULL, &toplevel->title, &border_font,
                       &border_text_color, NULL, NULL, NULL, NULL);

    ei_anchor_t border_anchor = ei_anc_north;

    int moins_vingt = -20;
    float un=1;
    ei_place(&toplevel->border->widget, &border_anchor, NULL, &moins_vingt, NULL, NULL, NULL, NULL, &un,NULL);

    toplevel->button = (ei_button_t*)ei_widget_create("button", &toplevel->border->widget);

    ei_size_t* bord=(ei_size_t*)malloc(sizeof(ei_size_t));
    bord->height = 12;
    bord->width=12;
    toplevel->button->color.alpha=255;
    toplevel->button->color.red=255;
    toplevel->button->color.green=0;
    toplevel->button->color.blue=0;
    toplevel->button->text="X";
    toplevel->button->text_font = hw_text_font_create("misc/font.ttf", ei_style_normal, 12);
    ei_anchor_t close_button_anchor = ei_anc_west;
    int close_button_pos_x = 4;
    ei_callback_t button_callback = destroy_widget;
    ei_button_configure(&toplevel->button->widget, bord, NULL, NULL, NULL, NULL,
                        NULL, NULL, NULL, NULL, NULL, NULL, NULL, &button_callback, NULL);

    ei_place(&toplevel->button->widget, &close_button_anchor, &close_button_pos_x, NULL, NULL,
             NULL, NULL, NULL, NULL, NULL);

    ei_callback_t _drag_start = drag_start;
    ei_callback_t _drag = drag;
    ei_callback_t _drag_stop = drag_stop;
    ei_bind(ei_ev_mouse_buttondown, &toplevel->border->widget, NULL, _drag_start, NULL);
    ei_bind(ei_ev_mouse_move, NULL, "all", _drag, &toplevel->frame.widget);
    ei_bind(ei_ev_mouse_buttonup, NULL, "all", _drag_stop, &toplevel->frame.widget);

    ei_size_t resize_button_size = ei_size(20, 20);
    ei_color_t resize_button_color = ei_color(0, 0, 0, 255);
    ei_anchor_t resize_button_anchor = ei_anc_southeast;
    ei_callback_t _resize_start = resize_start;
    ei_callback_t _resize = resize;
    ei_callback_t _resize_stop = resize_stop;

    ei_button_t* resize_button = (ei_button_t*)ei_widget_create("button", &toplevel->frame.widget);
    ei_button_configure(&resize_button->widget, &resize_button_size, &resize_button_color,
                        NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
    ei_place(&resize_button->widget, &resize_button_anchor, NULL, NULL, NULL,
             NULL, NULL, NULL, NULL, NULL);

    ei_bind(ei_ev_mouse_buttondown, &resize_button->widget, NULL, _resize_start, NULL);
    ei_bind(ei_ev_mouse_move, NULL, "all", _resize, &toplevel->frame.widget);
    ei_bind(ei_ev_mouse_buttonup, NULL, "all", _resize_stop, &toplevel->frame.widget);
}

void geomnotifyfunc_toplevel(ei_widget_t* widget, ei_rect_t rect)
{

}
