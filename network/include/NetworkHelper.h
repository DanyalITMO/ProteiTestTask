//
// Created by danyal on 19.06.18.
//

#ifndef PROTEITESTTASK_HELPER_H
#define PROTEITESTTASK_HELPER_H

#include <memory>
#include "HighLevelSocket.h"

namespace network {

    enum class Protocol {
        TCP,
        UDP
    };

    Protocol stringToProtocol(std::string_view);

    std::string recvApplication(HighLevelSocket& s, struct sockaddr_in *addr = nullptr);

    void sendApplication(HighLevelSocket& s, const std::string &msg, struct sockaddr_in *addr = nullptr);

}
#endif //PROTEITESTTASK_HELPER_H
