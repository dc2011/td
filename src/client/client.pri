CLIENT_HDRS +=  ./client/MainWindow.h \
                ./client/keybutton.h \
                ./client/keymap.h \
                ./client/lobbywindow.h

CLIENT_SRCS +=  ./client/main.cpp \
                ./client/MainWindow.cpp \
                ./client/keybutton.cpp \
                ./client/keymap.cpp \
                ./client/lobbywindow.cpp

FORMS +=        ./client/keymap.ui \
                ./client/lobbywindow.ui \
    client/stats.ui

HEADERS += \
    client/stats.h

SOURCES += \
    client/stats.cpp
