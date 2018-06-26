//
// Created by danyal on 21.06.18.
//

#ifndef PROTEITESTTASK_APPLICATIONPROTOCOL_H
#define PROTEITESTTASK_APPLICATIONPROTOCOL_H

#include <string>

namespace network {
class ApplicationProtocolMessage {
public:
   ApplicationProtocolMessage(const std::string&);

   static ApplicationProtocolMessage strToPacket(const std::string&);

   static std::size_t getSize(const std::string&);

   static std::size_t getLenghtHeaderSize();

   std::string getPacket() const noexcept;

   std::string getData() const noexcept;

   std::string getHeader() const noexcept;

   std::size_t getSize() const noexcept;

//   void setPacket(const std::string&);

private:

   ApplicationProtocolMessage() = default;
   static unsigned _lenght_size;
   std::size_t _msg_size;
   std::string _header;
   std::string _msg;
};
}
#endif //PROTEITESTTASK_APPLICATIONPROTOCOL_H
