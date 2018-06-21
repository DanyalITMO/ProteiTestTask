//
// Created by danyal on 21.06.18.
//

#ifndef PROTEITESTTASK_APPLICATIONPROTOCOL_H
#define PROTEITESTTASK_APPLICATIONPROTOCOL_H

#include <string>

class ApplicationProtocolMessage {
   unsigned _lenght_size = 5;
   short _msg_size;
   std::string _header;
   std::string _msg;

   ApplicationProtocolMessage(const std::string& data);

   std::string getPacket() const noexcept;
   std::string getData() const noexcept;
   std::string getHeader() const noexcept;

   void setPacket(const std::string& packet);
};

#endif //PROTEITESTTASK_APPLICATIONPROTOCOL_H
