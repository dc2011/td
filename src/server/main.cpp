#include <QCoreApplication>

#include "../network/lobbyserver.h"

int main(int argc, char **argv) {
    QCoreApplication a(argc, argv);
    td::LobbyServer ls;

    //td::SDriver* sd = new td::SDriver();

    /*
    int lobbyret = a.exec();

    // We're using the return value 1 as an indicator that we have forked
    if (lobbyret != 1) {
        return lobbyret;
    }

    qDebug() << "Continuing as fork...";

    QMap<QTcpSocket*, QString> players = ls->getPlayers();
    foreach (QString val, players) {
        qDebug() << "Nickname:" << val;
    }
    
    sd->startGame();*/

    return a.exec();
}
