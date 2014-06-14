#include "ei_application.h"
#include "ei_utils.h"
#include "ei_utils_2.h"
#include "ei_geometrymanager.h"
#include "ei_frame.h"
#include "ei_toplevel_banner.h"
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

void create_root()
{
    ei_size_t root_size = ei_size(800, 600);
    ei_color_t root_color = ei_color(60, 10, 80, 255);
    ei_app_create(&root_size, EI_FALSE);
    ei_frame_configure(ei_app_root_widget(), NULL, &root_color, NULL, NULL, NULL,
                       NULL, NULL, NULL, NULL, NULL, NULL);
}

void create_toplevel_1()
{
    ei_widget_t* toplevel = ei_widget_create("toplevel", ei_app_root_widget());
    ei_size_t toplevel_size = ei_size(200, 230);
    ei_color_t toplevel_color = ei_color(0x48, 0x6f, 0x0a, 200);
    int toplevel_border = 3;
    int toplevel_x = 300;
    int toplevel_y = 20;
    char* toplevel_text = "Toplevel 1";
    ei_bool_t toplevel_closable = EI_TRUE;
    ei_axis_set_t toplevel_resizable = ei_axis_both;
    ei_toplevel_configure(toplevel, &toplevel_size, &toplevel_color, &toplevel_border, &toplevel_text, &toplevel_closable,
                          &toplevel_resizable, NULL);
    ei_place(toplevel, NULL, &toplevel_x, &toplevel_y, NULL, NULL, NULL, NULL, NULL, NULL);

    ei_color_t color_banner = {0x78, 0x68, 0x0a, 200};
    ei_color_t color_button = {0x87, 0xb7, 0x3a, 200};
    ei_color_t color_button_text = {0x26, 0x03, 0x34, 200};
    ei_color_t color_text = {0xbc, 0xa8, 0x3b, 200};
    ei_banner_configure(toplevel, &color_banner, &color_text, &color_button, &color_button_text);

    ei_widget_t* frame = ei_widget_create("frame", toplevel);
    ei_color_t frame_color = ei_color(0x4e, 0x43, 0x03, 200);
    ei_color_t frame_text_color = ei_color(0x31, 0x15, 0x3c, 200);
    ei_anchor_t frame_anchor = ei_anc_center;
    char* frame_text = "Démo couleurs";
    ei_frame_configure(frame, NULL, &frame_color, NULL, NULL, &frame_text,
                       NULL, &frame_text_color, NULL, NULL, NULL, NULL);
    ei_place(frame, &frame_anchor, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
}

ei_widget_t* create_toplevel_2()
{
    ei_widget_t* toplevel = ei_widget_create("toplevel", ei_app_root_widget());
    ei_size_t toplevel_size = ei_size(200, 230);
    int toplevel_x = 20;
    int toplevel_y = 20;
    char* toplevel_text = "Toplevel 2";
    ei_bool_t toplevel_closable = EI_FALSE;
    ei_axis_set_t toplevel_resizable = ei_axis_none;
    ei_toplevel_configure(toplevel, &toplevel_size, NULL, NULL, &toplevel_text, &toplevel_closable,
                          &toplevel_resizable, NULL);
    ei_place(toplevel, NULL, &toplevel_x, &toplevel_y, NULL, NULL, NULL, NULL, NULL, NULL);


    ei_widget_t* frame = ei_widget_create("frame", toplevel);
    ei_anchor_t frame_anchor = ei_anc_center;
    char* frame_text = "Default";
    int y = 0;
    ei_frame_configure(frame, NULL, NULL, NULL, NULL, &frame_text,
                       NULL, NULL, NULL, NULL, NULL, NULL);
    ei_place(frame, &frame_anchor, NULL, &y, NULL, NULL, NULL, NULL, NULL, NULL);

    frame = ei_widget_create("frame", toplevel);
    frame_anchor = ei_anc_north;
    frame_text = "Not Closable";
    y = 10;
    ei_frame_configure(frame, NULL, NULL, NULL, NULL, &frame_text,
                       NULL, NULL, NULL, NULL, NULL, NULL);
    ei_place(frame, &frame_anchor, NULL, &y, NULL, NULL, NULL, NULL, NULL, NULL);

    frame = ei_widget_create("frame", toplevel);
    frame_anchor = ei_anc_south;
    frame_text = "Not Resizable";
    y = -10;
    ei_frame_configure(frame, NULL, NULL, NULL, NULL, &frame_text,
                       NULL, NULL, NULL, NULL, NULL, NULL);
    ei_place(frame, &frame_anchor, NULL, &y, NULL, NULL, NULL, NULL, NULL, NULL);


    return toplevel;
}

void create_toplevel_3()
{
    ei_widget_t* toplevel = ei_widget_create("toplevel", ei_app_root_widget());
    ei_size_t toplevel_size = ei_size(200, 230);
    ei_color_t toplevel_color = ei_color(0x60, 0x60, 0x60, 210);
    int toplevel_border = 3;
    int toplevel_x = 580;
    int toplevel_y = 20;
    char* toplevel_text = "Toplevel 3";
    ei_bool_t toplevel_closable = EI_FALSE;
    ei_axis_set_t toplevel_resizable = ei_axis_y;
    ei_toplevel_configure(toplevel, &toplevel_size, &toplevel_color, &toplevel_border, &toplevel_text, &toplevel_closable,
                          &toplevel_resizable, NULL);
    ei_place(toplevel, NULL, &toplevel_x, &toplevel_y, NULL, NULL, NULL, NULL, NULL, NULL);


    ei_widget_t* frame = ei_widget_create("frame", toplevel);
    ei_anchor_t frame_anchor = ei_anc_northeast;
    char* frame_text = "Y resize only";
    int x = -10; int y = 10;
    ei_frame_configure(frame, NULL, NULL, NULL, NULL, &frame_text,
                       NULL, NULL, NULL, NULL, NULL, NULL);
    ei_place(frame, &frame_anchor, &x, &y, NULL, NULL, NULL, NULL, NULL, NULL);

    ei_widget_t* frame2 = ei_widget_create("frame", toplevel);
    ei_anchor_t frame2_anchor = ei_anc_southwest;
    char* frame2_text = "Not closable";
    x = 10; y = -10;
    ei_frame_configure(frame2, NULL, NULL, NULL, NULL, &frame2_text,
                       NULL, NULL, NULL, NULL, NULL, NULL);
    ei_place(frame2, &frame2_anchor, &x, &y, NULL, NULL, NULL, NULL, NULL, NULL);
}

void create_toplevel_4()
{
    ei_widget_t* toplevel = ei_widget_create("toplevel", ei_app_root_widget());
    ei_size_t toplevel_size = ei_size(200, 230);
    ei_color_t toplevel_color = ei_color(0x51, 0x61, 0x31, 210);
    int toplevel_border = 3;
    int toplevel_x = 160;
    int toplevel_y = 300;
    char* toplevel_text = "Toplevel 4";
    ei_bool_t toplevel_closable = EI_TRUE;
    ei_axis_set_t toplevel_resizable = ei_axis_both;
    ei_toplevel_configure(toplevel, &toplevel_size, &toplevel_color, &toplevel_border, &toplevel_text, &toplevel_closable,
                          &toplevel_resizable, NULL);
    ei_place(toplevel, NULL, &toplevel_x, &toplevel_y, NULL, NULL, NULL, NULL, NULL, NULL);

    ei_widget_t* child_toplevel = ei_widget_create("toplevel", toplevel);
    ei_size_t ttoplevel_size = ei_size(140, 160);
    ei_size_t _ttoplevel_min_size = ei_size(80, 100);
    ei_size_t* ttoplevel_min_size = &_ttoplevel_min_size;
    ei_color_t ttoplevel_color = ei_color(0x5d, 0x31, 0x33, 200);
    int ttoplevel_x = 20;
    int ttoplevel_y = 10;
    char* ttoplevel_text = "Inner 1";
    ei_toplevel_configure(child_toplevel, &ttoplevel_size, &ttoplevel_color, NULL, &ttoplevel_text, NULL,
                          NULL, &ttoplevel_min_size);
    ei_place(child_toplevel, NULL, &ttoplevel_x, &ttoplevel_y, NULL, NULL, NULL, NULL, NULL, NULL);

    ei_widget_t* child_frame = ei_widget_create("frame", child_toplevel);
    ei_size_t child_frame_size = ei_size(42, 42);
    ei_color_t child_frame_color = ei_color(0, 0, 0, 0);
    ei_anchor_t child_frame_anchor = ei_anc_north;
    ei_surface_t child_frame_img = hw_image_load("misc/yinyang.png", ei_app_root_surface());
    ei_frame_configure(child_frame, &child_frame_size, &child_frame_color, NULL, NULL, NULL,
                       NULL, NULL, NULL, &child_frame_img, NULL, NULL);
    ei_place(child_frame, &child_frame_anchor, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);

    ei_widget_t* child_toplevel_2 = ei_widget_create("toplevel", child_toplevel);
    ei_size_t tttoplevel_size = ei_size(100, 80);
    ei_size_t _tttoplevel_min_size = ei_size(80, 60);
    ei_size_t* tttoplevel_min_size = &_tttoplevel_min_size;
    ei_color_t tttoplevel_color = ei_color(0x1d, 0x34, 0x35, 200);
    int tttoplevel_x = 10;
    int tttoplevel_y = 52;
    char* tttoplevel_text = "Inner 2";
    ei_toplevel_configure(child_toplevel_2, &tttoplevel_size, &tttoplevel_color, NULL, &tttoplevel_text, NULL,
                          NULL, &tttoplevel_min_size);
    ei_place(child_toplevel_2, NULL, &tttoplevel_x, &tttoplevel_y, NULL, NULL, NULL, NULL, NULL, NULL);

}

char buffer[20];
int current_click_nb = 0;

ei_bool_t click_callback(ei_widget_t* widget, ei_event_t* event, void* user_param)
{
    ei_widget_t* frame = (ei_widget_t*) user_param;
    sprintf(buffer, "%d", ++current_click_nb);
    char* text = buffer;
    ei_frame_configure(frame, NULL, NULL, NULL, NULL, &text, NULL, NULL, NULL, NULL, NULL, NULL);
    ei_anchor_t frame_anchor = ei_anc_north;
    int y = 10;
    ei_place(frame, &frame_anchor, NULL, &y, NULL, NULL, NULL, NULL, NULL, NULL);
    return EI_TRUE;
}

void create_toplevel_5()
{
    ei_widget_t* toplevel = ei_widget_create("toplevel", ei_app_root_widget());
    ei_size_t toplevel_size = ei_size(200, 230);
    ei_color_t toplevel_color = ei_color(0x68, 0x34, 0x34, 210);
    int toplevel_border = 0;
    int toplevel_x = 440;
    int toplevel_y = 300;
    char* toplevel_text = "Toplevel 5";
    ei_bool_t toplevel_closable = EI_TRUE;
    ei_axis_set_t toplevel_resizable = ei_axis_both;
    ei_toplevel_configure(toplevel, &toplevel_size, &toplevel_color, &toplevel_border, &toplevel_text, &toplevel_closable,
                          &toplevel_resizable, NULL);
    ei_place(toplevel, NULL, &toplevel_x, &toplevel_y, NULL, NULL, NULL, NULL, NULL, NULL);

    ei_widget_t* frame = ei_widget_create("frame", toplevel);
    ei_anchor_t frame_anchor = ei_anc_north;
    char* frame_text = "0";
    int y = 10;
    ei_frame_configure(frame, NULL, NULL, NULL, NULL, &frame_text,NULL,
                       NULL, NULL, NULL, NULL, NULL);
    ei_place(frame, &frame_anchor, NULL, &y, NULL, NULL, NULL, NULL, NULL, NULL);

    ei_widget_t* button = ei_widget_create("button", toplevel);
    ei_anchor_t button_anchor = ei_anc_center;
    char* button_text = "Click me !";
    ei_callback_t click_cb = click_callback;
    ei_button_configure(button, NULL, NULL, NULL, NULL,NULL, &button_text,
                        NULL, NULL, NULL, NULL, NULL, NULL, &click_cb, (void**)&frame);
    ei_place(button, &button_anchor, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
}

int ei_main(int argc, char* argv[])
{
    create_root();

    create_toplevel_1();
    create_toplevel_2();
    create_toplevel_3();
    create_toplevel_4();
    create_toplevel_5();

    ei_bind(ei_ev_keydown, NULL, "all", ei_quit, NULL);
    ei_app_run();
    ei_app_free();

    return (EXIT_SUCCESS);
}
