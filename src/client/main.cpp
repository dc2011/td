#include <QObject>
#include <QApplication>
#include <QThreadPool>
#include "MainWindow.h"
#include "lobbywindow.h"
#include "../util/thread.h"
#include "../engine/CDriver.h"
#include "../audio/manager.h"
#include "../network/netclient.h"

int main(int argc, char **argv) {
    QApplication a(argc, argv);
    QDir bin(QCoreApplication::applicationDirPath());

    /* Set working directory */
    bin.cdUp();
#if defined(Q_WS_MAC)
    bin.cdUp();    /* Fix this on Mac because of the .app folder, */
    bin.cdUp();    /* which means that the actual executable is   */
    bin.cdUp();    /* three levels deep. Grrr.                    */
#endif
    QDir::setCurrent(bin.absolutePath());

    /* Set the ThreadPool count to allow for lots of audio */
    QThreadPool::globalInstance()->setMaxThreadCount(16);

    td::LobbyWindow* lobby = new td::LobbyWindow();
    td::MainWindow* qmw = new td::MainWindow();
    td::CDriver* clientDriver = td::CDriver::init(qmw);
    td::Thread* driverThread = new td::Thread();

    QObject::connect(lobby, SIGNAL(startGame()),
                     clientDriver, SLOT(startGame()));
    QObject::connect(lobby, SIGNAL(startGame()),
                     qmw, SLOT(openWindow()));
    clientDriver->moveToThread(driverThread);

    driverThread->start();

    lobby->show();
    
    int exitCode = a.exec();

    td::AudioManager::instance()->shutdown();
    td::CDriver::shutdown();
    td::NetworkClient::instance()->shutdown();
    delete lobby;

    return exitCode;
}

