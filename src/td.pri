include(../3rdparty/libtiled/libtiled.pri)

win32:LIBS += ../lib/tiled.lib ws2_32.lib
else:LIBS += ../lib/libtiled.a -lz

TEMPLATE = app
CONFIG += qt debug
DESTDIR = ../bin
QT += network
OBJECTS_DIR = ../obj
MOC_DIR = ../moc
UI_DIR = ../uic
