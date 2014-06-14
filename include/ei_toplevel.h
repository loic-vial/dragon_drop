#ifndef EI_TOPLEVEL_H
#define EI_TOPLEVEL_H

#include "ei_button.h"

/**
  * @brief Structure that defines a TopLevel widget
  * A toplevel is a kind of window, it can be moved by clicking on its banner,
  * it can be resized by clicking on its bottom right button, and it can be closed
  * by clicking on its top left 'X' button.
  */
typedef struct ei_toplevel_t {
	ei_frame_t frame;	///< Allows the inheritance with frame and give all frame attributes to the toplevel
	char *title;		///< The title of the toplevel, wich will be displayed in the upper banner
	ei_bool_t closable;	///< A boolean that indicates if the toplevel window is closable or not
	ei_axis_set_t resizable;	///< Defines the axis where you can resize the toplevel
	ei_size_t *min_size;	///< The minimum size that the toplevel can take when resizing (NULL means no minimum size)
	ei_frame_t *banner;	///< The upper banner of the toplevel (Child of the toplevel)
	ei_button_t *close_button;	///< The close button (Child of the banner)
	ei_button_t *resize_button;	///< The resize button (Child of the toplevel)
	ei_font_t close_button_font;	///< The font of the close button
	ei_font_t banner_font;	///< The font of the banner
} ei_toplevel_t;

/**
 * @brief Allocates the required memory to all the attributes of a toplevel widget
 */
void *ei_toplevel_allocfunc();

/**
 * @brief Releases the attributes of a toplevel widget
 */
void ei_toplevel_releasefunc(ei_widget_t * widget);

/**
 * @brief Sets the default attributes of a toplevel widget
 */
void ei_toplevel_setdefaultsfunc(ei_widget_t * widget);

#endif
