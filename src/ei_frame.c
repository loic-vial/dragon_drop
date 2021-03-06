#include "ei_frame.h"
#include "ei_utils.h"
#include "ei_utils_2.h"
#include <stdlib.h>
#include <math.h>

#define PI 3.14159265

void *ei_frame_allocfunc()
{
	return calloc(1, sizeof(ei_frame_t));
}

void ei_frame_releasefunc(ei_widget_t * widget)
{
	ei_frame_t *frame = (ei_frame_t *) widget;
	if (frame->img != NULL) {
		hw_surface_free(frame->img);
	}
	if (frame->img_rect != NULL) {
		free(frame->img_rect);
	}
	ei_clear_tag_list(&frame->tag);
}

ei_linked_point_t *ei_arc(ei_point_t centre, float radius, float angle_debut,
		       float angle_fin)
{
	ei_linked_point_t *liste_points =
	    (ei_linked_point_t *) malloc(sizeof(ei_linked_point_t));
	ei_linked_point_t *current_point = liste_points;
	ei_point_t point;

	for (float angle = angle_debut; angle < angle_fin; angle += 1) {
		point.x = centre.x + radius * cos(angle * PI / 180.0);
		point.y = centre.y - radius * sin(angle * PI / 180.0);
		current_point->point = point;
		current_point->next = malloc(sizeof(ei_linked_point_t));
		current_point = current_point->next;
	}
	point.x = centre.x + radius * cos(angle_fin * PI / 180.0);
	point.y = centre.y - radius * sin(angle_fin * PI / 180.0);
	current_point->point = point;
	current_point->next = NULL;
	return (liste_points);
}

ei_linked_point_t *ei_rounded_frame_up(ei_rect_t rectangle, float rayon)
{
	ei_point_t centre = ei_point_add(rectangle.top_left,
					 ei_point(rectangle.size.width,
						  0));
	centre = ei_point_add(centre, ei_point(-rayon, rayon));
    ei_linked_point_t *liste_points = ei_arc(centre, rayon, 0, 90);
	ei_linked_point_t *current_point;
	for (current_point = liste_points; current_point->next != NULL;
	     current_point = current_point->next);
	centre = ei_point_add(rectangle.top_left, ei_point(rayon, rayon));
    current_point->next = ei_arc(centre, rayon, 90, 180);
	return liste_points;
}

ei_linked_point_t *ei_rounded_frame_down(ei_rect_t rectangle, float rayon)
{
	ei_point_t centre = ei_point_add(rectangle.top_left,
					 ei_point(0,
						  rectangle.size.height));
	centre = ei_point_add(centre, ei_point(rayon, -rayon));
    ei_linked_point_t *liste_points = ei_arc(centre, rayon, -180, -90);
	ei_linked_point_t *current_point;
	for (current_point = liste_points; current_point->next != NULL;
	     current_point = current_point->next);
	centre =
	    ei_point_add(rectangle.top_left,
			 ei_point(rectangle.size.width,
				  rectangle.size.height));
	centre = ei_point_add(centre, ei_point(-rayon, -rayon));
    current_point->next = ei_arc(centre, rayon, -90, 0);
	return liste_points;
}

