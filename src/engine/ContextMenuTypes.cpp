#include "ContextMenuTypes.h"
#include "../graphics/ContextMenuGraphicsComponentTypes.h"

namespace td {

BuildContextMenu::BuildContextMenu(Player* player) : ContextMenu(player) {
    graphics_ = new BuildContextMenuGraphicsComponent();
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
    graphics_ = new TowerContextMenuGraphicsComponent();
}

void TowerContextMenu::selectMenuItem(int keyPressed) {
    if (!menuIsOpen_ || 
            (keyPressed != UPGRADE_TOWER && keyPressed != SELL_TOWER)) {
        return;
    }
    if (keyPressed == UPGRADE_TOWER) {
        emit signalUpgradeTower(player_->getPos());
    } else {
        emit signalSellTower(player_->getPos()); 
    }
    ContextMenu::selectMenuItem(keyPressed);
}

PlayerContextMenu::PlayerContextMenu(Player* player) : ContextMenu(player) {
    graphics_ = new PlayerContextMenuGraphicsComponent();
}

void PlayerContextMenu::selectMenuItem(int keyPressed) {
    if (!menuIsOpen_ || 
            (keyPressed != UPGRADE_SPEED && keyPressed != UPGRADE_HARVEST &&
             keyPressed != UPGRADE_RECOVERY)) {
        return;
    }
    emit signalUpgradePlayer(keyPressed);
    ContextMenu::selectMenuItem(keyPressed);
}

} // end namespace td

