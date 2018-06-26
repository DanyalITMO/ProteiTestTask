//
// Created by danyal on 19.06.18.
//

#include <ApplicationProtocol.h>
#include "NetworkHelper.h"
#include "HighLevelSocket.h"

namespace network {

Protocol stringToProtocol(std::string_view str)
{
   if (str == "UDP")
      return Protocol::UDP;
   else if (str == "TCP")
      return Protocol::TCP;
   else
      throw std::runtime_error{"Incorrect protocol type"};
}

std::string recvApplication(HighLevelSocket& s, struct sockaddr_in* addr)
{
   std::string packet_str = s.recvAll(addr);

   auto packet = ApplicationProtocolMessage::strToPacket(packet_str);

   return packet.getData();
}

void sendApplication(HighLevelSocket& s, const std::string& msg, struct sockaddr_in* addr)
{
   ApplicationProtocolMessage ap{msg};
   auto p = ap.getPacket();
   s.sendall(p, addr);
}
}