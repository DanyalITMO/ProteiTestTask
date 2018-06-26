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
      _init = false;
      return;
   }

   _addr.sin_family = AF_INET;
   _addr.sin_port = htons(port);
   _addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
}

HighLevelSocket::HighLevelSocket(int sock) : _sock{sock}
{}

int HighLevelSocket::close()
{
   int ret = ::close(_sock);
   if (ret < 0)
      perror("HighLevelSocket::close()");
   return ret;
}

std::string HighLevelSocket::recvMessage(std::size_t min_size, struct sockaddr_in* addr)
{
   std::string ret;
   ssize_t bytes_read;

   while (ret.size() < min_size) {
      if (addr != nullptr) {
         socklen_t size = sizeof(*addr);
         bytes_read = recvfrom(_sock, _buf, _buf_size, 0, (struct sockaddr*) addr, &size);
      }
      else {
         bytes_read = ::recv(_sock, _buf, _buf_size, 0);
      }
      if (bytes_read <= 0) {
         perror("HighLevelSocket::recvMessage");
         throw std::runtime_error{"Сan not receive the whole package"};
      }

      ret += std::string(_buf, bytes_read);
   }

   return ret;
}

std::string HighLevelSocket::recvAll(struct sockaddr_in* addr)
{
   auto packet = recvMessage(ApplicationProtocolMessage::getLenghtHeaderSize(), addr);

   auto data_size = ApplicationProtocolMessage::getSize(packet);

   if(packet.size() < data_size + ApplicationProtocolMessage::getLenghtHeaderSize())
      packet += recvMessage(data_size + ApplicationProtocolMessage::getLenghtHeaderSize() - packet.size(), addr);

   return packet;
}


void HighLevelSocket::sendall(const std::string& msg, struct sockaddr_in* addr)
{
   int n = 1;
   std::size_t max_udp_size = 65507;  //64kb - ip (20 )- udp(8) headers

   auto chunk_count = static_cast<std::size_t>(msg.size() / max_udp_size);
   for (std::size_t i = 0; i < chunk_count && n > 0; i++) {
      n = sendMessage(msg.substr(i * max_udp_size, max_udp_size), addr);
   }
   n = sendMessage(msg.substr(chunk_count * max_udp_size, msg.size() - (chunk_count * max_udp_size)),
                   addr);
   if (n == -1) {
      perror("HighLevelSocket::sendAll");
      throw std::runtime_error{"Сan not send the whole package"};
   }
}

int HighLevelSocket::sendMessage(const std::string& msg, struct sockaddr_in* addr)
{
   std::size_t total = 0;
   ssize_t n;

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

bool HighLevelSocket::init() const noexcept
{
   return _init;
}

}

