#include "SfxManager.h"

namespace td {

// projectile fires
QStringList SfxManager::projectileFireArrow  
        = QStringList() << "arrow-1" << "arrow-2" << "arrow-3";
QStringList SfxManager::projectileFireCannon 
        = QStringList() << "cannon-1";
QStringList SfxManager::projectileFireFlame  
        = QStringList() << "flame-1" << "flame-2";
QStringList SfxManager::projectileFireTar    
        = QStringList() << "tar-1";
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
        = QStringList() << "";
QStringList SfxManager::towerBuildingFinished
        = QStringList() << "";
QStringList SfxManager::towerLevelUp
        = QStringList() << "";
QStringList SfxManager::towerSold
        = QStringList() << "";

// NPC wave entrance
QStringList SfxManager::npcPterodactylEnters
        = QStringList() << "";

// NPC death 
QStringList SfxManager::npcPterodactylDies
        = QStringList() << "";

// resource picked up
QStringList SfxManager::resourceLumber
        = QStringList() << "wood";

// player SFX
QStringList SfxManager::playerOpensMenu
        = QStringList() << "";
QStringList SfxManager::playerSelectsMenuItem
        = QStringList() << "";
QStringList SfxManager::playerLevelsUp
        = QStringList() << "";
QStringList SfxManager::playerHitsNpc
        = QStringList() << "peffect-1" << "peffect-2";

} // end namespace td

