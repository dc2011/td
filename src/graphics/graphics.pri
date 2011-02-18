include(../3rdparty/libtiled/libtiled.pri)

LIBS += ../lib/libtiled.a -lz

GRAPHICS_SRCS +=    ./graphics/mapdisplayer.cpp \
                    ./graphics/ContextMenuGraphicsComponent.cpp \
                    ./graphics/GraphicsComponent.cpp \
                    ./graphics/PlayerGraphicsComponent.cpp

GRAPHICS_HDRS +=    ./graphics/mapdisplayer.h \
                    ./graphics/ContextMenuGraphicsComponent.h \
                    ./graphics/GraphicsComponent.h \
                    ./graphics/PlayerGraphicsComponent.h \
                    ./graphics/PixmapFiles.h \
                    ./graphics/DrawParams.h

