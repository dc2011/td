######################################################################
# Automatically generated by qmake (2.01a) Wed Jan 26 20:18:46 2011
######################################################################

TEMPLATE = app
TARGET = 
DEPENDPATH += .
INCLUDEPATH += .

macx {
    LIBS += -framework OpenAL
    CONFIG += link_pkgconfig
    PKGCONFIG = vorbisfile vorbis
}

unix:!macx {
    CONFIG += link_pkgconfig
    PKGCONFIG = openal vorbisfile vorbis
}

# Input
HEADERS += manager.h openal_helper.h
SOURCES += manager.cpp openal_helper.cpp
