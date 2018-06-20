//
// Created by danyal on 19.06.18.
//

#include <iostream>
#include "ClientHelper.h"
#include "Settings.h"

void parseArgs(int argc, char* argv[])
{
   for(int i = 1; i < argc; i++)
   {
      parseLine(argv[i]);
   }
}
std::string_view getValue(std::string_view line)
{
   std::string separator{"="};
   auto pos = line.find(separator);
   return line.substr(pos + separator.size(), line.size() - pos);
}
void parseLine(std::string_view line)
{
   if(line.find("--tcp_port=") != std::string::npos)
   {
      Setting::Instance().setTCPPort(static_cast<short>(std::stoi(std::string{getValue(line)})));
   }
   else if(line.find("--udp_port=") != std::string::npos)
   {
      Setting::Instance().setUDPPort(static_cast<short>(std::stoi(std::string{getValue(line)})));
   }
   else if(line.find("--server_address=") != std::string::npos)
   {
      Setting::Instance().setAddress(getValue(line));
   }
   else if(line.find("--protocol=") != std::string::npos)
   {
      Setting::Instance().setProtocol(stringToProtocol(getValue(line)));
   }
}