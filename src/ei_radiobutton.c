#include "ei_radiobutton.h"
#include <stdlib.h>
#include <string.h>
#include "ei_placer.h"
#include "ei_types.h"
#include "ei_utils.h"
#include "ei_utils_2.h"
#include "ei_event.h"

ei_bool_t ei_click_button(ei_widget_t * widget, ei_event_t * event,
		       void *user_param)
{
	ei_button_t *field_button = (ei_button_t *) widget;
	ei_frame_t *field =
	    (ei_frame_t *) widget->parent->parent->children_head;

	while (field != NULL) {
		ei_button_t *button_tmp =
		    (ei_button_t *) field->widget.children_tail;
		button_tmp->frame.color = ei_color(255, 255, 255, 150);
		field = (ei_frame_t *) field->widget.next_sibling;
	}
	ei_color_t color = ei_color(0, 0, 0, 255);
	field_button->frame.color = color;
	return EI_FALSE;

}



void ei_add_children_radiobutton(char *text, ei_radiobutton_t * radio)
{

	ei_widget_t *widget = (ei_widget_t *) radio;
	ei_frame_t *field =
	    (ei_frame_t *) ei_widget_create("frame", widget);
	ei_frame_t *frame = (ei_frame_t *) ei_widget_create("frame",
							    (ei_widget_t *)
							    field);
	ei_anchor_t anc = ei_anc_west;
	ei_font_t font =
	    hw_text_font_create("misc/font.ttf", ei_style_normal, 15);
	ei_frame_configure(&frame->widget, NULL, &radio->frame.color, NULL,
			   NULL, &text, &font, NULL, &anc, NULL, NULL,
			   NULL);
	ei_frame_configure(&field->widget, NULL, &radio->frame.color, NULL,
			   NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
	float rel_width = 1;
	int height;
	if (radio->number == 0) {
		height = 20;
	} else {
		height = widget->requested_size.height / (radio->number);
	}
	ei_point_t point;
	if ((ei_widget_t *) field == widget->children_head) {
		point.x = 0;
		point.y = 0;
		field->widget.screen_location.top_left.x = 0;
		field->widget.screen_location.top_left.y = 0;

	} else {
		point.x = 0;
		point.y = height * radio->number;
		field->widget.screen_location.top_left.x = 0;
		field->widget.screen_location.top_left.y = point.y;
	}

	ei_place(&field->widget, NULL, &point.x, &point.y, NULL, &height,
		 NULL, NULL, &rel_width, NULL);
	int x_frame = 20;
	ei_place(&frame->widget, NULL, &x_frame, NULL, NULL, &height, NULL,
		 NULL, &rel_width, NULL);
	ei_button_t *select_button =
	    (ei_button_t *) ei_widget_create("button", &field->widget);
	select_button->frame.widget.requested_size = ei_size(12, 12);
	select_button->frame.border_width = 0;
	select_button->frame.color = ei_color(255, 255, 255, 150);
	select_button->frame.corner_radius = 6;
	select_button->frame.text_anchor = ei_anc_center;
	select_button->frame.rounded_down = EI_TRUE;
	select_button->frame.rounded_up = EI_TRUE;
    select_button->callback = ei_click_button;

	ei_anchor_t anchor = ei_anc_west;
	int position_x = 4;
	ei_place(&select_button->frame.widget, &anchor, &position_x, NULL,
		 NULL, NULL, NULL, NULL, NULL, NULL);
	ei_add_tag_widget((ei_widget_t *) select_button, "select_button");
	ei_add_tag_widget((ei_widget_t *) field, "field");
	radio->number++;
	widget->requested_size.height = radio->number * height;
	if (widget->geom_params != NULL) {

		ei_placer_geometry_param_t *placer =
		    (ei_placer_geometry_param_t *) widget->geom_params;
		ei_place(widget, &placer->anchor, &placer->x, &placer->y,
			 NULL, NULL, &placer->rel_x, &placer->rel_y, NULL,
			 NULL);
	} else
		ei_place(widget, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
			 NULL, NULL);
}

void ei_radiobutton_setdefaultsfunc(ei_widget_t * widget)
{
	ei_frame_setdefaultsfunc(widget);
	ei_radiobutton_t *radio = (ei_radiobutton_t *) widget;
	radio->number = 0;
	widget->requested_size.width = 150;
	widget->requested_size.height = 20;
	ei_add_children_radiobutton("First field", radio);
	ei_set_initial_tags(widget);
}

void ei_radiobutton_configure(ei_widget_t * widget,
			      ei_size_t * requested_size,
			      const ei_color_t * color, int *border_width,
			      ei_relief_t * relief)
{
	ei_widget_t *tpr = widget->children_head;

	if (requested_size != NULL) {
		int width, height;
		ei_size_t size;
		size = ei_size_zero();
		ei_radiobutton_t *radio = (ei_radiobutton_t *) widget;
		int height_frame = requested_size->height / radio->number;
        if (height_frame < 20)
		{
			height_frame = 20;
		}
		while (tpr != NULL) {
			ei_frame_t *tmp = (ei_frame_t *) tpr;
			ei_frame_t *frame =
			    (ei_frame_t *) tmp->widget.children_head;
			hw_text_compute_size(frame->text, tmp->text_font,
					     &width, &height);
            if (width > size.width)
			{
				size.width = width;
			}
			if (color != NULL) {
				tmp->color = *color;
				frame->color = *color;
			}
			tpr->requested_size.height = height_frame;
			tpr = tpr->next_sibling;

		}
		tpr = widget->children_head;
		width += 20;
		while (tpr != NULL) {
			ei_frame_t *tmp = (ei_frame_t *) tpr;
			if (size.width >= requested_size->width) {
				tmp->widget.requested_size.width =
				    size.width;
				requested_size->width = size.width;
			} else {
				tmp->widget.requested_size.width =
				    requested_size->width;
			}
			tmp->widget.requested_size.height =
			    height_frame * radio->number;
			ei_place(tpr, NULL, NULL, NULL, NULL, NULL, NULL,
				 NULL, NULL, NULL);
			tpr = tpr->next_sibling;
		}
	}
	ei_frame_configure(widget, requested_size, color, border_width,
			   relief, NULL, NULL, NULL, NULL, NULL, NULL,
			   NULL);
	ei_place(widget, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
		 NULL);
}

void ei_radiobutton_register_class()
{
	ei_widgetclass_t *radiobuttonclass =
	    (ei_widgetclass_t *) malloc(sizeof(ei_widgetclass_t));
	strcpy(radiobuttonclass->name, "radiobutton");
	radiobuttonclass->allocfunc = &ei_frame_allocfunc;
	radiobuttonclass->releasefunc = &ei_frame_releasefunc;
	radiobuttonclass->drawfunc = &ei_frame_drawfunc;
	radiobuttonclass->setdefaultsfunc =
	    &ei_radiobutton_setdefaultsfunc;
	radiobuttonclass->geomnotifyfunc = NULL;
	radiobuttonclass->next = NULL;
	ei_widgetclass_register(radiobuttonclass);
    ei_bind(ei_ev_mouse_buttonup, NULL, "select_button", ei_click_button,
		NULL);
}

ei_widget_t *ei_find_widget(ei_radiobutton_t * radio, int number)
{
	if (number <= radio->number) {
		ei_widget_t *widget = radio->frame.widget.children_head;
		for (int i = 1; i < number; i++) {
			widget = widget->next_sibling;
		}
		return widget;
	}
	return NULL;
}

void ei_destroy_field(ei_radiobutton_t * radio, int number)
{
	ei_widget_t *widget;
	widget = ei_find_widget(radio, number);
	if (widget != NULL) {
		ei_widget_t *tmp = widget->next_sibling;
		ei_widget_destroy(widget);
		radio->number--;
		radio->frame.widget.requested_size.height -=
		    widget->requested_size.height / (radio->number);
		while (tmp != NULL) {
			tmp->geom_params->manager->runfunc(tmp);
			float rel_width = 1;
			int height =
			    widget->requested_size.height /
			    (radio->number);
			ei_point_t point;

			point.x = 0;
			point.y =
			    tmp->screen_location.top_left.y -
			    widget->requested_size.height /
			    (radio->number);

			ei_place(tmp, NULL, &point.x, &point.y, NULL,
				 &height, NULL, NULL, &rel_width, NULL);
			tmp = tmp->next_sibling;
		}
		ei_place(&radio->frame.widget, NULL, NULL, NULL, NULL,
			 NULL, NULL, NULL, NULL, NULL);
	}
}

void ei_edit_field(ei_radiobutton_t * radio, int number, char *text)
{
	ei_widget_t *widget;
	widget = ei_find_widget(radio, number);
	if (widget != NULL) {
		ei_frame_t *frame = (ei_frame_t *) widget->children_head;
		frame->text = text;
	}
}

char *ei_return_field(ei_radiobutton_t * radio)
{
	ei_frame_t *field =
	    (ei_frame_t *) radio->frame.widget.children_head;
	ei_color_t color = { 0x00, 0x00, 0x00, 0xff };

	while (field != NULL) {
		ei_button_t *button =
		    (ei_button_t *) field->widget.children_tail;
		ei_frame_t *frame =
		    (ei_frame_t *) field->widget.children_head;
        if (ei_is_same_color(button->frame.color, color)) {
			return frame->text;
		} else {
			field = (ei_frame_t *) field->widget.next_sibling;
		}
	}
	return NULL;
}
