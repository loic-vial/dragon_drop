#include <stdio.h>
#include <stdlib.h>
#include "ei_application.h"
#include "ei_event.h"
#include "hw_interface.h"
#include "ei_widget.h"
#include "ei_geometrymanager.h"
#include "../src/ei_radiobutton.h"

ei_bool_t button_press(ei_widget_t* widget, ei_event_t* event, void* user_param);
ei_bool_t process_key(ei_widget_t* widget, ei_event_t* event, void* user_param);
ei_callback_t button_callback = button_press;


ei_bool_t button_press(ei_widget_t* widget, ei_event_t* event, void* user_param)
{
    printf("Click !\n");
    return EI_TRUE;
}

ei_bool_t process_key(ei_widget_t* widget, ei_event_t* event, void* user_param)
{
    if (event->param.key.key_sym == SDLK_ESCAPE) {
        ei_app_quit_request();
        return EI_TRUE;
    }

    return EI_FALSE;
}

int _______ei_main(int argc, char** argv)
{
    ei_size_t	screen_size	= {400, 400};
    ei_color_t      root_bgcol      = {0x52, 0x7f, 0xb4, 0xff};

    ei_app_create(&screen_size, EI_FALSE);
    ei_frame_configure(ei_app_root_widget(), NULL, &root_bgcol, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);

    ei_widget_t*	frame;
    ei_size_t	frame_size		= {200,200};
    int		frame_x			= 30;
    int		frame_y			= 30;
    ei_color_t	frame_color		= {0x00, 0x88, 0x88, 0xff};
    ei_relief_t	frame_relief		= ei_relief_raised;
    int		frame_border_width	= 6;


    frame = ei_widget_create("radiobutton", ei_app_root_widget());
  ei_radiobutton_configure(frame, &frame_size, &frame_color,
                &frame_border_width, &frame_relief, NULL, NULL, NULL, NULL,
                NULL, NULL, NULL);
    ei_place(frame, NULL, &frame_x, &frame_y, NULL, NULL, NULL, NULL, NULL, NULL );


    ei_bind(ei_ev_keydown, 		NULL, "all", process_key, NULL);

    ei_app_run();

    ei_unbind(ei_ev_keydown,	NULL, "all", process_key, NULL);

    ei_app_free();

    return (EXIT_SUCCESS);
}
