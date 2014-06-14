#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ei_radiobutton.h"
#include "ei_geometrymanager.h"
#include "ei_application.h"


ei_widget_t* frame;
ei_bool_t button_press(ei_widget_t* widget, ei_event_t* event, void* user_param);
ei_bool_t process_key(ei_widget_t* widget, ei_event_t* event, void* user_param);


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
    char* text =ei_return_field((ei_radiobutton_t*)widget->parent->parent);
    ei_frame_t* fframe=(ei_frame_t*)frame;
    fframe->text=text;
    return EI_TRUE;

}
int ei_main(int argc, char** argv)

{
    ei_size_t	screen_size	= {600, 600};
    ei_color_t      root_bgcol      = {0x52, 0x7f, 0xb4, 0xff};

    ei_app_create(&screen_size, EI_FALSE);
    ei_frame_configure(ei_app_root_widget(), NULL, &root_bgcol, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);

    ei_size_t	size	= {250, 300};
    ei_widget_t* frame_title = ei_widget_create("frame",ei_app_root_widget());
    char* text="Quelle musique aimez vous ?";
    ei_anchor_t anc=ei_anc_west;
    ei_anchor_t anc_text=ei_anc_north;
    ei_frame_configure(frame_title,&size,NULL,NULL,NULL,&text,NULL,NULL,&anc_text,NULL,NULL,NULL);
    int x=10;
    ei_place(frame_title, &anc,&x, NULL, NULL, NULL, NULL, NULL, NULL, NULL);

    ei_size_t	radio_size	= {200  , 30};
    ei_color_t      color      = {0x00, 0x54, 0xa4, 0xff};

    ei_widget_t* radio=ei_widget_create("radiobutton",frame_title);

    ei_radiobutton_configure(radio,&radio_size,&color,NULL,NULL);

    anc=ei_anc_center;

    ei_place(radio, &anc, NULL,NULL, NULL, NULL, NULL, NULL, NULL, NULL);
    ei_edit_field((ei_radiobutton_t*) radio,1,"Trance");
    ei_add_children_radiobutton("Dubstep", (ei_radiobutton_t*) radio);
    ei_add_children_radiobutton("Industriel", (ei_radiobutton_t*) radio);
    ei_add_children_radiobutton("Drum & Bass", (ei_radiobutton_t*) radio);
    ei_add_children_radiobutton("Trip hop", (ei_radiobutton_t*) radio);
    ei_add_children_radiobutton("Progressif", (ei_radiobutton_t*) radio);
    ei_add_children_radiobutton("Electro Swing", (ei_radiobutton_t*) radio);

    ei_size_t frame_size={200,200};

    frame=ei_widget_create("frame",ei_app_root_widget());

    ei_frame_configure(frame,&frame_size,&color,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL);
    ei_anchor_t frame_anc=ei_anc_east;
    x = -10;
    ei_place(frame,&frame_anc,&x,NULL,NULL,NULL,NULL,NULL,NULL,NULL);



      char* text1= "Vous aimez la musique";
     ei_widget_t* text_debut=ei_widget_create("frame",frame);
ei_font_t font = hw_text_font_create("misc/font.ttf", ei_style_normal, 15);
      ei_frame_configure(frame,NULL,&color,NULL,NULL,&text1,&font,NULL,NULL,NULL,NULL,NULL);
      ei_anchor_t frame_anc_debut=ei_anc_south;

    int  y = -100;
      ei_place(text_debut,&frame_anc_debut,NULL,&y,NULL,NULL,NULL,NULL,NULL,NULL);



    ei_bind(ei_ev_keydown, 		NULL, "all", process_key, NULL);

    display_tag(radio);
    printf("\n");
    display_tag(radio->children_head);
    printf("\n");

    display_tag(radio->children_head->children_tail);

    ei_bind(ei_ev_mouse_buttonup,	NULL, "select_button" ,field, NULL);
    ei_app_run();

    ei_unbind(ei_ev_keydown,	NULL, "all", process_key, NULL);

    ei_app_free();

    return (EXIT_SUCCESS);
}

