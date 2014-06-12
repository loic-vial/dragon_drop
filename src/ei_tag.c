#include "ei_tag.h"
#include <stdlib.h>
#include <string.h>
#include "ei_widgetclass.h"
#include "ei_frame.h"

ei_linked_tag_t* first_linked_tag =NULL;

void ei_add_tag(ei_tag_t tag)
{
    ei_linked_tag_t* last_tag = first_linked_tag;
    ei_linked_tag_t* new_tag=(ei_linked_tag_t*)malloc(sizeof(ei_linked_tag_t));
    new_tag->tag=tag;
    new_tag->next=NULL;
    if(first_linked_tag == NULL)
    {
        first_linked_tag=new_tag;
    }
    else
    {
        while(last_tag->next!=NULL)
        {
            if(last_tag->tag == tag)  return;
            last_tag=last_tag->next;
        }
        if(last_tag->tag == tag)  return;
        last_tag->next=new_tag;
    }
}

void ei_destroy_tag(ei_tag_t tag)

{
    if(first_linked_tag !=NULL)
    {
        ei_linked_tag_t* last_tag = first_linked_tag;
        while(last_tag != NULL)
        {
            if( strcmp(last_tag->next->tag,tag)!=0) break;


            last_tag=last_tag->next;
        }
        ei_linked_tag_t* to_destroy = last_tag->next; //TODO désalouer to_destroy
        last_tag->next=last_tag->next->next;
    }
}

ei_linked_tag_t* ei_initial_tag_t(ei_widget_t* widget)
{
    ei_linked_tag_t* all = (ei_linked_tag_t*)malloc(sizeof(ei_linked_tag_t));
    all->tag="all";
    ei_linked_tag_t* name = (ei_linked_tag_t*)malloc(sizeof(ei_linked_tag_t));
    name->tag=ei_widgetclass_stringname	(widget->wclass->name);
    all->next=name;
    name->next=NULL;
    ei_tag_t to_add = all->tag;
    ei_add_tag(to_add);
    to_add=name->tag;
    ei_add_tag(to_add);
    return all;
}

void ei_add_tag_widget(ei_widget_t* widget,ei_tag_t tag)
{
    ei_linked_tag_t* new_tag=(ei_linked_tag_t*)malloc(sizeof(ei_linked_tag_t));
    new_tag->next=NULL;
    new_tag->tag=
            tag;
    ei_frame_t* frame=(ei_frame_t*)widget;
    ei_linked_tag_t* tag_liste = frame->tag;
    while (tag_liste->next !=NULL)
    {
        tag_liste=tag_liste->next;
    }
    tag_liste->next=new_tag;
    ei_add_tag(tag);
}

void ei_destroy_tag_widget(ei_widget_t* widget,ei_tag_t tag)
{
    ei_frame_t* frame=(ei_frame_t*)widget;
    ei_linked_tag_t* tag_liste = frame->tag;
    if(strcmp((char*)tag_liste->tag,(char*)tag)==0)
    {
        frame->tag=frame->tag->next;
    }
    else
    {
        while (strcmp((char*)tag_liste->next->tag,(char*)tag) !=0)
        {
            tag_liste=tag_liste->next;
        }
        tag_liste->next=tag_liste->next->next; //TODO desalouer le tag detruit
    }
}
