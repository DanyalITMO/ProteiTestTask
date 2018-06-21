//
// Created by danyal on 21.06.18.
//

#include <stdexcept>
#include "ApplicationProtocol.h"

ApplicationProtocolMessage::ApplicationProtocolMessage(const std::string& data)
{
   if (data.size() > 65536)
      throw std::runtime_error{"data size > 64kb"};

   _header = std::to_string(data.size());

   while (_header.size() < _lenght_size) {
      _header = "0" + _header;
   }

}

std::string ApplicationProtocolMessage::getPacket() const noexcept
{
   return _header + _msg;
}

std::string ApplicationProtocolMessage::getData() const noexcept
{
   return _msg;
}

std::string ApplicationProtocolMessage::getHeader() const noexcept
{
   return _header;
}

void ApplicationProtocolMessage::setPacket(const std::string& packet)
{
   _header = packet.substr(0, _lenght_size);
   _msg_size = std::stol(_header);
   _msg = packet.substr(_lenght_size, packet.size() - _lenght_size);
}
