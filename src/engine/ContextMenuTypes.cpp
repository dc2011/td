#include "ContextMenuTypes.h"
#include "../graphics/ContextMenuGraphicsComponentTypes.h"

namespace td {

BuildContextMenu::BuildContextMenu(Player* player) : ContextMenu(player) {
    graphics_ = new BuildContextMenuGraphicsComponent(this);
}

void BuildContextMenu::selectMenuItem(int keyPressed) {
    if (!menuIsOpen_ || keyPressed < TOWER_ARROW
                     || keyPressed > TOWER_FLAK) {
        return;
    }
    emit signalTowerSelected(keyPressed, player_->getPos());
    ContextMenu::selectMenuItem(keyPressed);
}

TowerContextMenu::TowerContextMenu(Player* player) : ContextMenu(player) {
    graphics_ = new TowerContextMenuGraphicsComponent(this);
    upgradeLevels_ = 0;
}

void TowerContextMenu::selectMenuItem(int keyPressed) {
    if (!menuIsOpen_ || 
            (keyPressed != UPGRADE_TOWER && keyPressed != SELL_TOWER)) {
        return;
    }
    if (keyPressed == UPGRADE_TOWER) {
        if (upgradeLevels_ >= MAX_TOWER_LEVEL) { 
            return;
        }
        upgradeLevels_++;
        emit signalUpgradeTower(player_->getPos());
    } else {
        emit signalSellTower(player_->getPos()); 
    }
    ContextMenu::selectMenuItem(keyPressed);
}

PlayerContextMenu::PlayerContextMenu(Player* player) : ContextMenu(player) {
    graphics_ = new PlayerContextMenuGraphicsComponent(this);
}

void PlayerContextMenu::selectMenuItem(int keyPressed) {
    if (!menuIsOpen_ || 
            (keyPressed != UPGRADE_SPEED && keyPressed != UPGRADE_HARVEST &&
             keyPressed != UPGRADE_RECOVERY)) {
        return;
    }
    switch (keyPressed) {
        case UPGRADE_SPEED:     upgradeLevels_ | PLAYER_SPEED;      break;
        case UPGRADE_HARVEST:   upgradeLevels_ | PLAYER_HARVEST;    break;
        case UPGRADE_RECOVERY:  upgradeLevels_ | PLAYER_RECOVERY;   break;
    }
    emit signalUpgradePlayer(keyPressed, player_->getPos());
    ContextMenu::selectMenuItem(keyPressed);
}

} // end namespace td

