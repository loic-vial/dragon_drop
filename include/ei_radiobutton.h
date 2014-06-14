#ifndef EI_RADIOBUTTON_H
#define EI_RADIOBUTTON_H

#include "ei_button.h"

/**
 * \brief ei_radiobutton_t A type of widget wich represent a radiobutton
 *
 */
typedef struct ei_radiobutton_t
{
    ei_frame_t frame; ///< Frame to memorize all common field between frame and radiobutton. All fields of the radiobutton
                       /// will be children of this frame
    int number; ///< Number of field in the radiobutton
}
ei_radiobutton_t;

/**
 * @brief ei_add_children_radiobutton       A function that add a field in a radiobutton
 * @param text                              Text of this new field
 * @param radio                             Radiobutton where to add the field
 */
void ei_add_children_radiobutton(char * text, ei_radiobutton_t* radio);

/**
 * @brief ei_radiobutton_register_class     	Registers the "radiobutton" widget class in the program. This must be called only
 *                                          	once before widgets of the class "radiobutton" can be created and configured with
 *                                              \ref ei_radiobutton_configure.
 */
void ei_radiobutton_register_class();

/**
 * @brief ei_radiobutton_setdefaultsfunc        A function that sets all parameters of the radiobutton to default. A first field is create by default
 * @param widget                                Radiobutton widget to set to default
 */
void ei_radiobutton_setdefaultsfunc(ei_widget_t* widget);

/**
 * @brief ei_radiobutton_configure              Configures the attributes of widgets of the class "button".
 *
 * @param widget                                Widget to configure
 * @param requested_size                        Size that is requested to the radiobutton with all fields
 * @param color                                 Color of the radiobutton
 * @param border_width                          Border width of the radiobutton
 * @param relief                                Relief of the radiobuton
 */
void ei_radiobutton_configure(ei_widget_t* widget, ei_size_t* requested_size, const ei_color_t* color,
                              int* border_width, ei_relief_t* relief);

/**
 * @brief ei_destroy_field         A function that destroy a field in a radiobutton
 * @param radio                    The radiobutton where a field will be destroy
 * @param number                   Number of the field to destroy
 */
void ei_destroy_field(ei_radiobutton_t* radio,int number);

/**
 * @brief ei_edit_field         A function that change the text of a field
 * @param radio                 The radiobutton where to change a field
 * @param number                Number of the field to change
 * @param text                  New text of the field
 */
void ei_edit_field(ei_radiobutton_t* radio,int number, char* text);

/**
 * @brief ei_return_field       A function that returns the text of the field which is chosen
 * @param radio                 The radiobutton where to picked the chosen field
 * @return                      Return the text of the chosen field
 */
char* ei_return_field(ei_radiobutton_t* radio);

/**
 * @brief ei_find_widget        A function that return a field in the radiobutton
 * @param radio                 The radiobutton where the field is
 * @param number                Number of the field to return
 * @return                      Return a field
 */
ei_widget_t* ei_find_widget(ei_radiobutton_t* radio,int number);

#endif
