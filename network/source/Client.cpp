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
#include <Helper.h>
#include "ApplicationProtocol.h"

Client::Client(int port, __socket_type type)
{
   _sock = socket(AF_INET, type, 0);

   if (_sock < 0) {
      perror("socket");
      _init = false;
      return;
   }

   struct sockaddr_in addr;
   addr.sin_family = AF_INET;
   addr.sin_port = htons(port);
   addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

   if (connect(_sock, (struct sockaddr*) &addr, sizeof(addr)) < 0) {
      perror("connect");
      _init = false;
      return;
   }
}

void Client::send(const std::string& msg)
{
   int ret_code = sendApplication(_sock, msg.c_str());

   if(ret_code < 0)
   {
      perror("send");
      throw std::runtime_error{"It's impossible to correctly accept data"};
   }
}

std::string Client::recv()
{
   std::string msg;
   int ret_code = recvApplication(_sock, msg);
   if(ret_code < 0)
      throw std::runtime_error{"It's impossible to correctly accept data"};
   return msg;
}

Client::~Client()
{
   close(_sock);
}

bool Client::isInit() const noexcept
{
   return _init;
}
