#ifndef TD_DEFINES_H
#define TD_DEFINES_H

#include "gamedefs.h"

// TD Version
// Update this whenever an incompatible change is made, to ensure that features
// are matched between clients and the server
#define TD_VERSION      0x0003

// Network information
#define TD_PORT 26631
#define TD_GROUP(x) QHostAddress(QString("232.22.42.") + QString::number(x))

// milliseconds between game ticks
#define GAME_TICK_INTERVAL  30

// based on the number keys used to select the menu option
#define TOWER_ARROW         49
#define TOWER_CANNON        50
#define TOWER_FLAME         51
#define TOWER_TAR           52
#define TOWER_FLAK          53
#define TOWER_TYPE_MAX       5
#define UPGRADE_TOWER       49
#define SELL_TOWER          53
#define UPGRADE_SPEED       49
#define UPGRADE_HARVEST     50
#define UPGRADE_RECOVERY    51

// for player upgrade bitmask
#define PLAYER_NONE         0x0
#define PLAYER_SPEED        0x1
#define PLAYER_HARVEST      0x2
#define PLAYER_SPD_HAR      0x3
#define PLAYER_RECOVERY     0x4
#define PLAYER_SPD_REC      0x5
#define PLAYER_HAR_REC      0x6
#define PLAYER_ALL          0x7

#define MAX_TOWER_LEVEL         5

// context menu images
#define MENU_BASE               0
#define MENU_RESOURCES          1

// tower image indexes
#define MENU_TOWER_UPGRADE_ALL  1
#define MENU_TOWER_RESOURCES    2
#define MENU_TOWER_UPGRADE      7
#define MENU_TOWER_SELL         8

// tower types
// last group of 4 bits - tower level
// 2nd to last group of 4 bits - tower type
#define TOWER_ARROW_1   0x01
#define TOWER_ARROW_2   0x02
#define TOWER_ARROW_3   0x03
#define TOWER_ARROW_4   0x04
#define TOWER_ARROW_5   0x05
#define TOWER_CANNON_1  0x11
#define TOWER_CANNON_2  0x12
#define TOWER_CANNON_3  0x13
#define TOWER_CANNON_4  0x14
#define TOWER_CANNON_5  0x15
#define TOWER_FLAME_1   0x21
#define TOWER_FLAME_2   0x22
#define TOWER_FLAME_3   0x23
#define TOWER_FLAME_4   0x24
#define TOWER_FLAME_5   0x25
#define TOWER_TAR_1     0x31
#define TOWER_TAR_2     0x32
#define TOWER_TAR_3     0x33
#define TOWER_TAR_4     0x34
#define TOWER_TAR_5     0x35
#define TOWER_FLAK_1    0x41
#define TOWER_FLAK_2    0x42
#define TOWER_FLAK_3    0x43
#define TOWER_FLAK_4    0x44
#define TOWER_FLAK_5    0x45

// Current map to use
#define MAP      "bigmap"
#define MAP_TMX   QString("./maps/") + QString(MAP) + QString(".tmx")
#define MAP_NFO   QString("./maps/") + QString(MAP) + QString(".nfo")

