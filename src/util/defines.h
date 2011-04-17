#ifndef TD_DEFINES_H
#define TD_DEFINES_H

// TD Version
// Update this whenever an incompatible change is made, to ensure that features
// are matched between clients and the server
#define TD_VERSION      0x0002

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
#define FIRE_INTERVAL_ARROW     45
#define FIRE_INTERVAL_ARROW_2   35
#define FIRE_INTERVAL_ARROW_3   25
#define FIRE_INTERVAL_CANNON    120
#define FIRE_INTERVAL_CANNON_2  100
#define FIRE_INTERVAL_CANNON_3  80
#define FIRE_INTERVAL_FLAME     70
#define FIRE_INTERVAL_FLAME_2   60
#define FIRE_INTERVAL_FLAME_3   50
#define FIRE_INTERVAL_TAR       90
#define FIRE_INTERVAL_TAR_2     75
#define FIRE_INTERVAL_TAR_3     60
#define FIRE_INTERVAL_FLAK      15
#define FIRE_INTERVAL_FLAK_2    10
#define FIRE_INTERVAL_FLAK_3    5

// a tower's range
#define RADIUS_ARROW    240
#define RADIUS_ARROW_2  270
#define RADIUS_ARROW_3  300
#define RADIUS_CANNON   150
#define RADIUS_CANNON_2 180
#define RADIUS_CANNON_3 210
#define RADIUS_FLAME    90
#define RADIUS_FLAME_2  120
#define RADIUS_FLAME_3  150
#define RADIUS_TAR      170
#define RADIUS_TAR_2    200
#define RADIUS_TAR_3    230
#define RADIUS_FLAK     300
#define RADIUS_FLAK_2   330
#define RADIUS_FLAK_3   360

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
#define HARVEST_COUNTDOWN           60
#define HARVEST_COUNTDOWN_UPGRADE   45

// NPC types
#define NPC_NORM    0
#define NPC_SLOW    1
#define NPC_ARM     2
#define NPC_FAST    3
#define NPC_SWARM   4
#define NPC_FLY     5
#define NPC_BOSS    6

// Acceleration of NPC types
#define NPC_NORM_ACCEL  0.2  
#define NPC_SLOW_ACCEL  0.1  
#define NPC_ARM_ACCEL   0.1  
#define NPC_FAST_ACCEL  0.3  
#define NPC_SWARM_ACCEL 0.2  
#define NPC_FLY_ACCEL   0.2  
#define NPC_BOSS_ACCEL  0.1  

// Deceleration of NPC types
#define NPC_NORM_DECEL  0.25  
#define NPC_SLOW_DECEL  0.15  
#define NPC_ARM_DECEL   0.15  
#define NPC_FAST_DECEL  0.4  
#define NPC_SWARM_DECEL 0.25  
#define NPC_FLY_DECEL   0.25  
#define NPC_BOSS_DECEL  0.15  

// Maximum Velocity of NPC types
#define NPC_NORM_MAX_V  2  
#define NPC_SLOW_MAX_V  1
#define NPC_ARM_MAX_V   1
#define NPC_FAST_MAX_V  4
#define NPC_SWARM_MAX_V 2
#define NPC_FLY_MAX_V   2
#define NPC_BOSS_MAX_V  1

//NPC health
#define NPC_NORM_HP     100
#define NPC_SLOW_HP     200
#define NPC_ARM_HP      150
#define NPC_FAST_HP     75
#define NPC_SWARM_HP    50
#define NPC_FLY_HP      150
#define NPC_BOSS_HP     1000

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
#define PLAYER_MAX_V 5
#define PLAYER_UPGRADE_V 7.5

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
#define ARROW_DMG       -25
#define ARROW_DMG_2     -30
#define ARROW_DMG_3     -35
#define ARROW_DMG_4     -40
#define ARROW_DMG_5     -45
#define CANNON_DMG      -75
#define CANNON_DMG_2    -80
#define CANNON_DMG_3    -85
#define CANNON_DMG_4    -90
#define CANNON_DMG_5    -95
#define TAR_DMG         -10
#define TAR_DMG_2       -15
#define TAR_DMG_3       -20
#define TAR_DMG_4       -25
#define TAR_DMG_5       -30
#define FLAK_DMG        -10
#define FLAK_DMG_2      -20
#define FLAK_DMG_3      -30
#define FLAK_DMG_4      -40
#define FLAK_DMG_5      -50
#define FIRE_DMG        -10
#define BURN_DMG        -5
#define FIRE_DMG_2      -15
#define BURN_DMG_2      -10
#define FIRE_DMG_3      -20
#define BURN_DMG_3      -15
#define FIRE_DMG_4      -25
#define BURN_DMG_4      -20
#define FIRE_DMG_5      -30
#define BURN_DMG_5      -25

//Effect durations for each type
#define NPC_PLAYER_TIME 20
#define NPC_PLAYER_TIME_UPGRADE 5
#define TAR_TIME        100
#define TAR_TIME_2      130
#define TAR_TIME_3      160
#define TAR_TIME_4      190
#define TAR_TIME_5      220
#define ARROW_TIME      1
#define FLAK_TIME       1
#define CANNON_TIME     1
#define FIRE_TIME       1
#define BURN_TIME       90
#define BURN_TIME_2     120
#define BURN_TIME_3     150
#define BURN_TIME_4     180
#define BURN_TIME_5     210
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
#define ARROW_VELOCITY  15
#define CANNON_VELOCITY 10
#define FIRE_VELOCITY   6
#define TAR_VELOCITY    10
#define FLAK_VELOCITY   15

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
#define COST_FLAK_WOOD    0
#define COST_FLAK_STONE   1
#define COST_FLAK_BONE    0
#define COST_FLAK_OIL     0

#define COST_ARROW_WOOD   0
#define COST_ARROW_STONE  1
#define COST_ARROW_BONE   0
#define COST_ARROW_OIL    0

#define COST_CANNON_WOOD  0
#define COST_CANNON_STONE 1
#define COST_CANNON_BONE  0
#define COST_CANNON_OIL   0

#define COST_TAR_WOOD     0
#define COST_TAR_STONE    1
#define COST_TAR_BONE     0
#define COST_TAR_OIL      0

#define COST_FLAME_WOOD    0
#define COST_FLAME_STONE   1
#define COST_FLAME_BONE    0
#define COST_FLAME_OIL     0
#define COST_TOWER_UPGRADE      1
#define COST_TOWER_UPGRADE_2    2

//colors for tower colors
#define ARROW_COLOR     QColor(255,160,122)
#define CANNON_COLOR    QColor(255,0,255)
#define TAR_COLOR       QColor(0,0,255)
#define FLAME_COLOR     QColor(255,0,0)
#define FLAK_COLOR      QColor(0,255,0)

#endif
