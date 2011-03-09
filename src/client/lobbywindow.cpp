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

    connect(ui->btnConnect, SIGNAL(clicked()),
            this, SLOT(connectLobby()));

    connect(this, SIGNAL(startGame()),
            this, SLOT(close()));
}

LobbyWindow::~LobbyWindow()
{
    delete ui;
}

void LobbyWindow::connectLobby()
{
    ui->txtAddress->setDisabled(true);
    ui->txtUsername->setDisabled(true);
    ui->btnConnect->setDisabled(true);

    QString ip = ui->txtAddress->text();
    QHostAddress addr(ip);

    NetworkClient::init(addr);
    connect(NetworkClient::instance(), SIGNAL(TCPReceived(Stream*)),
            this, SLOT(onTCPReceived(Stream*)));

    Stream* s = new Stream();
    s->writeShort(0x0001);
    s->writeByte(ui->txtUsername->text().length());
    s->write(ui->txtUsername->text().toAscii());

    NetworkClient::instance()->send(network::kLobbyWelcome, s->data());
    delete s;
}

void LobbyWindow::onTCPReceived(Stream* s)
{
    unsigned char msgType = s->readByte();

    switch (msgType) {
        case network::kLobbyWelcome:
        {
            int players = s->readInt();
            ui->lblDisplayCount->setText(QString::number(players));

            if (players == 1) {
                emit startGame();
            }
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
