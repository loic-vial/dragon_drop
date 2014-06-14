#ifndef EI_BUTTON_H
#define EI_BUTTON_H

#include "ei_frame.h"


/**
 * \brief	ei_button_t     A type of widget which represent a button
 */
typedef struct ei_button_t
{
    ei_frame_t frame; ///< Frame to memorized all common fields between button and frame.All fields of the radiobutton
                         /// will be children of this frame
    ei_callback_t callback; ///< This function will be called then the button is clicked
    void* user_param; ///<Parameter send by the user
}
ei_button_t;

/**
 * @brief	ei_button_allocfunc     A function that is called to allocate a block of the size of a \ref ei_button_t in the memory.
 *                                  It initializes it to zero.
 *
 */
void* ei_button_allocfunc();

/**
 * @brief ei_button_releasefunc      Releases the memory used by the widget button.
 * @param widget                     This widget is a button that must be released.
 */
void ei_button_releasefunc(ei_widget_t* widget);

/**
 * @brief ei_button_setdefaultsfunc     Sets attributes to defaults values.
 * @param widget                        The button widget to set to default.
 *                                      Frame is set to defaults values with \ref ei_frame_setdefaultsfunc
 *                                      Callback and user_param are set to NULL.
 */
void ei_button_setdefaultsfunc(ei_widget_t* widget);

/**
 * @brief ei_button_click_down      Callback called when a button is down.
 * @param widget                    The widget button which is clicked
 * @param event                     The event \ref ei_ev_mouse_buttondown
 * @param user_param                Parameters send by the user
 * @return
 */
ei_bool_t ei_button_click_down(ei_widget_t* widget, ei_event_t* event, void* user_param);

/**
 * @brief ei_button_click_up        Callback called then a clicked button become up
 * @param widget                    The widget button which is released
 * @param event                     The event \ref ei_ev_mouse_buttonup
 * @param user_param                Parameters send by the user
 * @return
 */
ei_bool_t ei_button_click_up(ei_widget_t* widget, ei_event_t* event, void* user_param);

#endif