// how often the tower type can fire (in game ticks)
#define FIRE_INTERVAL_ARROW     GameDefs::instance()->getValue<int>("FIRE_INTERVAL_ARROW")
#define FIRE_INTERVAL_ARROW_2   GameDefs::instance()->getValue<int>("FIRE_INTERVAL_ARROW_2")
#define FIRE_INTERVAL_ARROW_3   GameDefs::instance()->getValue<int>("FIRE_INTERVAL_ARROW_3")
#define FIRE_INTERVAL_ARROW_4   GameDefs::instance()->getValue<int>("FIRE_INTERVAL_ARROW_4")
#define FIRE_INTERVAL_ARROW_5   GameDefs::instance()->getValue<int>("FIRE_INTERVAL_ARROW_5")
#define FIRE_INTERVAL_CANNON    GameDefs::instance()->getValue<int>("FIRE_INTERVAL_CANNON")
#define FIRE_INTERVAL_CANNON_2  GameDefs::instance()->getValue<int>("FIRE_INTERVAL_CANNON_2")
#define FIRE_INTERVAL_CANNON_3  GameDefs::instance()->getValue<int>("FIRE_INTERVAL_CANNON_3")
#define FIRE_INTERVAL_CANNON_4  GameDefs::instance()->getValue<int>("FIRE_INTERVAL_CANNON_4")
#define FIRE_INTERVAL_CANNON_5  GameDefs::instance()->getValue<int>("FIRE_INTERVAL_CANNON_5")
#define FIRE_INTERVAL_FLAME     GameDefs::instance()->getValue<int>("FIRE_INTERVAL_FLAME")
#define FIRE_INTERVAL_FLAME_2   GameDefs::instance()->getValue<int>("FIRE_INTERVAL_FLAME_2")
#define FIRE_INTERVAL_FLAME_3   GameDefs::instance()->getValue<int>("FIRE_INTERVAL_FLAME_3")
#define FIRE_INTERVAL_FLAME_4   GameDefs::instance()->getValue<int>("FIRE_INTERVAL_FLAME_4")
#define FIRE_INTERVAL_FLAME_5   GameDefs::instance()->getValue<int>("FIRE_INTERVAL_FLAME_5")
#define FIRE_INTERVAL_TAR       GameDefs::instance()->getValue<int>("FIRE_INTERVAL_TAR")
#define FIRE_INTERVAL_TAR_2     GameDefs::instance()->getValue<int>("FIRE_INTERVAL_TAR_2")
#define FIRE_INTERVAL_TAR_3     GameDefs::instance()->getValue<int>("FIRE_INTERVAL_TAR_3")
#define FIRE_INTERVAL_TAR_4     GameDefs::instance()->getValue<int>("FIRE_INTERVAL_TAR_4")
#define FIRE_INTERVAL_TAR_5     GameDefs::instance()->getValue<int>("FIRE_INTERVAL_TAR_5")
#define FIRE_INTERVAL_FLAK      GameDefs::instance()->getValue<int>("FIRE_INTERVAL_FLAK")
#define FIRE_INTERVAL_FLAK_2    GameDefs::instance()->getValue<int>("FIRE_INTERVAL_FLAK_2")
#define FIRE_INTERVAL_FLAK_3    GameDefs::instance()->getValue<int>("FIRE_INTERVAL_FLAK_3")
#define FIRE_INTERVAL_FLAK_4    GameDefs::instance()->getValue<int>("FIRE_INTERVAL_FLAK_4")
#define FIRE_INTERVAL_FLAK_5    GameDefs::instance()->getValue<int>("FIRE_INTERVAL_FLAK_5")

// how long the flame lasts in ticks
#define FIRE_DURATION           GameDefs::instance()->getValue<int>("FIRE_DURATION")
#define FIRE_SCALE_TIME         GameDefs::instance()->getValue<int>("FIRE_SCALE_TIME")
#define FIRE_RELOAD             GameDefs::instance()->getValue<int>("FIRE_RELOAD ")

// reload times for animation (in milliseconds)
#define RELOAD_ARROW        GameDefs::instance()->getValue<int>("RELOAD_ARROW")
#define RELOAD_CANNON       GameDefs::instance()->getValue<int>("RELOAD_CANNON")
#define RELOAD_FIRE         FIRE_RELOAD * FIRE_DURATION
#define RELOAD_FLAK_SLOW    GameDefs::instance()->getValue<int>("RELOAD_FLAK_SLOW")
#define RELOAD_FLAK_MEDIUM  GameDefs::instance()->getValue<int>("RELOAD_FLAK_MEDIUM")
#define RELOAD_FLAK_FAST    GameDefs::instance()->getValue<int>("RELOAD_FLAK_FAST")

