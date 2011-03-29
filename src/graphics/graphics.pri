BASE_GRAPHICS_HDRS += ./graphics/GraphicsComponent.h

BASE_GRAPHICS_SRCS += ./graphics/GraphicsComponent.cpp


GRAPHICS_HDRS +=    $$BASE_GRAPHICS_HDRS \
                    ./graphics/MapDisplayer.h \
                    ./graphics/ContextMenuGraphicsComponent.h \
                    ./graphics/PlayerGraphicsComponent.h \
                    ./graphics/PixmapFiles.h \
                    ./graphics/DrawParams.h \
                    ./graphics/ProjectileGraphicsComponent.h \
                    ./graphics/TowerGraphicsComponent.h \
                    ./graphics/TowerGraphicsComponentTypes.h \
                    ./graphics/ResourceGraphicsComponent.h \
                    ./graphics/NPCGraphicsComponent.h \
                    ./graphics/NPCGraphicsComponentTypes.h

GRAPHICS_SRCS +=    $$BASE_GRAPHICS_SRCS \
                    ./graphics/MapDisplayer.cpp \
                    ./graphics/ContextMenuGraphicsComponent.cpp \
                    ./graphics/PlayerGraphicsComponent.cpp \
                    ./graphics/ProjectileGraphicsComponent.cpp \
                    ./graphics/TowerGraphicsComponent.cpp \
                    ./graphics/TowerGraphicsComponentTypes.cpp \
                    ./graphics/ResourceGraphicsComponent.cpp \
                    ./graphics/NPCGraphicsComponent.cpp \
                    ./graphics/NPCGraphicsComponentTypes.cpp