ei_linked_point_t *ei_rounded_frame(ei_rect_t rectangle, float rayon,
				 ei_bool_t top, ei_bool_t bot)
{
	ei_linked_point_t *liste_points;
	ei_linked_point_t *current_point;
	if (top) {
        liste_points = ei_rounded_frame_up(rectangle, rayon);
		for (current_point = liste_points;
		     current_point->next != NULL;
		     current_point = current_point->next);
	} else {
		liste_points = (ei_linked_point_t *)
		    malloc(sizeof(ei_linked_point_t));
		liste_points->point =
		    ei_point_add(rectangle.top_left,
				 ei_point(rectangle.size.width, 0));
		liste_points->next = (ei_linked_point_t *)
		    malloc(sizeof(ei_linked_point_t));
		liste_points->next->point = rectangle.top_left;
		liste_points->next->next = NULL;
		current_point = liste_points->next;
	}
	if (bot) {
        current_point->next = ei_rounded_frame_down(rectangle, rayon);
		for (current_point = liste_points;
		     current_point->next != NULL;
		     current_point = current_point->next);
	} else {
		current_point->next = (ei_linked_point_t *)
		    malloc(sizeof(ei_linked_point_t));
		current_point->next->point =
		    ei_point_add(rectangle.top_left,
				 ei_point(0, rectangle.size.height));
		current_point->next->next = (ei_linked_point_t *)
		    malloc(sizeof(ei_linked_point_t));
		current_point->next->next->point =
		    ei_point_add(rectangle.top_left,
				 ei_point(rectangle.size.width,
					  rectangle.size.height));
		current_point->next->next->next = NULL;
	}
	return liste_points;
}


ei_linked_point_t *ei_relief_frame(ei_rect_t rectangle, float radius,
				ei_bool_t top, ei_bool_t bot,
				ei_bool_t sup)
{
	ei_point_t vertex = rectangle.top_left;
	ei_point_t centre;
	ei_linked_point_t *point_list = NULL;
	ei_linked_point_t *current_point = NULL;
	ei_point_t point_inter;
	float h;
	if (rectangle.size.height < rectangle.size.width) {
		h = rectangle.size.height / 2;
	} else {
		h = rectangle.size.width / 2;
	}
	// partie du haut
	if (sup) {
		//haut gauche
		vertex = rectangle.top_left;
		if (top) {
			centre.x = vertex.x + radius;
			centre.y = vertex.y + radius;
            point_list = ei_arc(centre, radius, 90, 180);
			current_point = point_list;
			while (current_point->next != NULL) {
				current_point = current_point->next;
			}
		} else {
			point_list = (ei_linked_point_t *)
			    malloc(sizeof(ei_linked_point_t));
			point_list->next = NULL;;
			point_list->point = vertex;
			current_point = point_list;
		}
		//bas gauche
		vertex.y += rectangle.size.height;
		if (bot) {
			centre.x = vertex.x + radius;
			centre.y = vertex.y - radius;
			current_point->next =
                ei_arc(centre, radius, -180, -135);
			while (current_point->next != NULL) {
				current_point = current_point->next;
			}
		} else {
			current_point->next =
			    malloc(sizeof(ei_linked_point_t));
			current_point->next->point = vertex;
			current_point = current_point->next;
		}
		// premier point intermédiaire
		point_inter.x = vertex.x + h;
		point_inter.y = vertex.y - h;
		current_point->next = malloc(sizeof(ei_linked_point_t));
		current_point->next->point = point_inter;
		current_point = current_point->next;
		// deuxième point intermédiaire
		vertex.x += rectangle.size.width;
		vertex.y += -rectangle.size.height;
		point_inter.x = vertex.x - h;
		point_inter.y = vertex.y + h;
		current_point->next = malloc(sizeof(ei_linked_point_t));
		current_point->next->point = point_inter;
		current_point = current_point->next;
		// haut droite
		if (top) {
			centre.x = vertex.x - radius;
			centre.y = vertex.y + radius;
            current_point->next = ei_arc(centre, radius, 45, 90);
			while (current_point->next != NULL) {
				current_point = current_point->next;
			}
		} else {
			current_point->next =
			    malloc(sizeof(ei_linked_point_t));
			current_point->next->point = vertex;
			current_point = current_point->next;
		}
	} else {
		// bas gauche
		vertex.y += rectangle.size.height;
		if (bot) {
			centre.x = vertex.x + radius;
			centre.y = vertex.y - radius;
            point_list = ei_arc(centre, radius, -135, -90);
			current_point = point_list;
			while (current_point->next != NULL) {
				current_point = current_point->next;
			}
		} else {
			point_list = (ei_linked_point_t *)
			    malloc(sizeof(ei_linked_point_t));
			point_list->next = NULL;
			point_list->point = vertex;
			current_point = point_list;
		}
		// bas droite
		vertex.x += rectangle.size.width;
		if (bot) {
			centre.x = vertex.x - radius;
			centre.y = vertex.y - radius;
            current_point->next = ei_arc(centre, radius, -90, 0);
			while (current_point->next != NULL) {
				current_point = current_point->next;
			}
		} else {
			current_point->next =
			    malloc(sizeof(ei_linked_point_t));
			current_point->next->point = vertex;
			current_point = current_point->next;
		}
		// haut droite
		vertex.y += -rectangle.size.height;
		if (top) {
			centre.x = vertex.x - radius;
			centre.y = vertex.y + radius;
            current_point->next = ei_arc(centre, radius, 0, 45);
			while (current_point->next != NULL) {
				current_point = current_point->next;
			}
		} else {
			current_point->next =
			    malloc(sizeof(ei_linked_point_t));
			current_point->next->point = vertex;
			current_point = current_point->next;
		}
		// premier point intermédiaire
		point_inter.x = vertex.x - h;
		point_inter.y = vertex.y + h;
		current_point->next = malloc(sizeof(ei_linked_point_t));
		current_point->next->point = point_inter;
		current_point = current_point->next;
		// deuxième point intermédiaire
		vertex.x += -rectangle.size.width;
		vertex.y += +rectangle.size.height;
		point_inter.x = vertex.x + h;
		point_inter.y = vertex.y - h;
		current_point->next = malloc(sizeof(ei_linked_point_t));
		current_point->next->point = point_inter;
		current_point = current_point->next;
	}
	current_point->next = NULL;
	return (point_list);
}

