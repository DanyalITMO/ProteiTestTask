//
// Created by danyal on 17.06.18.
//

#include "UDPServer.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstdio>
#include <iostream>
#include <Helper.h>

UDPServer::UDPServer(int port) : Server{port, SOCK_DGRAM}
{}


UDPIncomingMessage UDPServer::recv() {

    std::cout<<"udpserver recv"<<std::endl;
    struct sockaddr_in addr;
    std::string msg;
    int ret_code = recvApplication(_listener, msg, &addr);
    if (ret_code < 0)
        throw std::runtime_error{"It's impossible to correctly accept data"};

    UDPIncomingMessage udpSession{addr, _listener, msg};
    return udpSession;
}