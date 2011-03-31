TEMPLATE = app
CONFIG += qt debug
DESTDIR = ../bin
QT += network
win32:QMAKE_LIBS += ws2_32.lib
OBJECTS_DIR = ../obj
MOC_DIR = ../moc
UI_DIR = ../uic
