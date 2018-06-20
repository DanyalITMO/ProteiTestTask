#include <iostream>
#include "Helper.h"
#include "ClientHelper.h"
#include "Settings.h"

int main(int argc, char* argv[])
{
   parseArgs(argc, argv);
   auto client = makeClient(Setting::Instance().getProtocol());

   std::string msg;
   while(true)
   {
      std::cin>>msg;
      client->send(msg);
      std::cout << client->recv() << std::endl;
   }

   return 0;
}