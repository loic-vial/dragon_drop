#ifndef EI_TOPLEVEL_RESIZE_H
#define EI_TOPLEVEL_RESIZE_H

#include "ei_widget.h"
#include "ei_event.h"

/**
 * @brief Registers the "resize" widget class
 */
void ei_resize_register_class();

/**
 * @brief Sets the defaults attributes of widgets of the class "resize"
 */
void ei_resize_setdefaultsfunc(ei_widget_t * widget);

/**
 * @brief Mouse button down callback for "resize" widgets
 * This initializes the resize of toplevel widgets
 */
ei_bool_t ei_toplevel_resize_start_callback(ei_widget_t * widget,
					    ei_event_t * event,
					    void *user_param);

/**
 * @brief Mouse button move callback for "resize" widgets
 */
ei_bool_t ei_toplevel_resize_callback(ei_widget_t * widget,
				      ei_event_t * event,
				      void *user_param);

/**
 * @brief Mouse button up callback for "resize" widgets
 * This ends the resize of toplevel widgets
 */
ei_bool_t ei_toplevel_resize_stop_callback(ei_widget_t * widget,
					   ei_event_t * event,
					   void *user_param);

#endif
