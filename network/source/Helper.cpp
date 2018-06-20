//
// Created by danyal on 19.06.18.
//

#include "Helper.h"

Protocol stringToProtocol(std::string_view str) // TODO if incorrect
{
    if (str == "UDP")
        return Protocol::UDP;
    else if (str == "TCP")
        return Protocol::TCP;
    else
        throw std::runtime_error{"Incorrect protocol type"};
}

int sendall(int s, const std::string &msg) {
    int total = 0;
    int n;

    while (total < msg.size()) {
        n = send(s, msg.substr(total, msg.size() - total).c_str(), msg.size() - total, 0);
        if (n == -1) { break; }
        total += n;
    }
    return n == -1 ? -1 : 0;
}
// здесь количество действительно посланных байт
// вернуть -1 при сбое, 0 при успехе