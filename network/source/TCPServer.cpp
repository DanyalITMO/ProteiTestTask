//
// Created by danyal on 16.06.18.
//
#include <unistd.h>
#include <regex>
#include "TCPServer.h"

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
            perror("TCPServer::accept");
            throw std::runtime_error{"Session can not be created"};//TODO handle this
        }


        return TCPSession{HighLevelSocket(sock)};
    }
}

