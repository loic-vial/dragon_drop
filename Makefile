# Variable definitions.

PLATFORM	= $(shell uname)
CC			= gcc
OBJDIR		= ./objs
TESTS		= ./tests
SRCDIR		= ./src
INCLUDES	= ./include
INCFLAGS	:= -I${INCLUDES}
OPTFLAGS	:= -Os -DNDEBUG
#OPTFLAGS	:= -g
CCFLAGS		:= -c ${OPTFLAGS} -Wall -Wextra -Wno-unused -std=c99

# The list of objects to include in the library

LIBEIOBJS	:= 	$(OBJDIR)/ei_application.o $(OBJDIR)/ei_frame.o $(OBJDIR)/ei_event.o $(OBJDIR)/ei_widget.o $(OBJDIR)/ei_utils_2.o $(OBJDIR)/ei_widgetclass.o $(OBJDIR)/ei_toplevel.o $(OBJDIR)/ei_toplevel_resize.o $(OBJDIR)/ei_toplevel_banner.o $(OBJDIR)/ei_placer.o $(OBJDIR)/ei_geometrymanager.o $(OBJDIR)/ei_button.o $(OBJDIR)/ei_eventlist.o $(OBJDIR)/ei_radiobutton.o $(OBJDIR)/ei_tag.o $(OBJDIR)/ei_drag_and_drop.o
 
# Platform specific definitions (OS X, Linux, Windows)

ifeq (${PLATFORM},Darwin)

	# Building for Mac OS X
	
	PLATDIR		= _osx
	INCFLAGS	:= ${INCFLAGS} -I/opt/local/include/SDL
	LINK		= ${CC}
	LIBEI		= ${OBJDIR}/libei.a
	LIBEIBASE	= ${PLATDIR}/libeibase.a
	LIBS		= ${LIBEIBASE} -L/opt/local/lib -lSDL -lSDL_ttf -lSDL_gfx -lSDL_image -framework AppKit

else
	ifeq (${PLATFORM},Linux)

	# Building for Linux
	
	PLATDIR		= _x11
	INCFLAGS	:= ${INCFLAGS} -I/usr/include/SDL
	LINK		= ${CC}
	LIBEI		= ${OBJDIR}/libei.a
	LIBEIBASE	= ${PLATDIR}/libeibase.a
        LIBSDLGFX       = ${PLATDIR}/libSDL_gfx.a
        #LIBSDLGFX       = -lSDL_gfx
	LIBS		= ${LIBEIBASE} -lSDL -lSDL_ttf ${LIBSDLGFX} -lSDL_image

	else

	# Building for Windows
	
	PLATDIR		= _win
	INCFLAGS	:= ${INCFLAGS} -I/usr/include/SDL -I/usr/local/include/SDL
	LINK		= ${CC} -mwindows -mno-cygwin
	LIBEI		= ${OBJDIR}/libei.lib
	LIBEIBASE	= ${PLATDIR}/libeibase.lib
	LIBS		= -lmingw32 ${LIBEIBASE} /usr/lib/SDL_ttf.lib /usr/local/lib/libSDL_gfx.a /usr/lib/SDL_image.lib -L/usr/lib -lSDL

	endif
endif



# Main target of the makefile. To build specific targets, call "make <target_name>"

TARGETS		=	${LIBEI} \
			minimal frame button hello_world_absolute hello_world_relative puzzle test_radiobutton test_tag test_toplevel
			
all : ${TARGETS}

########## Test-programs

# minimal

minimal : ${OBJDIR}/minimal.o ${LIBEIBASE}
	${LINK} -o minimal ${OBJDIR}/minimal.o ${LIBS}

${OBJDIR}/minimal.o : ${TESTS}/minimal.c
	${CC} ${CCFLAGS} ${INCFLAGS} ${TESTS}/minimal.c -o ${OBJDIR}/minimal.o

# frame

frame : ${OBJDIR}/frame.o ${LIBEIBASE} ${LIBEI}
	${LINK} -o frame ${OBJDIR}/frame.o ${LIBEI} ${LIBS}

