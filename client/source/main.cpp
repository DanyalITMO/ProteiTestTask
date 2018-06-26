#include <iostream>
#include "NetworkHelper.h"
#include "ClientHelper.h"
#include "Settings.h"

int main(int argc, char* argv[])
{
   using namespace client;
   parseArgs(argc, argv);

   std::string msg;
   while(true)
   {
      auto client = makeClient(Setting::Instance().getProtocol());
      if(client == nullptr)
      {
         std::cerr<<"The client was not created\n";
         return 1;
      }

      try {
         std::cin>>msg;
         client->send(msg);
         std::cout << client->recv() << std::endl;
      }
      catch (std::runtime_error& er)
      {
         std::cerr<<er.what();
      }


   }

   return 0;
}