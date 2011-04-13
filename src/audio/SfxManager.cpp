#include "SfxManager.h"
#include "../engine/GameObject.h"
#include "../engine/Driver.h"
#include "../network/netmessages.h"

namespace td {

// projectile fires
QStringList SfxManager::projectileFireArrow  
        = QStringList() << "arrow-1" << "arrow-2" << "arrow-3";
QStringList SfxManager::projectileFireCannon 
        = QStringList() << "cannon-1" << "cannon-2" << "cannon-3";
QStringList SfxManager::projectileFireFlame  
        = QStringList() << "fire-1";
QStringList SfxManager::projectileFireTar    
        = QStringList() << "tar-1" << "tar-2" << "tar-3";
QStringList SfxManager::projectileFireFlak   
        = QStringList() << "flak-1" << "flak-2";

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
        = QStringList() << "entrance-1";

// NPC death 
QStringList SfxManager::npcPterodactylDies
        = QStringList() << "";

// resource harvesting
QStringList SfxManager::resourceWood
        = QStringList() << "wood";
QStringList SfxManager::resourceStone
        = QStringList() << "stone";
QStringList SfxManager::resourceBone
        = QStringList() << "bone";
QStringList SfxManager::resourceTar
        = QStringList() << "oil";

// player SFX
QStringList SfxManager::playerOpensMenu
        = QStringList() << "";
QStringList SfxManager::playerSelectsMenuItem
        = QStringList() << "";
QStringList SfxManager::playerLevelsUp
        = QStringList() << "";
QStringList SfxManager::playerHitsNpc
        = QStringList() << "peffect-1" << "peffect-2" << "peffect-3"
        << "peffect-4" << "peffect-5" << "peffect-6";

//Game Sfx
QStringList SfxManager::npcInBase
        = QStringList() << "base-1" << "base-2";

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

