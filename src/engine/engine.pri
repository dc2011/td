include(../3rdparty/libtiled/libtiled.pri)

LIBS += ../lib/libtiled.a -lz

ENGINE_HDRS +=  ./engine/ContextMenu.h \
                ./engine/CDriver.h \
                ./engine/Effect.h \
                ./engine/GameObject.h \
                ./engine/Map.h \
                ./engine/NPC.h \
                ./engine/Player.h \
                ./engine/Projectile.h \
                ./engine/ResManager.h \
                ./engine/SDriver.h \
                ./engine/Tile.h \
                ./engine/TileExtension.h \
                ./engine/Tower.h \
                ./engine/Resource.h \
                ./engine/Unit.h


ENGINE_SRCS +=  ./engine/ContextMenu.cpp \
                ./engine/CDriver.cpp \
                ./engine/Effect.cpp \
                ./engine/GameObject.cpp \
                ./engine/Map.cpp \
                ./engine/NPC.cpp \
                ./engine/Player.cpp \
                ./engine/Projectile.cpp \
                ./engine/ResManager.cpp \
                ./engine/SDriver.cpp \
                ./engine/Tile.cpp \
                ./engine/TileExtension.cpp \
                ./engine/Tower.cpp \
                ./engine/Resource.cpp \
                ./engine/Unit.cpp

