//
// Created by danyal on 16.06.18.
//

#ifndef SERVER_TCPSESSION_H
#define SERVER_TCPSESSION_H

#include <string>

class TCPSession {
public:
    explicit TCPSession(int);
    std::string recv();
    void send(std::string);

    ~TCPSession();
private:
    const int _buf_size{1024};
    int _sock;
};


#endif