// a tower's range
#define RADIUS_ARROW    GameDefs::instance()->getValue<int>("RADIUS_ARROW")
#define RADIUS_ARROW_2  GameDefs::instance()->getValue<int>("RADIUS_ARROW_2")
#define RADIUS_ARROW_3  GameDefs::instance()->getValue<int>("RADIUS_ARROW_3")
#define RADIUS_ARROW_4  GameDefs::instance()->getValue<int>("RADIUS_ARROW_4")
#define RADIUS_ARROW_5  GameDefs::instance()->getValue<int>("RADIUS_ARROW_5")
#define RADIUS_CANNON   GameDefs::instance()->getValue<int>("RADIUS_CANNON")
#define RADIUS_CANNON_2 GameDefs::instance()->getValue<int>("RADIUS_CANNON_2")
#define RADIUS_CANNON_3 GameDefs::instance()->getValue<int>("RADIUS_CANNON_3")
#define RADIUS_CANNON_4 GameDefs::instance()->getValue<int>("RADIUS_CANNON_4")
#define RADIUS_CANNON_5 GameDefs::instance()->getValue<int>("RADIUS_CANNON_5")
#define RADIUS_FLAME    GameDefs::instance()->getValue<int>("RADIUS_FLAME")
#define RADIUS_FLAME_2  GameDefs::instance()->getValue<int>("RADIUS_FLAME_2")
#define RADIUS_FLAME_3  GameDefs::instance()->getValue<int>("RADIUS_FLAME_3")
#define RADIUS_FLAME_4  GameDefs::instance()->getValue<int>("RADIUS_FLAME_4")
#define RADIUS_FLAME_5  GameDefs::instance()->getValue<int>("RADIUS_FLAME_5")
#define RADIUS_TAR      GameDefs::instance()->getValue<int>("RADIUS_TAR")
#define RADIUS_TAR_2    GameDefs::instance()->getValue<int>("RADIUS_TAR_2")
#define RADIUS_TAR_3    GameDefs::instance()->getValue<int>("RADIUS_TAR_3")
#define RADIUS_TAR_4    GameDefs::instance()->getValue<int>("RADIUS_TAR_4")
#define RADIUS_TAR_5    GameDefs::instance()->getValue<int>("RADIUS_TAR_5")
#define RADIUS_FLAK     GameDefs::instance()->getValue<int>("RADIUS_FLAK")
#define RADIUS_FLAK_2   GameDefs::instance()->getValue<int>("RADIUS_FLAK_2")
#define RADIUS_FLAK_3   GameDefs::instance()->getValue<int>("RADIUS_FLAK_3")
#define RADIUS_FLAK_4   GameDefs::instance()->getValue<int>("RADIUS_FLAK_4")
#define RADIUS_FLAK_5   GameDefs::instance()->getValue<int>("RADIUS_FLAK_5")

//Tile action types specifying action for spacebar
#define TILE_REGULAR    0
#define TILE_BUILDABLE  1
#define TILE_BUILDING   2
#define TILE_BUILT      3
#define TILE_BASE       4
#define TILE_RESOURCE   5

//state of tower completion
#define TOWER_COMPLETE_25   0
#define TOWER_COMPLETE_50   1
#define TOWER_COMPLETE_75   2

// resources that can be picked up by the player
#define RESOURCE_NONE   -1
#define RESOURCE_WOOD   0
#define RESOURCE_STONE  1
#define RESOURCE_BONE   2
#define RESOURCE_TAR    3
#define RESOURCE_TYPE_MAX   4
#define RESOURCE_GEM        99

// time to harvest a resource (in game ticks)
#define HARVEST_COUNTDOWN           GameDefs::instance()->getValue<int>("HARVEST_COUNTDOWN")
#define HARVEST_COUNTDOWN_UPGRADE   GameDefs::instance()->getValue<int>("HARVEST_COUNTDOWN_UPGRADE")

