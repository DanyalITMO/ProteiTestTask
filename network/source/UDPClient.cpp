//
// Created by danyal on 19.06.18.
//

#include "UDPClient.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstdio>
#include <string>

UDPClient::UDPClient(int port) {

    _sock= socket(AF_INET, SOCK_DGRAM, 0);
    if (_sock< 0) {
        perror("socket");
        return;
    }

    _addr.sin_family = AF_INET;
    _addr.sin_port = htons(port);
    _addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
}
void UDPClient::send(const std::string& msg)
{
    ::sendto(_sock, msg.c_str(), msg.size(), 0, (struct sockaddr *) &_addr, sizeof(_addr));
}

std::string UDPClient::recv()
{
    int _buf_size{1024};
    char _buf[_buf_size];
    struct sockaddr_in addr;//TODO add multiply connection
    socklen_t size = sizeof(_addr);
    auto bytes_read = recvfrom(_sock, _buf, _buf_size, 0, (struct sockaddr *) &_addr, &size);
//   if(bytes_read <= 0) return "";

    std::string t(_buf);

    return t;
}

UDPClient::~UDPClient()
{
    close(_sock);
}
