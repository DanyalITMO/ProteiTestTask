//
// Created by danyal on 17.06.18.
//

#ifndef PROTEITESTTASK_SERVER_H
#define PROTEITESTTASK_SERVER_H

#include "HighLevelSocket.h"

#include <sys/socket.h>

namespace network {

class Server {
public:
    explicit Server(int port, __socket_type type) noexcept;

    virtual ~Server();

    bool isInit() const noexcept;

    Server &operator=(const Server &) = delete;

    Server(const Server &) = delete;

protected:
    bool _init{true};
    HighLevelSocket _listener;


};
}
#endif //PROTEITESTTASK_SERVER_H
