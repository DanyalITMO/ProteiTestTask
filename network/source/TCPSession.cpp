//
// Created by danyal on 16.06.18.
//

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "TCPSession.h"
#include <unistd.h>



#include <cstdlib>
#include <iostream>
#include <Helper.h>
#include <ApplicationProtocol.h>

TCPSession::TCPSession(int sock) : _sock{sock}
{}

std::string TCPSession::recv() {
    std::string msg;
    int ret_code = recvAll(_sock, msg);
    if(ret_code < 0)
         throw std::runtime_error{"It's impossible to correctly accept data"};
    return msg;
}

void TCPSession::send(std::string msg) {
    ApplicationProtocolMessage ap{msg};
    auto p = ap.getPacket();
    ::send(_sock, p.c_str(), p.size(), 0);}

TCPSession::~TCPSession() {
    close(_sock);
}