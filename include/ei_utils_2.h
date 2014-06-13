#ifndef EI_UTILS_2_H
#define EI_UTILS_2_H

#include "ei_widget.h"

/**
 * @brief Computes the position of a child inside its parent at a specific anchor
 * @param parent_top_left_corner The top left corner of the parent
 * @param parent_size The size of the parent
 * @param child_size The size of the child
 * @param anchor The anchor
 */
ei_point_t ei_position_from_anchor(ei_point_t parent_top_left_corner, ei_size_t parent_size,
                              ei_size_t child_size, ei_anchor_t anchor);

/**
 * @brief Creates a new RGBA color inline
 */
ei_color_t ei_color(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha);

/**
 * @brief Tests if two colors are equal
 */
ei_bool_t is_same_color(ei_color_t color1, ei_color_t color2);

/**
 * @brief Tests if two rectangles are equal
 */
ei_bool_t is_same_rect(ei_rect_t rect1, ei_rect_t rect2);

/**
 * @brief Empty a linked list of rectangles
 */
void ei_clear_rect_list(ei_linked_rect_t** rects);

/**
 * @brief Computes the minimum of two integers
 */
int min(int x1, int x2);

/**
 * @brief Computes the maximum of two integers
 */
int max(int x1, int x2);

/**
 * @brief Computes the rectangle which intersects two rectangles
 */
ei_rect_t rectangle_intersection(ei_rect_t rect1, ei_rect_t rect2);

/**
 * @brief Moves a widget at the end (the tail) of its parent
 * The consequence is that this widget will be displayed in front of its siblings
 */
void ei_tail(ei_widget_t* widget);

#endif
