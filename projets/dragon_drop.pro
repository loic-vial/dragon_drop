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
    ../include/ei_frame.h \
    ../include/ei_placer.h \
    ../include/ei_button.h \
    ../include/ei_toplevel.h \
    ../include/ei_eventlist.h \
    ../include/ei_utils_2.h \
    ../include/ei_toplevel_resize.h \
    ../include/ei_toplevel_banner.h \
    ../include/ei_radiobutton.h \
    ../include/ei_tag.h \
    ../include/ei_drag_and_drop.h

SOURCES += \
    ../src/ei_widgetclass.c \
    ../src/ei_widget.c \
    ../src/ei_utils_2.c \
    ../src/ei_toplevel_resize.c \
    ../src/ei_toplevel_banner.c \
    ../src/ei_toplevel.c \
    ../src/ei_tag.c \
    ../src/ei_radiobutton.c \
    ../src/ei_placer.c \
    ../src/ei_geometrymanager.c \
    ../src/ei_frame.c \
    ../src/ei_eventlist.c \
    ../src/ei_event.c \
    ../src/ei_drag_and_drop.c \
    ../src/ei_button.c \
    ../src/ei_application.c \
    ../tests/test_radiobutton.c
