#include "ei_toplevel.h"
#include <stdlib.h>
#include "ei_types.h"
#include "ei_widget.h"
#include "ei_widgetclass.h"
#include "ei_geometrymanager.h"

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
    drawfunc_frame(widget, surface, pick_surface, clipper);
}

void setdefaultsfunc_toplevel(ei_widget_t* widget)
{
    setdefaultsfunc_frame(widget);
    ei_toplevel_t* toplevel = (ei_toplevel_t*) widget;
    toplevel->frame.widget.requested_size.width=320;
    toplevel->frame.widget.requested_size.height=420;
    toplevel->frame.color=ei_default_background_color;
    toplevel->frame.border_width=4;
    toplevel->title="Toplevel";
    toplevel->closable=EI_TRUE;
    toplevel->resizable=ei_axis_both;
    toplevel->min_size=malloc(sizeof(ei_size_t));
    toplevel->min_size->width=160;
    toplevel->min_size->height=120;

    toplevel->border=(ei_frame_t*)ei_widget_create("frame", &toplevel->frame.widget);
    toplevel->border->widget.requested_size.height=20;
    toplevel->border->color.alpha=255;
    toplevel->border->color.red=0;
    toplevel->border->color.blue=0;
    toplevel->border->color.green=0;

    ei_frame_configure(&toplevel->border->widget,NULL,NULL,
                       &toplevel->frame.border_width,NULL,&toplevel->title,NULL,NULL,NULL,NULL,NULL,NULL);

    ei_anchor_t border_anchor = ei_anc_north;
    ei_anchor_t button_anchor = ei_anc_east;

    float un=1;
    ei_place(&toplevel->border->widget, &border_anchor, NULL, NULL, NULL, NULL, NULL, NULL, &un,NULL);

    toplevel->button = (ei_button_t*)ei_widget_create("button", &toplevel->border->widget);

    ei_size_t* bord=(ei_size_t*)malloc(sizeof(ei_size_t));
    bord->height= 12;
    bord->width=12;
    toplevel->button->color.alpha=255;
    toplevel->button->color.red=255;
    toplevel->button->color.green=0;
    toplevel->button->color.blue=0;
    toplevel->button->text="X";
    toplevel->button->text_font = hw_text_font_create("misc/font.ttf", ei_style_normal, 12);
    ei_button_configure(&toplevel->button->widget, bord, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);


    int x=4;
    int y=4;
    ei_place(&toplevel->button->widget, &button_anchor, &x, &y,NULL, NULL, NULL, NULL, NULL, NULL);
}

void geomnotifyfunc_toplevel(ei_widget_t* widget, ei_rect_t rect)
{

}
