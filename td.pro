######################################################################
# Automatically generated by qmake (2.01a) Wed Jan 26 20:18:46 2011
######################################################################

TEMPLATE = app
TARGET = 
DEPENDPATH += .
INCLUDEPATH += .
DESTDIR = ./bin
QT += network

macx {
    LIBS += -framework OpenAL
    CONFIG += link_pkgconfig
    PKGCONFIG = vorbisfile vorbis
}

unix:!macx {
    CONFIG += link_pkgconfig
    PKGCONFIG = openal vorbisfile vorbis
}

AUDIO_HDRS +=   src/audio/manager.h \
                src/audio/openal_helper.h

AUDIO_SRCS +=   src/audio/manager.cpp \
                src/audio/openal_helper.cpp

NETWORK_HDRS += src/network/netclient.h \
                src/network/stream.h

NETWORK_SRCS += src/network/stream.cpp

# Input
HEADERS += $$AUDIO_HDRS $$NETWORK_HDRS
SOURCES += src/main.cpp $$AUDIO_SRCS $$NETWORK_SRCS
