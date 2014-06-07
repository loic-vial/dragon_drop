#ifndef EI_UTILS_2_H
#define EI_UTILS_2_H
#include "ei_widget.h"
#include "ei_types.h"

ei_point_t ei_position_from_anchor(ei_point_t parent_top_left_corner, ei_size_t parent_size,
                              ei_size_t child_size, ei_anchor_t anchor);

ei_color_t ei_color(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha);

ei_rect_t calcul_clipper(ei_rect_t parent, ei_rect_t child);

void ei_tail(ei_widget_t* widget);

#endif
