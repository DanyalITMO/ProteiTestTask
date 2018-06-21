//
// Created by danyal on 19.06.18.
//

#include "UDPClient.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstdio>
#include <string>

UDPClient::UDPClient(int port) : Client{port, SOCK_DGRAM}
{}
