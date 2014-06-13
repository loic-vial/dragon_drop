#include <stdio.h>
#include <stdlib.h>

#include "ei_application.h"
#include "ei_event.h"
#include "hw_interface.h"
#include "ei_widget.h"
#include "ei_geometrymanager.h"
#include "../src/ei_frame.h"
#include "../src/ei_tag.h"


ei_bool_t process_key(ei_widget_t* widget, ei_event_t* event, void* user_param)
{
    if (event->param.key.key_sym == SDLK_ESCAPE) {
        ei_app_quit_request();
        return EI_TRUE;
    }

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

    ei_widget_t*	frame;
    ei_size_t	frame_size		= {300,200};
    int		frame_x			= 150;
    int		frame_y			= 200;
    ei_color_t	frame_color		= {0x40, 0xA4, 0x97, 0xff};
    ei_relief_t	frame_relief		= ei_relief_raised;
    int		frame_border_width	= 8;

    /* Create the application and change the color of the background. */
    ei_app_create(&screen_size, EI_FALSE);
    ei_frame_configure(ei_app_root_widget(), NULL, &root_bgcol, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);

    /* Create, configure and place the frame on screen. */
    frame = ei_widget_create("frame", ei_app_root_widget());


    ei_frame_t* fframe = (ei_frame_t*) frame;

    fframe->rounded_up = EI_TRUE;
    fframe->rounded_down = EI_TRUE;
    fframe->corner_radius = 15;

    ei_frame_configure(frame, &frame_size, &frame_color,
                       &frame_border_width, &frame_relief, NULL, NULL, NULL, NULL,
                       NULL, NULL, NULL);
    ei_place(frame, NULL, &frame_x, &frame_y, NULL, NULL, NULL, NULL, NULL, NULL );

    printf("On affiche la liste initiale de tag \n");
    display_list_tag();
    printf("on ajoute le tag bullet au widget fframe \n");
    ei_tag_t tag = (ei_tag_t)"bullet";
    ei_add_tag_widget(frame,tag);
    display_list_tag();
    printf("On affiche les tag de frame \n");
    display_tag(frame);
    printf("On va detruire all dans frame \n");
    tag=(ei_tag_t)"all";

    ei_destroy_tag_widget(frame,tag);
    display_tag(frame);
    printf("on va detruire le tag frame dans tout les widget \n");
    tag=(ei_tag_t)"coucou";

ei_destroy_tag(tag);
display_list_tag();

    ei_bind(ei_ev_keydown, 		NULL, "all", process_key, NULL);

    ei_app_run();

    ei_unbind(ei_ev_keydown,	NULL, "all", process_key, NULL);

    ei_app_free();
    return (EXIT_SUCCESS);

}
