#ifndef EI_TAG_H
#define EI_TAG_H

#include "ei_event.h"

void ei_initial_tag_t(ei_widget_t* widget);

void ei_add_tag_widget(ei_widget_t* widget,ei_tag_t tag);

void ei_destroy_tag_widget(ei_widget_t* widget,ei_tag_t tag);

void add_tag(ei_tag_t tag);

void ei_destroy_tag(ei_tag_t tag);

extern ei_linked_tag_t* first_linked_tag;

#endif
