#include <QCoreApplication>
#include "../network/lobbyserver.h"

int main(int argc, char **argv) {
    QCoreApplication a(argc, argv);

    td::LobbyServer ls;

    return a.exec();
}
