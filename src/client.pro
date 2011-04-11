include(./td.pri)

include(./client/client.pri)

include(./audio/audio.pri)
include(./engine/engine.pri)
include(./graphics/graphics.pri)
include(./input/input.pri)
include(./network/network.pri)
include(./physics/physics.pri)
include(./util/util.pri)

DEPENDPATH += .
INCLUDEPATH += .
OBJECTS_DIR = ../obj/client

HEADERS += $$CLIENT_HDRS $$AUDIO_HDRS $$NETWORK_HDRS_C $$ENGINE_HDRS_C $$GRAPHICS_HDRS $$INPUT_HDRS $$PHYSICS_HDRS $$UTIL_HDRS
SOURCES += $$CLIENT_SRCS $$AUDIO_SRCS $$NETWORK_SRCS_C $$ENGINE_SRCS_C $$GRAPHICS_SRCS $$INPUT_SRCS $$PHYSICS_SRCS
