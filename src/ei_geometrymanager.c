#include "ei_geometrymanager.h"
#include "ei_placer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

ei_geometrymanager_t* first_manager = NULL;

void ei_geometrymanager_register (ei_geometrymanager_t* geometrymanager)
{
    if (first_manager == NULL)
    {
        first_manager = geometrymanager;
    }
    else
    {
        ei_geometrymanager_t* tmp;
        for (tmp = first_manager ; tmp->next != NULL ; tmp = tmp->next);
        tmp->next = geometrymanager;
    }
}

ei_geometrymanager_t* ei_geometrymanager_from_name (ei_geometrymanager_name_t name)
{
    for (ei_geometrymanager_t* tmp = first_manager ; tmp != NULL ; tmp = tmp->next)
    {
        if (strcmp(name, tmp->name) == 0)
        {
            return tmp;
        }
    }
    return NULL;
}

void ei_geometrymanager_unmap(ei_widget_t* widget)
{
    widget->geom_params->manager->releasefunc(widget);
}

void ei_register_placer_manager()
{
    ei_geometrymanager_t* placer = (ei_geometrymanager_t*) malloc(sizeof(ei_geometrymanager_t));
    strcpy(placer->name, "placer");
    placer->runfunc = &ei_runfunc_placer;
    placer->releasefunc = &ei_releasefunc_placer;
    placer->next = NULL;
    ei_geometrymanager_register(placer);
}

void set_default_values_to_placer(ei_placer_geometry_param_t* place)
{
    place->anchor = ei_anc_northwest;
    place->x = 0;
    place->y = 0;
    place->rel_x = 0;
    place->rel_y = 0;
    place->rel_width = -1;
    place->rel_height = -1;
}

void   ei_place   (ei_widget_t*  widget,
                   ei_anchor_t*  anchor,
                   int*   x,
                   int*   y,
                   int*   width,
                   int*   height,
                   float*   rel_x,
                   float*   rel_y,
                   float*   rel_width,
                   float*   rel_height)
{
    ei_placer_geometry_param_t* place;
    if (widget->geom_params == NULL)
    {
        place = ( ei_placer_geometry_param_t*)malloc(sizeof(ei_placer_geometry_param_t));
        place->geometry_param.manager=ei_geometrymanager_from_name("placer");
        set_default_values_to_placer(place);
        widget->geom_params=(ei_geometry_param_t*)place;
    }
    else if (strcmp(widget->geom_params->manager->name ,"placer") != 0)
    {
        ei_geometrymanager_unmap (widget);
        place = malloc(sizeof(ei_placer_geometry_param_t));
        place->geometry_param.manager=ei_geometrymanager_from_name("placer");
        set_default_values_to_placer(place);
        widget->geom_params=(ei_geometry_param_t*)place;
    }
    else
    {
        place = (ei_placer_geometry_param_t*)widget->geom_params;
    }

    if(anchor !=NULL)
    {
        place->anchor=*anchor;
    }

    if(x !=NULL)
    {

        place->x=*x;
    }

    if(y !=NULL)
    {
        if(strcmp(widget->parent->wclass->name,"toplevel")==0)
        {
            place->y=*y+20;
        }
        else place->y=*y;
    }

    if(width !=NULL)
    {
        place->width=*width;
        widget->requested_size.width=*width;
    }
    else
    {
        place->width=widget->requested_size.width;
    }

    if(height !=NULL)
    {
        place->height=*height;
        widget->requested_size.height=*height;
    }
    else
    {
        place->height=widget->requested_size.height;
    }

    if(rel_x !=NULL)
    {
        place->rel_x=*rel_x;
    }

    if(rel_y!=NULL)
    {
        place->rel_y=*rel_y;
    }

    if(rel_width !=NULL)
    {
        place->rel_width=*rel_width;
    }

    if(rel_height !=NULL)
    {
        place->rel_height=*rel_height;
    }
}



