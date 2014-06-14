#ifndef EI_BUTTON_H
#define EI_BUTTON_H

#include "ei_frame.h"


/**
 * \brief	ei_button_t     Button is a widget who has lot of common fields with frame and two for itself.
 */
typedef struct ei_button_t
{
    ei_frame_t frame; ///<It's a pointer to a widget and a frame. Many fields of frame are shared by others widgets.
    ei_callback_t callback; ///< This function will be called then the button is clicked
    void* user_param; ///<Parameter send by the user
}
ei_button_t;

/**
 * @brief	ei_button_allocfunc     A function that is called to allocate a block of the size of a \ref ei_button_t in the memory.
 *                                  It initialize it to zero.
 *
 */
void* ei_button_allocfunc();

/**
 * @brief ei_button_releasefunc A function that is called to release the memory used by the widget button.
 * @param widget    This widget is a button that must be released.
 */
void ei_button_releasefunc(ei_widget_t* widget);

/**
 * @brief ei_button_setdefaultsfunc     A function that set parameters to defaults values.
 * @param widget                        The button widget to set to default. It used the \ref ei_frame_setdefaultsfunc function.
 *                                      Callback and user_param are set to NULL.
 */
void ei_button_setdefaultsfunc(ei_widget_t* widget);

/**
 * @brief ei_button_click_down      A callback which is called when a button is clicked.
 * @param widget                    The widget button which is clicked
 * @param event                     The event \ref ei_ev_mouse_buttondown
 * @param user_param                Parameters send by the user
 * @return
 */
ei_bool_t ei_button_click_down(ei_widget_t* widget, ei_event_t* event, void* user_param);

/**
 * @brief ei_button_click_up        A callback which is called then a clicked button is unclicked
 * @param widget                    The widget button which is released
 * @param event                     The event \ref ei_ev_mouse_buttonup
 * @param user_param                Parameters send by the user
 * @return
 */
ei_bool_t ei_button_click_up(ei_widget_t* widget, ei_event_t* event, void* user_param);

#endif
