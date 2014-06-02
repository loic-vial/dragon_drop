#include "ei_application.h"
#include <stdio.h>
#include <stdlib.h>
#include "ei_frame.h"
#include "ei_widgetclass.h"
#include "string.h"

void ei_app_create(ei_size_t* main_window_size, ei_bool_t fullscreen)
{
    /*initializes the hardware */
    ei_surface_t surface_in;
    void hw_init();

    /* registers all classes of widget and all geometry managers*/

    /*register of the frame class */
    ei_widgetclass_t frame;
    strcpy(frame.name,"frame");
    frame.allocfunc=&allocfunc_frame;
    frame.releasefunc=&releasefunc_frame;
    frame.drawfunc=&drawfunc_frame;
    frame.setdefaultsfunc=&setdefaultsfunc_frame;
    frame.geomnotifyfunc=&geomnotifyfunc_frame;
    frame.next = NULL;

    ei_widgetclass_register(&frame); /* TODO mettre toutes les classes*/

/* registers all classes of widget and all geometry managers*/
surface_in = hw_create_window(main_window_size, (const ei_bool_t) fullscreen);
}

void ei_app_run()
{
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
}


ei_surface_t ei_app_root_surface()
{
    NULL;
}



void ei_app_free()
{
    NULL;
}

