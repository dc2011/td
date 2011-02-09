include(../3rdparty/libtiled/libtiled.pri)

LIBS += ../lib/libtiled.a
macx:LIBS += -lz

GRAPHICS_SRCS +=    ./graphics/mapdisplayer.cpp

GRAPHICS_HDRS +=    ./graphics/mapdisplayer.h
