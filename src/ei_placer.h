#ifndef EI_PLACER_H
#define EI_PLACER_H

#include "ei_geometrymanager.h"
#include "ei_widget.h"

typedef struct ei_placer_geometry_param_t
{
    ei_geometry_param_t geometry_param;
    ei_anchor_t	anchor;
    int x;
    int y;
    int width;
    int height;
    float rel_x;
    float rel_y;
    float rel_width;
    float rel_height;
}
ei_placer_geometry_param_t;

void ei_runfunc_placer(ei_widget_t* widget);

void ei_releasefunc_placer(ei_widget_t* widget);

#endif
