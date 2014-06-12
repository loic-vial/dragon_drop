#include "ei_placer.h"
#include "ei_utils.h"
#include "ei_utils_2.h"
#include "ei_application.h"
#include <stdlib.h>

void ei_runfunc_placer(ei_widget_t* widget)
{
    ei_placer_geometry_param_t* placer_param = (ei_placer_geometry_param_t*) widget->geom_params;

    if (placer_param->rel_width != -1 && widget->parent != NULL)
        widget->screen_location.size.width = widget->parent->screen_location.size.width * placer_param->rel_width;
    else
        widget->screen_location.size.width = placer_param->width;

    if (placer_param->rel_height != -1 && widget->parent != NULL)
        widget->screen_location.size.height = widget->parent->screen_location.size.height * placer_param->rel_height;
    else
        widget->screen_location.size.height = placer_param->height;

    ei_point_t top_left_pos;
    if (widget->parent != NULL)
    {
         top_left_pos = ei_position_from_anchor(widget->parent->screen_location.top_left,
                                                          widget->parent->screen_location.size,
                                                          widget->screen_location.size,
                                                          placer_param->anchor);
        top_left_pos.x += placer_param->x;
        top_left_pos.y += placer_param->y;
        top_left_pos.x += widget->parent->screen_location.size.width * placer_param->rel_x;
        top_left_pos.y += widget->parent->screen_location.size.height * placer_param->rel_y;
    }
    else
    {
        top_left_pos.x = placer_param->x;
        top_left_pos.y = placer_param->y;
    }
    widget->screen_location.top_left = top_left_pos;

    if (widget->wclass->geomnotifyfunc != NULL)
    {
        widget->wclass->geomnotifyfunc(widget, widget->screen_location);
    }
    ei_app_invalidate_rect(&widget->screen_location);
}

void ei_releasefunc_placer(ei_widget_t* widget)
{
    ei_placer_geometry_param_t* placer = (ei_placer_geometry_param_t*) widget->geom_params;
    free(placer);
    widget->geom_params = NULL;
}
