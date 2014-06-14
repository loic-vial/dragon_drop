#include "ei_toplevel_banner.h"
#include "ei_utils.h"
#include "ei_utils_2.h"
#include "ei_placer.h"
#include "ei_frame.h"
#include "ei_tag.h"
#include "ei_toplevel.h"
#include <stdlib.h>
#include <string.h>

static ei_point_t drag_mouse_position;

void ei_banner_setdefaultsfunc(ei_widget_t * widget)
{
	ei_frame_setdefaultsfunc(widget);
	ei_set_initial_tags(widget);
}

void ei_banner_configure(ei_widget_t * widget, ei_color_t * color_banner,
			 ei_color_t * color_text,
			 ei_color_t * color_button,
			 ei_color_t * color_button_text)
{
	if (strcmp(widget->wclass->name, "toplevel") == 0) {
		ei_toplevel_t *toplevel = (ei_toplevel_t *) widget;
		if (color_banner != NULL) {
			toplevel->banner->color = *color_banner;
		}
		if (color_text != NULL) {
			toplevel->banner->text_color = *color_text;
		}
		if (color_button != NULL) {
			toplevel->close_button->frame.color =
			    *color_button;
		}
		if (color_button_text != NULL) {
			toplevel->close_button->frame.text_color =
			    *color_button_text;
		}
	}
}

void ei_banner_register_class()
{
	ei_widgetclass_t *bannerclass =
	    (ei_widgetclass_t *) malloc(sizeof(ei_widgetclass_t));
	strcpy(bannerclass->name, "banner");
	bannerclass->allocfunc = &ei_frame_allocfunc;
	bannerclass->releasefunc = &ei_frame_releasefunc;
	bannerclass->drawfunc = &ei_frame_drawfunc;
	bannerclass->setdefaultsfunc = &ei_banner_setdefaultsfunc;
	bannerclass->geomnotifyfunc = NULL;
	bannerclass->next = NULL;
	ei_widgetclass_register(bannerclass);

	ei_bind(ei_ev_mouse_buttondown, NULL, "banner",
		ei_toplevel_drag_start_callback, NULL);
}

ei_bool_t ei_toplevel_drag_start_callback(ei_widget_t * widget,
					  ei_event_t * event,
					  void *user_param)
{
	ei_tail(widget->parent);
	drag_mouse_position.x = event->param.mouse.where.x;
	drag_mouse_position.y = event->param.mouse.where.y;
	ei_bind(ei_ev_mouse_move, NULL, "all", ei_toplevel_drag_callback,
		widget->parent);
	ei_bind(ei_ev_mouse_buttonup, NULL, "all",
		ei_toplevel_drag_stop_callback, widget->parent);
    return EI_FALSE;
}

ei_bool_t ei_toplevel_drag_callback(ei_widget_t * widget,
				    ei_event_t * event, void *user_param)
{
	ei_widget_t *toplevel = (ei_widget_t *) user_param;
	if (strcmp(toplevel->geom_params->manager->name, "placer") == 0) {
		ei_placer_geometry_param_t *placer =
		    (ei_placer_geometry_param_t *) toplevel->geom_params;
		ei_point_t diff_position =
		    ei_point_sub(event->param.mouse.where,
				 drag_mouse_position);
		placer->x += diff_position.x;
		placer->y += diff_position.y;
		drag_mouse_position = event->param.mouse.where;
	}
    return EI_FALSE;
}

ei_bool_t ei_toplevel_drag_stop_callback(ei_widget_t * widget,
					 ei_event_t * event,
					 void *user_param)
{
	ei_unbind(ei_ev_mouse_move, NULL, "all", ei_toplevel_drag_callback,
		  user_param);
	ei_unbind(ei_ev_mouse_buttonup, NULL, "all",
		  ei_toplevel_drag_stop_callback, user_param);
    return EI_FALSE;
}
