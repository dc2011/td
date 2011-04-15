#ifndef PIXMAPFILES_H
#define PIXMAPFILES_H

/**
 * This file is used to hold all the paths for external graphics files
 * The Max value referes to the total number of animations for each component
 * or the different types of graphics that each class can have. ie towers &
 * resources
 * @author Warren Voelkl, Karl Castillo
 */

#define PIX_CONTEXT_MENU_MAIN   QString("./img/buildmenu.png")
#define PIX_CONTEXT_MENU_RES    QString("./img/buildResources.png");
#define PIX_CONTEXT_MENU_T1     QString("./img/menuArrow.png")
#define PIX_CONTEXT_MENU_T2     QString("./img/menuCannon.png")
#define PIX_CONTEXT_MENU_T3     QString("./img/menuFlame.png")
#define PIX_CONTEXT_MENU_T4     QString("./img/menuTar.png")
#define PIX_CONTEXT_MENU_T5     QString("./img/menuFlak.png")
#define PIX_CONTEXT_MENU_MAX    7
#define PIX_PLAYER_0            QString("./img/player-stand.png")
#define PIX_PLAYER_1            QString("./img/player-move1.png")
#define PIX_PLAYER_2            QString("./img/player-move2.png")
#define PIX_PLAYER_3            QString("./img/player-move3.png")
#define PIX_PLAYER_4            QString("./img/player-move4.png")
#define PIX_PLAYER_5            QString("./img/player-move5.png")
#define PIX_PLAYER_6            QString("./img/player-move6.png")
#define PIX_PLAYER_MAX          7
#define PIX_PROJ_ARROW          QString("./img/arrowProjectile.png")
#define PIX_PROJ_ARROW_MAX      1
#define PIX_PROJ_TAR            QString("./img/tarProjectile.png")
#define PIX_PROJ_TAR_SPLAT_0    QString("./img/tarSplatter.png")
#define PIX_PROJ_TAR_SPLAT_1    QString("./img/tarSplatter2.png")
#define PIX_PROJ_TAR_MAX        4
#define PIX_PROJ_CANNON         QString("./img/cannonProjectile.png")
#define PIX_PROJ_CANNON_EXP_0   QString("./img/finalExp.png")
#define PIX_PROJ_CANNON_EXP_1   QString("./img/medExp.png")
#define PIX_PROJ_CANNON_EXP_2   QString("./img/smallExp.png")
#define PIX_PROJ_CANNON_MAX     4
#define PIX_PROJ_FIRE_0         QString("./img/flameProjectile1.png")
#define PIX_PROJ_FIRE_1         QString("./img/flameProjectile2.png")
#define PIX_PROJ_FIRE_2         QString("./img/medFlame.png")
#define PIX_PROJ_FIRE_3         QString("./img/smallFlame.png")
#define PIX_PROJ_FIRE_MAX       4
#define PIX_PROJ_FLAK           QString("./img/flakProjectile.png")
#define PIX_PROJ_FLAK_MAX       1
#define PIX_BUILDING_TOWER_25   QString("./img/build1.png")
#define PIX_BUILDING_TOWER_50   QString("./img/build2.png")
#define PIX_BUILDING_TOWER_75   QString("./img/build3.png")
#define PIX_BUILDING_TOWER_MAX  3
#define PIX_TOWER_ARROW         QString("./img/towerArrow.png")
#define PIX_TOWER_CANNON        QString("./img/towerCannon.png")
#define PIX_TOWER_TAR           QString("./img/towerTar.png")
#define PIX_TOWER_FLAME         QString("./img/towerFlame.png")
#define PIX_TOWER_FLAK          QString("./img/towerFlak.png")
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
#define PIX_NPC_PTERO_START     0
#define PIX_NPC_PTERO_0         QString("./img/ptero-1.png")
#define PIX_NPC_PTERO_1         QString("./img/ptero-2.png")
#define PIX_NPC_PTERO_2         QString("./img/ptero-3.png")
#define PIX_NPC_PTERO_3         QString("./img/ptero-4.png")
#define PIX_NPC_PTERO_MAX       4
#define PIX_NPC_PLEA_START      0
#define PIX_NPC_PLEA_0          QString("./img/plea-1.png")
#define PIX_NPC_PLEA_1          QString("./img/plea-2.png")
#define PIX_NPC_PLEA_MAX        2
#define PIX_NPC_MAMMOTH_START   0
#define PIX_NPC_MAMMOTH_0       QString("./img/mammoth1.png")
#define PIX_NPC_MAMMOTH_1       QString("./img/mammoth2.png")
#define PIX_NPC_MAMMOTH_MAX     2
#define PIX_NPC_ANKLY_START     0
#define PIX_NPC_ANKLY_0         QString("./img/anklyosaurus1.png")
#define PIX_NPC_ANKLY_1         QString("./img/anklyosaurus2.png")
#define PIX_NPC_ANKLY_2         QString("./img/anklyosaurus3.png")
#define PIX_NPC_ANKLY_MAX       3
#define PIX_NPC_BRONTO_START    0
#define PIX_NPC_BRONTO_0        QString("./img/Brontosaurus1.png")
#define PIX_NPC_BRONTO_1        QString("./img/Brontosaurus2.png")
#define PIX_NPC_BRONTO_2        QString("./img/Brontosaurus3.png")
#define PIX_NPC_BRONTO_3        QString("./img/Brontosaurus4.png")
#define PIX_NPC_BRONTO_4        QString("./img/Brontosaurus5.png")
#define PIX_NPC_BRONTO_MAX      5
#define PIX_NPC_SABER_START     0
#define PIX_NPC_SABER_0         QString("./img/fast1.png")
#define PIX_NPC_SABER_1         QString("./img/fast2.png")
#define PIX_NPC_SABER_MAX       2
#define PIX_NPC_TREX_START      0
#define PIX_NPC_TREX_0          QString("./img/trex1.png")
#define PIX_NPC_TREX_1          QString("./img/trex3.png")
#define PIX_NPC_TREX_2          QString("./img/trex2.png")
#define PIX_NPC_TREX_MAX        3
#define PIX_NPC_TRICERO_START   0
#define PIX_NPC_TRICERO_0       QString("./img/tri-1.png")
#define PIX_NPC_TRICERO_1       QString("./img/tri-2.png")
#define PIX_NPC_TRICERO_MAX     2

//ending animations for projectiles
#define PIX_END_CANNON_START    0
#define PIX_END_CANNON_0        QString("./img/smallExp.png");
#define PIX_END_CANNON_1        QString("./img/medExp.png");
#define PIX_END_CANNON_2        QString("./img/finalExp.png");
#define PIX_END_CANNON_MAX      3
#endif

