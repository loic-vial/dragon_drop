#include "ei_toplevel_resize.h"

#include "ei_utils.h"
#include "ei_utils_2.h"
#include "ei_placer.h"
#include "ei_button.h"
#include "ei_toplevel.h"
#include <stdlib.h>
#include <string.h>

static ei_point_t resize_mouse_position;

void ei_resize_register_class()
{
    ei_widgetclass_t* resizeclass = (ei_widgetclass_t*) malloc(sizeof(ei_widgetclass_t));
    strcpy(resizeclass->name, "resize");
    resizeclass->allocfunc = &allocfunc_button;
    resizeclass->releasefunc = &releasefunc_button;
    resizeclass->drawfunc = &drawfunc_button;
    resizeclass->setdefaultsfunc = &setdefaultsfunc_button;
    resizeclass->geomnotifyfunc = &geomnotifyfunc_button;
    resizeclass->next = NULL;
    ei_widgetclass_register(resizeclass);

    ei_callback_t _resize_start = ei_toplevel_resize_start_callback;
    ei_bind(ei_ev_mouse_buttondown, NULL, "resize", _resize_start, NULL);
}

ei_bool_t ei_toplevel_resize_start_callback(ei_widget_t* widget, ei_event_t* event, void* user_param)
{
    ei_tail(widget->parent);
    resize_mouse_position.x = event->param.mouse.where.x;
    resize_mouse_position.y = event->param.mouse.where.y;
    ei_callback_t _resize = ei_toplevel_resize_callback;
    ei_callback_t _resize_stop = ei_toplevel_resize_stop_callback;
    ei_bind(ei_ev_mouse_move, NULL, "all", _resize, widget->parent);
    ei_bind(ei_ev_mouse_buttonup, NULL, "all", _resize_stop, widget->parent);
    return EI_TRUE;
}

ei_bool_t ei_toplevel_resize_callback(ei_widget_t* widget, ei_event_t* event, void* user_param)
{
    widget = (ei_widget_t*) user_param;
    ei_toplevel_t* toplevel = (ei_toplevel_t*) user_param;
    if (strcmp(widget->geom_params->manager->name, "placer") == 0)
    {
        ei_placer_geometry_param_t* placer = (ei_placer_geometry_param_t*) widget->geom_params;
        ei_point_t diff_position = ei_point_sub(event->param.mouse.where, resize_mouse_position);
        ei_size_t new_size = toplevel->frame.widget.requested_size;

        if (toplevel->resizable == ei_axis_none) return EI_TRUE;
        else if (toplevel->resizable == ei_axis_x) diff_position.y = 0;
        else if (toplevel->resizable == ei_axis_y) diff_position.x = 0;

        new_size = ei_size_add(new_size, ei_size(diff_position.x, diff_position.y));

        if (toplevel->min_size->width > new_size.width)
            new_size.width = toplevel->min_size->width;

        if (toplevel->min_size->height > new_size.height)
            new_size.height = toplevel->min_size->height;

        placer->width = new_size.width;
        placer->height = new_size.height;
        toplevel->frame.widget.requested_size = new_size;

        if (toplevel->min_size->width < new_size.width)
            resize_mouse_position.x = event->param.mouse.where.x;
        if (toplevel->min_size->height < new_size.height)
            resize_mouse_position.y = event->param.mouse.where.y;
    }
    return EI_TRUE;
}

ei_bool_t ei_toplevel_resize_stop_callback(ei_widget_t* widget, ei_event_t* event, void* user_param)
{
    ei_callback_t _resize = ei_toplevel_resize_callback;
    ei_callback_t _resize_stop = ei_toplevel_resize_stop_callback;
    ei_unbind(ei_ev_mouse_move, NULL, "all", _resize, user_param);
    ei_unbind(ei_ev_mouse_buttonup, NULL, "all", _resize_stop, user_param);
    return EI_TRUE;
}

