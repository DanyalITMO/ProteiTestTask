//
// Created by danyal on 19.06.18.
//

#ifndef PROTEITESTTASK_SETTINGS_H
#define PROTEITESTTASK_SETTINGS_H

#include "string"
#include "Helper.h"



class Setting {
public:
   static Setting& Instance();

   short getUDPPort() const noexcept;
   short getTCPPort() const noexcept;
   std::string getAddress() const noexcept;
   Protocol getProtocol() const noexcept;

   void setUDPPort(short) noexcept;
   void setTCPPort(short) noexcept;
   void setAddress(std::string_view) noexcept;
   void setProtocol(Protocol) noexcept;
private:
   Protocol _proto{Protocol::TCP};
   short _server_port_udp{3426};
   short _server_port_tcp{3425};
   std::string _server_address{"127.0.0.1"};

   Setting() = default;
   ~Setting() = default;
};

#endif //PROTEITESTTASK_SETTINGS_H
