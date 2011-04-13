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

win32 {
    LIBS += OpenAL32.lib libogg.lib libvorbisfile.lib libvorbis.lib libspeex.lib
}
macx {
    LIBS += -framework OpenAL
    CONFIG += link_pkgconfig
    PKGCONFIG = vorbisfile vorbis speex
}
unix:!macx {
    CONFIG += link_pkgconfig
    PKGCONFIG = openal vorbisfile vorbis speex
}

HEADERS += $$CLIENT_HDRS $$AUDIO_HDRS_C $$NETWORK_HDRS_C $$ENGINE_HDRS_C $$GRAPHICS_HDRS $$INPUT_HDRS $$PHYSICS_HDRS $$UTIL_HDRS
SOURCES += $$CLIENT_SRCS $$AUDIO_SRCS_C $$NETWORK_SRCS_C $$ENGINE_SRCS_C $$GRAPHICS_SRCS $$INPUT_SRCS $$PHYSICS_SRCS
