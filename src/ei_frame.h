#include "ei_widget.h"
#include "stdlib.h"
#include "stdio.h"


typedef struct ei_frame_t
{
        ei_widget_t widget;
        ei_relief_t relief;
        char* text;
        ei_font_t font;
        ei_color_t color;
        ei_anchor_t anchor;
        ei_surface_t image;
        /* TODO : il manque le rectangle et le point où centrer */

}
ei_frame_t;


void* allocfunc_frame ()
{
    NULL;
}


 void	releasefunc_frame	(struct ei_widget_t*	widget)
 {
     NULL;
 }


void drawfunc_frame		(struct ei_widget_t*	widget,
                              ei_surface_t		surface,
                              ei_surface_t		pick_surface,
                              ei_rect_t*		clipper)
{
    NULL;
}

void setdefaultsfunc_frame	(struct ei_widget_t*	widget)
{
    NULL;
}

 void geomnotifyfunc_frame	(struct ei_widget_t*	widget,
                             ei_rect_t		rect)
 {
     NULL;
 }
