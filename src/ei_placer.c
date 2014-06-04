#include "ei_placer.h"

void ei_runfunc_placer(ei_widget_t* widget)
{
    ei_placer_geometry_param_t* placer_param = (ei_placer_geometry_param_t*) widget->geom_params;
    widget->screen_location.top_left.x = placer_param->x;
    widget->screen_location.top_left.y = placer_param->y;
    widget->screen_location.size.width = placer_param->width;
    widget->screen_location.size.height = placer_param->height;
}

void ei_releasefunc_placer(ei_widget_t* widget)
{

}
