include(./td.pri)

include(./client/client.pri)

include(./audio/audio.pri)
include(./engine/engine.pri)
include(./graphics/graphics.pri)
include(./network/network.pri)

DEPENDPATH += .
INCLUDEPATH += .

HEADERS += $$CLIENT_HDRS $$AUDIO_HDRS $$NETWORK_HDRS $$ENGINE_HDRS $$GRAPHICS_HDRS
SOURCES += $$CLIENT_SRCS $$AUDIO_SRCS $$NETWORK_SRCS $$ENGINE_SRCS $$GRAPHICS_SRCS
