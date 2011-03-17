#ifndef _netmessages_
#define _netmessages_

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

        /** A bad version was detected. */
        kBadVersion     =   0x02,

        /** Server Assigns ID to a Player **/
        kAssignPlayerID =   0x03,

        /** Indicates a blocks of player objects corresponding to the players in
         * the current game.
         */
        kServerPlayers  =   0x04,

        /** Indicates a block of object updates sent from the server to client. */
        kServerUpdate   =   0x05,


        /* * * * * * * UDP MESSAGES MUST BE BELOW THIS DECLARATION * * * * * * */

        /** Used as a separator to indicate UDP messages. */
        kBLOCK_UDP      =   0x80,

        /** Indicates a position update for a player */
        kPlayerPosition =   0x80,
        
        /** tower requests an ID from server **/
        kRequestTowerID = 0x81,

        /** Server Assigns ID to an Tower **/
        kAssignTowerID = 0x82,
	
	/** Server has created an object, sending object state to player **/
	kServerCreateObj = 0x85,
        
        /** Server has destroyed an object, updating all clients **/
        kServerDestroyObj = 0x86,

        /** Object has been destroyed client-side, notifying server **/
        kClientDestroyObj = 0x87,    

	/** temp (maybe used later) **/
	kServObjectUpdate = 0x88,

    };

} /* end namespace td::network */
} /* end namespace td */

#endif
