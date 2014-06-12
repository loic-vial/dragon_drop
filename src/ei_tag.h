#ifndef EI_TAG_H
#define EI_TAG_H

#include "ei_event.h"

 ei_linked_tag_t* ei_initial_tag_t(ei_widget_t* widget);

 void ei_add_tag(ei_widget_t* widget,ei_tag_t* tag);

 void ei_destroy_tag(ei_widget_t* widget,ei_tag_t* tag);


#endif
