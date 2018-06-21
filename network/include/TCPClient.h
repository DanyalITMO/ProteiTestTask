//
// Created by danyal on 19.06.18.
//

#ifndef PROTEITESTTASK_TCPCLIENT_H
#define PROTEITESTTASK_TCPCLIENT_H


#include <string>
#include "Client.h"

class TCPClient : public Client{
public:
    explicit TCPClient(int port);
};


#endif //PROTEITESTTASK_TCPCLIENT_H
