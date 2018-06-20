//
// Created by danyal on 19.06.18.
//

#include "Helper.h"

Protocol stringToProtocol(std::string_view str) // TODO if incorrect
{
   if(str == "UDP")
      return Protocol::UDP;
   else if(str == "TCP")
      return Protocol::TCP;
}