#ifndef EI_TAG_H
#define EI_TAG_H

#include "ei_event.h"

/**
 * @brief first_tag     A pointer to a list of all tags present in the application
 */
extern ei_linked_tag_t* first_tag;

/**
 * @brief ei_add_tag_to_list        Adds a tag to a list
 * @param tag_list                  The list where to add the tag
 * @param tag                       The tag to add
 */
void ei_add_tag_to_list(ei_linked_tag_t** tag_list, ei_tag_t tag);

/**
 * @brief ei_remove_tag_from_list      Removes a tag to a list
 * @param tag_list                     The list where to remove the tag
 * @param tag                          The tag to remove
 */
void ei_remove_tag_from_list(ei_linked_tag_t** tag_list, ei_tag_t tag);

/**
 * @brief ei_clear_tag_list            Destroys all tags in a list
 * @param tag_list                     The list to clear
 */
void ei_clear_tag_list(ei_linked_tag_t** tag_list);

/**
 * @brief ei_set_initial_tags           Adds the tag "all and the name of the class of the widget when a widget is set to default
 * @param widget                        Widget where to add these two tags
 */
void ei_set_initial_tags(ei_widget_t* widget);

/**
 * @brief ei_add_tag_widget         Adds a tag to a widget
 * @param widget                    The widget where to add the tag
 * @param tag                       The tag to add
 */
void ei_add_tag_widget(ei_widget_t* widget, ei_tag_t tag);

/**
 * @brief ei_destroy_tag_widget     Destroys a tag to a widget
 * @param widget                    The widget where to destroy the tag
 * @param tag                       The tag to destroy
 */
void ei_destroy_tag_widget(ei_widget_t* widget, ei_tag_t tag);

/**
 * @brief add_tag           Adds a tag in the list \ref first_tag
 * @param tag               The tag to add
 */
void add_tag(ei_tag_t tag);

/**
 * @brief ei_destroy_tag    Destroys a tag in the list \ref first_tag
 *                          If a tag is destroy in this list, all events linked to this tag become useless
 * @param tag               The tag to destroy
 */
void ei_destroy_tag(ei_tag_t tag);

/**
 * @brief widget_has_tags   A function to know if a widget has a list of tags
 * @param widget            The widget to test if it has tags or not
 * @return                  Return EI_TRUE if the widget has a list of tags
 */
ei_bool_t widget_has_tags(ei_widget_t* widget);

/**
 * @brief widget_has_this_tag   A function to know if a widget has one of particular tag
 * @param widget                The widget to test
 * @param tag                   The tag to test if it is present or not in the list of tags of the widget
 * @return                      Returns EI_TRUE if the tag is present in the list of tags of the widget
 */

ei_bool_t widget_has_this_tag(ei_widget_t* widget, ei_tag_t tag);

/**
 * @brief has_this_tag          A function to know if a particular tag is present in the list of all tags of the application
 * @param tag                   The tag to test
 * @return                      Returns EI_TRUE if the tag is present in the list of tags of the application
 */
ei_bool_t has_this_tag(ei_tag_t tag);

/**
 * @brief ei_list_has_this_tag  A function to know if a tag is present in a list
 * @param tag_list              The list where to seek the tag
 * @param tag                   The tag to test if it is present in the list
 * @return                      Returns EI_TRUE if the tag is present in the list
 */
ei_bool_t ei_list_has_this_tag(ei_linked_tag_t* tag_list, ei_tag_t tag);

#endif
