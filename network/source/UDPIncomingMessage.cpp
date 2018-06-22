//
// Created by danyal on 19.06.18.
//

#include <ApplicationProtocol.h>
#include "UDPIncomingMessage.h"

UDPIncomingMessage::UDPIncomingMessage(const struct sockaddr_in& addr, int socket, std::string_view msg): _addr{addr}, _server_socket{socket}, _message{msg}
{}

std::string UDPIncomingMessage::getMessage() const
{
    return _message;
}

void UDPIncomingMessage::send(const std::string& msg)
{
    ApplicationProtocolMessage ap{msg};
    auto p = ap.getPacket();
    ::sendto(_server_socket, p.c_str(), p.size(), 0, (struct sockaddr *) &_addr, sizeof(_addr));
}
