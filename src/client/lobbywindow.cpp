#include "lobbywindow.h"
#include "../../uic/ui_lobbywindow.h"
#include "../network/netclient.h"
#include <QMessageBox>

namespace td {

LobbyWindow::LobbyWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LobbyWindow)
{
    ui->setupUi(this);
    ui->btnStart->setEnabled(false);

    connect(ui->btnConnect, SIGNAL(clicked()),
            this, SLOT(connectLobby()));
    connect(ui->btnStart, SIGNAL(clicked()),
            this, SLOT(tmp_startGame()));
    connect(ui->chkSingleplayer, SIGNAL(clicked(bool)),
            ui->btnConnect, SLOT(setDisabled(bool)));
    connect(ui->chkSingleplayer, SIGNAL(clicked(bool)),
            ui->btnStart, SLOT(setEnabled(bool)));

    connect(this, SIGNAL(startGame(bool)),
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
    ui->chkSingleplayer->setDisabled(true);

    QString ip = ui->txtAddress->text();
    QHostAddress addr(ip);

    NetworkClient::init(addr);
    connect(NetworkClient::instance(), SIGNAL(TCPReceived(Stream*)),
            this, SLOT(onTCPReceived(Stream*)));

    Stream* s = new Stream();
    s->writeShort(TD_VERSION);
    s->writeByte(ui->txtUsername->text().length());
    s->write(ui->txtUsername->text().toAscii());

    NetworkClient::instance()->send(network::kLobbyWelcome, s->data());
    delete s;
}

void LobbyWindow::tmp_startGame()
{
    if (ui->chkSingleplayer->isChecked()) {
        disconnect(NetworkClient::instance(), SIGNAL(TCPReceived(Stream*)),
                this, SLOT(onTCPReceived(Stream*)));
        emit startGame(true);
        return;
    }

    Stream s;
    NetworkClient::instance()->send(network::kLobbyStartGame, s.data());
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
                ui->btnStart->setEnabled(true);
            }
            break;
        }
        case network::kLobbyStartGame:
        {
            disconnect(NetworkClient::instance(), SIGNAL(TCPReceived(Stream*)),
                    this, SLOT(onTCPReceived(Stream*)));
            emit startGame(false);
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
