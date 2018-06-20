//
// Created by danyal on 16.06.18.
//
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <regex>
#include <iostream>
#include "TCPServer.h"

#include <cstdio>
#include <TCPSession.h>

#include "TCPServer.h"
#include "TCPSession.h"

TCPServer::TCPServer(int port) : Server{port}{
   struct sockaddr_in addr;

   _listener = socket(AF_INET, SOCK_STREAM, 0);
   if (_listener < 0) {
      perror("socket");
//        exit(1);
   }

   addr.sin_family = AF_INET;
   addr.sin_port = htons(port);
   addr.sin_addr.s_addr = htonl(INADDR_ANY);
   if (bind(_listener, (struct sockaddr *) &addr, sizeof(addr)) < 0) {
      perror("bind");
//        exit(2);
   }
   listen(_listener, 1);
}

std::shared_ptr<TCPSession> TCPServer::accept() {
    int sock;
    sock = ::accept(_listener, nullptr, nullptr);
    if (sock < 0) {
        perror("accept");
        exit(3);
    }

//    _sessions.push_back((sock));
    return std::make_shared<TCPSession>(sock);//_sessions.back();
}
TCPServer::~TCPServer()
{
//    for(auto&& it : _sessions)
//        it.reset();

    close(_listener);
}


