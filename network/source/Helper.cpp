//
// Created by danyal on 19.06.18.
//

#include <ApplicationProtocol.h>
#include "Helper.h"

Protocol stringToProtocol(std::string_view str) {
    if (str == "UDP")
        return Protocol::UDP;
    else if (str == "TCP")
        return Protocol::TCP;
    else
        throw std::runtime_error{"Incorrect protocol type"};
}

int recvAll(int s, std::string &msg, struct sockaddr_in *addr) {
    int total = 0;
    int n;

    int _buf_size{65536};
    char _buf[_buf_size];
    int bytes_read;

    std::string temp;

    while (temp.size() < ApplicationProtocolMessage::getLenghtHeaderSize()) {
        if (addr != nullptr) {
            socklen_t size = sizeof(*addr);
            bytes_read = recvfrom(s, _buf, _buf_size, 0, (struct sockaddr *) addr, &size);
        } else {
            bytes_read = ::recv(s, _buf, _buf_size, 0);
        }
        if (bytes_read <= 0) return bytes_read;

        temp += std::string(_buf, bytes_read);
    }

    auto data_size = ApplicationProtocolMessage::getSize(temp);

    while (temp.size() < data_size) {
        if (addr != nullptr) {
            socklen_t size = sizeof(*addr);
            bytes_read = recvfrom(s, _buf, _buf_size, 0, (struct sockaddr *) addr, &size);
        } else {
            bytes_read = ::recv(s, _buf, _buf_size, 0);
        }
        if (bytes_read <= 0) return bytes_read;

        temp += std::string(_buf, bytes_read);
    }

    msg = temp;

    return msg.size();
}

int recvApplication(int s, std::string &msg, struct sockaddr_in *addr) {
    int _buf_size{65536};
    char _buf[_buf_size];

    std::string packet;
    int bytes_read = recvAll(s, packet,addr);

    if (bytes_read <= 0) return bytes_read;


    ApplicationProtocolMessage ap{"."};
    ap.setPacket(packet);

    msg = ap.getData();

    return msg.size();
}

int sendall(int s, const std::string &msg, struct sockaddr_in *addr) {
    int total = 0;
    int n;

    while (total < msg.size()) {
        if (addr != nullptr)
            n = sendto(s, msg.substr(total, msg.size() - total).c_str(), msg.size() - total, 0,
                       (struct sockaddr *) addr, sizeof(*addr));
        else
            n = send(s, msg.substr(total, msg.size() - total).c_str(), msg.size() - total, 0);

        if (n == -1) { break; }
        total += n;
    }
    return n == -1 ? -1 : 0;
}

int sendApplication(int s, const std::string &msg, struct sockaddr_in *addr) {
    ApplicationProtocolMessage ap{msg};
    auto p = ap.getPacket();
    int ret_code;
    ret_code = ::sendall(s, p, addr);

    return ret_code;

}