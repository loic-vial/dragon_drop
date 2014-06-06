#include "ei_toplevel.h"
#include "ei_types.h"
#include "ei_widget.h"
#include "ei_widgetclass.h"
#include "ei_geometrymanager.h"
#include "hw_interface.h"
#include "ei_event.h"
#include "ei_utils.h"
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
            ei_placer_geometry_param_t* placer = (ei_placer_geometry_param_t*) toplevel->parent->geom_params;
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

void setdefaultsfunc_toplevel(ei_widget_t* widget)
{
    setdefaultsfunc_frame(widget);
    ei_toplevel_t* toplevel = (ei_toplevel_t*) widget;
    toplevel->frame.widget.requested_size.width=340; //il faut prendre en compte la taille de la bannière
    toplevel->frame.widget.requested_size.height=260;
    toplevel->frame.color=ei_default_background_color;
    toplevel->frame.border_width=4;
    toplevel->title="Toplevel";
    toplevel->closable=EI_TRUE;
    toplevel->resizable=ei_axis_both;
    toplevel->min_size=malloc(sizeof(ei_size_t));
    toplevel->min_size->width=160;
    toplevel->min_size->height=120;

    toplevel->border=(ei_frame_t*)ei_widget_create("frame", &toplevel->frame.widget);
    toplevel->border->text=toplevel->title="Toplevel";

    toplevel->border->color.alpha=255;
    toplevel->border->color.red=0;
    toplevel->border->color.blue=0;
    toplevel->border->color.green=0;

    toplevel->border->text_color.alpha=255;
    toplevel->border->text_color.red=255;
    toplevel->border->text_color.green=255;
    toplevel->border->text_color.blue=255;

    toplevel->border->widget.requested_size.height=20;
    ei_font_t font =hw_text_font_create	("misc/font.ttf",ei_style_normal,18);
    toplevel->border->text_font=font;

    ei_frame_configure(&toplevel->border->widget,NULL,NULL,
                       &toplevel->frame.border_width,NULL,&toplevel->title,NULL,NULL,NULL,NULL,NULL,NULL);

    ei_anchor_t border_anchor = ei_anc_north;
    ei_anchor_t button_anchor = ei_anc_east;

    int moins_vingt = -20;
    float un=1;
    ei_place(&toplevel->border->widget, &border_anchor, NULL, &moins_vingt, NULL, NULL, NULL, NULL, &un,NULL);

    toplevel->button = (ei_button_t*)ei_widget_create("button", &toplevel->border->widget);

    ei_size_t* bord=(ei_size_t*)malloc(sizeof(ei_size_t));
    bord->height= 12;
    bord->width=12;
    toplevel->button->color.alpha=255;
    toplevel->button->color.red=255;
    toplevel->button->color.green=0;
    toplevel->button->color.blue=0;
    toplevel->button->text="X";
    toplevel->button->text_font = hw_text_font_create("misc/font.ttf", ei_style_normal, 12);
    ei_callback_t button_callback = destroy_widget;
    ei_button_configure(&toplevel->button->widget, bord, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, &button_callback, NULL);


    int x=4;
    int y=4;
    ei_place(&toplevel->button->widget, &button_anchor, &x, &y,NULL, NULL, NULL, NULL, NULL, NULL);

    ei_callback_t _drag_start = drag_start;
    ei_callback_t _drag = drag;
    ei_callback_t _drag_stop = drag_stop;
    ei_bind(ei_ev_mouse_buttondown, &toplevel->border->widget, NULL, _drag_start, NULL);
    ei_bind(ei_ev_mouse_move, NULL, "all", _drag, &toplevel->border->widget);
    ei_bind(ei_ev_mouse_buttonup, NULL, "all", _drag_stop, &toplevel->border->widget);
}

void geomnotifyfunc_toplevel(ei_widget_t* widget, ei_rect_t rect)
{

}
