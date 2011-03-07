include(./td.pri)

include(./server/server.pri)

include(./audio/audio.pri)
include(./engine/engine.pri)
include(./graphics/graphics.pri)
include(./input/input.pri)
include(./network/network.pri)
include(./physics/physics.pri)

DEPENDPATH += .
INCLUDEPATH += .
OBJECTS_DIR = ../obj/server
DEFINES += SERVER

HEADERS += $$SERVER_HDRS $$AUDIO_HDRS $$NETWORK_HDRS $$ENGINE_SERVER_HDRS $$ENGINE_HDRS $$GRAPHICS_HDRS $$INPUT_HDRS $$PHYSICS_HDRS
SOURCES += $$SERVER_SRCS $$AUDIO_SRCS $$NETWORK_SRCS $$ENGINE_SERVER_SRCS $$ENGINE_SRCS $$GRAPHICS_SRCS $$INPUT_SRCS $$PHYSICS_SRCS
