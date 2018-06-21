//
// Created by danyal on 19.06.18.
//

#include "Client.h"

#include "UDPClient.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstdio>
#include <string>

Client::Client(int port, __socket_type type) {

    _sock= socket(AF_INET, type, 0);
    if (_sock< 0) {
        perror("socket");
        return;
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    if (connect(_sock, (struct sockaddr *) &addr, sizeof(addr)) < 0) {
        perror("connect");
        exit(2);
    }
}
void Client::send(const std::string& msg)
{
    ::send(_sock, msg.c_str(), msg.size(), 0);
}

std::string Client::recv()
{
    int _buf_size{1024};
    char _buf[_buf_size];
    auto bytes_read = ::recv(_sock, _buf, _buf_size, 0);
//   if(bytes_read <= 0) return "";

    std::string t(_buf);

    return t;
}

Client::~Client()
{
    close(_sock);
}
