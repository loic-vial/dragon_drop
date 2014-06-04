#include "ei_application.h"
#include <stdio.h>
#include <stdlib.h>
#include "ei_frame.h"
#include "ei_widgetclass.h"
#include "string.h"

static ei_frame_t root;
static ei_surface_t root_surface;

void ei_app_create(ei_size_t* main_window_size, ei_bool_t fullscreen)
{
    hw_init();

    root_surface = hw_create_window(main_window_size, fullscreen);

    ei_frame_register_class();

    root.widget.wclass = ei_widgetclass_from_name("frame");
    root.widget.pick_id = 0;
    root.widget.pick_color = NULL;
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
    widget->wclass->drawfunc(widget, root_surface, root_surface, NULL);
    ei_widget_t* current = widget->children_head;
    while (current != NULL)
    {
        draw_widget(current);
        current = current->next_sibling;
    }
}

void ei_app_run()
{
    hw_surface_lock(root_surface);
    draw_widget(&root.widget);
    hw_surface_unlock(root_surface);
    hw_surface_update_rects(root_surface, NULL);
    getchar();
}

void ei_app_invalidate_rect(ei_rect_t* rect)
{
    NULL;
}

void ei_app_quit_request()
{
    NULL;
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
    NULL;
}
