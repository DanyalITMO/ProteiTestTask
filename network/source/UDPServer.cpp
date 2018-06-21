//
// Created by danyal on 17.06.18.
//

#include "UDPServer.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstdio>

UDPServer::UDPServer(int port) : Server{port, SOCK_DGRAM}
{}

UDPIncomingMessage UDPServer::recv()
{
   const int _buf_size = 2 + 65536;
   char _buf[_buf_size];
   struct sockaddr_in addr;//TODO add multiply connection
   socklen_t size = sizeof(addr);
   auto bytes_read = recvfrom(_listener, _buf, _buf_size, 0, (struct sockaddr *) &addr, &size);
//   if(bytes_read <= 0) return "";

   std::string t(_buf);

   UDPIncomingMessage udpSession{addr, _listener, t};
   return udpSession;
}
