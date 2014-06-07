#include "ei_application.h"
#include "ei_frame.h"
#include "ei_widgetclass.h"
#include "ei_geometrymanager.h"
#include "ei_event.h"
#include "ei_eventlist.h"
#include "ei_toplevel.h"
#include "ei_utils_2.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

static ei_frame_t root;
static ei_surface_t root_surface;
ei_surface_t offscreen_surface;
static bool want_quit;

void ei_app_create(ei_size_t* main_window_size, ei_bool_t fullscreen)
{
    hw_init();

    want_quit = false;
    root_surface = hw_create_window(main_window_size, fullscreen);
    offscreen_surface = hw_surface_create(root_surface, main_window_size, true);

    ei_frame_register_class();
    ei_button_register_class();
    ei_toplevel_register_class();
    ei_banner_register_class();
    ei_register_placer_manager();

    root.widget.wclass = ei_widgetclass_from_name("frame");
    root.widget.pick_id = 0;
    root.widget.pick_color = malloc(sizeof(ei_color_t));
    root.widget.pick_color->red = 0;
    root.widget.pick_color->green = 0;
    root.widget.pick_color->blue = 0;
    root.widget.pick_color->alpha = 255;
    root.widget.parent = NULL;
    root.widget.children_head = NULL;
    root.widget.children_tail = NULL;
    root.widget.next_sibling = NULL;
    root.widget.geom_params = NULL;
    root.widget.requested_size = *main_window_size;
    root.widget.screen_location.top_left.x = 0;
    root.widget.screen_location.top_left.y = 0;
    root.widget.screen_location.size = *main_window_size;
    root.widget.content_rect = &root.widget.screen_location;
    ei_place(&root.widget,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL);
}


ei_rect_t ei_clipper(ei_widget_t* widget)
{
    ei_rect_t clipper;
    clipper.size=widget->parent->requested_size;
    clipper.top_left=widget->parent->screen_location.top_left;

    if (widget->parent->parent ==NULL)
    {
        return clipper;
    }
    else
    {
        ei_widget_t* current = widget->parent->parent;
        ei_rect_t rect;
        while (current !=NULL)
        {
            rect.size=current->requested_size;
            rect.top_left=current->screen_location.top_left;
            clipper= calcul_clipper(rect, clipper);
            current=current->parent;
        }

        return clipper;
    }
}

void draw_widget(ei_widget_t* widget)
{
    if (widget == NULL) return;
    if (widget->geom_params == NULL) return;
    widget->geom_params->manager->runfunc(widget);

    if(widget->parent== NULL)
    {
        widget->wclass->drawfunc(widget, root_surface, offscreen_surface,NULL);
    }
    else
    {
        ei_rect_t clipper;
        clipper = ei_clipper(widget);

        if( strcmp(widget->wclass->name,"banner") ==0 )
        {
            clipper.top_left.y-=widget->requested_size.height;
            clipper.size.height=widget->requested_size.height;
        }
        if( strcmp(widget->parent->wclass->name,"banner") ==0 )
        {
            clipper.top_left=widget->screen_location.top_left;
            clipper.size=widget->requested_size;
        }
        widget->wclass->drawfunc(widget, root_surface, offscreen_surface,&clipper);
    }

    ei_widget_t* current = widget->children_head;
    while (current != NULL)
    {
        draw_widget(current);
        current = current->next_sibling;
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
        draw_widget(&root.widget);
        hw_surface_unlock(root_surface);
        hw_surface_unlock(offscreen_surface);
        hw_surface_update_rects(root_surface, NULL);
        hw_surface_update_rects(offscreen_surface, NULL);

        hw_event_wait_next(&event);

        ei_eventlist_t* tmp = first_eventlist;
        for (tmp = first_eventlist ; tmp != NULL ; tmp = tmp->next)
        {
            if (tmp->eventtype == event.type)
            {
                if (event.type == ei_ev_mouse_buttondown ||
                        event.type == ei_ev_mouse_buttonup ||
                        event.type == ei_ev_mouse_move)
                {
                    ei_widget_t* widget_picked = ei_widget_pick(&event.param.mouse.where);
                    if ((tmp->tag == NULL && widget_picked == tmp->widget) ||
                            (tmp->tag != NULL && strcmp(tmp->tag, "all") == 0) ||
                            (tmp->tag != NULL && strcmp(tmp->tag, widget_picked->wclass->name) == 0))
                    {
                        tmp->callback(widget_picked, &event, tmp->user_param);
                    }
                }
                else
                {
                    tmp->callback(tmp->widget, &event, tmp->user_param);
                }
            }
        }
    }
}

void ei_app_invalidate_rect(ei_rect_t* rect)
{

}

void ei_app_quit_request()
{
    want_quit = true;
}

ei_widget_t* ei_app_root_widget()
{
    return &root.widget;
}

ei_surface_t ei_app_root_surface()
{
    return root_surface;
}

void ei_app_free()
{
    hw_quit();
}
