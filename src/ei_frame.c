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
        point.x = centre.x + rayon*cos(angle*PI/180.0);
        point.y = centre.y - rayon*sin(angle*PI/180.0);
        current_point->point = point;
        current_point->next = malloc(sizeof(ei_linked_point_t));
        current_point = current_point->next;
    }
    point.x = centre.x + rayon*cos(angle_fin*PI/180.0);
    point.y = centre.y - rayon*sin(angle_fin*PI/180.0);
    current_point->point = point;
    current_point->next = NULL;
    return(liste_points);
}

ei_linked_point_t rounded_frame(ei_rect_t rectangle, float rayon,
                                ei_bool_t top, ei_bool_t bot){
    ei_point_t sommet = rectangle.top_left;
    ei_point_t centre;
    ei_linked_point_t liste_points;
    liste_points.point = rectangle.top_left;
    liste_points.next = NULL;
    ei_linked_point_t* current_point = &liste_points;
    //haut gauche
    sommet = rectangle.top_left;
    if (top){
        centre.x = sommet.x + rayon;
        centre.y = sommet.y + rayon;
        liste_points = arc(centre, rayon, 90, 180);
        current_point = &liste_points;
        while (current_point->next != NULL) {
            current_point = current_point->next;
        }
    }
    else {
        liste_points.point = sommet;
        current_point = &liste_points;
    }
    //bas gauche
    sommet.y += rectangle.size.height;
    if (bot){
        centre.x = sommet.x + rayon;
        centre.y = sommet.y - rayon;
        current_point->next = malloc(sizeof(ei_linked_point_t));
        *current_point->next = arc(centre, rayon, -180, -90);
        while (current_point->next != NULL) {
            current_point = current_point->next;
        }
    }
    else {
        current_point->next = malloc(sizeof(ei_linked_point_t));
        current_point->next->point = sommet;
        current_point = current_point->next;
    }
    //bas droite
    sommet.x += +rectangle.size.width;
    if (bot){
        centre.x = sommet.x - rayon;
        centre.y = sommet.y - rayon;
        current_point->next = malloc(sizeof(ei_linked_point_t));
        *current_point->next = arc(centre, rayon, -90, 0);
        while (current_point->next != NULL) {
            current_point = current_point->next;
        }
    }
    else {
        current_point->next = malloc(sizeof(ei_linked_point_t));
        current_point->next->point = sommet;
        current_point = current_point->next;
    }
    //haut droite
    sommet.y += -rectangle.size.height;
    if (top){
        centre.x = sommet.x - rayon;
        centre.y = sommet.y + rayon;
        current_point->next = malloc(sizeof(ei_linked_point_t));
        *current_point->next = arc(centre, rayon, 0, 90);
        while (current_point->next != NULL) {
            current_point = current_point->next;
        }
    }
    else {
        current_point->next = malloc(sizeof(ei_linked_point_t));
        current_point->next->point = sommet;
        current_point = current_point->next;
    }
    current_point->next = NULL;
    return(liste_points);
}

void drawfunc_frame(ei_widget_t* widget, ei_surface_t surface,
                    ei_surface_t pick_surface, ei_rect_t*  clipper)
{
    ei_frame_t* frame = (ei_frame_t*)widget;

    ei_rect_t rect = widget->screen_location;
    ei_linked_point_t points = rounded_frame(rect, 15, EI_TRUE, EI_FALSE);

    ei_draw_polygon(surface, &points, frame->color, clipper);

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
    ei_draw_polygon(pick_surface, &points, *widget->pick_color, clipper);

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
