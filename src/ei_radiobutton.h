#ifndef EI_RADIOBUTTON_H
#define EI_RADIOBUTTON_H

#include "ei_types.h"
#include "ei_frame.h"
#include "ei_button.h"
#include "ei_widget.h"
#include "ei_event.h"

typedef struct ei_radiobutton_t
{
    ei_frame_t frame;
    int number;
}
ei_radiobutton_t;

void ei_add_children_radiobutton(char * text, ei_radiobutton_t* radio);

void ei_radiobutton_register_class();

void setdefaultsfunc_radiobutton(ei_widget_t* widget);

void ei_radiobutton_configure(ei_widget_t* widget, ei_size_t* requested_size, const ei_color_t* color,
                        int* border_width, ei_relief_t* relief);

void ei_destroy_field(ei_radiobutton_t* radio,int number);

void ei_edit_field(ei_radiobutton_t* radio,int number, char* text);

char* ei_return_field(ei_radiobutton_t* radio);


ei_widget_t* ei_find_widget(ei_radiobutton_t* radio,int number);
#endif
