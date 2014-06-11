TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CFLAGS += -std=c99 -Wno-unused

INCLUDEPATH += ../include /usr/include/SDL

LIBS += -L$$_PRO_FILE_PWD_/../lib/
LIBS += -leibase -lSDL_gfx -lSDL -lSDL_ttf -lSDL_image

DESTDIR = $$_PRO_FILE_PWD_/..

OBJECTS_DIR = $$_PRO_FILE_PWD_/../obj

SOURCES += \
    ../tests/minimal.c \
    ../src/ei_application.c \
    ../tests/frame.c \
    ../src/ei_widget.c \
    ../src/ei_geometrymanager.c \
    ../src/ei_widgetclass.c \
    ../src/ei_frame.c \
    ../src/ei_placer.c \
    ../src/ei_event.c \
    ../src/ei_button.c \
    ../src/ei_toplevel.c \
    ../src/ei_eventlist.c \
    ../src/ei_utils_2.c \
    ../tests/puzzle.c \
    ../tests/hello_world_relative.c \
    ../src/ei_toplevel_resize.c \
    ../src/ei_toplevel_banner.c \
    ../src/ei_radiobutton.c

HEADERS += \
    ../include/ei_application.h \
    ../include/ei_draw.h \
    ../include/ei_event.h \
    ../include/ei_geometrymanager.h \
    ../include/ei_main.h \
    ../include/ei_types.h \
    ../include/ei_utils.h \
    ../include/ei_widget.h \
    ../include/ei_widgetclass.h \
    ../include/hw_interface.h \
    ../src/ei_frame.h \
    ../src/ei_placer.h \
    ../src/ei_button.h \
    ../src/ei_toplevel.h \
    ../src/ei_eventlist.h \
    ../src/ei_utils_2.h \
    ../src/ei_toplevel_resize.h \
    ../src/ei_toplevel_banner.h \
    ../src/ei_radiobutton.h
