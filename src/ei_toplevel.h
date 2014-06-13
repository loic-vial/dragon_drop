#ifndef EI_TOPLEVEL_H
#define EI_TOPLEVEL_H

#include "ei_types.h"
#include "ei_widget.h"
#include "ei_frame.h"
#include "ei_button.h"
#include "ei_event.h"

typedef struct ei_toplevel_t
{
    ei_frame_t frame;
    char* title;
    ei_bool_t closable;
    ei_axis_set_t resizable;
    ei_size_t* min_size;
    ei_frame_t* border;
    ei_button_t* close_button;
    ei_button_t* resize_button;
    ei_font_t close_button_font;
    ei_font_t border_font;
}
ei_toplevel_t;

void* ei_toplevel_allocfunc();

void ei_toplevel_releasefunc(ei_widget_t* widget);

void ei_toplevel_setdefaultsfunc(ei_widget_t* widget);

#endif
