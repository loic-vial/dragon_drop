#include "ei_utils_2.h"

#include <stdlib.h>

ei_point_t ei_position_from_anchor(ei_point_t top_left_corner, ei_size_t parent_size,
                                   ei_size_t child_size, ei_anchor_t anchor)
{
    if (anchor == ei_anc_northwest || anchor == ei_anc_none)
    {
        // already at good position
    }
    else if (anchor == ei_anc_north)
    {
        top_left_corner.x += parent_size.width / 2;
        top_left_corner.x -= child_size.width / 2;
    }
    else if (anchor == ei_anc_northeast)
    {
        top_left_corner.x += parent_size.width;
        top_left_corner.x -= child_size.width;
    }
    else if (anchor == ei_anc_east)
    {
        top_left_corner.x += parent_size.width;
        top_left_corner.x -= child_size.width;
        top_left_corner.y += parent_size.height / 2;
        top_left_corner.y -= child_size.height / 2;
    }
    else if (anchor == ei_anc_southeast)
    {
        top_left_corner.x += parent_size.width;
        top_left_corner.x -= child_size.width;
        top_left_corner.y += parent_size.height;
        top_left_corner.y -= child_size.height;
    }
    else if (anchor == ei_anc_south)
    {
        top_left_corner.x += parent_size.width / 2;
        top_left_corner.x -= child_size.width/2;
        top_left_corner.y += parent_size.height;
        top_left_corner.y -= child_size.height;
    }
    else if (anchor == ei_anc_southwest)
    {
        top_left_corner.y += parent_size.height;
        top_left_corner.y -= child_size.height;
    }
    else if (anchor == ei_anc_west)
    {
        top_left_corner.y += parent_size.height / 2;
        top_left_corner.y -= child_size.height / 2;
    }
    else if (anchor == ei_anc_center)
    {
        top_left_corner.x += parent_size.width / 2;
        top_left_corner.y += parent_size.height / 2;
        top_left_corner.x -= child_size.width / 2;
        top_left_corner.y -= child_size.height / 2;
    }
    return top_left_corner;
}

ei_color_t ei_color(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha)
{
    ei_color_t color;
    color.red = red;
    color.green = green;
    color.blue = blue;
    color.alpha = alpha;
    return color;
}

ei_bool_t is_same_color(ei_color_t color1, ei_color_t color2)
{
    return (color1.red == color2.red &&
            color1.green == color2.green &&
            color1.blue == color2.blue &&
            color1.alpha == color2.alpha);
}

int min(int x1,int x2)
{
    if (x1>=x2)
    {
        return x2;
    }
    else return x1;
}
int max (int x1,int x2)
{
    if (x1>= x2)
    {
        return x1;
    }
    else return x2;
}

ei_rect_t calcul_clipper(ei_rect_t parent, ei_rect_t child)
{
    ei_rect_t rect;
    int maxgauche=max(parent.top_left.x,child.top_left.x);
    int  mindroit=min(parent.top_left.x+parent.size.width,child.top_left.x+child.size.width);
    int  maxbas=max(parent.top_left.y,child.top_left.y);
    int  minhaut=min(parent.top_left.y+parent.size.height,child.top_left.y+child.size.height);

    if ( maxgauche<mindroit && maxbas<minhaut)
    {
        rect.top_left.x=maxgauche;
        rect.size.width=mindroit-maxgauche;
        rect.top_left.y=maxbas;
        rect.size.height=minhaut-maxbas;
    }
    else
    {
        rect.size.height=0;
        rect.size.width=0;
        rect.top_left.x=0;
        rect.top_left.y=0;
    }

    return rect;

}

void ei_tail(ei_widget_t* widget)
{
    if (widget->parent->children_tail == widget) return;

    if(widget->parent->children_head == widget)
    {
        widget->parent->children_head=widget->next_sibling;
        widget->parent->children_tail->next_sibling = widget;
        widget->parent->children_tail = widget;
        widget->next_sibling=NULL;
    }
    else
    {
        ei_widget_t* prec=widget->parent->children_head;
        while(prec->next_sibling !=widget)
        {
            prec=prec->next_sibling;
        }
        prec->next_sibling=widget->next_sibling;
        widget->parent->children_tail->next_sibling = widget;
        widget->parent->children_tail = widget;
        widget->next_sibling=NULL;
    }
}
