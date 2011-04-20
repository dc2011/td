#ifndef PIXMAPFILES_H
#define PIXMAPFILES_H

/**
 * This file is used to hold all the paths for external graphics files
 * The Max value referes to the total number of animations for each component
 * or the different types of graphics that each class can have. ie towers &
 * resources
 * @author Warren Voelkl, Karl Castillo
 */

#define PIX_BUILD_MENU_MAIN     QString("./img/buildmenu.png")
#define PIX_BUILD_MENU_RES      QString("./img/buildResources.png")
#define PIX_BUILD_MENU_T1       QString("./img/menuArrow.png")
#define PIX_BUILD_MENU_T2       QString("./img/menuCannon.png")
#define PIX_BUILD_MENU_T3       QString("./img/menuFlame.png")
#define PIX_BUILD_MENU_T4       QString("./img/menuTar.png")
#define PIX_BUILD_MENU_T5       QString("./img/menuFlak.png")
#define PIX_BUILD_MENU_MAX      7
#define PIX_TOWER_MENU_MAIN     QString("./img/towerUpgradeMenu.png")
#define PIX_TOWER_MENU_MAIN_2   QString("./img/towerUpgradeMenu2.png")
#define PIX_TOWER_MENU_RES_L1   QString("./img/towerUpgradeMenuCost1.png")
#define PIX_TOWER_MENU_RES_L2   QString("./img/towerUpgradeMenuCost2.png")
#define PIX_TOWER_MENU_RES_L3   QString("./img/towerUpgradeMenuCost3.png")
#define PIX_TOWER_MENU_RES_L4   QString("./img/towerUpgradeMenuCost4.png")
#define PIX_TOWER_MENU_RES_L5   QString("./img/buildResources.png")
#define PIX_TOWER_MENU_UPGR     QString("./img/towerUpgradeIcon.png")
#define PIX_TOWER_MENU_SELL     QString("./img/sellIcon.png")
#define PIX_TOWER_MENU_MAX      9
#define PIX_TOWER_LEVEL_TRI     QString("./img/upgradeMarker.png")
#define PIX_PLAYER_MENU_MAIN    QString("./img/playerUpgradeMenu.png")
#define PIX_PLAYER_MENU_MAIN_2  QString("./img/playerUpgradeMenu2.png")
#define PIX_PLAYER_MENU_MAIN_3  QString("./img/playerUpgradeMenu4.png")
#define PIX_PLAYER_MENU_MAIN_4  QString("./img/playerUpgradeMenu3.png")
#define PIX_PLAYER_MENU_MAIN_5  QString("./img/playerUpgradeMenu6.png")
#define PIX_PLAYER_MENU_MAIN_6  QString("./img/playerUpgradeMenu7.png")
#define PIX_PLAYER_MENU_MAIN_7  QString("./img/playerUpgradeMenu5.png")
#define PIX_PLAYER_MENU_MAIN_8  QString("./img/playerUpgradeMenu8.png")
#define PIX_PLAYER_MENU_RES     QString("./img/playerUpgradeMenuCost.png")
#define PIX_PLAYER_MENU_RES_2   QString("./img/playerUpgradeMenuCost2.png")
#define PIX_PLAYER_MENU_RES_3   QString("./img/playerUpgradeMenuCost5.png")
#define PIX_PLAYER_MENU_RES_4   QString("./img/playerUpgradeMenuCost3.png")
#define PIX_PLAYER_MENU_RES_5   QString("./img/playerUpgradeMenuCost8.png")
#define PIX_PLAYER_MENU_RES_6   QString("./img/playerUpgradeMenuCost7.png")
#define PIX_PLAYER_MENU_RES_7   QString("./img/playerUpgradeMenuCost6.png")
#define PIX_PLAYER_MENU_RES_8   QString("./img/playerUpgradeMenuCost4.png")
#define PIX_PLAYER_MENU_SPD     QString("./img/speedIcon.png")
#define PIX_PLAYER_MENU_HAR     QString("./img/harvestIcon.png")
#define PIX_PLAYER_MENU_REC     QString("./img/stunIcon.png")
#define PIX_PLAYER_MENU_MAX     19
#define PIX_PLAYER_0(x)         QString("./img/player") + QString::number(x) \
                                + QString("-stand.png")
