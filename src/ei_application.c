#include "ei_application.h"
#include <stdio.h>
#include <stdlib.h>
#include "ei_frame.h"
#include "ei_widgetclass.h"
#include "string.h"

ei_widget_t root;

void ei_app_create(ei_size_t* main_window_size, ei_bool_t fullscreen)
{
    /*initializes the hardware */
    ei_surface_t surface_in;
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

void ei_app_run()
{
    // pour chaque widget
    // on recupere la classe, donc la fonction de draw

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
    NULL;
    // on retourne le widget "root" déclaré en global ici tout en haut
}


ei_surface_t ei_app_root_surface()
{
    NULL;
}



void ei_app_free()
{
    NULL;
}

