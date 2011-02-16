include(../3rdparty/libtiled/libtiled.pri)

LIBS += ../lib/libtiled.a -lz

GRAPHICS_SRCS +=    ./graphics/mapdisplayer.cpp \
                    ./graphics/ProjectileGraphicsComponent.cpp

GRAPHICS_HDRS +=    ./graphics/mapdisplayer.h \
                    ./graphics/ProjectileGraphicsComponent.h
