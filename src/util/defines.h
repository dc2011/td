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

//Tile action types specifying action for spacebar
#define TILE_REGULAR    0
#define TILE_BUILDABLE  1
#define TILE_BUILT      2
#define TILE_BASE       3
#define TILE_RESOURCE   4

//NPC path key for waypoints
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

// Temp defines pending a map object
#define MAP_ROWS 99
#define MAP_COLS 99

//temp defines
#define TILE_HEIGHT 48
#define TILE_WIDTH 48

#endif

