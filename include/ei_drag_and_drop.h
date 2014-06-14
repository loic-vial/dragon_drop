#ifndef EI_DRAG_AND_DROP_H
#define EI_DRAG_AND_DROP_H

#include "ei_types.h"
#include "ei_widget.h"
#include "ei_event.h"

/**
 * @brief Enables any widget with the tag "movable" to be "dragged and dropped"
 */
void ei_enable_movable_tag();

/**
 * @brief Mouse button move callback for movable widgets
 */
ei_bool_t ei_movable_drag_callback(ei_widget_t * widget,
				   ei_event_t * event, void *user_param);

/**
 * @brief Mouse button up callback for movable widgets
 * This function ends the drag and drop for a widget
 */
ei_bool_t ei_movable_drag_stop_callback(ei_widget_t * widget,
					ei_event_t * event,
					void *user_param);

/**
 * @brief Mouse button down callback for movable widgets
 * This function initializes the drag and drop for a widget
 */
ei_bool_t ei_movable_drag_start_callback(ei_widget_t * widget,
					 ei_event_t * event,
					 void *user_param);

#endif
