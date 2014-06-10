#include "ei_toplevel_banner.h"

#include "ei_utils.h"
#include "ei_utils_2.h"
#include "ei_placer.h"
#include "ei_frame.h"
#include <stdlib.h>
#include <string.h>

static ei_point_t drag_mouse_position;

void ei_banner_register_class()
{
    ei_widgetclass_t* bannerclass = (ei_widgetclass_t*) malloc(sizeof(ei_widgetclass_t));
    strcpy(bannerclass->name, "banner");
    bannerclass->allocfunc = &allocfunc_frame;
    bannerclass->releasefunc = &releasefunc_frame;
    bannerclass->drawfunc = &drawfunc_frame;
    bannerclass->setdefaultsfunc = &setdefaultsfunc_frame;
    bannerclass->geomnotifyfunc = &geomnotifyfunc_frame;
    bannerclass->next = NULL;
    ei_widgetclass_register(bannerclass);

    ei_callback_t drag_start = ei_toplevel_drag_start_callback;
    ei_bind(ei_ev_mouse_buttondown, NULL, "banner", drag_start, NULL);
}

ei_bool_t ei_toplevel_drag_start_callback(ei_widget_t* widget, ei_event_t* event, void* user_param)
{
    ei_tail(widget->parent);
    drag_mouse_position.x = event->param.mouse.where.x;
    drag_mouse_position.y = event->param.mouse.where.y;
    ei_callback_t _drag = ei_toplevel_drag_callback;
    ei_callback_t _drag_stop = ei_toplevel_drag_stop_callback;
    ei_bind(ei_ev_mouse_move, NULL, "all", _drag, widget->parent);
    ei_bind(ei_ev_mouse_buttonup, NULL, "all", _drag_stop, widget->parent);
    return EI_TRUE;
}

ei_bool_t ei_toplevel_drag_callback(ei_widget_t* widget, ei_event_t* event, void* user_param)
{
    ei_widget_t* toplevel = (ei_widget_t*) user_param;
    if (strcmp(toplevel->geom_params->manager->name, "placer") == 0)
    {
        ei_placer_geometry_param_t* placer = (ei_placer_geometry_param_t*) toplevel->geom_params;
        ei_point_t diff_position = ei_point_sub(event->param.mouse.where, drag_mouse_position);
        placer->x += diff_position.x;
        placer->y += diff_position.y;
        drag_mouse_position = event->param.mouse.where;
    }
    return EI_TRUE;
}

ei_bool_t ei_toplevel_drag_stop_callback(ei_widget_t* widget, ei_event_t* event, void* user_param)
{
    ei_callback_t _drag = ei_toplevel_drag_callback;
    ei_callback_t _drag_stop = ei_toplevel_drag_stop_callback;
    ei_unbind(ei_ev_mouse_move, NULL, "all", _drag, user_param);
    ei_unbind(ei_ev_mouse_buttonup, NULL, "all", _drag_stop, user_param);
    return EI_TRUE;
}
