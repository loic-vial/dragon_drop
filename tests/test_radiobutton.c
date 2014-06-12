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


ei_bool_t field(ei_widget_t* widget, ei_event_t* event, void* user_param)
{
    char* text =ei_return_field((ei_radiobutton_t*)widget);
    printf("%s!\n",text);
    return EI_TRUE;

}
int ___ei_main(int argc, char** argv)
{
    ei_size_t	screen_size	= {400, 400};
    ei_color_t      root_bgcol      = {0x52, 0x7f, 0xb4, 0xff};

    ei_app_create(&screen_size, EI_FALSE);
    ei_frame_configure(ei_app_root_widget(), NULL, &root_bgcol, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);

    ei_size_t	size	= {300, 300};
    ei_widget_t* frame = ei_widget_create("frame",ei_app_root_widget());
    char* text="Début";
    ei_anchor_t anc=ei_anc_center;
    ei_frame_configure(frame,&size,NULL,NULL,NULL,&text,NULL,NULL,NULL,NULL,NULL,NULL);

    ei_place(frame, &anc, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);

    ei_size_t	radio_size	= {150, 30};
    ei_color_t      color      = {0x00, 0x54, 0xa4, 0xff};

    ei_widget_t* radio=ei_widget_create("radiobutton",ei_app_root_widget());

    ei_radiobutton_configure(radio,&radio_size,&color,NULL,NULL);

    anc=ei_anc_northwest;
    ei_place(radio, &anc, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
    ei_add_children_radiobutton("1", (ei_radiobutton_t*) radio);
    ei_bind(ei_ev_keydown, 		NULL, "all", process_key, NULL);

    ei_bind(ei_ev_mouse_buttondown,	radio, NULL ,field, NULL);
    ei_app_run();

    ei_unbind(ei_ev_keydown,	NULL, "all", process_key, NULL);

    ei_app_free();

    return (EXIT_SUCCESS);
}
