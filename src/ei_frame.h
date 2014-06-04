#include "ei_widget.h"

typedef struct ei_frame_t
{
    ei_widget_t		widget;
    ei_color_t	color;
    int			border_width;
    ei_relief_t		relief;
    char*			text;
    ei_font_t		text_font;
    ei_color_t		text_color;
    ei_anchor_t		text_anchor;
    ei_surface_t*		img;
    ei_rect_t*		img_rect;
    ei_anchor_t		img_anchor;
}
ei_frame_t;


void* allocfunc_frame ();

void releasefunc_frame	(struct ei_widget_t*	widget);

void drawfunc_frame		(struct ei_widget_t*	widget,
                         ei_surface_t		surface,
                         ei_surface_t		pick_surface,
                         ei_rect_t*		clipper);
void setdefaultsfunc_frame	(struct ei_widget_t*	widget);

void geomnotifyfunc_frame	(struct ei_widget_t*	widget,
                             ei_rect_t		rect);
