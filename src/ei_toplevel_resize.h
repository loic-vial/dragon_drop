#ifndef EI_TOPLEVEL_RESIZE_H
#define EI_TOPLEVEL_RESIZE_H

#include "ei_types.h"
#include "ei_widget.h"
#include "ei_event.h"

void ei_resize_register_class();

ei_bool_t ei_toplevel_resize_start_callback(ei_widget_t* widget, ei_event_t* event, void* user_param);

ei_bool_t ei_toplevel_resize_callback(ei_widget_t* widget, ei_event_t* event, void* user_param);

ei_bool_t ei_toplevel_resize_stop_callback(ei_widget_t* widget, ei_event_t* event, void* user_param);

#endif
