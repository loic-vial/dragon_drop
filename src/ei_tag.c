#include "ei_tag.h"
#include <stdlib.h>
#include <string.h>
#include "ei_widgetclass.h"
#include "ei_frame.h"

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

void ei_add_tag(ei_widget_t* widget,ei_tag_t* tag)
{
    ei_linked_tag_t* new_tag=(ei_linked_tag_t*)malloc(sizeof(ei_linked_tag_t));
    new_tag->next=NULL;
    new_tag->tag=*tag;
    ei_frame_t* frame=(ei_frame_t*)widget;
    ei_linked_tag_t* tag_liste = frame->tag;
    while (tag_liste->next !=NULL)
    {
        tag_liste=tag_liste->next;
    }
    tag_liste->next=new_tag;
}

void ei_destroy_tag(ei_widget_t* widget,ei_tag_t* tag)
{
    ei_frame_t* frame=(ei_frame_t*)widget;
    ei_linked_tag_t* tag_liste = frame->tag;
    while (strcmp((char*)tag_liste->next->tag,(char*)tag) !=0)
    {
        tag_liste=tag_liste->next;
    }
    tag_liste->next=tag_liste->next->next; //TODO desalouer le tag detruit

}
