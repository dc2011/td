#include "lobbywindow.h"
#include "ui_lobbywindow.h"
#include "../network/netclient.h"
#include <QMessageBox>

namespace td {

LobbyWindow::LobbyWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LobbyWindow)
{
    ui->setupUi(this);

    connect(ui->btnConnect, SIGNAL(triggered()),
            this, SLOT(connectLobby()));
}

LobbyWindow::~LobbyWindow()
{
    delete ui;
}

void LobbyWindow::connectLobby()
{
    QString ip = ui->lblAddress->text();
    QHostAddress addr(ip);

    NetworkClient::init(addr);
    connect(NetworkClient::instance(), SIGNAL(TCPReceived(Stream*)),
            this, SLOT(onTCPReceived(Stream*)));
}

void LobbyWindow::onTCPReceived(Stream* s)
{
    unsigned char msgType = s->readByte();

    switch (msgType) {
        case network::kLobbyWelcome:
        {
            int players = s->readInt();
            ui->lblDisplayCount->setText(QString::number(players));
            break;
        }
        case network::kBadVersion:
        {
            QMessageBox(QMessageBox::Critical, "Tower Defense: Error",
                    "Your game version does not match the server.").exec();
            break;
        }
    }
}

} /* end namespace td */
