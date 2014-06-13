#include "ei_tag.h"
#include "ei_widgetclass.h"
#include "ei_frame.h"
#include <stdlib.h>
#include <string.h>

ei_linked_tag_t* first_tag = NULL;

void ei_add_tag(ei_tag_t tag)
{
    if(first_tag == NULL)
    {
        first_tag=(ei_linked_tag_t*)malloc(sizeof(ei_linked_tag_t));
        first_tag->tag=tag;
        first_tag->next=NULL;
    }
    else
    {
        ei_linked_tag_t* current_tag = first_tag;
        while(current_tag->next!=NULL)
        {
            if(current_tag->tag == tag) return;
            current_tag=current_tag->next;
        }
        if(current_tag->tag == tag) return;
        current_tag->next=(ei_linked_tag_t*)malloc(sizeof(ei_linked_tag_t));
        current_tag->next->tag=tag;
        current_tag->next->next=NULL;
    }
}

void ei_destroy_tag(ei_tag_t tag)
{
    if(first_tag != NULL)
    {
        if (strcmp(first_tag->tag, tag) == 0)
        {
            ei_linked_tag_t* next_tag = first_tag->next;
            free(first_tag);
            first_tag = next_tag;
        }
        else
        {
            ei_linked_tag_t* current_tag = first_tag;
            while(current_tag->next != NULL)
            {
                ei_linked_tag_t* next_tag = current_tag->next;
                if (strcmp(next_tag->tag, tag) == 0)
                {
                    current_tag->next = next_tag->next;
                    current_tag = next_tag->next;
                    free(next_tag);
                }
                else
                {
                    current_tag = next_tag;
                }
            }
        }
    }
}

void ei_initial_tag_t(ei_widget_t* widget)
{
    ei_tag_t tag = (ei_tag_t)"all";
    ei_add_tag_widget(widget,tag);
    char* text=ei_widgetclass_stringname(widget->wclass->name);
    tag=(ei_tag_t)text;
    ei_add_tag_widget(widget,tag);
}

void ei_add_tag_widget(ei_widget_t* widget,ei_tag_t tag)
{
    ei_frame_t* frame = (ei_frame_t*) widget;
    if (frame->tag == NULL)
    {
        frame->tag = (ei_linked_tag_t*)malloc(sizeof(ei_linked_tag_t));
        frame->tag->next = NULL;
        frame->tag->tag = tag;
    }
    else
    {
        ei_linked_tag_t* current_tag = frame->tag;
        while (current_tag->next !=NULL)
        {
            current_tag = current_tag->next;
        }
        current_tag->next = (ei_linked_tag_t*)malloc(sizeof(ei_linked_tag_t));
        current_tag->next->next = NULL;
        current_tag->next->tag = tag;
    }
    ei_add_tag(tag);
}

void ei_destroy_tag_widget(ei_widget_t* widget,ei_tag_t tag)
{
    ei_frame_t* frame = (ei_frame_t*)widget;
    ei_linked_tag_t* tag_liste = frame->tag;
    if(strcmp((char*)tag_liste->tag,(char*)tag) == 0)
    {
        ei_linked_tag_t* next_tag = frame->tag->next;
        free(frame->tag);
        frame->tag=next_tag;
    }
    else
    {
        while (strcmp((char*)tag_liste->next->tag,(char*)tag) !=0)
        {
            tag_liste=tag_liste->next;
        }
        ei_linked_tag_t* next_tag = tag_liste->next->next;
        free(tag_liste->next);
        tag_liste->next=next_tag;
    }
}
