//
// Created by danyal on 22.06.18.
//

#include "Setting.h"

namespace server {

Setting &Setting::Instance() {
    static Setting s;
    return s;
}

short Setting::getUDPPort() const noexcept {
    return _server_port_udp;
}

short Setting::getTCPPort() const noexcept {
    return _server_port_tcp;
}

void Setting::setUDPPort(short port) noexcept {
    _server_port_udp = port;
}

void Setting::setTCPPort(short port) noexcept {
    _server_port_tcp = port;
}
}

