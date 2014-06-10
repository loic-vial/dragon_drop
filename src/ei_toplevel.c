#include "ei_toplevel.h"
#include "ei_types.h"
#include "ei_widget.h"
#include "ei_widgetclass.h"
#include "ei_geometrymanager.h"
#include "hw_interface.h"
#include "ei_event.h"
#include "ei_utils.h"
#include "ei_utils_2.h"
#include "ei_placer.h"
#include "ei_toplevel_resize.h"
#include "ei_toplevel_banner.h"
#include <stdlib.h>
#include <string.h>

void* allocfunc_toplevel()
{
    return calloc(1, sizeof(ei_toplevel_t));
}

void releasefunc_toplevel(ei_widget_t* widget)
{
    free(widget);
}

void drawfunc_toplevel(ei_widget_t* widget, ei_surface_t surface,
                       ei_surface_t pick_surface, ei_rect_t* clipper)
{
    drawfunc_frame(widget, surface, pick_surface, clipper);
}

ei_bool_t close_button_click(ei_widget_t* widget, ei_event_t* event, void* user_param)
{
    ei_widget_destroy(widget->parent->parent);
    return EI_TRUE;
}

void setdefaultsfunc_toplevel(ei_widget_t* widget)
{
    setdefaultsfunc_frame(widget);
    ei_toplevel_t* toplevel = (ei_toplevel_t*) widget;

    toplevel->frame.rounded_up = EI_FALSE;
    toplevel->frame.rounded_down = EI_TRUE;
    toplevel->frame.corner_radius = 5;
    toplevel->frame.widget.requested_size.width = 320;
    toplevel->frame.widget.requested_size.height = 240;
    toplevel->frame.color = ei_default_background_color;
    toplevel->frame.border_width = 4;
    toplevel->title = "Toplevel";
    toplevel->closable = EI_TRUE;
    toplevel->resizable = ei_axis_both;
    toplevel->min_size = malloc(sizeof(ei_size_t));
    toplevel->min_size->width = 160;
    toplevel->min_size->height = 120;

    toplevel->border=(ei_frame_t*) ei_widget_create("banner", &toplevel->frame.widget);
    toplevel->border->text = "Toplevel";
    toplevel->border->border_width =0;
    toplevel->border->widget.requested_size.height = 20;
    toplevel->border->rounded_up=EI_TRUE;
    toplevel->border->rounded_down=EI_FALSE;
    toplevel->border->corner_radius=5;
    ei_font_t border_font = hw_text_font_create("misc/font.ttf",ei_style_normal, 16);
    ei_color_t border_color = ei_color(0, 0, 0, 255);
    ei_color_t border_text_color = ei_color(255, 255, 255, 255);
    int border =0;
    ei_frame_configure(&toplevel->border->widget, NULL, &border_color,
                       &border, NULL, &toplevel->title, &border_font,
                       &border_text_color, NULL, NULL, NULL, NULL);

    ei_anchor_t border_anchor = ei_anc_north;

    int border_position_y = -toplevel->border->widget.requested_size.height;
    float un=1;
    ei_place(&toplevel->border->widget, &border_anchor, NULL, &border_position_y, NULL, NULL, NULL, NULL, &un, NULL);

    toplevel->button = (ei_button_t*)ei_widget_create("button", &toplevel->border->widget);

    ei_size_t* bord=(ei_size_t*)malloc(sizeof(ei_size_t));
    bord->height = 12;
    bord->width = 12;
    toplevel->button->frame.border_width =0;
    toplevel->button->frame.color = ei_color(255, 0, 0, 255);
    int close_button_corner_radius = 6;
    char* text="x";
    ei_font_t textfont = hw_text_font_create("misc/font.ttf", ei_style_bold, 10);
    ei_anchor_t close_button_anchor = ei_anc_west;
    int close_button_pos_x = 4;
    ei_callback_t button_callback = close_button_click;
    ei_anchor_t close_button_text_anchor = ei_anc_center;
    toplevel->button->frame.rounded_down=EI_TRUE;
    toplevel->button->frame.rounded_up=EI_TRUE;
    ei_button_configure(&toplevel->button->frame.widget, bord, NULL,&toplevel->button->frame.border_width, &close_button_corner_radius, NULL,
                        &text, &textfont, NULL, &close_button_text_anchor, NULL, NULL, NULL,
                        &button_callback, NULL);

    ei_place(&toplevel->button->frame.widget, &close_button_anchor, &close_button_pos_x, NULL, NULL,
             NULL, NULL, NULL, NULL, NULL);


    ei_size_t resize_button_size = ei_size(20, 20);
    ei_color_t resize_button_color = ei_color(0, 0, 0, 255);
    ei_anchor_t resize_button_anchor = ei_anc_southeast;
    ei_callback_t _resize_start = ei_toplevel_resize_start_callback;

    ei_button_t* resize_button = (ei_button_t*)ei_widget_create("resize", &toplevel->frame.widget);
    ei_button_configure(&resize_button->frame.widget, &resize_button_size, &resize_button_color,
                        NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);

    ei_place(&resize_button->frame.widget, &resize_button_anchor, NULL, NULL, NULL,
             NULL, NULL, NULL, NULL, NULL);

    ei_bind(ei_ev_mouse_buttondown, &resize_button->frame.widget, NULL, _resize_start, NULL);
    toplevel->resize_button = resize_button;
}

void geomnotifyfunc_toplevel(ei_widget_t* widget, ei_rect_t rect)
{

}
