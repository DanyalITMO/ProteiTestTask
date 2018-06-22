//
// Created by danyal on 19.06.18.
//

#ifndef PROTEITESTTASK_SETTINGS_H
#define PROTEITESTTASK_SETTINGS_H

#include "string"
#include "Helper.h"
namespace client {

class Setting {
public:
   static Setting& Instance();

   short getUDPPort() const noexcept;
   short getTCPPort() const noexcept;
   network::Protocol getProtocol() const noexcept;

   void setUDPPort(short) noexcept;
   void setTCPPort(short) noexcept;
   void setProtocol(network::Protocol) noexcept;
private:
    network::Protocol _proto{network::Protocol::TCP};
   short _server_port_udp{3426};
   short _server_port_tcp{3425};

   Setting() = default;
   ~Setting() = default;
};
}
#endif //PROTEITESTTASK_SETTINGS_H
