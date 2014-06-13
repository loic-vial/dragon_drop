#ifndef EI_TOPLEVEL_BANNER_H
#define EI_TOPLEVEL_BANNER_H

#include "ei_types.h"
#include "ei_widget.h"
#include "ei_event.h"

void ei_banner_register_class();

void ei_banner_setdefaultsfunc(ei_widget_t* widget);

void ei_configure_banner (ei_widget_t* widget,ei_color_t* color_banner, ei_color_t* color_text, ei_color_t* color_button, ei_color_t* color_button_text);

ei_bool_t ei_toplevel_drag_start_callback(ei_widget_t* widget, ei_event_t* event, void* user_param);

ei_bool_t ei_toplevel_drag_callback(ei_widget_t* widget, ei_event_t* event, void* user_param);

ei_bool_t ei_toplevel_drag_stop_callback(ei_widget_t* widget, ei_event_t* event, void* user_param);

#endif
