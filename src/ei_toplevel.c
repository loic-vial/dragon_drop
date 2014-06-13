#include "ei_toplevel.h"
#include "ei_utils.h"
#include "ei_utils_2.h"
#include "ei_placer.h"
#include <stdlib.h>

void* ei_toplevel_allocfunc()
{
    return calloc(1, sizeof(ei_toplevel_t));
}

void ei_toplevel_releasefunc(ei_widget_t* widget)
{
    ei_toplevel_t* toplevel = (ei_toplevel_t*) widget;
    if (toplevel->min_size != NULL)
    {
        free(toplevel->min_size);
        toplevel->min_size = NULL;
    }
    hw_text_font_free(toplevel->close_button_font);
    hw_text_font_free(toplevel->border_font);
}

ei_bool_t close_button_click(ei_widget_t* widget, ei_event_t* event, void* user_param)
{
    ei_widget_destroy(widget->parent->parent);
    return EI_FALSE;
}

void toplevel_frame_init(ei_toplevel_t* toplevel)
{
    toplevel->frame.widget.requested_size = ei_size(320, 240);
    toplevel->frame.border_width = 4;
    toplevel->title = "Toplevel";
    toplevel->closable = EI_TRUE;
    toplevel->resizable = ei_axis_both;
    toplevel->min_size = (ei_size_t*) malloc(sizeof(ei_size_t));
    *toplevel->min_size = ei_size(160, 120);
    toplevel->frame.rounded_up = EI_FALSE;
    toplevel->frame.rounded_down = EI_TRUE;
    toplevel->frame.corner_radius = 5;
}

void toplevel_banner_init(ei_toplevel_t* toplevel)
{
    toplevel->border = (ei_frame_t*) ei_widget_create("banner", &toplevel->frame.widget);
    toplevel->border->text = "Toplevel";
    toplevel->border->border_width = 0;
    toplevel->border->widget.requested_size.height = 20;
    toplevel->border->rounded_up = EI_TRUE;
    toplevel->border->rounded_down = EI_FALSE;
    toplevel->border->corner_radius = 5;
    toplevel->border->text_font = hw_text_font_create("misc/font.ttf", ei_style_normal, 16);
    toplevel->border_font = toplevel->border->text_font;
    toplevel->border->color = ei_color(0, 0, 0, 255);
    toplevel->border->text_color = ei_color(255, 255, 255, 255);
    toplevel->border->border_width = 0;
    ei_anchor_t anchor = ei_anc_north;
    int position_y = -toplevel->border->widget.requested_size.height;
    float rel_width = 1;
    ei_place(&toplevel->border->widget, &anchor, NULL, &position_y, NULL,
             NULL, NULL, NULL, &rel_width, NULL);
}

void toplevel_close_button_init(ei_toplevel_t* toplevel)
{
    toplevel->close_button = (ei_button_t*) ei_widget_create("button", &toplevel->border->widget);

    toplevel->close_button->frame.border_width = 0;
    toplevel->close_button->frame.color = ei_color(255, 0, 0, 255);

    toplevel->close_button->frame.text = "x";
    toplevel->close_button->frame.text_font = hw_text_font_create("misc/font.ttf", ei_style_bold, 12);
    int height,width;
    hw_text_compute_size((toplevel->close_button->frame.text),toplevel->close_button->frame.text_font,&width,&height);
    int taille=max(height,width);
    toplevel->close_button->frame.widget.requested_size = ei_size(taille,taille);
     toplevel->close_button->frame.corner_radius = taille/2;
    toplevel->close_button_font = toplevel->close_button->frame.text_font;
    toplevel->close_button->frame.text_anchor = ei_anc_center;
    toplevel->close_button->frame.rounded_down=EI_TRUE;
    toplevel->close_button->frame.rounded_up=EI_TRUE;
    toplevel->close_button->callback = close_button_click;
    ei_bind(ei_ev_mouse_buttonup, &toplevel->close_button->frame.widget, NULL, close_button_click, NULL);
    ei_anchor_t anchor = ei_anc_west;
    int position_x = 4;
    ei_place(&toplevel->close_button->frame.widget, &anchor, &position_x, NULL, NULL,
             NULL, NULL, NULL, NULL, NULL);
}

void toplevel_resize_button_init(ei_toplevel_t* toplevel)
{
    toplevel->resize_button = (ei_button_t*) ei_widget_create("resize", &toplevel->frame.widget);
    toplevel->resize_button->frame.widget.requested_size = ei_size(20, 20);
    toplevel->resize_button->frame.color = ei_color(0, 0, 0, 255);
    ei_anchor_t anchor = ei_anc_southeast;
    ei_place(&toplevel->resize_button->frame.widget, &anchor, NULL, NULL, NULL,
             NULL, NULL, NULL, NULL, NULL);
}

void ei_toplevel_setdefaultsfunc(ei_widget_t* widget)
{
    ei_frame_setdefaultsfunc(widget);
    ei_toplevel_t* toplevel = (ei_toplevel_t*) widget;
    toplevel_frame_init(toplevel);
    toplevel_banner_init(toplevel);
    toplevel_close_button_init(toplevel);
    toplevel_resize_button_init(toplevel);
    ei_initial_tag_t( widget);
}
