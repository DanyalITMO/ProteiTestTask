//
// Created by danyal on 19.06.18.
//

#ifndef PROTEITESTTASK_UDPSESSION_H
#define PROTEITESTTASK_UDPSESSION_H

#include <netinet/in.h>
#include <string>

class UDPIncomingMessage {
public:
    UDPIncomingMessage(const struct sockaddr_in& addr, int socket, std::string_view msg);
    ~UDPIncomingMessage() = default;
    std::string getMessage() const;
    void send(const std::string& message);

private:
    struct sockaddr_in _addr;
    const int _server_socket;
    std::string _message;

};


#endif //PROTEITESTTASK_UDPSESSION_H
