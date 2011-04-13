BASE_GRAPHICS_HDRS += ./graphics/GraphicsComponent.h

BASE_GRAPHICS_SRCS += ./graphics/GraphicsComponent.cpp


GRAPHICS_HDRS +=    $$BASE_GRAPHICS_HDRS \
                    ./graphics/CollectableGraphicsComponent.h \
                    ./graphics/CollectableGraphicsComponentTypes.h \
                    ./graphics/MapDisplayer.h \
                    ./graphics/ContextMenuGraphicsComponent.h \
                    ./graphics/PlayerGraphicsComponent.h \
                    ./graphics/PixmapFiles.h \
                    ./graphics/DrawParams.h \
                    ./graphics/ProjectileGraphicsComponent.h \
                    ./graphics/ProjectileGraphicsComponentTypes.h \
                    ./graphics/TowerGraphicsComponent.h \
                    ./graphics/TowerGraphicsComponentTypes.h \
                    ./graphics/BuildingTowerGraphicsComponent.h \
                    ./graphics/ResourceGraphicsComponent.h \
                    ./graphics/NPCGraphicsComponent.h \
                    ./graphics/NPCGraphicsComponentTypes.h \
                    ./graphics/Console.h \
                    ./graphics/EndingGraphicsComponent.h

GRAPHICS_SRCS +=    $$BASE_GRAPHICS_SRCS \
                    ./graphics/CollectableGraphicsComponent.cpp \
                    ./graphics/CollectableGraphicsComponentTypes.cpp \
                    ./graphics/MapDisplayer.cpp \
                    ./graphics/ContextMenuGraphicsComponent.cpp \
                    ./graphics/PlayerGraphicsComponent.cpp \
                    ./graphics/ProjectileGraphicsComponent.cpp \
                    ./graphics/ProjectileGraphicsComponentTypes.cpp \
                    ./graphics/TowerGraphicsComponent.cpp \
                    ./graphics/TowerGraphicsComponentTypes.cpp \
                    ./graphics/BuildingTowerGraphicsComponent.cpp \
                    ./graphics/ResourceGraphicsComponent.cpp \
                    ./graphics/NPCGraphicsComponent.cpp \
                    ./graphics/NPCGraphicsComponentTypes.cpp \
                    ./graphics/Console.cpp \
                    ./graphics/EndingGraphicsComponent.cpp
