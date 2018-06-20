//
// Created by danyal on 19.06.18.
//

#include "TCPClient.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <iostream>

TCPClient::TCPClient(int port) {
    struct sockaddr_in addr;

    _sock = socket(AF_INET, SOCK_STREAM, 0);
    if (_sock < 0) {
        perror("socket");
        exit(1);
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(3425); // или любой другой порт...
    addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    if (connect(_sock, (struct sockaddr *) &addr, sizeof(addr)) < 0) {
        perror("connect");
        exit(2);
    }

}

void TCPClient::send(const std::string &msg) {
    ::send(_sock, msg.c_str(), msg.size(), 0);

}

std::string TCPClient::recv() {
    int buf_size{1024};
    char buf[buf_size];

    ::recv(_sock, buf, buf_size, 0);
    return std::string(buf);
}

TCPClient::~TCPClient() {
    close(_sock);
}
