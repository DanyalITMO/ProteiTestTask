//
// Created by danyal on 21.06.18.
//

#ifndef PROTEITESTTASK_APPLICATIONPROTOCOL_H
#define PROTEITESTTASK_APPLICATIONPROTOCOL_H

#include <string>

class ApplicationProtocolMessage {
public:
    static std::size_t getSize(const std::string&);

    ApplicationProtocolMessage(const std::string&);

    std::string getPacket() const noexcept;

    std::string getData() const noexcept;

    std::string getHeader() const noexcept;

    std::size_t getSize() const noexcept;

    void setPacket(const std::string&);

private:
    static unsigned _lenght_size;
    std::size_t _msg_size;
    std::string _header;
    std::string _msg;
};

#endif //PROTEITESTTASK_APPLICATIONPROTOCOL_H
