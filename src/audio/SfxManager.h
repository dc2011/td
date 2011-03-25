#ifndef TD_SFXMANAGER_H
#define TD_SFXMANAGER_H

#include <QStringList>
#include "manager.h"

#define PLAY_SFX(x)  td::AudioManager::instance()->playSfx(x)

namespace td {

/**
 * The purpose of this class is to keep all of the SFX filename info in one
 * place. Don't include the path and file extension when adding filenames in
 * the .cpp file; they will be added on in the audio manager.
 * 
 * eg. use:
 *  "tar-1" instead of "./sound/sfx/tar-1.ogg"
 *
 * To play a sound effect anywhere in the program, use the PLAY_SFX macro:
 * @code
 *  PLAY_SFX(SfxManager::projectileFireArrow);
 * @endcode
 *
 * @author Dean Morin
 */
class SfxManager {

public:
    // projectile fires
    static QStringList projectileFireArrow;
    static QStringList projectileFireCannon;
    static QStringList projectileFireFlame;
    static QStringList projectileFireTar;
    static QStringList projectileFireFlak;

    // projectile lands
    static QStringList projectileHitArrow;
    static QStringList projectileHitCannon;
    static QStringList projectileHitFlame;
    static QStringList projectileHitTar;
    static QStringList projectileHitFlak;

    // tower SFX
    static QStringList towerBuildingStarted;
    static QStringList towerBuildingFinished;
    static QStringList towerLevelUp;
    static QStringList towerSold;

    // NPC wave entrance
    static QStringList npcPterodactylEnters;

    // NPC death 
    static QStringList npcPterodactylDies;
    
    // resource picked up
    static QStringList resourceLumber;

    // player SFX
    static QStringList playerOpensMenu;
    static QStringList playerSelectsMenuItem;
    static QStringList playerLevelsUp;
    static QStringList playerHitsNpc;
};

} // end namespace td

#endif

