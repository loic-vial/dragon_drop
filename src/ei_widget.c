#include <stdio.h>
#include <stdlib.h>
#include "ei_widget.h"

ei_widget_t*		ei_widget_create		(ei_widgetclass_name_t	class_name,
                             ei_widget_t*		parent)
{

    NULL;
}

void			ei_widget_destroy		(ei_widget_t*		widget)
{
    NULL;
}
ei_widget_t*		ei_widget_pick			(ei_point_t*		where)
{
    NULL;
}




void			ei_frame_configure		(ei_widget_t*		widget,
                             ei_size_t*		requested_size,
                             const ei_color_t*	color,
                             int*			border_width,
                             ei_relief_t*		relief,
                             char**			text,
                             ei_font_t*		text_font,
                             ei_color_t*		text_color,
                             ei_anchor_t*		text_anchor,
                             ei_surface_t*		img,
                             ei_rect_t**		img_rect,
                             ei_anchor_t*		img_anchor)
{
    NULL;

}

void ei_button_configure (ei_widget_t*		widget,ei_size_t* requested_size,const ei_color_t* color,int* border_width,
                             int* corner_radius,ei_relief_t* relief,char** text,ei_font_t* text_font, ei_color_t* text_color,
                             ei_anchor_t* text_anchor,ei_surface_t* img, ei_rect_t** img_rect, ei_anchor_t*	img_anchor,
                             ei_callback_t*		callback,void**			user_param)
{
    NULL;
}


void ei_toplevel_configure (ei_widget_t* widget,ei_size_t* requested_size,ei_color_t* color,int* border_width,
                             char**	title,ei_bool_t* closable,ei_axis_set_t* resizable, ei_size_t** min_size)
{
    NULL;
}
