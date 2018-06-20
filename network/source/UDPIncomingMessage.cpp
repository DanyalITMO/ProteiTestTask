//
// Created by danyal on 19.06.18.
//

#include "UDPIncomingMessage.h"

UDPIncomingMessage::UDPIncomingMessage(const struct sockaddr_in& addr, int socket, std::string_view msg): _addr{addr}, _server_socket{socket}, _message{msg}
{}

std::string UDPIncomingMessage::getMessage() const
{
    return _message;
}

void UDPIncomingMessage::send(const std::string& msg)
{
    ::sendto(_server_socket, msg.c_str(), msg.size(), 0, (struct sockaddr *) &_addr, sizeof(_addr));
}
