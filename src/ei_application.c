#include "ei_application.h"
#include "ei_frame.h"
#include "ei_widgetclass.h"
#include "ei_geometrymanager.h"
#include "ei_event.h"
#include "ei_eventlist.h"
#include "ei_toplevel.h"
#include "ei_utils.h"
#include "ei_utils_2.h"
#include "ei_radiobutton.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

extern ei_widgetclass_t* first_class;
static ei_frame_t* root;
static ei_surface_t root_surface;
ei_surface_t offscreen_surface;
static bool want_quit;
ei_linked_rect_t* invalid_rects;

void ei_app_create(ei_size_t* main_window_size, ei_bool_t fullscreen)
{
    hw_init();

    want_quit = false;
    invalid_rects = NULL;
    root_surface = hw_create_window(main_window_size, fullscreen);
    offscreen_surface = hw_surface_create(root_surface, main_window_size, true);

    ei_radiobutton_register_class();
    ei_frame_register_class();
    ei_button_register_class();
    ei_toplevel_register_class();
    ei_register_placer_manager();

    root = (ei_frame_t*) ei_widget_create("frame", NULL);
    ei_color_t color = ei_color(0, 0, 0, 255);
    ei_frame_configure(&root->widget, main_window_size, &color, NULL, NULL, NULL, NULL,
                       NULL, NULL, NULL, NULL, NULL);
    ei_place(&root->widget, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
}


ei_rect_t compute_clipper(ei_widget_t* widget)
{
    ei_rect_t clipper = ei_rect(ei_point_zero(), hw_surface_get_size(root_surface));
    while (widget->parent != NULL)
    {
        ei_rect_t rect = *widget->parent->content_rect;
        if (strcmp(widget->wclass->name,"banner") == 0)
        {
            rect.top_left.y -= widget->content_rect->size.height;
            rect.size.height = widget->content_rect->size.height;
        }
        clipper = rectangle_intersection(rect, clipper);
        widget = widget->parent;
    }
    return clipper;
}

void draw_widget(ei_widget_t* widget)
{
    if (widget == NULL) return;
    if (widget->geom_params == NULL) return;
    widget->geom_params->manager->runfunc(widget);
    ei_rect_t clipper = compute_clipper(widget);
    widget->wclass->drawfunc(widget, root_surface, offscreen_surface, &clipper);
    for (ei_widget_t* current = widget->children_head ; current != NULL ; current = current->next_sibling)
    {
        draw_widget(current);
    }
}

void clear_rect_list(ei_linked_rect_t** rects)
{
    if (rects == NULL) return;
    ei_linked_rect_t* rect = *rects;
    while (rect != NULL)
    {
        ei_linked_rect_t* next_rect = rect->next;
        free(rect);
        rect = next_rect;
    }
    *rects = NULL;
}

void manage_event(ei_event_t event)
{
    ei_eventlist_t* event_tmp = first_event;
    while (event_tmp != NULL)
    {
        ei_eventlist_t* next_event = event_tmp->next;
        if (event_tmp->eventtype == event.type)
        {
            if (event.type == ei_ev_mouse_buttondown ||
                event.type == ei_ev_mouse_buttonup ||
                event.type == ei_ev_mouse_move)
            {
                ei_widget_t* widget_picked = ei_widget_pick(&event.param.mouse.where);
                if ((event_tmp->tag == NULL && widget_picked == event_tmp->widget) ||
                    (event_tmp->tag != NULL && strcmp(event_tmp->tag, "all") == 0) ||
                    (event_tmp->tag != NULL && strcmp(event_tmp->tag, widget_picked->wclass->name) == 0))
                {
                    event_tmp->callback(widget_picked, &event, event_tmp->user_param);
                }
            }
            else
            {
                event_tmp->callback(event_tmp->widget, &event, event_tmp->user_param);
            }
        }
        event_tmp = next_event;
    }
}

void ei_app_run()
{
    ei_event_t event;
    event.type = ei_ev_none;
    while (!want_quit)
    {
        hw_surface_lock(root_surface);
        hw_surface_lock(offscreen_surface);
        draw_widget(&root->widget);
        hw_surface_unlock(root_surface);
        hw_surface_unlock(offscreen_surface);
        //if (invalid_rects != NULL)
        {
            hw_surface_update_rects(root_surface, NULL);
            hw_surface_update_rects(offscreen_surface, NULL);
        }
        clear_rect_list(&invalid_rects);
        hw_event_wait_next(&event);
        manage_event(event);
    }
}

void ei_app_invalidate_rect(ei_rect_t* rect)
{
    ei_rect_t root_rect = ei_rect(ei_point_zero(), hw_surface_get_size(root_surface));
    ei_rect_t new_rect = rectangle_intersection(*rect, root_rect);
    if (invalid_rects == NULL)
    {
        invalid_rects = (ei_linked_rect_t*) malloc(sizeof(ei_linked_rect_t));
        invalid_rects->rect = new_rect;
        invalid_rects->next = NULL;
    }
    else
    {
        ei_linked_rect_t* tmp = invalid_rects;
        while (tmp->next != NULL) tmp = tmp->next;
        tmp->next = (ei_linked_rect_t*) malloc(sizeof(ei_linked_rect_t));
        tmp->next->rect = new_rect;
        tmp->next->next = NULL;
    }
}

void ei_app_quit_request()
{
    want_quit = true;
}

ei_widget_t* ei_app_root_widget()
{
    return &root->widget;
}

ei_surface_t ei_app_root_surface()
{
    return root_surface;
}

void ei_app_free()
{
    ei_widget_destroy(&root->widget);
    hw_surface_free(root_surface);
    hw_surface_free(offscreen_surface);

    ei_linked_tag_t* tag = first_tag;
    while (tag != NULL)
    {
        ei_linked_tag_t* next_tag = tag->next;
        free(tag);
        tag = next_tag;
    }

    ei_eventlist_t* event = first_event;
    while (event != NULL)
    {
        ei_eventlist_t* next_event = event->next;
        free(event);
        event = next_event;
    }

    ei_widgetclass_t* wclass = first_class;
    while (wclass != NULL)
    {
        ei_widgetclass_t* next_wclass = wclass->next;
        free(wclass);
        wclass = next_wclass;
    }

    hw_quit();
}
