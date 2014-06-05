#include "ei_toplevel.h"
#include <stdlib.h>
#include "ei_types.h"
#include "ei_widget.h"
#include "ei_widgetclass.h"

void* allocfunc_toplevel()
{
    return calloc(1, sizeof(ei_toplevel_t));
}

void releasefunc_toplevel(ei_widget_t* widget)
{
    free(widget);
}

void drawfunc_toplevel(ei_widget_t* widget, ei_surface_t surface,
                       ei_surface_t pick_surface, ei_rect_t* clipper)
{
    ei_toplevel_t* toplevel = (ei_toplevel_t*)widget;
    toplevel->border->widget.wclass->drawfunc(widget, surface,pick_surface,clipper);
    //toplevel->contains->widget.wclass->drawfunc(widget, surface,pick_surface,clipper);
   // toplevel->close->widget.wclass->drawfunc(widget, surface,pick_surface,clipper);
}

void setdefaultsfunc_toplevel(ei_widget_t* widget)
{
    ei_toplevel_t* toplevel = (ei_toplevel_t*) widget;
    toplevel->widget.requested_size.width=320;
    toplevel->widget.requested_size.height=420;
    toplevel->color=ei_default_background_color;
    toplevel->border_width=4;
    toplevel->title="Toplevel";
    toplevel->closable=EI_TRUE;
    toplevel->resizable=ei_axis_both;
    toplevel->min_size=malloc(sizeof(ei_size_t));
    toplevel->min_size->width=160;
    toplevel->min_size->height=120;

    ei_size_t* bord=(ei_size_t*)malloc(sizeof(ei_size_t));
    bord->height=toplevel->widget.requested_size.height/50;
    bord->width=toplevel->widget.requested_size.width/50;
    ei_color_t* color=(ei_color_t*)malloc(sizeof(ei_color_t));
    color->alpha=255;
    color->red=0;
    color->blue=0;
    color->green=0;
    toplevel->border= (ei_frame_t*)malloc(sizeof(ei_frame_t));
    toplevel->border->widget= *ei_widget_create("frame", widget);
    toplevel->border->widget.wclass->setdefaultsfunc;
    ei_frame_configure((ei_widget_t*)toplevel->border,bord,color,&toplevel->border_width,NULL,&toplevel->title,NULL,NULL,NULL,NULL,NULL,NULL);

    toplevel->contains= malloc(sizeof(ei_frame_t));
    toplevel->contains->widget= *ei_widget_create("frame", widget);
    toplevel->contains->widget.wclass->setdefaultsfunc;

    toplevel->close=malloc(sizeof(ei_button_t));
    toplevel->close->widget= *ei_widget_create("frame", widget);
    toplevel->close->widget.wclass->setdefaultsfunc;
}

void geomnotifyfunc_toplevel(ei_widget_t* widget, ei_rect_t rect)
{

}
