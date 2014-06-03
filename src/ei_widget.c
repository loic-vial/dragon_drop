#include <stdio.h>
#include <stdlib.h>
#include "ei_widget.h"
#include "ei_frame.h"
#include "ei_types.h"
#include "hw_interface.h"
#include "ei_utils.h"

ei_widget_t* ei_widget_create(ei_widgetclass_name_t	class_name, ei_widget_t* parent)
{
    ei_widgetclass_t* widgetclass = ei_widgetclass_from_name(class_name);
    ei_widget_t* widget = (ei_widget_t*) widgetclass->allocfunc();
    widget->wclass = widgetclass;
    widget->pick_id = 0;
    widget->pick_color = NULL;
    widget->parent = parent;
    widget->children_head = NULL;
    widget->children_tail = NULL;
    widget->next_sibling = NULL;
    if (parent->children_tail == NULL)
    {
        parent->children_head = widget;
        parent->children_tail = widget;
    }
    else
    {
        parent->children_tail->next_sibling = widget;
        parent->children_tail = widget;
    }
    widget->geom_params = NULL;
    widget->requested_size = ei_size_zero();
    widget->screen_location = ei_rect_zero();
    widget->content_rect = &widget->screen_location;
    widgetclass->setdefaultsfunc(widget);
    return widget;
}

void ei_widget_destroy(ei_widget_t*	widget)
{
    NULL;
}

ei_widget_t* ei_widget_pick(ei_point_t* where)
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
    ei_frame_t* frame = (ei_frame_t*)widget;
    /*initialisation de requested_size*/
    if (requested_size != NULL)
    {
        widget->requested_size = *requested_size;
        widget->screen_location.size = *requested_size;
    }

    /*initialisation de color*/
    if (color != NULL) {
        frame->color = *color ;
    }

    /*initialisation de border_width */
    if (border_width != NULL )
    {
        frame->border_width = border_width ;
    }

    /*initialisation de relief */
    if (relief !=NULL )
    {
        frame->relief = *relief ;
    }


    /*initialisation du text*/
    if (text !=NULL)
    {
        frame->text= text ;
    }


    /*initialisation du text_font*/
    if (text_font !=NULL )
    {
        frame->text_font = text_font;
    }

    /*initialisation du text_color*/
    if (text_color !=NULL )
    {
        frame->text_color = *text_color;
    }

    /*initialisation du text_anchor*/
    if (text_anchor !=NULL )
    {
        frame->text_anchor = *text_anchor;
    }

    /*initialisation du img */
    if (img !=NULL)
    {
        frame->img = img;
    }

    /*initialisation du img_rect*/
    if (img_rect !=NULL)
    {
        frame->img_rect = img_rect;
    }

    /*initialisation du img_anchor*/
    if (img_anchor !=NULL )
    {
        frame->img_anchor = *img_anchor;
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
