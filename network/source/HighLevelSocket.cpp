//
// Created by danyal on 25.06.18.
//

#include <iostream>
#include "ApplicationProtocol.h"
#include "HighLevelSocket.h"

namespace network {

HighLevelSocket::HighLevelSocket(int port, __socket_type type)
{
   _sock = socket(AF_INET, type, 0);

   if (_sock < 0) {
      perror("socket");
//      _init = false;
      return;
   }

   _addr.sin_family = AF_INET;
   _addr.sin_port = htons(port);
   _addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
}

HighLevelSocket::HighLevelSocket(int sock) : _sock{sock}
{}


int HighLevelSocket::close() {
    ::close(_sock);
}

int HighLevelSocket::recvAll(std::string& msg, struct sockaddr_in* addr)
{
   int bytes_read;
   std::string temp;

   while (temp.size() < ApplicationProtocolMessage::getLenghtHeaderSize()) {
      if (addr != nullptr) {
         socklen_t size = sizeof(*addr);
         bytes_read = recvfrom(_sock, _buf, _buf_size, 0, (struct sockaddr*) addr, &size);
      }
      else {
         bytes_read = ::recv(_sock, _buf, _buf_size, 0);
      }
      if (bytes_read <= 0) return bytes_read;

      temp += std::string(_buf, bytes_read);
   }

   auto data_size = ApplicationProtocolMessage::getSize(temp);

   while (temp.size() < data_size) {
      if (addr != nullptr) {
         socklen_t size = sizeof(*addr);
         bytes_read = recvfrom(_sock, _buf, _buf_size, 0, (struct sockaddr*) addr, &size);
      }
      else {
         bytes_read = ::recv(_sock, _buf, _buf_size, 0);
      }
      if (bytes_read <= 0) return bytes_read;

      temp += std::string(_buf, bytes_read);
   }

   msg = temp;

   return msg.size();
}

int HighLevelSocket::sendall(const std::string& msg, struct sockaddr_in* addr)
{
   std::string temp;
   int max_udp_size = 65507;  //64kb - ip (20 )- udp(8) headers
   if (msg.size() > max_udp_size) {
      int chunk_count = msg.size() / max_udp_size;
      int send_position = 0;
      for (int i = 0; i < chunk_count; i++) {
         send_position = i * max_udp_size;
         auto n = sendMessage(msg.substr(send_position, max_udp_size), addr);
         if (n == -1) return n;
      }
      send_position += max_udp_size;
      auto n = sendMessage(msg.substr(send_position, msg.size() - send_position),
                           addr);
      if (n == -1) return n;
   }
   else {
      auto n = sendMessage(msg, addr);
      if (n == -1) return n;
   }
   return msg.size();
}

int HighLevelSocket::sendMessage(const std::string& msg, struct sockaddr_in* addr)
{
   int total = 0;
   int n;

   while (total < msg.size()) {
      if (addr != nullptr)
         n = sendto(_sock, msg.substr(total, msg.size() - total).c_str(),
                    msg.size() - total,
                    0,
                    (struct sockaddr*) addr, sizeof(*addr));
      else
         n = send(_sock, msg.substr(total, msg.size() - total).c_str(),
                  msg.size() - total,
                  0);

      if (n == -1) { break; }
      total += n;
   }
   return n == -1 ? -1 : 0;
}

int HighLevelSocket::getLowLevelSocket() const noexcept
{
   return _sock;
}

const struct sockaddr_in& HighLevelSocket::getSockAddr() const noexcept
{
   return _addr;
}

}

