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
int recvApplication(int s, std::string& msg, struct sockaddr_in* addr = nullptr);
int sendApplication(int s, const std::string &msg, struct sockaddr_in *addr = nullptr);
int sendall(int s, const std::string& msg);

#endif //PROTEITESTTASK_HELPER_H
