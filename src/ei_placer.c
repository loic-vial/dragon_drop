#include "ei_placer.h"

void ei_runfunc_placer(ei_widget_t* widget)
{
    widget->screen_location.size = widget->requested_size;
}

void ei_releasefunc_placer(ei_widget_t* widget)
{

}
