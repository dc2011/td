######################################################################
# Automatically generated by qmake (2.01a) Wed Jan 26 20:18:46 2011
######################################################################

TEMPLATE = app
TARGET = 
DEPENDPATH += .
INCLUDEPATH += .
DESTDIR = ./bin

macx {
    LIBS += -framework OpenAL
    CONFIG += link_pkgconfig
    PKGCONFIG = vorbisfile vorbis
}

unix:!macx {
    CONFIG += link_pkgconfig
    PKGCONFIG = openal vorbisfile vorbis
}

SERVER_HDRS +=  SDriver.h
                
SERVER_SRCS +=  SDriver.cpp



HEADERS += $$SERVER_HDRS 
SOURCES += main.cpp $$SERVER_SRCS 