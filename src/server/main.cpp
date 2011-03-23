#include <QMainWindow>

#include "../engine/SDriver.h"
#include "../network/lobbyserver.h"

int main(int argc, char **argv) {
    QCoreApplication a(argc, argv);
    //td::LobbyServer* ls = new td::LobbyServer();
    td::SDriver s;
    s.startGame();
    
    return a.exec();
}