#define PIX_PLAYER_1(x)         QString("./img/player") + QString::number(x) \
                                + QString("-move1.png")
#define PIX_PLAYER_2(x)         QString("./img/player") + QString::number(x) \
                                + QString("-move2.png")
#define PIX_PLAYER_3(x)         QString("./img/player") + QString::number(x) \
                                + QString("-move3.png")
#define PIX_PLAYER_4(x)         QString("./img/player") + QString::number(x) \
                                + QString("-move4.png")
#define PIX_PLAYER_5(x)         QString("./img/player") + QString::number(x) \
                                + QString("-move5.png")
#define PIX_PLAYER_6(x)         QString("./img/player") + QString::number(x) \
                                + QString("-move6.png")
#define PIX_PLAYER_FRAMES       7
#define PIX_PLAYER_TYPES        8
#define PIX_PLAYER_MAX          PIX_PLAYER_FRAMES * PIX_PLAYER_TYPES
#define PIX_PROJ_ARROW          QString("./img/arrowProjectile.png")
#define PIX_PROJ_ARROW_MAX      1
#define PIX_PROJ_ARROW_2        QString("./img/arrowProjectile2.png")
#define PIX_PROJ_ARROW_2_MAX    1
#define PIX_PROJ_ARROW_3        QString("./img/arrowProjectile3.png")
#define PIX_PROJ_ARROW_3_MAX    1
#define PIX_PROJ_TAR            QString("./img/tarProjectile.png")
#define PIX_PROJ_TAR_MAX        1
#define PIX_PROJ_TAR_2          QString("./img/tarProjectile2.png")
#define PIX_PROJ_TAR_2_MAX      1
#define PIX_PROJ_TAR_3          QString("./img/tarProjectile3.png")
#define PIX_PROJ_TAR_3_MAX      1
#define PIX_PROJ_CANNON         QString("./img/cannonProjectile.png")
#define PIX_PROJ_CANNON_MAX     1
#define PIX_PROJ_CANNON_2       QString("./img/cannonProjectile2.png")
#define PIX_PROJ_CANNON_2_MAX   1
#define PIX_PROJ_CANNON_3       QString("./img/cannonProjectile3.png")
#define PIX_PROJ_CANNON_3_MAX   1
#define PIX_PROJ_FIRE_0         QString("./img/smallFlame.png")
#define PIX_PROJ_FIRE_1         QString("./img/medFlame.png")
#define PIX_PROJ_FIRE_2         QString("./img/flameProjectile1.png")
#define PIX_PROJ_FIRE_3         QString("./img/flameProjectile2.png")
#define PIX_PROJ_FIRE_4         QString("./img/flameProjectile.png")
#define PIX_PROJ_FIRE_MAX       5
#define PIX_PROJ_FIRE_2_0       QString("./img/smallFlame2.png")
#define PIX_PROJ_FIRE_2_1       QString("./img/medFlame2.png")
#define PIX_PROJ_FIRE_2_2       QString("./img/flameProjectile2-2.png")
#define PIX_PROJ_FIRE_2_3       QString("./img/flameProjectile2-1.png")
#define PIX_PROJ_FIRE_2_MAX     4
#define PIX_PROJ_FIRE_3_0       QString("./img/smallFlame.png")
#define PIX_PROJ_FIRE_3_1       QString("./img/medFlame.png")
#define PIX_PROJ_FIRE_3_2       QString("./img/flameProjectile3.png")
#define PIX_PROJ_FIRE_3_3       QString("./img/flameProjectile3-2.png")
#define PIX_PROJ_FIRE_3_4       QString("./img/flameProjectile3-3.png")
#define PIX_PROJ_FIRE_3_MAX     5
#define PIX_PROJ_FLAK           QString("./img/flakProjectile.png")
#define PIX_PROJ_FLAK_MAX       1
#define PIX_PROJ_FLAK_2         QString("./img/flakprojectile2.png")
#define PIX_PROJ_FLAK_2_MAX     1
#define PIX_PROJ_FLAK_3         QString("./img/flakprojectile3.png")
#define PIX_PROJ_FLAK_3_MAX     1
#define PIX_BUILDING_TOWER_25   QString("./img/build1.png")
#define PIX_BUILDING_TOWER_50   QString("./img/build2.png")
#define PIX_BUILDING_TOWER_75   QString("./img/build3.png")
#define PIX_BUILDING_TOWER_MAX  3
#define PIX_TOWER_ARROW         QString("./img/towerArrow.png")
#define PIX_TOWER_ARROW_2       QString("./img/towerArrow2.png")
#define PIX_TOWER_ARROW_3       QString("./img/towerArrow3.png")
#define PIX_TOWER_CANNON        QString("./img/towerCannon.png")
#define PIX_TOWER_CANNON_2      QString("./img/towerCannon2.png")
#define PIX_TOWER_CANNON_3      QString("./img/towerCannon3.png")
#define PIX_TOWER_TAR           QString("./img/towerTar.png")
#define PIX_TOWER_TAR_2         QString("./img/towerTar2.png")
#define PIX_TOWER_TAR_3         QString("./img/towerTar3.png")
#define PIX_TOWER_FLAME         QString("./img/towerFlame.png")
#define PIX_TOWER_FLAME_2       QString("./img/towerFlame2.png")
#define PIX_TOWER_FLAME_3       QString("./img/towerFlame3.png")
#define PIX_TOWER_FLAK          QString("./img/towerFlak.png")
#define PIX_TOWER_FLAK_2        QString("./img/towerFlak2.png")
#define PIX_TOWER_FLAK_3        QString("./img/towerFlak3.png")
#define PIX_TOWER_ARROW_FIRE    QString("./img/towerArrowFire1.png")
#define PIX_TOWER_ARROW_FIRE_2  QString("./img/towerArrowFire2.png")
#define PIX_TOWER_ARROW_FIRE_3  QString("./img/towerArrowFire3.png")
#define PIX_TOWER_CANNON_FIRE   QString("./img/towerCannonFire1.png")
#define PIX_TOWER_CANNON_FIRE_2 QString("./img/towerCannonFire2.png")
#define PIX_TOWER_CANNON_FIRE_3 QString("./img/towerCannonFire3.png")
#define PIX_TOWER_FLAME_FIRE    QString("./img/towerFlameFire1.png")
#define PIX_TOWER_FLAME_FIRE_2  QString("./img/towerFlameFire2.png")
#define PIX_TOWER_FLAME_FIRE_3  QString("./img/towerFlameFire3.png")
#define PIX_TOWER_FLAK_FIRE     QString("./img/towerFlakFire1.png")
#define PIX_TOWER_FLAK_FIRE_2   QString("./img/towerFlakFire2.png")
#define PIX_TOWER_FLAK_FIRE_3   QString("./img/towerFlakFire3.png")
#define PIX_TOWER_MAX           5
#define PIX_RESOURCE_WOOD       QString("./img/woodTile.png")
#define PIX_RESOURCE_STONE      QString("./img/stoneTile.png")
#define PIX_RESOURCE_BONE       QString("./img/boneTile.png")
#define PIX_RESOURCE_TAR        QString("./img/oilTile.png")
#define PIX_RESOURCE_MAX        4
#define PIX_ICON_WOOD           QString("./img/woodIcon.png")
#define PIX_ICON_STONE          QString("./img/stoneIcon.png")
#define PIX_ICON_BONE           QString("./img/boneIcon.png")
#define PIX_ICON_TAR            QString("./img/oilIcon.png")
#define PIX_ICON_MAX            4
#define PIX_COLL_WOOD           QString("./img/woodIcon.png")
#define PIX_COLL_WOOD_MAX       1
#define PIX_COLL_STONE          QString("./img/stoneIcon.png")
#define PIX_COLL_STONE_MAX      1
#define PIX_COLL_BONE           QString("./img/boneIcon.png")
#define PIX_COLL_BONE_MAX       1
#define PIX_COLL_TAR            QString("./img/oilIcon.png")
#define PIX_COLL_TAR_MAX        1
#define PIX_COLL_GEM            QString("./img/gem.png")
#define PIX_COLL_GEM_MAX        1
#define PIX_NPC_FLY_START       0
#define PIX_NPC_FLY_0           QString("./img/ptero-1.png")
#define PIX_NPC_FLY_1           QString("./img/ptero-2.png")
#define PIX_NPC_FLY_2           QString("./img/ptero-3.png")
#define PIX_NPC_FLY_3           QString("./img/ptero-4.png")
#define PIX_NPC_FLY_MAX         4
#define PIX_NPC_ARM_START       0
#define PIX_NPC_ARM_0           QString("./img/mammoth1.png")
#define PIX_NPC_ARM_1           QString("./img/mammoth2.png")
#define PIX_NPC_ARM_MAX         2
#define PIX_NPC_SLOW_START      0
#define PIX_NPC_SLOW_0          QString("./img/Brontosaurus1.png")
#define PIX_NPC_SLOW_1          QString("./img/Brontosaurus2.png")
#define PIX_NPC_SLOW_2          QString("./img/Brontosaurus3.png")
#define PIX_NPC_SLOW_3          QString("./img/Brontosaurus4.png")
#define PIX_NPC_SLOW_4          QString("./img/Brontosaurus5.png")
#define PIX_NPC_SLOW_MAX        5
#define PIX_NPC_SWARM_START     0
#define PIX_NPC_SWARM_0         QString("./img/fast1.png")
#define PIX_NPC_SWARM_1         QString("./img/fast2.png")
#define PIX_NPC_SWARM_MAX       2
#define PIX_NPC_BOSS_START      0
#define PIX_NPC_BOSS_0          QString("./img/trex1.png")
#define PIX_NPC_BOSS_1          QString("./img/trex2.png")
#define PIX_NPC_BOSS_2          QString("./img/trex3.png")
#define PIX_NPC_BOSS_MAX        3
#define PIX_NPC_NORM_START      0
#define PIX_NPC_NORM_0          QString("./img/tri-1.png")
#define PIX_NPC_NORM_1          QString("./img/tri-2.png")
#define PIX_NPC_NORM_MAX        2
#define PIX_NPC_FAST_START      0
#define PIX_NPC_FAST_0          QString("./img/raptor1.png")
#define PIX_NPC_FAST_1          QString("./img/raptor2.png")
#define PIX_NPC_FAST_2          QString("./img/raptor3.png")
#define PIX_NPC_FAST_MAX        3

