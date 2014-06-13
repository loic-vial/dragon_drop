#include <stdio.h>
#include <stdlib.h>

#include "ei_application.h"
#include "ei_geometrymanager.h"
#include "ei_frame.h"
#include "ei_utils_2.h"

ei_widget_t* frame_tooltip;
ei_widget_t* frame;
ei_bool_t quit(ei_widget_t* widget, ei_event_t* event, void* user_param)
{
    if (event->param.key.key_sym == SDLK_ESCAPE) {
        ei_app_quit_request();
        return EI_TRUE;
    }

    return EI_FALSE;
}


ei_bool_t display(ei_widget_t* widget, ei_event_t* event, void* user_param)
{
    ei_widget_t* widget_tooltip=(ei_widget_t*)frame_tooltip;
    if(widget_has_this_tag(widget,"tooltip"))
    {
        if(widget_has_this_tag(widget,"tooltip_positif"))
        {
            ei_frame_t* frame=(ei_frame_t*)frame_tooltip;
            frame->text="=)";
        }
        ei_tail(widget_tooltip);
        ei_point_t location = widget->screen_location.top_left;
        location.y+=200;
        ei_place(frame_tooltip, NULL ,&location.x, &location.y, NULL, NULL, NULL, NULL, NULL, NULL );
    }
    else
    {
        ei_geometrymanager_unmap(widget_tooltip);
    }
    return EI_FALSE;
}


ei_bool_t activation(ei_widget_t* widget, ei_event_t* event, void* user_param)
{
     ei_add_tag_widget(frame,"tooltip");
     return EI_FALSE;
}

ei_bool_t positif(ei_widget_t* widget, ei_event_t* event, void* user_param)
{
    ei_destroy_tag_widget(frame,"tooltip_negatif");
     ei_add_tag_widget(frame,"tooltip_positif");
     return EI_FALSE;
}


ei_bool_t desactivation(ei_widget_t* widget, ei_event_t* event, void* user_param)
{
     ei_destroy_tag_widget(frame,"tooltip");
     return EI_FALSE;
}

void display_list_tag()
{
    ei_linked_tag_t* last_tag = first_tag;
    while(last_tag !=NULL)
    {
        printf("%s \n", (char*)last_tag->tag);
        last_tag=last_tag->next;
    }
}

void display_tag(ei_widget_t* widget)
{
    ei_frame_t* frame=(ei_frame_t*)widget;
    ei_linked_tag_t* last_tag = frame->tag;
    while(last_tag !=NULL)
    {
        printf("%s \n", (char*)last_tag->tag);
        last_tag=last_tag->next;
    }
}