// NPC types
#define NPC_NORM    0
#define NPC_SLOW    1
#define NPC_ARM     2
#define NPC_FAST    3
#define NPC_SWARM   4
#define NPC_FLY     5
#define NPC_BOSS    6

// Acceleration of NPC types
#define NPC_NORM_ACCEL  GameDefs::instance()->getValue<float>("NPC_NORM_ACCEL")
#define NPC_SLOW_ACCEL  GameDefs::instance()->getValue<float>("NPC_SLOW_ACCEL")
#define NPC_ARM_ACCEL   GameDefs::instance()->getValue<float>("NPC_ARM_ACCEL")
#define NPC_FAST_ACCEL  GameDefs::instance()->getValue<float>("NPC_FAST_ACCEL")
#define NPC_SWARM_ACCEL GameDefs::instance()->getValue<float>("NPC_SWARM_ACCEL")
#define NPC_FLY_ACCEL   GameDefs::instance()->getValue<float>("NPC_FLY_ACCEL")
#define NPC_BOSS_ACCEL  GameDefs::instance()->getValue<float>("NPC_BOSS_ACCEL")

// Deceleration of NPC types
#define NPC_NORM_DECEL  GameDefs::instance()->getValue<float>("NPC_NORM_DECEL")
#define NPC_SLOW_DECEL  GameDefs::instance()->getValue<float>("NPC_SLOW_DECEL")
#define NPC_ARM_DECEL   GameDefs::instance()->getValue<float>("NPC_ARM_DECEL")
#define NPC_FAST_DECEL  GameDefs::instance()->getValue<float>("NPC_FAST_DECEL")
#define NPC_SWARM_DECEL GameDefs::instance()->getValue<float>("NPC_SWARM_DECEL")
#define NPC_FLY_DECEL   GameDefs::instance()->getValue<float>("NPC_FLY_DECEL")
#define NPC_BOSS_DECEL  GameDefs::instance()->getValue<float>("NPC_BOSS_DECEL")

// Maximum Velocity of NPC types
#define NPC_NORM_MAX_V  GameDefs::instance()->getValue<float>("NPC_NORM_MAX_V")  
#define NPC_SLOW_MAX_V  GameDefs::instance()->getValue<float>("NPC_SLOW_MAX_V")
#define NPC_ARM_MAX_V   GameDefs::instance()->getValue<float>("NPC_ARM_MAX_V")
#define NPC_FAST_MAX_V  GameDefs::instance()->getValue<float>("NPC_FAST_MAX_V")
#define NPC_SWARM_MAX_V GameDefs::instance()->getValue<float>("NPC_SWARM_MAX_V")
#define NPC_FLY_MAX_V   GameDefs::instance()->getValue<float>("NPC_FLY_MAX_V")
#define NPC_BOSS_MAX_V  GameDefs::instance()->getValue<float>("NPC_BOSS_MAX_V")

//NPC health
#define NPC_NORM_HP     GameDefs::instance()->getValue<int>("NPC_NORM_HP")
#define NPC_SLOW_HP     GameDefs::instance()->getValue<int>("NPC_SLOW_HP")
#define NPC_ARM_HP      GameDefs::instance()->getValue<int>("NPC_ARM_HP")
#define NPC_FAST_HP     GameDefs::instance()->getValue<int>("NPC_FAST_HP")
#define NPC_SWARM_HP    GameDefs::instance()->getValue<int>("NPC_SWARM_HP")
#define NPC_FLY_HP      GameDefs::instance()->getValue<int>("NPC_FLY_HP")
#define NPC_BOSS_HP     GameDefs::instance()->getValue<int>("NPC_BOSS_HP")

