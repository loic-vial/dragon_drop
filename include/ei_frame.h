#ifndef EI_FRAME_H
#define EI_FRAME_H

#include "ei_widget.h"
#include "ei_tag.h"

/**
* \brief ei_frame_t     A type of widget wich represent a frame
*
*/
typedef struct ei_frame_t
{
    ei_widget_t widget; ///< Memorize the place in the hierarchie of widget
    ei_color_t color; ///< Color of the frame
    int border_width; ///<Border width around the frame
    ei_relief_t relief; /// Relief of the frame, the size of the border width
    char* text; ///< Text inside the frame
    ei_font_t text_font ; ///<Font of the text
    ei_color_t text_color; ///< Color of the text
    ei_anchor_t text_anchor;///Anchor of the text
    ei_surface_t img;///< Image of the frame. The frame can't has a text and a image
    ei_rect_t* img_rect; ///< Rectangle to say wich part of the image will be displayed
    ei_anchor_t img_anchor; ///< anchor of the image
    int corner_radius; ///<Radius of the corner of thr frame
    ei_bool_t rounded_up; ///< True if the two corner in the top of the frame are rounded
    ei_bool_t rounded_down;///< True if the two corner in the bottom of the frame are rounded
    ei_linked_tag_t* tag; ///< List of tag
}
ei_frame_t;

/**
 * @brief ei_frame_allocfunc    Allocates a block in the memory the size of a \ref ei_frame_t, initialized to zero
 * @return                      Returns a pointer to a frame
 */
void* ei_frame_allocfunc();

/**
 * @brief ei_frame_releasefunc  Releases all parameters of a frame
 * @param widget                The widget to release
 */
void ei_frame_releasefunc(ei_widget_t* widget);

/**
 * @brief ei_frame_drawfunc     Draws a frame
 * @param widget                The frame to draw
 * @param surface               The root surface where to draw the widget
 * @param pick_surface          The offscreen surface where to draw the widget with it pick_color
 * @param clipper               Defines the surface where to draw the widget
 */
void ei_frame_drawfunc(ei_widget_t* widget, ei_surface_t surface,
                      ei_surface_t pick_surface, ei_rect_t* clipper);

/**
 * @brief ei_frame_setdefaultsfunc      Sets default all attributes of a frame
 * @param widget                        The frame widget to set to defaults values
 */
void ei_frame_setdefaultsfunc(ei_widget_t* widget);

/**
 * @brief arc           Creates a list a point in a circle, and only a part of this circle is returned
 * @param centre        Center of the circle
 * @param radius        Radius of the circle
 * @param angle_debut   Angle where is the first point
 * @param angle_fin     Angle where is the last point
 * @return              A list of point wich represents only a piece of circle
 */
ei_linked_point_t* arc(ei_point_t centre, float radius, float angle_debut, float angle_fin);

#endif
