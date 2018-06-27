//
// Created by danyal on 19.06.18.
//

#include "Settings.h"

namespace client {

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

network::Protocol Setting::getProtocol() const noexcept {
    return _proto;
}

void Setting::setUDPPort(short port) noexcept {
    _server_port_udp = port;
}

void Setting::setTCPPort(short port) noexcept {
    _server_port_tcp = port;
}

void Setting::setProtocol(network::Protocol proto) noexcept {
    _proto = proto;
}
}