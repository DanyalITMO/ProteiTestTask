//
// Created by danyal on 17.06.18.
//

#ifndef PROTEITESTTASK_UDPSERVER_H
#define PROTEITESTTASK_UDPSERVER_H

#include "Server.h"
#include "UDPIncomingMessage.h"

namespace network {

class UDPServer : public Server {
public:
    explicit UDPServer(int port);

    UDPIncomingMessage recv();

private:
    const int _buf_size{1024};
};

}

#endif //PROTEITESTTASK_UDPSERVER_H
