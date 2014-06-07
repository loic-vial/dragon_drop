#ifndef EI_TOPLEVEL_H
#define EI_TOPLEVEL_H

#include "ei_types.h"
#include "ei_widget.h"
#include "ei_frame.h"
#include "ei_button.h"
#include "ei_event.h"

typedef struct ei_toplevel_t
{
    ei_frame_t frame;
    char*			title;
    ei_bool_t		closable;
    ei_axis_set_t		resizable;
    ei_size_t*		min_size;
    ei_frame_t* border;
    ei_button_t* button;
}
ei_toplevel_t;

void ei_banner_register_class();
void ei_resize_register_class();

void* allocfunc_toplevel();

void releasefunc_toplevel(ei_widget_t* widget);

void drawfunc_toplevel(ei_widget_t* widget, ei_surface_t surface,
                       ei_surface_t pick_surface, ei_rect_t* clipper);

void setdefaultsfunc_toplevel(ei_widget_t* widget);

void geomnotifyfunc_toplevel(ei_widget_t* widget, ei_rect_t rect);

ei_bool_t ei_toplevel_drag_start_callback(ei_widget_t* widget, ei_event_t* event, void* user_param);

ei_bool_t ei_toplevel_drag_callback(ei_widget_t* widget, ei_event_t* event, void* user_param);

ei_bool_t ei_toplevel_drag_stop_callback(ei_widget_t* widget, ei_event_t* event, void* user_param);

#endif