//NPC dimensions
#define NPC_NORM_HEIGHT     25
#define NPC_NORM_WIDTH      90
#define NPC_SLOW_HEIGHT     30
#define NPC_SLOW_WIDTH      120
#define NPC_ARM_HEIGHT      35
#define NPC_ARM_WIDTH       70
#define NPC_FAST_HEIGHT     15
#define NPC_FAST_WIDTH      80
#define NPC_SWARM_HEIGHT    20
#define NPC_SWARM_WIDTH     50
#define NPC_FLY_HEIGHT      90
#define NPC_FLY_WIDTH       30
#define NPC_BOSS_HEIGHT     30
#define NPC_BOSS_WIDTH      100

//Player velocity
#define PLAYER_MAX_V GameDefs::instance()->getValue<float>("PLAYER_MAX_V")
#define PLAYER_UPGRADE_V GameDefs::instance()->getValue<float>("PLAYER_UPGRADE_V")

//effect types for operator==
#define EFFECT_NONE         0
#define EFFECT_NPCPLAYER    1
#define EFFECT_SLOW         2
#define EFFECT_FAST         3
// These 5 need to stay in the same block
#define EFFECT_ARROW        40
#define EFFECT_ARROW_2      41
#define EFFECT_ARROW_3      42
#define EFFECT_ARROW_4      43
#define EFFECT_ARROW_5      45
#define EFFECT_TAR          50
#define EFFECT_TAR_2        51
#define EFFECT_TAR_3        52
#define EFFECT_TAR_4        53
#define EFFECT_TAR_5        55
#define EFFECT_BURN         60
#define EFFECT_BURN_2       61
#define EFFECT_BURN_3       62
#define EFFECT_BURN_4       63
#define EFFECT_BURN_5       65
#define EFFECT_CANNON       70
#define EFFECT_CANNON_2     71
#define EFFECT_CANNON_3     72
#define EFFECT_CANNON_4     73
#define EFFECT_CANNON_5     75
#define EFFECT_FIRE         80
#define EFFECT_FIRE_2       81
#define EFFECT_FIRE_3       82
#define EFFECT_FIRE_4       83
#define EFFECT_FIRE_5       85
#define EFFECT_FLAK         90
#define EFFECT_FLAK_2       91
#define EFFECT_FLAK_3       92
#define EFFECT_FLAK_4       93
#define EFFECT_FLAK_5       95

