//
// Created by danyal on 19.06.18.
//

#include <ApplicationProtocol.h>
#include <Helper.h>
#include "UDPIncomingMessage.h"
namespace network {

    UDPIncomingMessage::UDPIncomingMessage(const struct sockaddr_in &addr, int socket, std::string_view msg) : _addr{
            addr}, _server_socket{socket}, _message{msg} {}

    std::string UDPIncomingMessage::getMessage() const {
        return _message;
    }

    void UDPIncomingMessage::send(const std::string &msg) {
        int ret_code = sendApplication(_server_socket, msg.c_str(), &_addr);
        if (ret_code < 0)
            throw std::runtime_error{"It's impossible to correctly accept data"};
    }
}