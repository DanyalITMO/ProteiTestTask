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
#include <NetworkHelper.h>
#include <ApplicationProtocol.h>

namespace network {

TCPSession::TCPSession(HighLevelSocket&& sock) : _sock{sock}
{}

std::string TCPSession::recv()
{
   return recvApplication(_sock);
}

void TCPSession::send(const std::string& msg)
{
   sendApplication(_sock, msg.c_str());
}
}