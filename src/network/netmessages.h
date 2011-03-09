#ifndef _netmessages_
#define _netmessages_

#define TD_PORT 26631
#define TD_GROUP QHostAddress("232.22.42.1")

namespace td {
namespace network {

    enum {
        /** Used as a separator to indicate TCP messages. */
        kBLOCK_TCP      =   0x00,

        /**
         * Requests to join the lobby server or indicates the number of players
         * connected to the lobby.
         * */
        kLobbyWelcome   =   0x00,

        /** Indicates or requests that the game starts. */
        kLobbyStartGame =   0x01,

        kBadVersion     =   0x02,

        /** Indicates a block of object updates sent from the server to client. */
        kServerUpdate   =   0x03,


        /* * * * * * * UDP MESSAGES MUST BE BELOW THIS DECLARATION * * * * * * */

        /** Used as a separator to indicate UDP messages. */
        kBLOCK_UDP      =   0x80,

        /** Indicates a position update for a player */
        kPlayerPosition =   0x80,
        
        /** tower requests an ID from server **/
        kRequestTowerID = 0x81,

        /** Server Assigns ID to an Tower **/
        kAssignTowerID = 0x82,
	
        /** Player Requests and ID from server **/
        kRequestPlayerID = 0x83,

        /** Server Assigns ID to a Player **/
        kAssignPlayerID = 0x84,

    };

} /* end namespace td::network */
} /* end namespace td */

#endif
