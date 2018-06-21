//
// Created by danyal on 21.06.18.
//

#include <stdexcept>
#include "ApplicationProtocol.h"

unsigned ApplicationProtocolMessage::_lenght_size = 5;
ApplicationProtocolMessage::ApplicationProtocolMessage(const std::string& data) : _msg{data}
{
   if (data.size() > 65536)
      throw std::runtime_error{"data size > 64kb"};

   _msg_size = data.size();
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

std::size_t ApplicationProtocolMessage::getSize() const noexcept
{
   return _msg_size;
}

void ApplicationProtocolMessage::setPacket(const std::string& packet)
{
   _header = packet.substr(0, _lenght_size);
   _msg_size = std::stoull(_header);
   _msg = packet.substr(_lenght_size, packet.size() - _lenght_size);
}

std::size_t ApplicationProtocolMessage::getSize(const std::string& packet)
{
   if(packet.size() < _lenght_size)
      std::runtime_error{"incorrect packet. Size is less than header size"};

   auto header = packet.substr(0, _lenght_size);
   return std::stoull(header);
}
