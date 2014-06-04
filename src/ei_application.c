#include "ei_application.h"
#include "ei_frame.h"
#include "ei_widgetclass.h"
#include "ei_geometrymanager.h"
#include "ei_event.h"
#include "ei_eventlist.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

static ei_frame_t root;
static ei_surface_t root_surface;
static ei_surface_t offscreen_surface;
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
}

void draw_widget(ei_widget_t* widget)
{
    if (widget == NULL) return;
    if (widget->geom_params != NULL) {
        widget->geom_params->manager->runfunc(widget);
    }
    widget->wclass->drawfunc(widget, root_surface, offscreen_surface, NULL);
    ei_widget_t* current = widget->children_head;
    while (current != NULL)
    {
        draw_widget(current);
        current = current->next_sibling;
    }
}

bool is_same_color(ei_color_t color1, ei_color_t color2)
{
    return (color1.red == color2.red &&
            color1.green == color2.green &&
            color1.blue == color2.blue &&
            color1.alpha == color2.alpha);
}

ei_widget_t* get_widget_with_pick_color(ei_widget_t* widget, ei_color_t color) // avec id cay plus classe
{
    if (widget == NULL) return NULL;
    if (is_same_color(*widget->pick_color, color)) return widget;
    ei_widget_t* current = widget->children_head;
    while (current != NULL)
    {
        ei_widget_t* tmp = get_widget_with_pick_color(current, color);
        if (tmp != NULL) return tmp;
        current = current->next_sibling;
    }
    return NULL;
}

ei_widget_t* pick_widget(ei_point_t position)
{
    uint8_t* buffer = hw_surface_get_buffer(offscreen_surface);
    ei_size_t size = hw_surface_get_size(offscreen_surface);
    buffer = &buffer[(position.x + position.y * size.width) * sizeof(ei_color_t)];
    ei_color_t color;
    int ir, ig, ib, ia;
    hw_surface_get_channel_indices(offscreen_surface, &ir, &ig, &ib, &ia);
    color.red = buffer[ir];
    color.green = buffer[ig];
    color.blue = buffer[ib];
    color.alpha = 255;
    return get_widget_with_pick_color(&root.widget, color);
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
                if (strcmp(tmp->tag, "all") == 0)
                {
                    tmp->callback(tmp->widget, &event, tmp->user_param);
                }
                else
                {
                    if (event.type == ei_ev_mouse_buttondown ||
                         event.type == ei_ev_mouse_buttonup ||
                         event.type == ei_ev_mouse_move)
                    {
                        if (pick_widget(event.param.mouse.where) == tmp->widget)
                        {
                            tmp->callback(tmp->widget, &event, tmp->user_param);
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
