//
// Created by danyal on 19.06.18.
//

#ifndef PROTEITESTTASK_UDPCLIENT_H
#define PROTEITESTTASK_UDPCLIENT_H

#include <netinet/in.h>
#include <string>
#include "Client.h"

class UDPClient : public Client {
public:
    explicit UDPClient(int port);
    ~UDPClient() override ;
    void send(const std::string& msg) override;
    std::string recv() override;

private:
    int _sock;
    struct sockaddr_in _addr;
};


#endif //PROTEITESTTASK_UDPCLIENT_H
