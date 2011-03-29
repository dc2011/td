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
#define PIX_PROJECTILE_0        QString("./img/arrowProjectile.png")
#define PIX_PROJECTILE_1        QString("./img/tarCannonProjectile.png")
#define PIX_PROJECTILE_2        QString("./img/flameProjectile.png")
#define PIX_PROJECTILE_3        QString("./img/flakProjectile.png")
#define PIX_PROJECTILE_MAX      4
#define PIX_TOWER_ARROW         QString("./img/towerArrow.png")
#define PIX_TOWER_CANNON        QString("./img/towerCannon.png")
#define PIX_TOWER_TAR           QString("./img/towerTar.png")
#define PIX_TOWER_FLAME         QString("./img/towerFlame.png")
#define PIX_TOWER_FLAK          QString("./img/towerFlak.png")
#define PIX_TOWER_MAX           5
#define PIX_RESOURCE_LUMBER     QString("./img/wood.png")
#define PIX_RESOURCE_CRYSTAL    QString("./img/Crystal.png")
#define PIX_RESOURCE_OIL        QString("./img/Oil.png")
#define PIX_RESOURCE_TAR        QString("./img/Tar.png")
#define PIX_RESOURCE_STONE      QString("./img/Stone.png")
#define PIX_RESOURCE_IRON       QString("./img/Rock.png")
#define PIX_RESOURCE_MAX        6
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
//this final value will be total of all NPC pix maps
#define PIX_NPC_TOTAL           PIX_NPC_PTERO_MAX + PIX_NPC_PLEA_MAX
#endif

