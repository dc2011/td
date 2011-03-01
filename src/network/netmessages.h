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
    };

} /* end namespace td::network */
} /* end namespace td */

#endif
