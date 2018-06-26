//
// Created by danyal on 19.06.18.
//

#include <ApplicationProtocol.h>
#include <NetworkHelper.h>
#include "UDPIncomingMessage.h"
#include "HighLevelSocket.h"

namespace network {

UDPIncomingMessage::UDPIncomingMessage(const struct sockaddr_in &addr, HighLevelSocket socket, std::string_view msg)
        : _addr{
        addr}, _server_socket{socket}, _message{msg} {}

std::string UDPIncomingMessage::getMessage() const {
    return _message;
}

void UDPIncomingMessage::send(const std::string &msg) {
    sendApplication(_server_socket, msg.c_str(), &_addr);
}
}