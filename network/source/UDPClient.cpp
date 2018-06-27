//
// Created by danyal on 19.06.18.
//

#include "UDPClient.h"

namespace network {

UDPClient::UDPClient(int port) : Client{port, SOCK_DGRAM} {}
}