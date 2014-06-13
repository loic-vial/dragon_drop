#ifndef EI_DRAG_AND_DROP_H
#define EI_DRAG_AND_DROP_H

#include "ei_types.h"
#include "ei_widget.h"
#include "ei_event.h"

void ei_movable();

ei_bool_t ei_movable_drag_callback(ei_widget_t* widget, ei_event_t* event, void* user_param);
ei_bool_t ei_movable_drag_stop_callback(ei_widget_t* widget, ei_event_t* event, void* user_param);
ei_bool_t ei_movable_drag_start_callback(ei_widget_t* widget, ei_event_t* event, void* user_param);

#endif
