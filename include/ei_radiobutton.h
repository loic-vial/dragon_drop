#ifndef EI_RADIOBUTTON_H
#define EI_RADIOBUTTON_H
#include "ei_button.h"
/**
 * \brief A type of widget wich represent a radiobutton
 *
 */
    typedef struct ei_radiobutton_t {
	ei_frame_t frame;	///< Frame to memorize all common field between frame and radiobutton. All fields of the radiobutton will be children of this frame
	int number;		///< Number of field in the radiobutton
} ei_radiobutton_t;

/**
 * @brief Adds a field in a radiobutton
 * @param text                              Text of this new field
 * @param radio                             Radiobutton where to add the field
 */
void ei_add_children_radiobutton(char *text, ei_radiobutton_t * radio);

/**
 * @brief Registers the "radiobutton" widget class in the program. This must be called only
 *                                          	once before widgets of the class "radiobutton" can be created and configured with
 *                                              \ref ei_radiobutton_configure.
 */
void ei_radiobutton_register_class();

/**
 * @brief Sets all attributes of the radiobutton to default.
 *                                              Frame is set to defaults values with \ref ei_frame_setdefaultsfunc
 *                                              A first field is create by default with the text "First field"
 *                                              The requested size is {150,20} by default
 * @param widget                                Radiobutton widget to set to default
 */
void ei_radiobutton_setdefaultsfunc(ei_widget_t * widget);

/**
 * @brief Configures the attributes of widgets of the class "button".
 *
 * @param widget                                Widget to configure
 * @param requested_size                        Size that is requested to the radiobutton with all fields
 * @param color                                 Color of the radiobutton
 * @param border_width                          Border width of the radiobutton
 * @param relief                                Relief of the radiobuton
 */
void ei_radiobutton_configure(ei_widget_t * widget,
			      ei_size_t * requested_size,
			      const ei_color_t * color, int *border_width,
			      ei_relief_t * relief);

/**
 * @brief Destroys a field in a radiobutton
 * @param radio                    The radiobutton where a field will be destroy
 * @param number                   Number of the field to destroy
 */
void ei_destroy_field(ei_radiobutton_t * radio, int number);

/**
 * @brief Changes text of a field
 * @param radio                 The radiobutton where to change a field
 * @param number                Number of the field to change
 * @param text                  New text of the field
 */
void ei_edit_field(ei_radiobutton_t * radio, int number, char *text);

/**
 * @brief Returns the text of the field which is chosen
 * @param radio                 The radiobutton where to picked the chosen field
 * @return                      Return the text of the chosen field or NULL if the field doesn't exist
 */
char *ei_return_field(ei_radiobutton_t * radio);

/**
 * @brief Returns a field in the radiobutton
 * @param radio                 The radiobutton where the field is present
 * @param number                Number of the field to return
 * @return                      Return a field or NULL if the field doesn't exist
 */
ei_widget_t *ei_find_widget(ei_radiobutton_t * radio, int number);

#endif
