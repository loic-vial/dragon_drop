#include "ei_radiobutton.h"
#include "ei_button.h"
#include <stdlib.h>
#include <string.h>
#include "ei_types.h"
#include "ei_frame.h"
#include "ei_placer.h"

void add_children_radiobutton(char * text, ei_radiobutton_t* radio,ei_size_t size, ei_color_t color, ei_point_t point)
{
    ei_widget_t* widget = (ei_widget_t*)radio;
    ei_frame_t* frame = (ei_frame_t*)ei_widget_create("frame",widget);
    ei_relief_t relief = ei_relief_raised;
    ei_frame_configure(widget,&size,&color,NULL,&relief,&text,NULL,NULL,NULL,NULL,NULL,NULL);
    ei_place(&frame->widget, NULL, NULL,NULL,&point.x, &point.y, NULL, NULL, NULL, NULL );
}

void setdefaultsfunc_radiobutton(ei_widget_t* widget)
{
    setdefaultsfunc_frame(widget);
    ei_radiobutton_t* radio=(ei_radiobutton_t*)widget;
    ei_size_t size={15,15};
    ei_color_t color={0x00,0x55,0x12,0xff};
    ei_point_t point={20,20};
    add_children_radiobutton("premier champs",radio,size,color,point);
}

void ei_radiobutton_configure(ei_widget_t* widget, ei_size_t* requested_size, const ei_color_t* color,
                        int* border_width, ei_relief_t* relief, char** text,
                        ei_font_t* text_font, ei_color_t* text_color, ei_anchor_t* text_anchor,
                        ei_surface_t* img, ei_rect_t** img_rect, ei_anchor_t* img_anchor)
{
     ei_frame_configure(widget,requested_size,color,border_width,relief,text,text_font,text_color,text_anchor,img,img_rect,img_anchor);

}

void ei_radiobutton_register_class()
{
    ei_widgetclass_t* radiobuttonclass = (ei_widgetclass_t*) malloc(sizeof(ei_widgetclass_t));
    strcpy(radiobuttonclass->name, "radiobutton");
    radiobuttonclass->allocfunc = &allocfunc_frame;
    radiobuttonclass->releasefunc = &releasefunc_frame;
    radiobuttonclass->drawfunc = &drawfunc_frame;
    radiobuttonclass->setdefaultsfunc = &setdefaultsfunc_radiobutton;
    radiobuttonclass->geomnotifyfunc = &geomnotifyfunc_frame;
    radiobuttonclass->next = NULL;
    ei_widgetclass_register(radiobuttonclass);
}
