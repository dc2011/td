#ifndef TD_SFXMANAGER_H
#define TD_SFXMANAGER_H

#define TOWER_FIRE_ARROW    "arrow-1" << "arrow-2" << "arrow-3"
#define TOWER_FIRE_CANNON   "cannon-1"
#define TOWER_FIRE_FLAME    "flame-1" << "flame-2" 
#define TOWER_FIRE_TAR      "tar-1"
#define TOWER_FIRE_FLAK     ""

#define PLAY_SFX(x)  td::AudioManager::instance()->playSfx(x)

#include <QStringList>
#include "manager.h"

class SfxManager {

public:
    static QStringList towerFireArrow;
    static QStringList towerFireCannon;
    static QStringList towerFireFlame;
    static QStringList towerFireTar;
    static QStringList towerFireFlak;
};

#endif

