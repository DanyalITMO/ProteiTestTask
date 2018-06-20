//
// Created by danyal on 17.06.18.
//

#include "Server.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstdio>

Server::Server(int port) {
}

Server::~Server()
{
    close(_listener);
}