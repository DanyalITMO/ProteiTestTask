//
// Created by danyal on 19.06.18.
//

#ifndef PROTEITESTTASK_UDPSESSION_H
#define PROTEITESTTASK_UDPSESSION_H

#include <netinet/in.h>
#include <string>
#include "HighLevelSocket.h"

namespace network {

    class UDPIncomingMessage {
    public:
        UDPIncomingMessage(const struct sockaddr_in &addr, HighLevelSocket socket, std::string_view msg);

        ~UDPIncomingMessage() = default;

        std::string getMessage() const;

        void send(const std::string &message);

        UDPIncomingMessage &operator=(const UDPIncomingMessage &) = delete;

        UDPIncomingMessage(const UDPIncomingMessage &) = delete;

    private:
        struct sockaddr_in _addr;
        HighLevelSocket _server_socket;
        std::string _message;

    };
}

#endif //PROTEITESTTASK_UDPSESSION_H
