CLIENT_HDRS +=  ./client/MainWindow.h \
                ./client/MainMenu.h \
                ./client/lobbywindow.h \
                ./client/keybutton.h \
                ./client/keymap.h \
                ./client/settingswindow.h \
                ./client/stats.h

CLIENT_SRCS +=  ./client/main.cpp \
                ./client/MainMenu.cpp \
                ./client/MainWindow.cpp \
                ./client/lobbywindow.cpp \
                ./client/keybutton.cpp \
                ./client/keymap.cpp \
                ./client/settingswindow.cpp \
                ./client/stats.cpp

FORMS +=        ./client/lobbywindow.ui \
                ./client/settingswindow.ui \
                ./client/keymap.ui \
                ./client/MainMenu.ui \
                ./client/stats.ui

RESOURCES += 	./client/client.qrc
