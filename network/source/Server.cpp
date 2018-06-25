//
// Created by danyal on 17.06.18.
//

#include "Server.h"
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstdio>

namespace network {

    Server::Server(int port, __socket_type type) : _listener{port, type}{

        int yes = 1;
        if (setsockopt(_listener.getLowLevelSocket(), SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
            perror("setsockopt");
            _init = false;
            return;
        }

        if (bind(_listener.getLowLevelSocket(), (struct sockaddr *) &_listener.getSockAddr(), sizeof(_listener.getSockAddr())) == -1) {
            perror("bind");
            _init = false;
            return;
        }

    }

    bool Server::isInit() const noexcept {
        return _init;
    }

    Server::~Server() {
        _listener.close();
    }
}