//Effect health changes for each type
#define ARROW_DMG        GameDefs::instance()->getValue<int>("ARROW_DMG")
#define ARROW_DMG_2      GameDefs::instance()->getValue<int>("ARROW_DMG_2")
#define ARROW_DMG_3      GameDefs::instance()->getValue<int>("ARROW_DMG_3")
#define ARROW_DMG_4      GameDefs::instance()->getValue<int>("ARROW_DMG_4")
#define ARROW_DMG_5      GameDefs::instance()->getValue<int>("ARROW_DMG_5")
#define ARROW_ARM_DMG    GameDefs::instance()->getValue<int>("ARROW_ARM_DMG")
#define ARROW_ARM_DMG_2  GameDefs::instance()->getValue<int>("ARROW_ARM_DMG_2")
#define ARROW_ARM_DMG_3  GameDefs::instance()->getValue<int>("ARROW_ARM_DMG_3")
#define ARROW_ARM_DMG_4  GameDefs::instance()->getValue<int>("ARROW_ARM_DMG_4")
#define ARROW_ARM_DMG_5  GameDefs::instance()->getValue<int>("ARROW_ARM_DMG_5")
#define CANNON_DMG       GameDefs::instance()->getValue<int>("CANNON_DMG")
#define CANNON_DMG_2     GameDefs::instance()->getValue<int>("CANNON_DMG_2")
#define CANNON_DMG_3     GameDefs::instance()->getValue<int>("CANNON_DMG_3")
#define CANNON_DMG_4     GameDefs::instance()->getValue<int>("CANNON_DMG_4")
#define CANNON_DMG_5     GameDefs::instance()->getValue<int>("CANNON_DMG_5")
#define TAR_DMG          GameDefs::instance()->getValue<int>("TAR_DMG")
#define TAR_DMG_2        GameDefs::instance()->getValue<int>("TAR_DMG_2")
#define TAR_DMG_3        GameDefs::instance()->getValue<int>("TAR_DMG_3")
#define TAR_DMG_4        GameDefs::instance()->getValue<int>("TAR_DMG_4")
#define TAR_DMG_5        GameDefs::instance()->getValue<int>("TAR_DMG_5")
#define FLAK_DMG         GameDefs::instance()->getValue<int>("FLAK_DMG")
#define FLAK_DMG_2       GameDefs::instance()->getValue<int>("FLAK_DMG_2")
#define FLAK_DMG_3       GameDefs::instance()->getValue<int>("FLAK_DMG_3")
#define FLAK_DMG_4       GameDefs::instance()->getValue<int>("FLAK_DMG_4")
#define FLAK_DMG_5       GameDefs::instance()->getValue<int>("FLAK_DMG_5")
#define FIRE_DMG         GameDefs::instance()->getValue<int>("FIRE_DMG")
#define BURN_DMG         GameDefs::instance()->getValue<int>("BURN_DMG")
#define FIRE_DMG_2       GameDefs::instance()->getValue<int>("FIRE_DMG_2")
#define BURN_DMG_2       GameDefs::instance()->getValue<int>("BURN_DMG_2")
#define FIRE_DMG_3       GameDefs::instance()->getValue<int>("FIRE_DMG_3")
#define BURN_DMG_3       GameDefs::instance()->getValue<int>("BURN_DMG_3")
#define FIRE_DMG_4       GameDefs::instance()->getValue<int>("FIRE_DMG_4")
#define BURN_DMG_4       GameDefs::instance()->getValue<int>("BURN_DMG_4")
#define FIRE_DMG_5       GameDefs::instance()->getValue<int>("FIRE_DMG_5")
#define BURN_DMG_5       GameDefs::instance()->getValue<int>("BURN_DMG_5")

//Effect durations for each type
#define NPC_PLAYER_TIME GameDefs::instance()->getValue<int>("NPC_PLAYER_TIME")
#define NPC_PLAYER_TIME_UPGRADE GameDefs::instance()->getValue<int>("NPC_PLAYER_TIME_UPGRADE")
#define TAR_TIME        GameDefs::instance()->getValue<int>("TAR_TIME")
#define TAR_TIME_2      GameDefs::instance()->getValue<int>("TAR_TIME_2")
#define TAR_TIME_3      GameDefs::instance()->getValue<int>("TAR_TIME_3")
#define TAR_TIME_4      GameDefs::instance()->getValue<int>("TAR_TIME_4")
#define TAR_TIME_5      GameDefs::instance()->getValue<int>("TAR_TIME_5")
#define ARROW_TIME      GameDefs::instance()->getValue<int>("ARROW_TIME")
#define FLAK_TIME       GameDefs::instance()->getValue<int>("FLAK_TIME")
#define CANNON_TIME     GameDefs::instance()->getValue<int>("CANNON_TIME")
#define FIRE_TIME       GameDefs::instance()->getValue<int>("FIRE_TIME")
#define BURN_TIME       GameDefs::instance()->getValue<int>("BURN_TIME")
#define BURN_TIME_2     GameDefs::instance()->getValue<int>("BURN_TIME_2")
#define BURN_TIME_3     GameDefs::instance()->getValue<int>("BURN_TIME_3")
#define BURN_TIME_4     GameDefs::instance()->getValue<int>("BURN_TIME_4")
#define BURN_TIME_5     GameDefs::instance()->getValue<int>("BURN_TIME_5")
//DONT USE THIS MACRO UNLESS YOUR NAME IS DTRAIN
#define NO_TIME         0,false

