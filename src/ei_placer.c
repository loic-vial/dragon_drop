#include "ei_placer.h"
#include <stdlib.h>

void ei_runfunc_placer(ei_widget_t* widget)
{
    ei_place(widget, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
    ei_placer_geometry_param_t* placer_param = (ei_placer_geometry_param_t*) widget->geom_params;
    widget->screen_location.top_left.x = placer_param->x;
    widget->screen_location.top_left.y = placer_param->y;
    if (widget->parent != NULL)
    {
        widget->screen_location.top_left.x += widget->parent->screen_location.top_left.x+widget->parent->screen_location.size.width*placer_param->rel_x;
        widget->screen_location.top_left.y += widget->parent->screen_location.top_left.y+widget->parent->screen_location.size.height*placer_param->rel_y;
    }
    widget->screen_location.size.width = placer_param->width;
    widget->screen_location.size.height = placer_param->height;

    if(widget->parent !=NULL && placer_param->rel_width != -1)
    {
        widget->screen_location.size.width = widget->parent->screen_location.size.width*placer_param->rel_width;
    }
    if (widget->parent !=NULL && placer_param->rel_height != -1)
    {
        widget->screen_location.size.height = widget->parent->screen_location.size.height*placer_param->rel_height;
    }
}

void ei_releasefunc_placer(ei_widget_t* widget)
{

}
