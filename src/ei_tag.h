#ifndef EI_TAG_H
#define EI_TAG_H

#include "ei_event.h"

extern ei_linked_tag_t* first_tag;

void ei_add_tag_to_list(ei_linked_tag_t** tag_list, ei_tag_t tag);

void ei_remove_tag_from_list(ei_linked_tag_t** tag_list, ei_tag_t tag);

void ei_clear_tag_list(ei_linked_tag_t** tag_list);

void ei_set_initial_tags(ei_widget_t* widget);

void ei_add_tag_widget(ei_widget_t* widget, ei_tag_t tag);

void ei_destroy_tag_widget(ei_widget_t* widget, ei_tag_t tag);

void add_tag(ei_tag_t tag);

void ei_destroy_tag(ei_tag_t tag);

ei_bool_t widget_has_tags(ei_widget_t* widget);

ei_bool_t widget_has_this_tag(ei_widget_t* widget, ei_tag_t tag);

#endif
