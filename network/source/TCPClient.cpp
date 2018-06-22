//
// Created by danyal on 19.06.18.
//

#include "TCPClient.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <iostream>

namespace network {
    TCPClient::TCPClient(int port) : Client{port, SOCK_STREAM} {}
}
