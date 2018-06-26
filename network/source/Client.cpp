//
// Created by danyal on 19.06.18.
//

#include "Client.h"

//#include "UDPClient.h"
#include <NetworkHelper.h>

namespace network {

    Client::Client(int port, __socket_type type) : _sock{port, type} {
        if (connect(_sock.getLowLevelSocket(), (struct sockaddr *) &_sock.getSockAddr(), sizeof(_sock.getSockAddr())) < 0) {
            perror("connect");
            _init = false;
            return;
        }
    }

    void Client::send(const std::string &msg) {
        int ret_code = sendApplication(_sock, msg.c_str());

        if (ret_code < 0) {
            perror("send");
            throw std::runtime_error{"It's impossible to correctly accept data"};
        }
    }

    std::string Client::recv() {
        std::string msg;
        int ret_code = recvApplication(_sock, msg);
        if (ret_code < 0)
            throw std::runtime_error{"It's impossible to correctly accept data"};
        return msg;
    }

    Client::~Client() {
        _sock.close();
    }

    bool Client::isInit() const noexcept {
        return _init;
    }
}