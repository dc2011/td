#ifndef _netmessages_
#define _netmessages_

#define TD_PORT 26631
#define TD_GROUP QHostAddress("232.22.42.1")

namespace td {
namespace network {

    enum {
        /** Used as a separator to indicate TCP messages. */
        kBLOCK_TCP      =   0x00,

        /** Indicates a block of object updates sent from the server to client. */
        kServerUpdate   =   0x00,


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
	
	/** Server has created an object, sending object state to player **/
	kServerCreateObj = 0x85,
        
        /** Server has destroyed an object, updating all clients **/
        kServerDestroyObj = 0x86,

        /** Object has been destroyed client-side, notifying server **/
        kClientDestroyObj = 0x87,    
	
	kServObjectUpdate = 0x88,

    };

} /* end namespace td::network */
} /* end namespace td */

#endif
