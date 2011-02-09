include(./td.pri)

include(./server/server.pri)
include(./network/network.pri)

HEADERS += $$SERVER_HDRS $$NETWORK_HDRS
SOURCES += $$SERVER_SRCS $$NETWORK_SRCS
