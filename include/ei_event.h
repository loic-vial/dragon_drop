/**
 *  @file	ei_event.h
 *  @brief	Allows the binding and unbinding of callbacks to events.
 *
 *  \author 
 *  Created by François Bérard on 30.12.11.
 *  Copyright 2011 Ensimag. All rights reserved.
 *
 */
#ifndef EI_EVENT_H
#define EI_EVENT_H

#include "ei_types.h"
#include "ei_widget.h"


/**
 * @brief	A string that can be attached to a widget. All widget have the tag of the name of
 *		their widget class, and the tag "all".
 */
typedef char* ei_tag_t;

/**
 * @brief	A tag and a pointer to create a linked list.
 */
typedef struct ei_linked_tag_t {
	ei_tag_t		tag;
	struct ei_linked_tag_t*	next;
} ei_linked_tag_t;

/**
 * @brief	The types of events.
 */
typedef enum {
	ei_ev_none		= 0,	///< No event, used on an un-initialized structure.
	ei_ev_app,			///< An application event, created by \ref hw_event_post_app.
	ei_ev_keydown,			///< A keyboard key has been pressed.
	ei_ev_keyup,			///< A keyboard key has been released.

	/* event types at or above "ei_ev_mouse_buttondown" are mouse events, need picking. */
	ei_ev_mouse_buttondown,		///< A mouse button has been pressed.
	ei_ev_mouse_buttonup,		///< A mouse button has been released.
	ei_ev_mouse_move,		///< The mouse has moved.

	ei_ev_last			///< Last event type, its value is the number of event types.
} ei_eventtype_t;

/**
 * @brief	The modifier keys (shift, alt, etc.)
 */
typedef enum {
	ei_mod_shift_right	= 0,	///< The "shift" key at the right of the space bar.
	ei_mod_shift_left,		///< The "shift" key at the left of the space bar.
	ei_mod_ctrl_right,		///< The "control" key at the right of the space bar.
	ei_mod_ctrl_left,		///< The "control" key at the left of the space bar.
	ei_mod_alt_right,		///< The "alternate" key at the right of the space bar.
	ei_mod_alt_left,		///< The "alternate" key at the left of the space bar.
	ei_mod_meta_right,		///< The "meta" (command) key at the right of the space bar.
	ei_mod_meta_left		///< The "meta" (command) key at the left of the space bar.

} ei_modifier_key_t;

/**
 * @brief	A bitfield indicating which of the modifier keys are currently pressed.
 */
typedef uint32_t	ei_modifier_mask_t;

/**
 * @brief	Tests is a modifier key is currently pressed, according to a bitfield.
 *
 * @param	mask		The bitfield.
 * @param	modifier	The modifier key that is tested.
 *
 * @return			EI_TRUE is this modifier key is currently pressed, EI_FALSE
 *				otherwise.
 */
static
inline ei_bool_t	ei_has_modifier	(ei_modifier_mask_t	mask,
					 ei_modifier_key_t	modifier)
						{ return (ei_bool_t)(mask & (1 << modifier)); }

/**
 * @brief	The event parameter for keyboard-related event types.
 */
typedef struct {
	SDLKey				key_sym;	///< The keyboard key symbol (see \ref SDL_keysym.h)
	ei_modifier_mask_t		modifier_mask;	///< The state of the modifier keys at the time of the event.
} ei_key_event_t;

/**
 * @brief	The event parameter for mouse-related event types.
 */
typedef struct {
	ei_point_t			where;		///< Where the mouse pointer was at the time of the event.
	int				button_number;	///< The number of the button that was pressed or released. Only valid for \ref ei_ev_mouse_buttondown or \ref ei_ev_mouse_buttonup event types.
} ei_mouse_event_t;

/**
 * @brief	The event parameter for application defined event types.
 */
typedef struct {
	void*				user_param;
} ei_app_event_t;

/**
 * @brief	Describes an event.
 */
typedef struct ei_event_t {
	ei_eventtype_t	type;				///< The type of the event.
	union {
		ei_key_event_t		key;		///< Event parameters for keyboard-related events (see \ref ei_key_event_t).
		ei_mouse_event_t	mouse;		///< Event parameters for mouse-related	events (see \ref ei_mouse_event_t).
		ei_app_event_t		application;	///< Event parameters for application-related events (see \ref ei_app_event_t).
	} param;
} ei_event_t;





/**
 * \brief	Binds a callback to an event type and a widget or a tag.
 *
 * @param	eventtype	The type of the event.
 * @param	widget		The callback is only called if the event is related to this widget.
 *				This parameter must be NULL if the "tag" parameter is not NULL.
 * @param	tag		The callback is only called if the event is related to a widget that
 *				has this tag. A tag can be a widget class name, or the tag "all".
 *				This parameter must be NULL is the "widget" parameter is not NULL.
 * @param	callback	The callback (i.e. the function to call).
 * @param	user_param	A user parameter that will be passed to the callback when it is
 *				called.
 */
void		ei_bind			(ei_eventtype_t		eventtype,
					 ei_widget_t*		widget,
					 ei_tag_t		tag,
					 ei_callback_t		callback,
					 void*			user_param);

/**
 * \brief	Unbinds a callback from an event type and widget or tag.
 *
 * @param	eventtype, widget, tag, callback, user_param
 *				All parameters must have the same value as when \ref ei_bind was
 *				called to create the binding.
 */
void		ei_unbind		(ei_eventtype_t		eventtype,
					 ei_widget_t*		widget,
					 ei_tag_t		tag,
					 ei_callback_t		callback,
					 void*			user_param);



#endif
