//
// Created by danyal on 19.06.18.
//

#include <iostream>
#include "Settings.h"

Setting& Setting::Instance() {
   static Setting s;
   return s;
}

short Setting::getUDPPort() const noexcept
{
   return _server_port_udp;
}

short Setting::getTCPPort() const noexcept
{
   return _server_port_tcp;
}

std::string Setting::getAddress() const noexcept
{
   return _server_address;
}

Protocol Setting::getProtocol() const noexcept
{
   return _proto;
}

void Setting::setUDPPort(short port) noexcept
{
   _server_port_udp = port;
}

void Setting::setTCPPort(short port) noexcept
{
   _server_port_tcp = port;
}

void Setting::setAddress(std::string_view address) noexcept
{
   _server_address = address;
}

void Setting::setProtocol(Protocol proto) noexcept
{
   _proto = proto;
}
