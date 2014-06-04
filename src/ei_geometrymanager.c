#include "ei_geometrymanager.h"
#include <stdio.h>
#include <stdlib.h>
#include "ei_placer.h"

ei_geometrymanager_t* first_manager = NULL;

void ei_geometrymanager_register	(ei_geometrymanager_t* geometrymanager)
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


ei_geometrymanager_t*	ei_geometrymanager_from_name	(ei_geometrymanager_name_t name)
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



void			ei_geometrymanager_unmap	(ei_widget_t*		widget)
{
    NULL;
}



void 			ei_register_placer_manager 	()
{
    ei_geometrymanager_t* placer = (ei_geometrymanager_t*) malloc(sizeof(ei_geometrymanager_t));
    strcpy(placer->name, "placer");
    placer->runfunc = &ei_runfunc_placer;
    placer->releasefunc = &ei_releasefunc_placer;
    placer->next = NULL;
    ei_geometrymanager_register(placer);
}


void			ei_place			(ei_widget_t*		widget,
                             ei_anchor_t*		anchor,
                             int*			x,
                             int*			y,
                             int*			width,
                             int*			height,
                             float*			rel_x,
                             float*			rel_y,
                             float*			rel_width,
                             float*			rel_height)
{
    if(widget->geom_params != NULL)
    {
        ei_geometrymanager_unmap (widget);
    }
}