ei_color_t ei_light_color(ei_color_t color)
{
	int percent = 70;
	color.red =
	    max(min(round(color.red + color.red * percent / 100), 255), 0);
	color.green =
	    max(min(round(color.green + color.green * percent / 100), 255),
		0);
	color.blue =
	    max(min(round(color.blue + color.blue * percent / 100), 255),
		0);
	return color;
}

ei_color_t ei_dark_color(ei_color_t color)
{
	int percent = 70;
	color.red = max(min(round(color.red * percent / 100), 255), 0);
	color.green = max(min(round(color.green * percent / 100), 255), 0);
	color.blue = max(min(round(color.blue * percent / 100), 255), 0);
	return color;
}

void ei_free_points(ei_linked_point_t * points)
{
	ei_linked_point_t *point = points;
	while (point != NULL) {
		ei_linked_point_t *next_point = point->next;
		free(point);
		point = next_point;
	}
}

void ei_frame_drawfunc(ei_widget_t * widget, ei_surface_t surface,
		       ei_surface_t pick_surface, ei_rect_t * clipper)
{
	ei_frame_t *frame = (ei_frame_t *) widget;
	ei_rect_t rect = widget->screen_location;
	ei_linked_point_t *points =
        ei_rounded_frame(rect, frame->corner_radius, frame->rounded_up,
			  frame->rounded_down);
	if (frame->border_width != 0) {
		ei_rect_t rect_2;
		rect_2.top_left.x = rect.top_left.x + frame->border_width;
		rect_2.top_left.y = rect.top_left.y + frame->border_width;
		rect_2.size.width =
		    rect.size.width - 2 * frame->border_width;
		rect_2.size.height =
		    rect.size.height - 2 * frame->border_width;
		int radius_2 = frame->corner_radius - frame->border_width;
		radius_2 = radius_2 < 0 ? 0 : radius_2;
		ei_linked_point_t *points_2 =
            ei_rounded_frame(rect_2, radius_2, frame->rounded_up,
				  frame->rounded_down);
        ei_color_t light = ei_light_color(frame->color);
        ei_color_t dark = ei_dark_color(frame->color);
		ei_linked_point_t *points_up =
            ei_relief_frame(rect, frame->corner_radius,
				 frame->rounded_up, frame->rounded_down,
				 EI_TRUE);
		ei_linked_point_t *points_down =
            ei_relief_frame(rect, frame->corner_radius,
				 frame->rounded_up, frame->rounded_down,
				 EI_FALSE);
		if (frame->relief == ei_relief_raised) {
			ei_draw_polygon(surface, points_up, light,
					clipper);
			ei_draw_polygon(surface, points_down, dark,
					clipper);
			ei_draw_polygon(surface, points_2, frame->color,
					clipper);
		} else if (frame->relief == ei_relief_sunken) {
			ei_draw_polygon(surface, points_up, dark, clipper);
			ei_draw_polygon(surface, points_down, light,
					clipper);
			ei_draw_polygon(surface, points_2, frame->color,
					clipper);
		} else if (frame->relief == ei_relief_none) {
			ei_draw_polygon(surface, points, dark, clipper);
			ei_draw_polygon(surface, points_2, frame->color,
					clipper);
		}

        ei_free_points(points_up);
        ei_free_points(points_down);
        ei_free_points(points_2);
	} else {
		ei_draw_polygon(surface, points, frame->color, clipper);
	}

	if (frame->text != NULL) {
		ei_size_t text_size;
		hw_text_compute_size(frame->text, frame->text_font,
				     &text_size.width, &text_size.height);
		ei_point_t top_left_corner =
		    ei_position_from_anchor(widget->
					    screen_location.top_left,
					    widget->screen_location.size,
					    text_size,
					    frame->text_anchor);

		ei_draw_text(surface, &top_left_corner, frame->text,
			     frame->text_font, &frame->text_color,
			     clipper);
	}

	if (frame->img != NULL) {
		ei_rect_t img_rect;
		if (frame->img_rect != NULL) {
			img_rect = *frame->img_rect;
		} else {
			img_rect =
			    ei_rect(ei_point_zero(),
				    hw_surface_get_size(frame->img));
		}

		ei_point_t top_left_corner =
		    ei_position_from_anchor(widget->
					    screen_location.top_left,
					    widget->screen_location.size,
					    img_rect.size,
					    frame->img_anchor);

		ei_rect_t rect = ei_rect(top_left_corner, img_rect.size);
		ei_rect_t rect_2 = img_rect;

        rect = ei_rectangle_intersection(*clipper, rect);
		rect_2.size = rect.size;

		if (top_left_corner.x < clipper->top_left.x) {
			rect_2.top_left.x +=
			    clipper->top_left.x - top_left_corner.x;
		}

		if (top_left_corner.y < clipper->top_left.y) {
			rect_2.top_left.y +=
			    clipper->top_left.y - top_left_corner.y;
		}

		hw_surface_lock(frame->img);
		ei_copy_surface(surface, &rect, frame->img, &rect_2,
				EI_TRUE);
		hw_surface_unlock(frame->img);
	}

	ei_draw_polygon(pick_surface, points, *widget->pick_color,
			clipper);

    ei_free_points(points);
}

void ei_frame_setdefaultsfunc(ei_widget_t * widget)
{
	ei_frame_t *frame = (ei_frame_t *) widget;
	frame->color = ei_default_background_color;
	frame->border_width = 0;
	frame->relief = ei_relief_none;
	frame->text = NULL;
	frame->text_font = ei_default_font;
	frame->text_color = ei_font_default_color;
	frame->text_anchor = ei_anc_center;
	frame->img = NULL;
	frame->img_rect = NULL;
	frame->img_anchor = ei_anc_center;
	frame->corner_radius = 0;
	frame->rounded_up = EI_FALSE;
	frame->rounded_down = EI_FALSE;
	frame->widget.requested_size = ei_size_zero();
	ei_set_initial_tags(widget);
}
