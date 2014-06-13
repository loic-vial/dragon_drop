#include "ei_tag.h"
#include "ei_frame.h"
#include <stdlib.h>
#include <string.h>

ei_linked_tag_t* first_tag = NULL;

void ei_add_tag_to_list(ei_linked_tag_t** tag_list, ei_tag_t tag)
{
    if (tag_list == NULL) return;
    if (*tag_list == NULL)
    {
        (*tag_list) = (ei_linked_tag_t*) malloc(sizeof(ei_linked_tag_t));
        (*tag_list)->tag = tag;
        (*tag_list)->next = NULL;
    }
    else
    {
        ei_linked_tag_t* current_tag = *tag_list;
        while (current_tag->next!=NULL)
        {
            if (current_tag->tag == tag) return;
            current_tag=current_tag->next;
        }
        if (current_tag->tag == tag) return;
        current_tag->next = (ei_linked_tag_t*) malloc(sizeof(ei_linked_tag_t));
        current_tag->next->tag = tag;
        current_tag->next->next = NULL;
    }
}

void ei_remove_tag_from_list(ei_linked_tag_t** tag_list, ei_tag_t tag)
{
    if (tag_list == NULL) return;
    if (*tag_list == NULL) return;
    if (strcmp((*tag_list)->tag, tag) == 0)
    {
        ei_linked_tag_t* next_tag = (*tag_list)->next;
        free(*tag_list);
        (*tag_list) = next_tag;
    }
    else
    {
        ei_linked_tag_t* current_tag = *tag_list;
        while (strcmp(current_tag->next->tag, tag) !=0)
        {
            current_tag = current_tag->next;
        }
        ei_linked_tag_t* next_tag = current_tag->next->next;
        free(current_tag->next);
        current_tag->next = next_tag;
    }
}

void ei_clear_tag_list(ei_linked_tag_t** tag_list)
{
    ei_linked_tag_t* tag = *tag_list;
    while (tag != NULL)
    {
        ei_linked_tag_t* next_tag = tag->next;
        free(tag);
        tag = next_tag;
    }
    *tag_list = NULL;
}

void ei_add_tag(ei_tag_t tag)
{
    ei_add_tag_to_list(&first_tag, tag);
}

void ei_destroy_tag(ei_tag_t tag)
{
    ei_remove_tag_from_list(&first_tag, tag);
}

void ei_set_initial_tags(ei_widget_t* widget)
{
    if (!widget_has_tags(widget)) return;
    ei_frame_t* frame = (ei_frame_t*) widget;
    ei_clear_tag_list(&frame->tag);
    ei_add_tag_widget(widget, "all");
    ei_add_tag_widget(widget, ei_widgetclass_stringname(widget->wclass->name));
}

void ei_add_tag_widget(ei_widget_t* widget, ei_tag_t tag)
{
    if (!widget_has_tags(widget)) return;
    ei_frame_t* frame = (ei_frame_t*) widget;
    ei_add_tag_to_list(&frame->tag, tag);
}

void ei_destroy_tag_widget(ei_widget_t* widget, ei_tag_t tag)
{
    if (!widget_has_tags(widget)) return;
    ei_frame_t* frame = (ei_frame_t*) widget;
    ei_remove_tag_from_list(&frame->tag, tag);
}

ei_bool_t widget_has_tags(ei_widget_t *widget)
{
    if (strcmp(widget->wclass->name,"frame") == 0 ||
        strcmp(widget->wclass->name,"button") == 0 ||
        strcmp(widget->wclass->name,"toplevel") == 0 ||
        strcmp(widget->wclass->name,"radiobutton") == 0 ||
        strcmp(widget->wclass->name,"banner") == 0 ||
        strcmp(widget->wclass->name,"resize") == 0)
    {
        return EI_TRUE;
    }
    else
    {
        return EI_FALSE;
    }
}

ei_bool_t widget_has_this_tag(ei_widget_t* widget, ei_tag_t tag)
{
    if (widget == NULL || tag == NULL) return EI_FALSE;
    if (!widget_has_tags(widget)) return EI_FALSE;
    ei_frame_t* frame = (ei_frame_t*) widget;
    ei_linked_tag_t* tag_liste = frame->tag;
    while (tag_liste != NULL)
    {
        if (strcmp(tag_liste->tag, tag) == 0)
        {
            return EI_TRUE;
        }
        tag_liste = tag_liste->next;
    }
    return EI_FALSE;
}
