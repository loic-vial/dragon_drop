#include "ei_utils_2.h"

ei_point_t ei_position_from_anchor(ei_point_t top_left_corner, ei_size_t parent_size,
                              ei_size_t child_size, ei_anchor_t anchor)
{
    if (anchor == ei_anc_northwest || anchor == ei_anc_none)
    {
        // already at good position
    }
    else if (anchor == ei_anc_north)
    {
        top_left_corner.x += parent_size.width / 2;
        top_left_corner.x -= child_size.width / 2;
    }
    else if (anchor == ei_anc_northeast)
    {
        top_left_corner.x += parent_size.width;
        top_left_corner.x -= child_size.width;
    }
    else if (anchor == ei_anc_east)
    {
        top_left_corner.x += parent_size.width;
        top_left_corner.x -= child_size.width;
        top_left_corner.y += parent_size.height / 2;
        top_left_corner.y -= child_size.height / 2;
    }
    else if (anchor == ei_anc_southeast)
    {
        top_left_corner.x += parent_size.width;
        top_left_corner.x -= child_size.width;
        top_left_corner.y += parent_size.height;
        top_left_corner.y -= child_size.height;
    }
    else if (anchor == ei_anc_south)
    {
        top_left_corner.x += parent_size.width / 2;
        top_left_corner.x -= child_size.width/2;
        top_left_corner.y += parent_size.height;
        top_left_corner.y -= child_size.height;
    }
    else if (anchor == ei_anc_southwest)
    {
        top_left_corner.y += parent_size.height;
        top_left_corner.y -= child_size.height;
    }
    else if (anchor == ei_anc_west)
    {
        top_left_corner.y += parent_size.height / 2;
        top_left_corner.y -= child_size.height / 2;
    }
    else if (anchor == ei_anc_center)
    {
        top_left_corner.x += parent_size.width / 2;
        top_left_corner.y += parent_size.height / 2;
        top_left_corner.x -= child_size.width / 2;
        top_left_corner.y -= child_size.height / 2;
    }
    return top_left_corner;
}

ei_color_t ei_color(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha)
{
    ei_color_t color;
    color.red = red;
    color.green = green;
    color.blue = blue;
    color.alpha = alpha;
    return color;
}
