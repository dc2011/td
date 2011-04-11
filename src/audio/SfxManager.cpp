#include "SfxManager.h"
#include "../engine/GameObject.h"
#include "../engine/Driver.h"
#include "../network/netmessages.h"

namespace td {

// projectile fires
QStringList SfxManager::projectileFireArrow  
        = QStringList() << "arrow-1" << "arrow-2" << "arrow-3";
QStringList SfxManager::projectileFireCannon 
        = QStringList() << "cannon-1";
QStringList SfxManager::projectileFireFlame  
        = QStringList() << "flame-1" << "flame-2";
QStringList SfxManager::projectileFireTar    
        = QStringList() << "tar-1" << "tar-2" << "tar-3";
QStringList SfxManager::projectileFireFlak   
        = QStringList() << "";

// projectile lands
QStringList SfxManager::projectileHitArrow  
        = QStringList() << "";
QStringList SfxManager::projectileHitCannon 
        = QStringList() << "";
QStringList SfxManager::projectileHitFlame  
        = QStringList() << "";
QStringList SfxManager::projectileHitTar    
        = QStringList() << "";
QStringList SfxManager::projectileHitFlak   
        = QStringList() << "";

// tower SFX
QStringList SfxManager::towerBuildingStarted
        = QStringList() << "wood";
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

// NPC wave entrance
QStringList SfxManager::npcPterodactylEnters
        = QStringList() << "";

// NPC death 
QStringList SfxManager::npcPterodactylDies
        = QStringList() << "";

// resource harvesting
QStringList SfxManager::resourceWood
        = QStringList() << "wood";
QStringList SfxManager::resourceStone
        = QStringList() << "shovel";
QStringList SfxManager::resourceBone
        = QStringList() << "wood";
QStringList SfxManager::resourceTar
        = QStringList() << "tar-1";

// player SFX
QStringList SfxManager::playerOpensMenu
        = QStringList() << "";
QStringList SfxManager::playerSelectsMenuItem
        = QStringList() << "";
QStringList SfxManager::playerLevelsUp
        = QStringList() << "";
QStringList SfxManager::playerHitsNpc
        = QStringList() << "peffect-1" << "peffect-2";

//lobby SFX
QStringList SfxManager::lobbyStart 
        = QStringList() << "start";
QStringList SfxManager::lobbySingle
        = QStringList() << "single";
QStringList SfxManager::lobbyMulti
        = QStringList() << "multi";
QStringList SfxManager::lobbyConnect
        = QStringList() << "connecting";

void SfxManager::makeSfxNetworkMsg(GameObject* gameObject, QStringList sfxList,  
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
    gameObject->getDriver()->sendNetMessage(network::kPlaySfx, s.data());
}

} // end namespace td

