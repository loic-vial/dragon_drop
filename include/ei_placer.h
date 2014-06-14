#ifndef EI_PLACER_H
#define EI_PLACER_H

#include "ei_geometrymanager.h"

/**
  * @brief Structure that defines the "placer" geometry manager
  */
typedef struct ei_placer_geometry_param_t {
	ei_geometry_param_t geometry_param;	///< Allows the inheritance of geometry_param attributes
	ei_anchor_t anchor;	///< The anchor where to display the widget within its parent
	int x;			///< The x position offset of the widget within its parent
	int y;			///< The y position offset of the widget within its parent
	int width;		///< The width of the widget, overrides the requested size of the widget
	int height;		///< The height of the widget, overrides the requested size of the widget
	float rel_x;		///< The relative x position added to the 'x' attribute, relative to the widget parent
	float rel_y;		///< The relative y position added to the 'y' attribute, relative to the widget parent
	float rel_width;	///< The relative width of the widget, relative to the widget parent, override the "width"
	float rel_height;	///< The relative height of the widget, relative to the widget parent, override the "height"
} ei_placer_geometry_param_t;

/**
 * @brief Places a widget correctly in the screen according to the placer's geometry parameters
 * @param widget                The widget to place
 * This function will use the parameters of the placer geometry manager of the widget to
 * adjust the screen_location attribute of the widget.
 * If the screen_location is modified between the beginning and the end of the function, then
 * the geomnotify function of the widget is called, and both the old screen location and the new one
 * are invalidated.
 */
void ei_runfunc_placer(ei_widget_t * widget);

/**
 * @brief Releases the parameters of the placer geometry manager of the widget
 */
void ei_releasefunc_placer(ei_widget_t * widget);

#endif