${OBJDIR}/frame.o : ${TESTS}/frame.c
	${CC} ${CCFLAGS} ${INCFLAGS} ${TESTS}/frame.c -o ${OBJDIR}/frame.o

# button

button : ${OBJDIR}/button.o ${LIBEIBASE} ${LIBEI}
	${LINK} -o button ${OBJDIR}/button.o ${LIBEI} ${LIBS}

${OBJDIR}/button.o : ${TESTS}/button.c
	${CC} ${CCFLAGS} ${INCFLAGS} ${TESTS}/button.c -o ${OBJDIR}/button.o

# hello_world_absolute

hello_world_absolute : ${OBJDIR}/hello_world_absolute.o ${LIBEIBASE} ${LIBEI}
	${LINK} -o hello_world_absolute ${OBJDIR}/hello_world_absolute.o ${LIBEI} ${LIBS}

${OBJDIR}/hello_world_absolute.o : ${TESTS}/hello_world_absolute.c
	${CC} ${CCFLAGS} ${INCFLAGS} ${TESTS}/hello_world_absolute.c -o ${OBJDIR}/hello_world_absolute.o

# hello_world_relative

hello_world_relative : ${OBJDIR}/hello_world_relative.o ${LIBEIBASE} ${LIBEI}
	${LINK} -o hello_world_relative ${OBJDIR}/hello_world_relative.o ${LIBEI} ${LIBS}

${OBJDIR}/hello_world_relative.o : ${TESTS}/hello_world_relative.c
	${CC} ${CCFLAGS} ${INCFLAGS} ${TESTS}/hello_world_relative.c -o ${OBJDIR}/hello_world_relative.o

# puzzle

puzzle : ${OBJDIR}/puzzle.o ${LIBEIBASE} ${LIBEI}
	${LINK} -o puzzle ${OBJDIR}/puzzle.o ${LIBEI} ${LIBS}

${OBJDIR}/puzzle.o : ${TESTS}/puzzle.c
	${CC} ${CCFLAGS} ${INCFLAGS} ${TESTS}/puzzle.c -o ${OBJDIR}/puzzle.o

# test_radiobutton

test_radiobutton : ${OBJDIR}/test_radiobutton.o ${LIBEIBASE} ${LIBEI}
	${LINK} -o test_radiobutton ${OBJDIR}/test_radiobutton.o ${LIBEI} ${LIBS}

${OBJDIR}/test_radiobutton.o : ${TESTS}/test_radiobutton.c
	${CC} ${CCFLAGS} ${INCFLAGS} ${TESTS}/test_radiobutton.c -o ${OBJDIR}/test_radiobutton.o

# test_tag

test_tag : ${OBJDIR}/test_tag.o ${LIBEIBASE} ${LIBEI}
	${LINK} -o test_tag ${OBJDIR}/test_tag.o ${LIBEI} ${LIBS}

${OBJDIR}/test_tag.o : ${TESTS}/test_tag.c
	${CC} ${CCFLAGS} ${INCFLAGS} ${TESTS}/test_tag.c -o ${OBJDIR}/test_tag.o

# test_toplevel

test_toplevel : ${OBJDIR}/test_toplevel.o ${LIBEIBASE} ${LIBEI}
	${LINK} -o test_toplevel ${OBJDIR}/test_toplevel.o ${LIBEI} ${LIBS}

${OBJDIR}/test_toplevel.o : ${TESTS}/test_toplevel.c
	${CC} ${CCFLAGS} ${INCFLAGS} ${TESTS}/test_toplevel.c -o ${OBJDIR}/test_toplevel.o



# Building of the library libei

${LIBEI} : ${LIBEIOBJS}
	ar rcs ${LIBEI} ${LIBEIOBJS}

$(OBJDIR)/%.o : src/%.c
	${CC} ${CCFLAGS} ${INCFLAGS} -c -o $@ $^
        

# Building of the doxygen documentation.

doc :
	doxygen docs/doxygen.cfg


# Removing all built files.

clean:
	rm -f ${TARGETS}
	rm -f *.exe
	rm -f ${OBJDIR}/*
