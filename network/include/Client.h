//
// Created by danyal on 19.06.18.
//

#ifndef PROTEITESTTASK_CLIENT_H
#define PROTEITESTTASK_CLIENT_H

#include <string>
#include <netinet/in.h>
#include "HighLevelSocket.h"

namespace network {
class Client {
public:
    Client(int, __socket_type);

    virtual ~Client();

    virtual void send(const std::string &msg);

    virtual std::string recv();

    virtual bool isInit() const noexcept;

    Client &operator=(const Client &) = delete;

    Client(const Client &) = delete;

protected:
    bool _init{true};
    HighLevelSocket _sock;
};
}
#endif //PROTEITESTTASK_CLIENT_H