//ending animations for projectiles
#define PIX_END_CANNON_START    0
#define PIX_END_CANNON_0        QString("./img/smallExp.png")
#define PIX_END_CANNON_1        QString("./img/medExp.png")
#define PIX_END_CANNON_2        QString("./img/finalExp.png")
#define PIX_END_CANNON_MAX      3

#define PIX_END_ARROW_START     0
#define PIX_END_ARROW_0         QString("./img/blood.png")
#define PIX_END_ARROW_MAX       1

#define PIX_END_TAR_START       0
#define PIX_END_TAR_0           QString("./img/tarSplatter.png")
#define PIX_END_TAR_1           QString("./img/tarSplatter2.png")
#define PIX_END_TAR_MAX         2

//ending animations for NPCs
#define PIX_END_FLYING_START    0
#define PIX_END_FLYING_0        QString("./img/ptero-death-1.png")
#define PIX_END_FLYING_1        QString("./img/ptero-death-2.png")
#define PIX_END_FLYING_2        QString("./img/ptero-death-3.png")
#define PIX_END_FLYING_3        QString("./img/ptero-death-4.png")
#define PIX_END_FLYING_MAX      4

#define PIX_END_GENERIC_START    0
#define PIX_END_GENERIC_0        QString("./img/death1.png")
#define PIX_END_GENERIC_1        QString("./img/death2.png")
#define PIX_END_GENERIC_2        QString("./img/death3.png")
#define PIX_END_GENERIC_MAX      3

#endif

