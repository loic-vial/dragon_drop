#include <stdio.h>
#include <stdlib.h>
#include "ei_widget.h"
#include "ei_frame.h"
#include "ei_types.h"

ei_widget_t*		ei_widget_create		(ei_widgetclass_name_t	class_name,
                             ei_widget_t*		parent)
{
ei_widget_t* widget;
   ei_widgetclass_t* name=ei_widgetclass_from_name (class_name);
   return widget;
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
   ei_frame_t* frame = widget;
   if (requested_size != NULL)
   {
       if (frame->requested_size != requested_size)
       {
           frame->requested_size = requested_size;
       }
   }
   else
   {
       if (frame->requested_size != NULL)
       {
           frame->requested_size = requested_size;
       }
       else
       {
           if (frame->text==NULL && frame->img==NULL)
           {
               frame->requested_size->width = 0;
               frame->requested_size->height = 0;
           }
       }
   }
   if (color != NULL && frame->color != color) {
       frame->color = color ;
   }
   if (border_width != NULL && frame->border_width != border_width) {
       frame->border_width = border_width ;
   }
   if (relief !=NULL && frame->relief != relief) {
       frame->relief = relief ;
   }

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
