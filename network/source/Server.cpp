//
// Created by danyal on 17.06.18.
//

#include "Server.h"
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstdio>

namespace network {

    Server::Server(int port, __socket_type type) {
        struct sockaddr_in addr;

        _listener = socket(AF_INET, type, 0);
        if (_listener < 0) {
            perror("socket");
            _init = false;
            return;
        }

        int yes = 1;
        if (setsockopt(_listener, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
            perror("setsockopt");
            _init = false;
            return;
        }

        addr.sin_family = AF_INET;
        addr.sin_port = htons(port);
        addr.sin_addr.s_addr = htonl(INADDR_ANY);

        if (bind(_listener, (struct sockaddr *) &addr, sizeof(addr)) == -1) {
            perror("bind");
            _init = false;
            return;
        }

    }

    bool Server::isInit() const noexcept {
        return _init;
    }

    Server::~Server() {
        close(_listener);
    }
}