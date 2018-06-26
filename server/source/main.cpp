#include <netinet/in.h>
#include <iostream>
#include <UDPServer.h>
#include <thread>
#include <Setting.h>
#include "TCPServer.h"
#include "ServerHelper.h"
#include "Statistic.h"
#include "SyncOut.h"
#include "SyncErr.h"

namespace server {

void commonHandler(const std::string& r)
{
   Statistic stats;
   auto numbers = filterNumber(r);
   if (!numbers.empty()) {
      stats.add(numbers);
      std::string res;
      res += "Max: " + std::to_string(stats.getMax()) + "\n"
             + " Min: " + std::to_string(stats.getMin()) + "\n"
             + " Sum: " + std::to_string(stats.getSum()) + "\n";

      res += "Sort: \n";
      for (auto&& it : stats.getSort()) {
         res += std::to_string(it) + ",";
      }
      res.pop_back();
      SyncOut{} << res << std::endl;
   }
}

void tcpConnection(int port)
{
   network::TCPServer tcp_server{port};

   if (!tcp_server.isInit()) {
      SyncErr{} << "TCP server can not be created" << std::endl;
      return;
   }

   SyncOut{} << "The TCP server is running on the port "
             << Setting::Instance().getTCPPort() << std::endl;

   while (true) {
      try {

         auto session = tcp_server.accept();
         try {
            auto r = session.recv();

            commonHandler(r);
            session.send(r);
         }
         catch (const std::runtime_error& ex) {
            session.send(std::string("Error:") + ex.what());
         }
      }
      catch (const std::runtime_error& ex) {
         SyncErr{} << ex.what() << std::endl;
      }
   }

}

void udpConnection(int port)
{

   network::UDPServer udp_server{port};

   if (!udp_server.isInit())
      return;

   SyncOut{} << "The UDP server is running on the port "
             << Setting::Instance().getUDPPort() << std::endl;

   while (true) {
      auto dataSocket = udp_server.recv();
      auto r = dataSocket.getMessage();

      try {
         commonHandler(r);
         dataSocket.send(r);
      }
      catch (const std::exception& ex) {
         dataSocket.send("Error");
         SyncErr{} << ex.what();
      }
   }
}

}

int main(int argc, char* argv[])
{
   using namespace server;

   parseArgs(argc, argv);

   std::thread tcp_thread(tcpConnection, Setting::Instance().getTCPPort());
   std::thread udp_thread(udpConnection, Setting::Instance().getUDPPort());

   if (tcp_thread.joinable())
      tcp_thread.join();
   if (udp_thread.joinable())
      udp_thread.join();

   return 0;
}

