#include <stdio.h>
#include <stdlib.h>

#include "ei_application.h"
#include "ei_event.h"
#include "hw_interface.h"
#include "ei_widget.h"
#include "ei_geometrymanager.h"


/*
 * button_press --
 *
 *	Callback called when a user clicks on the button.
 */
ei_bool_t button_press(ei_widget_t* widget, ei_event_t* event, void* user_param)
{
	printf("Click !\n");
	return EI_TRUE;
}

/*
 * process_key --
 *
 *	Callback called when any key is pressed by the user.
 *	Simply looks for the "Escape" key to request the application to quit.
 */
ei_bool_t process_key(ei_widget_t* widget, ei_event_t* event, void* user_param)
{
	if (event->param.key.key_sym == SDLK_ESCAPE) {
		ei_app_quit_request();
		return EI_TRUE;
	}
	
	return EI_FALSE;
}

/*
 * ei_main --
 *
 *	Main function of the application.
 */
int ei_main(int argc, char** argv)
{
	ei_size_t	screen_size		= {400, 400};
	ei_color_t	root_bgcol		= {0x52, 0x7f, 0xb4, 0xff};

	ei_widget_t*	button;
	int		button_x		= 10;
	int		button_y		= 10;	     
	int		button_width		= 100;
	int		button_height		= 40;	     
	ei_color_t	button_color		= {0x88, 0x88, 0x88, 0xff};
	char*		button_title		= "click";
	ei_color_t	button_text_color	= {0x00, 0x00, 0x00, 0xff};
	ei_relief_t	button_relief		= ei_relief_raised;
	int		button_border_width	= 2;
	ei_callback_t 	button_callback 	= button_press;
	
	ei_widget_t*	window;
	ei_size_t	window_size		= {200,200};
	char*		window_title		= "Hello World";
	ei_color_t	window_color		= {0xA0,0xA0,0xA0, 0xff};
	int		window_border_width	= 2;
	ei_bool_t	window_closable		= EI_TRUE;
	ei_axis_set_t	window_resizable 	= ei_axis_both;
	ei_point_t	window_position	 	= {30, 10};	    

	
	/* Create the application and change the color of the background. */
	ei_app_create(&screen_size, EI_FALSE); 
	ei_frame_configure(ei_app_root_widget(), NULL, &root_bgcol, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);	  

	/* Create, configure and place a toplevel window on screen. */
	window = ei_widget_create("toplevel", ei_app_root_widget());
	ei_toplevel_configure(window, &window_size, &window_color, &window_border_width,
				&window_title, &window_closable, &window_resizable, NULL);
	ei_place(window, NULL, &(window_position.x), &(window_position.y), NULL, NULL, NULL, NULL, NULL, NULL);

	/* Create, configure and place a button as a descendant of the toplevel window. */
	button = ei_widget_create("button", window);
	ei_button_configure(button, NULL, &button_color, 
			    &button_border_width, NULL, &button_relief, &button_title, NULL, &button_text_color, NULL,
			    NULL, NULL, NULL, &button_callback, NULL);
	ei_place(button, NULL, &button_x, &button_y, &button_width, &button_height, NULL, NULL, NULL, NULL );

	/* Hook the keypress callback to the event. */
	ei_bind(ei_ev_keydown,		NULL, "all", process_key, NULL);

	/* Run the application's main loop. */
	ei_app_run();

	/* We just exited from the main loop. Terminate the application (cleanup). */
	ei_unbind(ei_ev_keydown,	NULL, "all", process_key, NULL);
	ei_app_free();

	return (EXIT_SUCCESS);
}
