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

class TCPServer : public Server{
public:
    explicit TCPServer(int port);
    virtual ~TCPServer();
    std::shared_ptr<TCPSession> accept();

private:
    std::list<std::shared_ptr<TCPSession>> _sessions;
};


#endif //SERVER_SOCKETWRAPPER_H
