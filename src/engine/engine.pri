include(../3rdparty/libtiled/libtiled.pri)

LIBS += ../lib/libtiled.a -lz

ENGINE_HDRS +=  ./engine/Driver.h \
                ./engine/Effect.h \
                ./engine/GameObject.h \
                ./engine/Map.h \
                ./engine/NPC.h \
                ./engine/Player.h \
                ./engine/Projectile.h \
                ./engine/ResManager.h \
                ./engine/Tile.h \
                ./engine/TileExtension.h \
                ./engine/Tower.h \
                ./engine/Resource.h \
                ./engine/Unit.h


ENGINE_SRCS +=  ./engine/Driver.cpp \
                ./engine/Effect.cpp \
                ./engine/GameObject.cpp \
                ./engine/Map.cpp \
                ./engine/NPC.cpp \
                ./engine/Player.cpp \
                ./engine/Projectile.cpp \
                ./engine/ResManager.cpp \
                ./engine/Tile.cpp \
                ./engine/TileExtension.cpp \
                ./engine/Tower.cpp \
                ./engine/Resource.cpp \
                ./engine/Unit.cpp

# Client-side engine headers and sources
ENGINE_HDRS_C +=    $$ENGINE_HDRS \
                    ./engine/ContextMenu.h \
                    ./engine/CDriver.h

ENGINE_SRCS_C +=    $$ENGINE_SRCS \
                    ./engine/ContextMenu.cpp \
                    ./engine/CDriver.cpp

# Server-side engine headers and sources
ENGINE_HDRS_S +=    $$ENGINE_HDRS \
                    ./engine/SDriver.h

ENGINE_SRCS_S +=    $$ENGINE_SRCS \
                    ./engine/SDriver.cpp
