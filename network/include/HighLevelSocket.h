//
// Created by danyal on 25.06.18.
//

#ifndef PROTEITESTTASK_HIGHLEVELSOCKET_H
#define PROTEITESTTASK_HIGHLEVELSOCKET_H


#include "HighLevelSocket.h"
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstdio>
#include <string>
namespace network {

class HighLevelSocket {
public:

   explicit HighLevelSocket(int sock);
   HighLevelSocket(int port, __socket_type type);

   HighLevelSocket(const HighLevelSocket&) = default;
   HighLevelSocket& operator=(const HighLevelSocket&) = default;

   ~HighLevelSocket() = default;

   int close();

   int getLowLevelSocket() const noexcept;
   const struct sockaddr_in& getSockAddr() const noexcept;

    int recvAll(std::string& msg, struct sockaddr_in* addr = nullptr);
    int sendall(const std::string& msg, struct sockaddr_in* addr = nullptr);

private:
    int sendMessage(const std::string& msg, struct sockaddr_in* addr = nullptr);

   constexpr static int _buf_size{65536};
   char _buf[_buf_size];

   int _sock;
   struct sockaddr_in _addr;

};
}


#endif //PROTEITESTTASK_HIGHLEVELSOCKET_H
