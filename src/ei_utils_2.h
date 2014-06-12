#ifndef EI_UTILS_2_H
#define EI_UTILS_2_H

#include "ei_widget.h"
#include "ei_types.h"

ei_point_t ei_position_from_anchor(ei_point_t parent_top_left_corner, ei_size_t parent_size,
                              ei_size_t child_size, ei_anchor_t anchor);

ei_color_t ei_color(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha);

ei_bool_t is_same_color(ei_color_t color1, ei_color_t color2);

ei_bool_t is_same_rect(ei_rect_t rect1, ei_rect_t rect2);

ei_rect_t rectangle_intersection(ei_rect_t parent, ei_rect_t child);

void ei_tail(ei_widget_t* widget);

int min(int x1, int x2);
int max (int x1,int x2);

#endif
