//
// Created by danyal on 16.06.18.
//
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <regex>
#include <iostream>
#include "TCPServer.h"

#include <cstdio>
#include <TCPSession.h>

#include "TCPServer.h"
#include "TCPSession.h"

#include <optional>
#include <HighLevelSocket.h>

namespace network {

    TCPServer::TCPServer(int port) : Server{port, SOCK_STREAM} {
        if (listen(_listener.getLowLevelSocket(), 1)) {
            _init = false;
            return;
        }
    }

    TCPSession TCPServer::accept() {
        int sock;
        sock = ::accept(_listener.getLowLevelSocket(), nullptr, nullptr);
        if (sock < 0) {
            perror("accept");
            throw std::runtime_error{"can not accept. Try again"};//TODO handle this
        }


        return TCPSession{HighLevelSocket(sock)};
    }
}

