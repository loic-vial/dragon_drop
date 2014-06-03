#include "ei_frame.h"



void* allocfunc_frame ()
{
    ei_frame_t* e=malloc(sizeof(ei_frame_t));
    return e;
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
   const struct ei_frame_t* frame = widget;
    ei_linked_point_t	first_point;
    ei_linked_point_t	second_point;
    ei_linked_point_t	third_point;
    ei_linked_point_t	fourth_point;
    first_point.point = widget->screen_location.top_left;
    first_point.next = &second_point;
    second_point.point = widget->screen_location.top_left;
    second_point.point.x += widget->screen_location.size.width;
    second_point.next=&third_point;
    third_point=second_point;
    third_point.point.y+=widget->screen_location.size.height;
    third_point.next=&fourth_point;
    fourth_point=first_point;
    fourth_point.point.y+=widget->screen_location.size.height;

    ei_draw_polyline	(surface,&first_point, *frame->color, clipper);

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
