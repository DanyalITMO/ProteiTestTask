//
// Created by danyal on 17.06.18.
//

#include "UDPServer.h"
#include <NetworkHelper.h>

namespace network {

UDPServer::UDPServer(int port) : Server{port, SOCK_DGRAM} {}

UDPIncomingMessage UDPServer::recv() {
    struct sockaddr_in addr;
    std::string msg = recvApplication(_listener, &addr);

    return UDPIncomingMessage{addr, _listener, msg};
}
}