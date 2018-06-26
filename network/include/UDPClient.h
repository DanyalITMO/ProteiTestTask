//
// Created by danyal on 19.06.18.
//

#ifndef PROTEITESTTASK_UDPCLIENT_H
#define PROTEITESTTASK_UDPCLIENT_H

#include <netinet/in.h>
#include <string>
#include "Client.h"

namespace network {

class UDPClient : public Client {
public:
    explicit UDPClient(int port);
};

}

#endif //PROTEITESTTASK_UDPCLIENT_H
