TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

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
    ../src/ei_widgetclass.c

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
    ../src/ei_frame.h
