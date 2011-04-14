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
    ContextMenu::selectMenuItem(keyPressed);
}

} // end namespace td

