#ifndef EI_EVENTLIST_H
#define EI_EVENTLIST_H

#include "ei_event.h"

/**
 * @brief Defines a doubly linked list of events.
 */ 
typedef struct ei_eventlist_t {
	ei_eventtype_t eventtype; ///< The type of event
	ei_widget_t *widget; ///< The widget associated with the event
	ei_tag_t tag; ///< The tag associciated with the event
	ei_callback_t callback; ///< The callback function associated with the event
	void *user_param; ///< The parameters of the callback
	struct ei_eventlist_t *next; ///< A pointer to the next event
	struct ei_eventlist_t *previous; ///< A pointer to the previous event
} ei_eventlist_t;

/// @brief Global variable to give access to all events
extern ei_eventlist_t *first_event;

#endif
