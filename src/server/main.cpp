#include <QApplication>
#include "../network/lobbyserver.h"

int main(int argc, char **argv) {
    QApplication a(argc, argv);

    td::LobbyServer ls;

    return a.exec();
}
