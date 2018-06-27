//
// Created by danyal on 19.06.18.
//

#include "TCPClient.h"

namespace network {
TCPClient::TCPClient(int port) : Client{port, SOCK_STREAM} {}
}
