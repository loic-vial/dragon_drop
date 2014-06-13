#include "ei_drag_and_drop.h"
#include "ei_utils_2.h"
#include "ei_placer.h"
#include "ei_utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
static ei_point_t drag_mouse_position;

void ei_movable()
{
     ei_bind(ei_ev_mouse_buttondown, NULL, "movable", ei_movable_drag_start_callback, NULL);

}


ei_bool_t ei_movable_drag_start_callback(ei_widget_t* widget, ei_event_t* event, void* user_param)
{
    ei_tail(widget);
    drag_mouse_position.x = event->param.mouse.where.x;
    drag_mouse_position.y = event->param.mouse.where.y;
    ei_callback_t _drag = ei_movable_drag_callback;
    ei_callback_t _drag_stop = ei_movable_drag_stop_callback;
    ei_bind(ei_ev_mouse_move, NULL, "all", _drag, widget);
    ei_bind(ei_ev_mouse_buttonup, NULL, "all", _drag_stop, widget);
    return EI_TRUE;
}

ei_bool_t ei_movable_drag_callback(ei_widget_t* widget, ei_event_t* event, void* user_param)
{
    widget = (ei_widget_t*) user_param;
    if (strcmp(widget->geom_params->manager->name, "placer") == 0)
    {
        ei_placer_geometry_param_t* placer = (ei_placer_geometry_param_t*) widget->geom_params;
        ei_point_t diff_position = ei_point_sub(event->param.mouse.where, drag_mouse_position);
        placer->x += diff_position.x;
        placer->y += diff_position.y;
        drag_mouse_position = event->param.mouse.where;
    }
    return EI_TRUE;
}

ei_bool_t ei_movable_drag_stop_callback(ei_widget_t* widget, ei_event_t* event, void* user_param)
{
    ei_callback_t _drag = ei_movable_drag_callback;
    ei_callback_t _drag_stop = ei_movable_drag_stop_callback;
    ei_unbind(ei_ev_mouse_move, NULL, "all", _drag, user_param);
    ei_unbind(ei_ev_mouse_buttonup, NULL, "all", _drag_stop, user_param);
    return EI_TRUE;
}

