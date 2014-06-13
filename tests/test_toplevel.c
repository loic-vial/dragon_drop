#include "ei_application.h"
#include "ei_utils.h"
#include "ei_utils_2.h"
#include "ei_geometrymanager.h"
#include"ei_toplevel_banner.h"
#include <stdio.h>
#include <stdlib.h>

ei_bool_t ei_quit(ei_widget_t* widget, ei_event_t* event, void* user_param)
{
    if (event->param.key.key_sym == SDLK_ESCAPE) {
        ei_app_quit_request();
        return EI_TRUE;
    }

    return EI_FALSE;
}

void create_toplevel_1_frame(ei_widget_t* toplevel)
{
    ei_widget_t* frame = ei_widget_create("frame", toplevel);
    ei_size_t frame_size = ei_size(50, 30);
    ei_color_t frame_color = ei_color(210, 123, 200, 210);
    ei_anchor_t frame_anchor = ei_anc_center;
    char* frame_text = "Salut ! Hej ! Hola !";
    ei_frame_configure(frame, &frame_size, &frame_color, NULL, NULL, &frame_text,
                       NULL, NULL, NULL, NULL, NULL, NULL);
    ei_place(frame, &frame_anchor, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
}

ei_widget_t* create_toplevel_1()
{
    ei_widget_t* toplevel = ei_widget_create("toplevel", ei_app_root_widget());
    ei_size_t toplevel_size = ei_size(200, 230);
    ei_color_t toplevel_color = ei_color(23, 187, 200, 210);
    int toplevel_border = 3;
    int toplevel_x = 40;
    int toplevel_y = 20;
    ei_bool_t toplevel_closable = EI_TRUE;
    ei_axis_set_t toplevel_resizable = ei_axis_both;
    ei_toplevel_configure(toplevel, &toplevel_size, &toplevel_color, &toplevel_border, NULL, &toplevel_closable,
                          &toplevel_resizable, NULL);
    ei_place(toplevel, NULL, &toplevel_x, &toplevel_y, NULL, NULL, NULL, NULL, NULL, NULL);

    create_toplevel_1_frame(toplevel);
    return toplevel;

}

void create_root()
{
    ei_size_t root_size = ei_size(800, 600);
    ei_color_t root_color = ei_color(60, 10, 80, 255);
    ei_app_create(&root_size, EI_FALSE);
    ei_frame_configure(ei_app_root_widget(), NULL, &root_color, NULL, NULL, NULL,
                       NULL, NULL, NULL, NULL, NULL, NULL);
}

int mlkmlei_main(int argc, char* argv[])
{
    create_root();

    ei_widget_t* toplevel =create_toplevel_1();

    ei_color_t color_banner={0xcd,0x00,0x74,0xff};
    ei_color_t color_button={0xc7,0x99,0x74,0xff};
        ei_color_t color_button_text={0x00,0x00,0xff,0xff};
    ei_color_t color_text = {0,0,0,255};
    ei_configure_banner (toplevel, &color_banner, &color_text,NULL,&color_button_text);

    ei_bind(ei_ev_keydown, NULL, "all", ei_quit, NULL);

    ei_app_run();

    ei_app_free();

    return (EXIT_SUCCESS);
}
