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
    ../tests/minimal.c
