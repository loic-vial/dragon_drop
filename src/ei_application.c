#include "ei_application.h"
#include <stdio.h>
#include <stdlib.h>
#include "ei_frame.h"
#include "ei_widgetclass.h"
#include "string.h"

ei_widget_t root;
ei_surface_t surface_in;

void ei_app_create(ei_size_t* main_window_size, ei_bool_t fullscreen)
{
    /*initializes the hardware */
    void hw_init();

    /*creates the root widget to accress the root window. */

   root.wclass = NULL;
    root.pick_id=0xFFFFFF;
    root.pick_color=0xFFFFFF;
    root.parent=NULL;
    root.children_head=NULL;
    root.children_tail;
    root.next_sibling;
    root.geom_params=NULL;
    /*   ei_size_t		requested_size;	///< Size requested by the widget (big enough for its label, for example), or by the programmer. This can be different than its screen size defined by the placer.
        ei_rect_t		screen_location;///< Position and size of the widget expressed in the root window reference.
        ei_rect_t*		content_rect;	///< Where to place children, when this widget is used as a container. By defaults, points to the screen_location.
*/


    /* registers all classes of widget and all geometry managers*/
    /* TODO mettre toutes les classes*/
   ei_frame_register_class ();

    /*creates the root window (either in a system window, or the entire
 *				screen),*/
    surface_in = hw_create_window(main_window_size, (const ei_bool_t) fullscreen);
}

void draw_widget(ei_widget_t* widget)
{
    if (widget == NULL) return;
    widget->wclass->drawfunc(widget, surface_in, surface_in, NULL);
    ei_widget_t* current = widget->children_head;
    while (current != NULL)
    {
        draw_widget(current);
        current = current->next_sibling;
    }
}

void ei_app_run()
{
    ei_widget_t* root = ei_app_root_widget();
    draw_widget(root);

      getchar();
   // ei_widget_t* root = ei_app_root_widget();
    //parcours de la hiérarchie des widgets
  //  while (root->children_head)

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
    return &root;
}


ei_surface_t ei_app_root_surface()
{
    NULL;
}



void ei_app_free()
{
    NULL;
}

