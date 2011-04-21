#include "SfxManager.h"
#include "../engine/GameObject.h"
#include "../engine/Driver.h"
#include "../network/netmessages.h"

namespace td {

// projectile fires
QStringList SfxManager::projectileFireArrow  
        = QStringList() << "fireArrow1" << "fireArrow2" << "fireArrow3";
QStringList SfxManager::projectileFireCannon 
        = QStringList() << "fireCannon1" << "fireCannon2" << "fireCannon3";
QStringList SfxManager::projectileFireFlame  
        = QStringList() << "fireFlame1" << "fireFlame2";
QStringList SfxManager::projectileFireTar    
        = QStringList() << "fireTar1" << "fireTar2" << "fireTar3";
QStringList SfxManager::projectileFireFlak   
        = QStringList() << "flak1" << "flak2" << "flak3";

// projectile lands
QStringList SfxManager::projectileHitArrow  
        = QStringList() << "death-3";
QStringList SfxManager::projectileHitCannon 
        = QStringList() << "bridge";
QStringList SfxManager::projectileHitFlame  
        = QStringList() << "";
QStringList SfxManager::projectileHitTar    
        = QStringList() << "death-1";
QStringList SfxManager::projectileHitFlak   
        = QStringList() << "death-2";

// tower SFX
QStringList SfxManager::towerBuildingStarted
        = QStringList() << "resourceWood";
QStringList SfxManager::towerBuildingFinished
        = QStringList() << "";
QStringList SfxManager::towerLevelUp
        = QStringList() << "";
QStringList SfxManager::towerSold
        = QStringList() << "";

// menu SFX
QStringList SfxManager::contextMenuOpened
        = QStringList() << "arrow-1";
QStringList SfxManager::contextMenuClosed
        = QStringList() << "arrow-2";
QStringList SfxManager::contextMenuSelect
        = QStringList() << "arrow-3";
QStringList SfxManager::contextMenuNotEnoughGems
        = QStringList() << "menuNotEnoughGems";

// NPC wave entrance
QStringList SfxManager::npcPterodactylEnters
        = QStringList() << "entrance";

// NPC death 
QStringList SfxManager::npcPterodactylDies
        = QStringList() << "dinoSmall" << "dinoCroak" << "dinoBig";

// resource harvesting
QStringList SfxManager::resourceWood
        = QStringList() << "resourceWood";
QStringList SfxManager::resourceStone
        = QStringList() << "resourceStone";
QStringList SfxManager::resourceBone
        = QStringList() << "resourceBone";
QStringList SfxManager::resourceTar
        = QStringList() << "resourceOil";

// player SFX
QStringList SfxManager::playerOpensMenu
        = QStringList() << "";
QStringList SfxManager::playerSelectsMenuItem
        = QStringList() << "";
QStringList SfxManager::playerLevelsUp
        = QStringList() << "";
QStringList SfxManager::playerHitsNpc
        = QStringList() << "npcCollision1" << "npcCollision2" << "npcCollision3"
        << "npcCollision4" << "npcCollision5" << "npcCollision";

//Game Sfx
QStringList SfxManager::npcInBase
        = QStringList() << "base-1" << "base-2";
QStringList SfxManager::winTheGame
        = QStringList() << "congrats";
QStringList SfxManager::loseTheGame
        = QStringList() << "fail";

//lobby SFX
QStringList SfxManager::lobbyStart 
        = QStringList() << "start";
QStringList SfxManager::lobbySingle
        = QStringList() << "single";
QStringList SfxManager::lobbyMulti
        = QStringList() << "multi";
QStringList SfxManager::lobbyConnect
        = QStringList() << "connecting";

void SfxManager::makeSfxNetworkMsg(QObject* gameObject, QStringList sfxList,  
        int type)
{
    int rdNum;

    if(sfxList.size() < 1) {
	    qCritical("SfxManager::makeSfxNetworkMsg(): Empty List");
	    return;
    }
    
    rdNum = rand() % sfxList.size();
    QString filename = sfxList[rdNum];
    
    Stream s;
    s.writeInt(type);
    s.writeInt(filename.size());
    s.write(filename.toAscii());
    ((Driver*)gameObject->parent())->sendNetMessage(network::kPlaySfx, s.data());
}

} // end namespace td

