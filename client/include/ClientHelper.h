//
// Created by danyal on 19.06.18.
//

#ifndef PROTEITESTTASK_CLIENTHELPER_H
#define PROTEITESTTASK_CLIENTHELPER_H

#include <Helper.h>
#include "string"
#include "Settings.h"
#include "UDPClient.h"
#include "TCPClient.h"

namespace client {
    void parseArgs(int argc, char *argv[]);

    void parseLine(std::string_view);

    inline decltype(auto) makeClient(network::Protocol type) {
        std::unique_ptr<network::Client> client;
        if (type == network::Protocol::UDP)
            client.reset(new network::UDPClient(Setting::Instance().getUDPPort()));
        else if (type == network::Protocol::TCP)
            client.reset(new network::TCPClient(Setting::Instance().getTCPPort()));

        if (client != nullptr)
            if (!client->isInit())
                client.reset();

        return client;
    }
}
#endif //PROTEITESTTASK_CLIENTHELPER_H
