//
// Created by danyal on 16.06.18.
//

#include "TCPSession.h"

#include <NetworkHelper.h>

namespace network {

TCPSession::TCPSession(HighLevelSocket &&sock) : _sock{sock} {}

std::string TCPSession::recv() {
    return recvApplication(_sock);
}

void TCPSession::send(const std::string &msg) {
    sendApplication(_sock, msg.c_str());
}
}