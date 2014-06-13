#include <stdio.h>
#include <stdlib.h>
#include "ei_application.h"
#include "ei_widget.h"
#include "ei_utils.h"
#include "ei_utils_2.h"
#include "ei_event.h"
#include "ei_geometrymanager.h"

ei_bool_t process_key(ei_widget_t* widget, ei_event_t* event, void* user_param);


int sf_ei_main(int argc, char* argv[])
{
    ei_size_t	root_window_size		= { 800, 600 };
	ei_color_t	root_bgcol			= { 0x52, 0x7f, 0xb4, 0xff };
    ei_bool_t	fullscreen			= EI_FALSE;

	ei_app_create(&root_window_size, fullscreen);
    ei_frame_configure(ei_app_root_widget(), NULL, &root_bgcol, NULL, NULL, NULL,
                       NULL, NULL, NULL, NULL, NULL, NULL);


    ei_widget_t* toplevel = ei_widget_create("toplevel", ei_app_root_widget());
    ei_size_t toplevel_size = ei_size(200, 230);
    ei_color_t toplevel_color = ei_color(210, 123, 200, 210);
    int toplevel_border = 0;
    int toplevel_x = 40;
    int toplevel_y = 20;
    ei_bool_t toplevel_closable = EI_TRUE;
    ei_axis_set_t toplevel_resizable = ei_axis_y;
    ei_toplevel_configure(toplevel, &toplevel_size, &toplevel_color, &toplevel_border, NULL, &toplevel_closable,
                       &toplevel_resizable, NULL);
    ei_place(toplevel, NULL, &toplevel_x, &toplevel_y, NULL, NULL, NULL, NULL, NULL, NULL);


    ei_widget_t* frame = ei_widget_create("frame", toplevel);
    ei_size_t frame_size = ei_size(50, 30);
    ei_color_t frame_color = ei_color(210, 123, 200, 210);
    ei_frame_configure(frame, &frame_size, &frame_color, NULL, NULL, NULL,
                       NULL, NULL, NULL, NULL, NULL, NULL);
    ei_place(frame, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);

    ei_bind(ei_ev_keydown, NULL, "all", process_key, NULL);

	ei_app_run();
	
	ei_app_free();

	return (EXIT_SUCCESS);
}
