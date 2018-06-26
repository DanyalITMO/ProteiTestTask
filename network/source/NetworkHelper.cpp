//
// Created by danyal on 19.06.18.
//

#include <ApplicationProtocol.h>
#include "NetworkHelper.h"
#include "HighLevelSocket.h"

namespace network {

    Protocol stringToProtocol(std::string_view str) {
        if (str == "UDP")
            return Protocol::UDP;
        else if (str == "TCP")
            return Protocol::TCP;
        else
            throw std::runtime_error{"Incorrect protocol type"};
    }

    void recvApplication(HighLevelSocket& s, std::string &msg, struct sockaddr_in *addr) {
        std::string packet_str;
        s.recvAll(packet_str, addr);

        auto packet =ApplicationProtocolMessage::strToPacket(packet_str);

        msg = packet.getData();
    }

    void sendApplication(HighLevelSocket& s, const std::string &msg, struct sockaddr_in *addr) {
        ApplicationProtocolMessage ap{msg};
        auto p = ap.getPacket();
        s.sendall(p, addr);
    }
}