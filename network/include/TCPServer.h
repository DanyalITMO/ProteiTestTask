//
// Created by danyal on 16.06.18.
//

#ifndef SERVER_SOCKETWRAPPER_H
#define SERVER_SOCKETWRAPPER_H


#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "TCPSession.h"
#include "Server.h"

namespace network {

class TCPServer : public Server {
public:
    explicit TCPServer(int port);

    virtual ~TCPServer() = default;

    TCPSession accept();
};
}

#endif //SERVER_SOCKETWRAPPER_H
