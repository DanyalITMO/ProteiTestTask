//
// Created by danyal on 19.06.18.
//

#include <ApplicationProtocol.h>
#include "Helper.h"
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

    int recvApplication(HighLevelSocket& s, std::string &msg, struct sockaddr_in *addr) {
        std::string packet;
        int bytes_read = s.recvAll(packet, addr);

        if (bytes_read <= 0) return bytes_read;

        ApplicationProtocolMessage ap{"."};
        ap.setPacket(packet);

        msg = ap.getData();

        return msg.size();
    }
    int sendApplication(HighLevelSocket& s, const std::string &msg, struct sockaddr_in *addr) {
        ApplicationProtocolMessage ap{msg};
        auto p = ap.getPacket();
        int ret_code;
        ret_code = s.sendall(p, addr);

        return ret_code;
    }
}