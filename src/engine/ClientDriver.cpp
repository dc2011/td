#include <QTimer>

#include "ClientDriver.h"
#include "PlayerPhysicsComponent.h"
#include "PlayerInputComponent.h"

ClientDriver::ClientDriver() {
    timer_ = new QTimer(this);
    player_ = CreateHumanPlayer();
    
    connect(timer_, SIGNAL(timeout()), player_, SLOT(Update()));
    
}

ClientDriver::~ClientDriver() {
    delete timer_;
    delete player_;
}

void ClientDriver::Start() {
    timer_->start(1000);
}

Player* ClientDriver::CreateHumanPlayer() {
    PhysicsComponent* physics = new PlayerPhysicsComponent();
    InputComponent* input = new PlayerInputComponent();
    return new Player(input, physics);
}