//
// Created by danyal on 19.06.18.
//

#ifndef PROTEITESTTASK_CLIENTHELPER_H
#define PROTEITESTTASK_CLIENTHELPER_H

#include <Helper.h>
#include "string"
#include "Settings.h"


void parseArgs(int argc, char* argv[]);
void parseLine(std::string_view);

inline decltype(auto) makeClient(Protocol type)
{
    std::unique_ptr<Client> client;
    if (type == Protocol::UDP)
        client.reset(new UDPClient(Setting::Instance().getUDPPort()));
    else if (type == Protocol::TCP)
        client.reset(new TCPClient(Setting::Instance().getTCPPort()));

    return client;
}

#endif //PROTEITESTTASK_CLIENTHELPER_H
