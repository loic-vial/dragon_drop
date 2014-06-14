/**
 *  @file	widgetclass.h
 *  @brief	Definition and registration of widget classes.
 *
 *  \author 
 *  Created by François Bérard on 02.12.11.
 *  Copyright 2011 Ensimag. All rights reserved.
 *
 */

#ifndef EI_WIDGETCLASS_H
#define EI_WIDGETCLASS_H

#include "hw_interface.h"
#include "ei_draw.h"




/**
 * \brief	A name of a class of widget.
 */
typedef char 		ei_widgetclass_name_t[20];

struct ei_widget_t;

/**
 * \brief	A function that allocates a block of memory that is big enough to store the
 *		attributes of a widget of a class. After allocation, the function *must*
 *		initialize the memory to 0.
 *
 * @return		A block of memory with all bytes set to 0.
 */
typedef void*	(*ei_widgetclass_allocfunc_t)		();

/**
 * \brief	A function that releases the memory used by a widget before it is destroyed.
 *		The \ref ei_widget_t structure itself, passed as parameter, must *not* by freed by
 *		these functions. Can be set to NULL in \ref ei_widgetclass_t if no memory is used by
 *		a class of widget.
 *
 * @param	widget		The widget which resources are to be freed.
 */
typedef void	(*ei_widgetclass_releasefunc_t)		(struct ei_widget_t*	widget);

/**
 * \brief	A function that draws widgets of a class.
 *
 * @param	widget		A pointer to the widget instance to draw.
 * @param	surface		Where to draw the widget. The actual location of the widget in the
 *				surface is stored in its "screen_location" field.
 * @param	clipper		If not NULL, the drawing is restricted within this rectangle
 *				(expressed in the surface reference frame).
 */
typedef void	(*ei_widgetclass_drawfunc_t)		(struct ei_widget_t*	widget,
							 ei_surface_t		surface,
							 ei_surface_t		pick_surface,
							 ei_rect_t*		clipper);

/**
 * \brief	A function that sets the default values for a class.
 *
 * @param	widget		A pointer to the widget instance to intialize.
 */
typedef void	(*ei_widgetclass_setdefaultsfunc_t)	(struct ei_widget_t*	widget);

/**
 * \brief 	A function that is called to notify the widget that its geometry has been modified
 *		by its geometry manager. Can set to NULL in \ref ei_widgetclass_t.
 *
 * @param	widget		The widget instance to notify of a geometry change.
 * @param	rect		The new rectangular screen location of the widget
 *				(i.e. = widget->screen_location).
 */
typedef void	(*ei_widgetclass_geomnotifyfunc_t)	(struct ei_widget_t*	widget,
							 ei_rect_t		rect);

/**
 * \brief	A structure that stores information about a class of widgets.
 */
typedef struct ei_widgetclass_t {
	ei_widgetclass_name_t			name;			///< The string name of this class of widget.
	ei_widgetclass_allocfunc_t		allocfunc;		///< The function that allocated instances of this class of widget.
	ei_widgetclass_releasefunc_t		releasefunc;		///< The function that releases all the resources used by an instance of this class of widget.
	ei_widgetclass_drawfunc_t		drawfunc;		///< The function that draws on screen an instance of this class of widget.
	ei_widgetclass_setdefaultsfunc_t	setdefaultsfunc;	///< The function that sets the default values to all the parameters of an instance of this class of widget.
	ei_widgetclass_geomnotifyfunc_t		geomnotifyfunc;		///< The function that is called to notify an instance of widget of this class that its geometry has changed.
	struct ei_widgetclass_t*		next;			///< A pointer to the next instance of ei_widget_class_t, allows widget class descriptions to be chained.
} ei_widgetclass_t;





/**
 * \brief	Returns the string of the name of a class.
 *
 * @param	name		The class name.
 *
 * @return			The string representing the name of the class.
 */
static inline char*	ei_widgetclass_stringname	(ei_widgetclass_name_t name);

/**
 * @brief	Registers a class to the program so that widgets of this class can be created.
 *		This must be done only once in the application.
 *
 * @param	widgetclass	The structure describing the class.
 */
void			ei_widgetclass_register		(ei_widgetclass_t* widgetclass);


/**
 * @brief	Returns the structure describing a class, from its name.
 *
 * @param	name		The name of the class of widget.
 *
 * @return			The structure describing the class.
 */
ei_widgetclass_t*	ei_widgetclass_from_name	(ei_widgetclass_name_t name);

/**
 * \brief	Registers the "frame" widget class in the program. This must be called only
 *		once before widgets of the class "frame" can be created and configured with
 *		\ref ei_frame_configure.
 */
void			ei_frame_register_class 	();

/**
 * \brief	Registers the "button" widget class in the program. This must be called only
 *		once before widgets of the class "button" can be created and configured with
 *		\ref ei_button_configure.
 */
void			ei_button_register_class 	();

/**
 * \brief	Registers the "toplevel" widget class in the program. This must be called only
 *		once before widgets of the class "toplevel" can be created and configured with
 *		\ref ei_toplevel_configure.
 */
void			ei_toplevel_register_class 	();


/* Inline function definitions. */

static inline char*	ei_widgetclass_stringname	(ei_widgetclass_name_t name)
{
	return (char*)name;
}

#endif
