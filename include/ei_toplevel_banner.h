#ifndef EI_TOPLEVEL_BANNER_H
#define EI_TOPLEVEL_BANNER_H

#include "ei_types.h"
#include "ei_widget.h"
#include "ei_event.h"

/**
 * @brief Registers the "banner" widget class
 */
void ei_banner_register_class();

/**
 * @brief Sets the defaults attributes of widgets of the class "banner"
 */
void ei_banner_setdefaultsfunc(ei_widget_t * widget);

/**
 * @brief Configures the attributes of widgets of the class "banner"
 */
void ei_banner_configure(ei_widget_t * widget, ei_color_t * color_banner,
			 ei_color_t * color_text,
			 ei_color_t * color_button,
			 ei_color_t * color_button_text);

/**
 * @brief Mouse button down callback for "banner" widgets
 * This initializes the drag and drop for toplevel widgets
 */
ei_bool_t ei_toplevel_drag_start_callback(ei_widget_t * widget,
					  ei_event_t * event,
					  void *user_param);

/**
 * @brief Mouse button move callback for "banner" widgets
 */
ei_bool_t ei_toplevel_drag_callback(ei_widget_t * widget,
				    ei_event_t * event, void *user_param);

/**
 * @brief Mouse button up callback for "banner" widgets
 * This ends the drag and drop for toplevel widgets
 */
ei_bool_t ei_toplevel_drag_stop_callback(ei_widget_t * widget,
					 ei_event_t * event,
					 void *user_param);

#endif
