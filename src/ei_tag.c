#include "ei_tag.h"
#include <stdlib.h>
#include "ei_widgetclass.h"

ei_linked_tag_t* ei_initial_tag_t(ei_widget_t* widget)
{
    ei_linked_tag_t* all = (ei_linked_tag_t*)malloc(sizeof(ei_linked_tag_t));
    all->tag="all";
    ei_linked_tag_t* name = (ei_linked_tag_t*)malloc(sizeof(ei_linked_tag_t));
    name->tag=ei_widgetclass_stringname	(widget->wclass->name);
    all->next=name;
    name->next=NULL;
    return all;
}
