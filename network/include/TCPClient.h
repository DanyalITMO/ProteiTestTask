//
// Created by danyal on 19.06.18.
//

#ifndef PROTEITESTTASK_TCPCLIENT_H
#define PROTEITESTTASK_TCPCLIENT_H


#include "Client.h"

namespace network {

class TCPClient : public Client {
public:
    explicit TCPClient(int port);
};
}

#endif //PROTEITESTTASK_TCPCLIENT_H
