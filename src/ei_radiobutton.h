#ifndef EI_RADIOBUTTON_H
#define EI_RADIOBUTTON_H

#include "ei_types.h"
#include "ei_frame.h"
#include "ei_button.h"
#include "ei_widget.h"

typedef struct ei_radiobutton_t
{
    ei_frame_t frame;
}
ei_radiobutton_t;

void add_children_radiobutton(char * text, ei_radiobutton_t* radio,ei_size_t size, ei_color_t color, ei_point_t point);

void ei_radiobutton_register_class();

void setdefaultsfunc_radiobutton(ei_widget_t* widget);

void ei_radiobutton_configure(ei_widget_t* widget, ei_size_t* requested_size, const ei_color_t* color,
                        int* border_width, ei_relief_t* relief, char** text,
                        ei_font_t* text_font, ei_color_t* text_color, ei_anchor_t* text_anchor,
                        ei_surface_t* img, ei_rect_t** img_rect, ei_anchor_t* img_anchor);


#endif
