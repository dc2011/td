#include "ContextMenuTypes.h"
#include "Driver.h"
#include "Map.h"
#include "TileExtension.h"
#include "Tower.h"
#include "../audio/SfxManager.h"
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
        Map* map = player_->getDriver()->getGameMap();
        Tile* tile = map->getTile(player_->getPos().x(), player_->getPos().y());
        int level = ((Tower*) tile->getExtension())->getLevel();

        if (level >= MAX_TOWER_LEVEL) { 
            return;
        }

        int gems = player_->getDriver()->getGemCount();

        if (level == 1 && gems < GEMS_TO_L2) {
            PLAY_LOCAL_NOTIFY(SfxManager::contextMenuNotEnoughGems);
            return;
        }
        if (level == 2 && gems < GEMS_TO_L3) {
            PLAY_LOCAL_NOTIFY(SfxManager::contextMenuNotEnoughGems);
            return;
        }
        if (level == 3 && gems < GEMS_TO_L4) {
            PLAY_LOCAL_NOTIFY(SfxManager::contextMenuNotEnoughGems);
            return;
        }
        if (level == 4 && gems < GEMS_TO_L5) {
            PLAY_LOCAL_NOTIFY(SfxManager::contextMenuNotEnoughGems);
            return;
        }
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
    
    int upgrades = player_->getUpgrades();

    switch (keyPressed) {
        case UPGRADE_SPEED:     upgrades = upgrades | PLAYER_SPEED;     break;
        case UPGRADE_HARVEST:   upgrades = upgrades | PLAYER_HARVEST;   break;
        case UPGRADE_RECOVERY:  upgrades = upgrades | PLAYER_RECOVERY;  break;
    }
    if (upgrades == player_->getUpgrades()) {
        return;
    }
    player_->setUpgrades(upgrades);
    emit signalUpgradePlayer(keyPressed);
    ContextMenu::selectMenuItem(keyPressed);
}

} // end namespace td

