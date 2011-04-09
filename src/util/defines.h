#ifndef TD_DEFINES_H
#define TD_DEFINES_H

// TD Version
// Update this whenever an incompatible change is made, to ensure that features
// are matched between clients and the server
#define TD_VERSION      0x0001

// Network information
#define TD_PORT 26631
#define TD_GROUP QHostAddress("232.22.42.1")

// based on the number keys used to select the tower
#define TOWER_ARROW     49
#define TOWER_CANNON    50
#define TOWER_FLAME     51
#define TOWER_TAR       52
#define TOWER_FLAK      53

// how often the tower type can fire (in game ticks)
#define FIRE_INTERVAL_ARROW     45
#define FIRE_INTERVAL_CANNON    120
#define FIRE_INTERVAL_FLAME     300
#define FIRE_INTERVAL_TAR       90
#define FIRE_INTERVAL_FLAK      15

// a tower's range
#define RADIUS_ARROW    240
#define RADIUS_CANNON   150
#define RADIUS_FLAME    90
#define RADIUS_TAR      170
#define RADIUS_FLAK     300

//Tile action types specifying action for spacebar
#define TILE_REGULAR    0
#define TILE_BUILDABLE  1
#define TILE_BUILT      2
#define TILE_BASE       3
#define TILE_RESOURCE   4

// resources that can be picked up by the player
#define RESOURCE_NONE   0
#define RESOURCE_WOOD   1
#define RESOURCE_STONE  2
#define RESOURCE_BONE   3
#define RESOURCE_TAR    4

// time to harvest a resource (in game ticks)
#define HARVEST_COUNTDOWN   120

// NPC types
#define NPC_NORM    0
#define NPC_SLOW    1
#define NPC_FAST    2
#define NPC_FLY     3
#define NPC_BOSS    4

// Acceleration of NPC types
#define NPC_NORM_ACCEL  0.2  
#define NPC_SLOW_ACCEL  0.1  
#define NPC_FAST_ACCEL  0.3  
#define NPC_FLY_ACCEL   0.2  
#define NPC_BOSS_ACCEL  0.1  

// Deceleration of NPC types
#define NPC_NORM_DECEL  0.25  
#define NPC_SLOW_DECEL  0.15  
#define NPC_FAST_DECEL  0.4  
#define NPC_FLY_DECEL   0.25  
#define NPC_BOSS_DECEL  0.15  

// Maximum Velocity of NPC types
#define NPC_NORM_MAX_V  2  
#define NPC_SLOW_MAX_V  1  
#define NPC_FAST_MAX_V  4  
#define NPC_FLY_MAX_V   2  
#define NPC_BOSS_MAX_V  1  

//Effect durations for each type
#define NPC_PLAYER_TIME 20
#define TAR_TIME        10
#define BURN_TIME       5
#define ARROW_TIME      1
#define NO_TIME         0,false

//NPC path key for waypoints
//TODO: either take out or change to something generic
#define WP_TRICERATOPS  0
#define WP_ANKLYO       1
#define WP_SABERTOOTH   2
#define WP_COMPIES      3
#define WP_BRONTO       4
#define WP_TREX         5
#define WP_STEGO        6
#define WP_GODZILLA     7
#define WP_SOG_RAPTOR   8
#define WP_MAMMOTH      9
#define WP_PTERO        10

//Projectile types
#define PROJ_ARROW  0
#define PROJ_CANNON 1
#define PROJ_FIRE   2
#define PROJ_TAR    3
#define PROJ_FLAK   4

//Projectile Velocity
#define ARROW_VELOCITY  15
#define CANNON_VELOCITY 10
#define FIRE_VELOCITY   10
#define TAR_VELOCITY    10
#define FLAK_VELOCITY   15

// healthbar size, in pixels
#define HEALTHBAR_WIDTH     50
#define HEALTHBAR_HEIGHT    4

// resource collection bar size, in pixels
#define RESBAR_WIDTH    30
#define RESBAR_HEIGHT   6

// Temp defines pending a map object
#define MAP_ROWS 99
#define MAP_COLS 99

//temp defines
#define TILE_HEIGHT 48
#define TILE_WIDTH 48
#define TILE_SIZE 48

#endif

