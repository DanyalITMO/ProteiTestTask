//
// Created by danyal on 20.06.18.
//

#include <gtest/gtest.h>
#include <ClientHelper.h>
#include "Settings.h"

std::string random_string(size_t length)
{
   auto randchar = []() -> char {
      const char charset[] =
            "0123456789"
                  "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                  "abcdefghijklmnopqrstuvwxyz";
      const size_t max_index = (sizeof(charset) - 1);
      return charset[rand() % max_index];
   };
   std::string str(length, 0);
   std::generate_n(str.begin(), length, randchar);
   return str;
}

class ClientTester : public ::testing::Test {
public:
   std::unique_ptr<Client> _client;

   ClientTester()
   {
      constexpr int argc{4};
      char* argv[argc];

      argv[1] = "--protocol=TCP";
      argv[2] = "--tcp_port=3425";
      argv[3] = "--udp_port=3426";

      parseArgs(argc, argv);

      _client = makeClient(Setting::Instance().getProtocol());

      if (_client == nullptr) {
         std::cerr << "The client was not created\n";
         return;
      }
   }

   void checker(const std::string& msg)
   {
      _client->send(msg);
      auto recv_msg = _client->recv();

      EXPECT_EQ(msg, recv_msg);
   }
};

TEST_F(ClientTester, small)
{
   auto msg = random_string(8);
   checker(msg);
}


