//
// Created by danyal on 19.06.18.
//

#ifndef PROTEITESTTASK_HELPER_H
#define PROTEITESTTASK_HELPER_H

#include <UDPClient.h>
#include <TCPClient.h>
#include <memory>

enum class Protocol{
   TCP,
   UDP
};

Protocol stringToProtocol(std::string_view);
int recvAll(int s, std::string& packet);
int recvAll(int s, std::string& msg, struct sockaddr_in* addr);
int sendall(int s, const std::string& msg);

#endif //PROTEITESTTASK_HELPER_H
