//
// Created by danyal on 26.06.18.
//

#include <TCPServer.h>
#include "gtest/gtest.h"
#include "Client.h"
#include "../../client/include/Settings.h"
#include "../../client/include/ClientHelper.h"

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

class IntegrateTCPTester : public ::testing::Test {
public:
   std::unique_ptr<network::Client> _client;
   const int port{3425};
   network::TCPServer tcp_server{port};

   IntegrateTCPTester()
   {
      constexpr int argc{3};
      char* argv[argc];

      argv[1] = "--protocol=TCP";
      strcpy(argv[2],std::string{std::string{"--tcp_port="} + std::to_string(port)}.c_str());

      client::parseArgs(argc, argv);

      _client = client::makeClient(client::Setting::Instance().getProtocol());

      if (_client == nullptr) {
         std::cerr << "The client was not created\n";
         return;
      }

      if (!tcp_server.isInit())
         return;

   }

   void checker(const std::string& msg)
   {
      _client->send(msg);
      auto recv_msg = _client->recv();

      EXPECT_EQ(msg, recv_msg);
   }
};

TEST_F(IntegrateTCPTester, IfPassOnlyCharacterShouldWork)
{
   auto msg = "qwerty";
   checker(msg);
}

TEST_F(IntegrateTCPTester, ShouldWorkIfMessageSmallSize)
{
   auto msg = random_string(8);
   checker(msg);
}

TEST_F(IntegrateTCPTester, ShouldWorkIfMessageMediumSize)
{
   auto msg = random_string(1000);
   checker(msg);
}

TEST_F(IntegrateTCPTester, ShouldWorkIfMessagBigSize)
{
   auto msg = random_string(10000);
   checker(msg);
}

TEST_F(IntegrateTCPTester, ShouldWorkIfMessageVeryBigSize)
{
   auto msg = random_string(65536);
   checker(msg);
}

TEST_F(IntegrateTCPTester, ShouldThrowExceptionIfMessagOverSizeSize)
{
   auto msg = random_string(65537);
   ASSERT_ANY_THROW(_client->send(msg));

}