int ei_main(int argc, char** argv)
{
    ei_size_t	screen_size		= {600, 600};
    ei_color_t	root_bgcol		= {0x52, 0x7f, 0xb4, 0xff};


    ei_size_t	frame_size		= {200,200};

    ei_color_t	frame_color		= {0x40, 0xA4, 0x97, 0xff};
    ei_relief_t	frame_relief		= ei_relief_none;
    int		frame_border_width	= 1;

    /* Create the application and change the color of the background. */
    ei_app_create(&screen_size, EI_FALSE);
    ei_frame_configure(ei_app_root_widget(), NULL, &root_bgcol, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);

    /* Create, configure and place the frame on screen. */
    frame = ei_widget_create("frame", ei_app_root_widget());
    char* text = "Une tooltip existe ici";
    ei_frame_configure(frame, &frame_size, &frame_color,
                       &frame_border_width, &frame_relief, &text, NULL, NULL, NULL,
                       NULL, NULL, NULL);
    ei_anchor_t anc=ei_anc_center;
    ei_place(frame,  &anc,NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL );
    ei_tag_t tag = (ei_tag_t)"tooltip";
    ei_add_tag_widget(frame,tag);

    /*Create a button*/
    ei_widget_t* button1 = ei_widget_create("button", ei_app_root_widget());
    text="Ce bouton désactive la tooltip";
    ei_font_t font = hw_text_font_create("misc/font.ttf", ei_style_normal, 13);
    ei_size_t	button_size		= {10,60};
    ei_color_t	button_color		= {0x40, 0xA4, 0x97, 0xff};
    ei_relief_t	button_relief		= ei_relief_raised;
    int		button_border_width	= 4;
    ei_callback_t desactivation_callback = desactivation;
    ei_button_configure(button1, &button_size, &button_color,
                        &button_border_width, NULL,&button_relief, &text,&font, NULL, NULL,
                        NULL, NULL, NULL,&desactivation_callback,NULL); //il faut mettre la callback
    anc=ei_anc_northwest;
    int x=10;
    int y=50;
    ei_place(button1,&anc,&x, &y, NULL, NULL,NULL,NULL, NULL, NULL );


    /*Create a button*/
    ei_widget_t* button2 = ei_widget_create("button", ei_app_root_widget());
    text="Ce bouton active la tooltip";

    ei_callback_t activation_callback = activation;

    ei_button_configure(button2, &button_size, &button_color,
                        &button_border_width, NULL,&button_relief, &text,&font, NULL, NULL,
                        NULL, NULL, NULL,&activation_callback,NULL); //il faut mettre la callback
    anc=ei_anc_southwest;
    int x2=10;
    int y2=-50;
    ei_place(button2,&anc,&x2, &y2, NULL, NULL,NULL,NULL, NULL, NULL );


    /*Create a button*/
    ei_widget_t* button3 = ei_widget_create("button", ei_app_root_widget());
    text="Ce bouton affiche un message positif";

    ei_callback_t positif_callback = positif;

    ei_button_configure(button3, &button_size, &button_color,
                        &button_border_width, NULL,&button_relief, &text,&font, NULL, NULL,
                        NULL, NULL, NULL,&positif_callback,NULL); //il faut mettre la callback
    anc=ei_anc_northeast;
    int x3=-10;
    int y3=50;
    ei_place(button3,&anc,&x3, &y3, NULL, NULL,NULL,NULL, NULL, NULL );
    /*Create a third frame*/
    /*ei_widget_t* frame3 = ei_widget_create("frame", ei_app_root_widget());
    text="Il en existe une ici";
    ei_frame_configure(frame3, &frame_size, &frame_color,
                       &frame_border_width, &frame_relief, &text, NULL, NULL, NULL,
                       NULL, NULL, NULL);
    anc=ei_anc_east;
 //   ei_place(frame3,  &anc,NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL );
    ei_add_tag_widget(frame3,tag);

*/
    /*Create a frame for display*/
    frame_tooltip = ei_widget_create("frame", ei_app_root_widget());
    text="Je suis une tooltip";
    ei_size_t	frame_tooltip_size		= {100,50};
    ei_color_t color ={0xff,0xff,0xff,50};
    ei_frame_configure(frame_tooltip, &frame_tooltip_size, &color,
                       &frame_border_width, &frame_relief, &text, NULL, NULL, NULL,
                       NULL, NULL, NULL);

    /*test d'ajout et de suppression*/
    printf("On affiche la liste initiale de tag \n");
    display_list_tag();
    printf("on ajoute le tag bullet au widget fframe \n");

    tag = (ei_tag_t)"bullet";
    ei_add_tag_widget(frame,tag);
    display_list_tag();
    printf("On affiche les tag de frame \n");
    display_tag(frame);
    printf("On va detruire frame dans frame \n");
    tag=(ei_tag_t)"frame";

    ei_destroy_tag_widget(frame,tag);
    display_tag(frame);
    printf("on va detruire le tag frame dans tout les widget \n");
    tag=(ei_tag_t)"frame";
    ei_destroy_tag(tag);
    display_list_tag();


    ei_bind(ei_ev_keydown, 		NULL, "all", quit, NULL);

    ei_bind(ei_ev_mouse_move,NULL, "all", display, NULL);

    ei_app_run();

    ei_unbind(ei_ev_keydown,	NULL, "all", quit, NULL);

    ei_app_free();
    return (EXIT_SUCCESS);

}