//Projectile types
#define PROJ_ARROW      0
#define PROJ_ARROW_2    1
#define PROJ_ARROW_3    2
#define PROJ_ARROW_4    3
#define PROJ_ARROW_5    4
#define PROJ_CANNON     5
#define PROJ_CANNON_2   6
#define PROJ_CANNON_3   7
#define PROJ_CANNON_4   8
#define PROJ_CANNON_5   9
#define PROJ_FIRE       10
#define PROJ_FIRE_2     11
#define PROJ_FIRE_3     12
#define PROJ_FIRE_4     13
#define PROJ_FIRE_5     14
#define PROJ_TAR        15
#define PROJ_TAR_2      16
#define PROJ_TAR_3      17
#define PROJ_TAR_4      18
#define PROJ_TAR_5      19
#define PROJ_FLAK       20
#define PROJ_FLAK_2     21
#define PROJ_FLAK_3     22
#define PROJ_FLAK_4     23
#define PROJ_FLAK_5     24

//Projectile Dimensions
#define ARROW_HEIGHT    10
#define ARROW_WIDTH     48
#define CANNON_HEIGHT   120
#define CANNON_WIDTH    120
#define CANNON_HEIGHT_2 140
#define CANNON_WIDTH_2  140
#define CANNON_HEIGHT_3 160
#define CANNON_WIDTH_3  160
#define CANNON_HEIGHT_4 180
#define CANNON_WIDTH_4  180
#define CANNON_HEIGHT_5 200
#define CANNON_WIDTH_5  200
#define TAR_HEIGHT      48
#define TAR_WIDTH       48
#define TAR_HEIGHT_2    72
#define TAR_WIDTH_2     72
#define TAR_HEIGHT_3    72
#define TAR_WIDTH_3     72
#define TAR_HEIGHT_4    96
#define TAR_WIDTH_4     96
#define TAR_HEIGHT_5    120
#define TAR_WIDTH_5     120
#define FLAK_HEIGHT     40
#define FLAK_WIDTH      40
#define FLAK_HEIGHT_2   60
#define FLAK_WIDTH_2    60
#define FLAK_HEIGHT_3   80
#define FLAK_WIDTH_3    80
#define FLAK_HEIGHT_4   100
#define FLAK_WIDTH_4    100
#define FLAK_HEIGHT_5   120
#define FLAK_WIDTH_5    120

#define FLAME_WIDTH     90
#define FLAME_HEIGHT    30
#define FLAME_3_WIDTH   80
#define FLAME_3_HEIGHT  52

#define FLAME_2_SCALE   4 / 3
#define FLAME_3_SCALE   1.875


//Projectile Velocity
#define ARROW_VELOCITY  GameDefs::instance()->getValue<float>("ARROW_VELOCITY")
#define CANNON_VELOCITY GameDefs::instance()->getValue<float>("CANNON_VELOCITY")
#define FIRE_VELOCITY   GameDefs::instance()->getValue<float>("FIRE_VELOCITY")
#define TAR_VELOCITY    GameDefs::instance()->getValue<float>("TAR_VELOCITY")
#define FLAK_VELOCITY   GameDefs::instance()->getValue<float>("FLAK_VELOCITY")

// collectable misc
#define COLLECTABLE_VELOCITY    3
#define GEM_SIZE                0.6
#define RESOURCE_SIZE           0.8
#define TIME_TO_DISAPPEAR       600
#define FLICKER_RATE            9
#define FLICKER_POINT           (int) (TIME_TO_DISAPPEAR * 0.25) \
                              - (int) (TIME_TO_DISAPPEAR * 0.25) % FLICKER_RATE

// healthbar info (sizes are in pixels)
#define HEALTHBAR_WIDTH     50
#define HEALTHBAR_HEIGHT    4
#define DAMAGE_DISPLAY_TIME 50

// resource collection bar size, in pixels
#define RESBAR_WIDTH    30
#define RESBAR_HEIGHT   6

