//
// Created by danyal on 16.06.18.
//

#ifndef SERVER_TCPSESSION_H
#define SERVER_TCPSESSION_H

#include <string>
namespace network {

    class TCPSession {
    public:
        explicit TCPSession(int);

        std::string recv();

        void send(std::string);

        ~TCPSession();

        TCPSession &operator=(const TCPSession &) = delete;

        TCPSession(const TCPSession &) = delete;

    private:
        const int _buf_size{1024};
        int _sock;
    };
}

#endif
