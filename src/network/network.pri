NETWORK_HDRS += ./network/stream.h

NETWORK_SRCS += ./network/stream.cpp

# Client-side headers and sources
NETWORK_HDRS_C +=   $$NETWORK_HDRS \
                    ./network/netclient.h

NETWORK_SRCS_C +=   $$NETWORK_SRCS \
                    ./network/netclient.cpp

# Server-side headers and sources
NETWORK_HDRS_S +=   $$NETWORK_HDRS \
                    ./network/lobbyserver.h \
                    ./network/netserver.h

NETWORK_SRCS_S +=   $$NETWORK_SRCS \
                    ./network/lobbyserver.cpp \
                    ./network/netserver.cpp