// tower requirements
#define COST_FLAK_WOOD    GameDefs::instance()->getValue<int>("COST_FLAK_WOOD")
#define COST_FLAK_STONE   GameDefs::instance()->getValue<int>("COST_FLAK_STONE")
#define COST_FLAK_BONE    GameDefs::instance()->getValue<int>("COST_FLAK_BONE")
#define COST_FLAK_OIL     GameDefs::instance()->getValue<int>("COST_FLAK_OIL")

#define COST_ARROW_WOOD   GameDefs::instance()->getValue<int>("COST_ARROW_WOOD")
#define COST_ARROW_STONE  GameDefs::instance()->getValue<int>("COST_ARROW_STONE")
#define COST_ARROW_BONE   GameDefs::instance()->getValue<int>("COST_ARROW_BONE")
#define COST_ARROW_OIL    GameDefs::instance()->getValue<int>("COST_ARROW_OIL")

#define COST_CANNON_WOOD  GameDefs::instance()->getValue<int>("COST_CANNON_WOOD")
#define COST_CANNON_STONE GameDefs::instance()->getValue<int>("COST_CANNON_STONE")
#define COST_CANNON_BONE  GameDefs::instance()->getValue<int>("COST_CANNON_BONE")
#define COST_CANNON_OIL   GameDefs::instance()->getValue<int>("COST_CANNON_OIL")

#define COST_TAR_WOOD     GameDefs::instance()->getValue<int>("COST_TAR_WOOD")
#define COST_TAR_STONE    GameDefs::instance()->getValue<int>("COST_TAR_STONE")
#define COST_TAR_BONE     GameDefs::instance()->getValue<int>("COST_TAR_BONE")
#define COST_TAR_OIL      GameDefs::instance()->getValue<int>("COST_TAR_OIL")

#define COST_FLAME_WOOD    GameDefs::instance()->getValue<int>("COST_FLAME_WOOD")
#define COST_FLAME_STONE   GameDefs::instance()->getValue<int>("COST_FLAME_STONE")
#define COST_FLAME_BONE    GameDefs::instance()->getValue<int>("COST_FLAME_BONE")
#define COST_FLAME_OIL     GameDefs::instance()->getValue<int>("COST_FLAME_OIL")

#define COST_TOWER_UPGRADE      GameDefs::instance()->getValue<int>("COST_TOWER_UPGRADE")
#define COST_TOWER_UPGRADE_2    GameDefs::instance()->getValue<int>("COST_TOWER_UPGRADE_2")
#define COST_TOWER_UPGRADE_3    GameDefs::instance()->getValue<int>("COST_TOWER_UPGRADE_3")
#define COST_TOWER_UPGRADE_4    GameDefs::instance()->getValue<int>("COST_TOWER_UPGRADE_4")

// tower upgrade costs
#define GEMS_TO_L2      GameDefs::instance()->getValue<int>("GEMS_TO_L2")
#define GEMS_TO_L3      GameDefs::instance()->getValue<int>("GEMS_TO_L3")
#define GEMS_TO_L4      GameDefs::instance()->getValue<int>("GEMS_TO_L4")
#define GEMS_TO_L5      GameDefs::instance()->getValue<int>("GEMS_TO_L5")

// player upgrade costs
#define GEMS_SPEED      GameDefs::instance()->getValue<int>("GEMS_SPEED")
#define GEMS_HARVEST    GameDefs::instance()->getValue<int>("GEMS_HARVEST")
#define GEMS_RECOVERY   GameDefs::instance()->getValue<int>("GEMS_RECOVERY")

//colors for tower colors
#define ARROW_COLOR     QColor(255,160,122)
#define CANNON_COLOR    QColor(255,0,255)
#define TAR_COLOR       QColor(0,0,255)
#define FLAME_COLOR     QColor(255,0,0)
#define FLAK_COLOR      QColor(0,255,0)

#endif
