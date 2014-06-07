#include "ei_frame.h"
#include "ei_utils.h"
#include "ei_eventlist.h"
#include "ei_utils_2.h"
#include <stdlib.h>
#include <math.h>

#define PI 3.14159265

void* allocfunc_frame()
{
    return calloc(1, sizeof(ei_frame_t));
}

void releasefunc_frame(ei_widget_t* widget)
{
    free(widget);
}

ei_linked_point_t arc(ei_point_t centre, float rayon, float angle_debut, float angle_fin)
{
    ei_linked_point_t liste_points;
    ei_linked_point_t* current_point = &liste_points;
    ei_point_t point;

    for(float angle=angle_debut; angle<angle_fin; angle+=1){
        point.x = centre.x + rayon*cos(angle*PI/180);
        point.y = centre.y + rayon*sin(angle*PI/180);
        current_point->point = point;
        current_point->next = malloc(sizeof(ei_linked_point_t));
        current_point = current_point->next;
    }
    point.x = centre.x + rayon*cos(angle_fin*PI/180);
    point.y = centre.y + rayon*sin(angle_fin*PI/180);
    current_point->point = point;
    current_point->next = NULL;
    return(liste_points);
}

ei_linked_point_t rounded_frame(ei_rect_t rectangle, float rayon){
    ei_point_t sommet;
    ei_point_t centre;
    ei_linked_point_t liste_points;
    ei_linked_point_t* current_point = &liste_points;
    //haut gauche
    sommet = rectangle.top_left;
    centre.x = sommet.x + rayon;
    centre.y = sommet.y - rayon;
    liste_points = arc(centre, rayon, 90, 180);
    current_point = &liste_points;
    while (current_point->next != NULL) {
        current_point = current_point->next;
    }
    //haut droite
    sommet.x += rectangle.size.width;
    centre.x = sommet.x - rayon;
    current_point->next = malloc(sizeof(ei_linked_point_t));
    *current_point->next = arc(centre, rayon, -90, 0);
    while (current_point->next != NULL) {
        current_point = current_point->next;
    }

    //bas droite
    sommet.y += -rectangle.size.height;
    centre.y = sommet.y + rayon;
    current_point->next = malloc(sizeof(ei_linked_point_t));
    *current_point->next = arc(centre, rayon, 0, 90);
    while (current_point->next != NULL) {
        current_point = current_point->next;
    }
    //bas gauche
    sommet.x += -rectangle.size.width;
    centre.x = sommet.x + rayon;
    current_point->next = malloc(sizeof(ei_linked_point_t));
    *current_point->next = arc(centre, rayon, 90, 180);
    while (current_point->next != NULL) {
        current_point = current_point->next;
    }

    current_point = NULL;
    //return
    return(liste_points);
}

void drawfunc_frame(ei_widget_t* widget, ei_surface_t surface,
                    ei_surface_t pick_surface, ei_rect_t*  clipper)
{
    ei_frame_t* frame = (ei_frame_t*)widget;
    ei_linked_point_t first_point;
    ei_linked_point_t second_point;
    ei_linked_point_t third_point;
    ei_linked_point_t fourth_point;
    first_point.point = widget->screen_location.top_left;
    first_point.next = &second_point;
    second_point.point = widget->screen_location.top_left;
    second_point.point.x += widget->screen_location.size.width;
    second_point.next = &third_point;
    third_point.point = second_point.point;
    third_point.point.y += widget->screen_location.size.height;
    third_point.next = &fourth_point;
    fourth_point.point = first_point.point;
    fourth_point.point.y += widget->screen_location.size.height;
    fourth_point.next = NULL;


    ei_draw_polygon(surface, &first_point, frame->color, clipper);

    if (frame->text != NULL)
    {
        ei_size_t text_size;
        hw_text_compute_size(frame->text, frame->text_font, &text_size.width, &text_size.height);
        ei_point_t top_left_corner = ei_position_from_anchor(widget->screen_location.top_left,
                                                             widget->screen_location.size,
                                                             text_size,
                                                             frame->text_anchor);

        ei_draw_text(surface, &top_left_corner, frame->text, frame->text_font, &frame->text_color, clipper);
    }
    //tracé de l'image

    if (frame->img != NULL)
    {
        ei_size_t size = frame->img_rect->size;

        ei_point_t top_left_corner = ei_position_from_anchor(widget->screen_location.top_left,
                                                             widget->screen_location.size,
                                                             size,
                                                             frame->img_anchor);

        ei_rect_t rect =calcul_clipper(*clipper,widget->screen_location);
        ei_rect_t bon_top;
        bon_top.top_left=top_left_corner;
        bon_top.size=size;
        rect =calcul_clipper(bon_top,rect);


        ei_rect_t rect_2;
        rect_2.size=rect.size;
        rect_2.top_left=frame->img_rect->top_left;
         hw_surface_lock(*frame->img);
        ei_copy_surface		(surface,&rect,*frame->img,&rect_2,EI_TRUE);



        hw_surface_unlock(*frame->img);
    }
    ei_draw_polygon(pick_surface, &first_point, *widget->pick_color, clipper);

    if (frame->text != NULL)
    {
        ei_size_t text_size;
        hw_text_compute_size(frame->text, frame->text_font, &text_size.width, &text_size.height);
        ei_point_t text_top_left_position = ei_position_from_anchor(widget->screen_location.top_left,
                                                                    widget->screen_location.size,
                                                                    text_size,
                                                                    frame->text_anchor);
        ei_draw_text(surface, &text_top_left_position, frame->text, frame->text_font,
                     &frame->text_color, clipper);
    }
    /*
    if (frame->img != NULL)
    {
        ei_size_t img_size = frame->img_rect->size;
        ei_point_t img_top_left_position = ei_position_from_anchor(widget->screen_location.top_left,
                                                                   widget->screen_location.size,
                                                                   img_size,
                                                                   frame->img_anchor);
        ei_rect_t img_rect_on_screen = ei_rect(img_top_left_position, img_size);
        hw_surface_lock(*frame->img);
        ei_copy_surface(surface, &img_rect_on_screen, *frame->img, frame->img_rect, EI_TRUE);
        hw_surface_unlock(*frame->img);
    }
*/
}

void setdefaultsfunc_frame(ei_widget_t* widget)
{
    ei_frame_t* frame = (ei_frame_t*) widget;
    frame->color = ei_default_background_color;
    frame->border_width = 0;
    frame->relief = ei_relief_none;
    frame->text = NULL;
    frame->text_font = ei_default_font;
    frame->text_color = ei_font_default_color;
    frame->text_anchor = ei_anc_center;
    frame->img = NULL;
    frame->img_rect = NULL;
    frame->img_anchor = ei_anc_center;
}

void geomnotifyfunc_frame(ei_widget_t* widget, ei_rect_t rect)
{

}
