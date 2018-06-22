//
// Created by danyal on 16.06.18.
//

#ifndef SERVER_SOCKETWRAPPER_H
#define SERVER_SOCKETWRAPPER_H


#include <memory>
#include "string_view"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "TCPSession.h"
#include <list>
#include "Server.h"
#include <optional>

class TCPServer : public Server{
public:
    explicit TCPServer(int port);
    virtual ~TCPServer();

    TCPSession accept();
//    std::optional<TCPSession> accept();
};


#endif //SERVER_SOCKETWRAPPER_H
