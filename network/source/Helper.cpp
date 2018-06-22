//
// Created by danyal on 19.06.18.
//

#include <ApplicationProtocol.h>
#include "Helper.h"

Protocol stringToProtocol(std::string_view str)
{
   if (str == "UDP")
      return Protocol::UDP;
   else if (str == "TCP")
      return Protocol::TCP;
   else
      throw std::runtime_error{"Incorrect protocol type"};
}



int sendall(int s, const std::string& msg)
{
   int total = 0;
   int n;

   while (total < msg.size()) {
      n = send(s, msg.substr(total, msg.size() - total).c_str(), msg.size() - total, 0);
      if (n == -1) { break; }
      total += n;
   }
   return n == -1 ? -1 : 0;
}

int recvAll(int s, std::string& msg)
{
   int _buf_size{1024};
   char _buf[_buf_size];
   auto bytes_read = ::recv(s, _buf, _buf_size, 0);

   if(bytes_read <= 0) return bytes_read;

   std::string packet(_buf, bytes_read);

   ApplicationProtocolMessage ap{"."};
   ap.setPacket(packet);

   msg = ap.getData();

   return msg.size();
}


int recvAll(int s, std::string& msg, struct sockaddr_in* addr)
{
    int _buf_size{1024};
    char _buf[_buf_size];

    socklen_t size = sizeof(*addr);
    auto bytes_read = recvfrom(s, _buf, _buf_size, 0, (struct sockaddr *) addr, &size);

    if(bytes_read <= 0) return bytes_read;

    std::string packet(_buf, bytes_read);

    ApplicationProtocolMessage ap{"."};
    ap.setPacket(packet);

    msg = ap.getData();

    return msg.size();
}
// здесь количество действительно посланных байт
// вернуть -1 при сбое, 0 при успехе