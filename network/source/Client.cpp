//
// Created by danyal on 19.06.18.
//

#include "Client.h"

//#include "UDPClient.h"
#include <NetworkHelper.h>

namespace network {

Client::Client(int port, __socket_type type) : _sock{port, type} {
    if (connect(_sock.getLowLevelSocket(), (struct sockaddr *) &_sock.getSockAddr(), sizeof(_sock.getSockAddr())) < 0) {
        perror("Client::Client connect");
        _init = false;
        return;
    }
}

void Client::send(const std::string &msg) {
    sendApplication(_sock, msg.c_str());
}

std::string Client::recv() {
    return recvApplication(_sock);
}

Client::~Client() {
    _sock.close();
}

bool Client::isInit() const noexcept {
    return _init;
}
}