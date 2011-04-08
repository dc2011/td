#ifndef _netmessages_
#define _netmessages_

namespace td {
namespace network {

    enum {
        /** Used as a separator to indicate TCP messages. */
        kBLOCK_TCP      =   0x00,

        /**
         * Requests to join the lobby server or indicates the number of
         * players connected to the lobby.
         * See Also: @ref lobbywelcome
         * */
        kLobbyWelcome   =   0x00,

        /**
         * Indicates or requests that the game starts.
         * See Also: @ref lobbystartgame
         * */
        kLobbyStartGame =   0x01,

        /**
         * A bad version was detected.
         * See Also: @ref badversion
         * */
        kBadVersion     =   0x02,

        /**
         * Server assignment of a GameObject ID to a client's player.
         * See Also: @ref assignplayerid
         */
        kAssignPlayerID =   0x03,

        /**
         * Indicates a blocks of player objects corresponding to the
         * players in the current game.
         * See Also: @ref serverplayers
         */
        kServerPlayers  =   0x04,

        /**
         * Indicates a block of object updates sent from the server to client.
         * See Also: @ref serverupdate
         */
        kServerUpdate   =   0x05,

        /**
         * Indicates a deletion of a game object, sent from the server to clients.
         * See Also: @ref destroyobject
         */
        kDestroyObject  =   0x06,

        /**
         * Indicates a request to build a tower. This includes the player
         * ID of the player that built the tower.
         * See Also: @ref buildtower
         */
        kBuildTower     =   0x07,

        /**
         * Indicates the last digit of the multicast IP address.
         * See Also: @ref multicastip
         */
        kMulticastIP    =   0x08,


        /* * * * * * * UDP MESSAGES MUST BE BELOW THIS DECLARATION * * * * * * */

        /** Used as a separator to indicate UDP messages. */
        kBLOCK_UDP      =   0x80,

        /** Indicates a position update for a player */
        kPlayerPosition =   0x80,

        /** Indicates a position update for an NPC wave */
        kNPCWave        =   0x81,
        
	    /** Server has created an object, sending object state to player **/
	    kServerCreateObj = 0x85,
        
        /** Server has destroyed an object, updating all clients **/
        kServerDestroyObj = 0x86,

        /** Object has been destroyed client-side, notifying server **/
        kClientDestroyObj = 0x87,    

	    /** temp (maybe used later) **/
	    kServObjectUpdate = 0x88,

        /** Server requires clients to play a SFX **/
        kPlaySfx = 0x89,
    };

} /* end namespace td::network */
} /* end namespace td */

#endif

/** @page netmsgs Network Messages
 * This page describes the data format of the various network messages.
 *
 * @section lobbywelcome Lobby Welcome Message
 * This message differs between the client and the server.
 *
 * The client sends this message initially to join a waiting queue in the
 * game lobby.
 * The client format is as follows:
 * @code
 *    // The message type
 *  byte msgType = td::network::kLobbyWelcome
 *    // The client version number
 *  short version
 *    // The length of the nickname string
 *  byte nickname_length
 *    // The actual nickname string
 *  char[nickname_length] nickname
 * @endcode
 *
 * The server replies with this message every time a new client joins the
 * lobby, to inform all other clients of the current number of connected
 * players.
 * The server format is as follows:
 * @code
 *    // The message type
 *  byte msgType = td::network::kLobbyWelcome
 *    // The number of connected clients in the lobby
 *  int num_clients
 * @endcode
 *
 * @section lobbystartgame Lobby Start Game Message
 * This is sent by a client to the lobby to start a game with all the
 * current lobby players. The server sends this message to all connected
 * clients to inform them of the game starting.
 * @code
 *    // The message type
 *  byte msgType = td::network::kLobbyStartGame
 * @endcode
 *
 * @section badversion Bad Version Message
 * This is sent by the lobby server to a client if the client version does not
 * match the server version.
 * @code
 *    // The message type
 *  byte msgType = td::network::kBadVersion
 * @endcode
 *
 * @section assignplayerid Assign Player ID Message
 * This is sent individually from the server to each client to inform the client
 * of their local player's GameObject ID.
 * @code
 *    // The message type
 *  byte msgType = td::network::kAssignPlayerID
 *    // The GameObject ID of the player
 *  int playerID
 * @endcode
 *
 * @section serverplayers Server Players Message
 * This message contains the initial state of every game player and is sent to
 * all clients, allowing them to initialize the game with proper player
 * information.
 * @code
 *    // The message type
 *  byte msgType = td::network::kServerPlayers
 *    // The number of players
 *  byte playerCount
 *    // The actual player states, read with td::Player::networkRead
 *  td::Player[playerCount] players
 * @endcode
 *
 * @section serverupdate Server Update Message
 * This message is essentially just a block of serialized object states, sent by
 * the server to all clients on a timer.
 * @code
 *    // The message type
 *  byte msgType = td::network::kServerUpdate
 *    // The number of objects
 *  byte objCount;
 *    // The serialized object states, read with td::GameObject::networkRead
 *  td::GameObject[objCount] objects
 * @endcode
 *
 * @section destroyobject Destroy Object Message
 * This message is sent from the server to clients to inform them of the
 * destruction of the object with the specified ID.
 * @code
 *    // The message type
 *  byte msgType = td::network::kDestroyObject
 *    // The ID of the object to be destroyed
 *  int objID
 * @endcode
 *
 * @section buildtower Build Tower Message
 * This message is sent from a client to the server to request that a
 * tower be built.
 * @code
 *    // The message type
 *  byte msgType = td::network::kBuildTower
 *    // The ID of the player building the tower
 *  int playerID
 *    // The type of tower being build
 *  int towerType
 *    // The X position of the tower
 *  float posX
 *    // The Y position of the tower
 *  float posY
 * @endcode
 *
 * @section multicastip Multicast IP Message
 * This message informs clients of the multicast address for a game session.
 * @code
 *    // The message type
 *  byte msgType = td::network::kMulticastIP
 *    // The final octet of the multicast address
 *  byte finalOctet
 * @endcode
 *
 * @section playsfx Play SFX Message
 * This message is generated by an event on the server that requires that the 
 * clients play a SFX in response.
 * @code
 *    // The message type
 *  byte msgType = td::network::kPlaySfx
 *    // The type of SFX (sfx or ntf)
 *  int type;
 *    // The length of the SFX filename
 *  int filenameLength
 *    // The actual filename string
 *  char[nicknameLength] filename
 * @endcode
 */
