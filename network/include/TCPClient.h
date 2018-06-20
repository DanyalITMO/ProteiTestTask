//
// Created by danyal on 19.06.18.
//

#ifndef PROTEITESTTASK_TCPCLIENT_H
#define PROTEITESTTASK_TCPCLIENT_H


#include <string>
#include "Client.h"

class TCPClient : public Client{
public:
    TCPClient(int port);
    void send(const std::string& msg) override;
    std::string recv() override;

    ~TCPClient();
private:
    int _sock;
};


#endif //PROTEITESTTASK_TCPCLIENT_H
