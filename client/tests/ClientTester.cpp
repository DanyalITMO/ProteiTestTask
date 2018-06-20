//
// Created by danyal on 20.06.18.
//

#include <gtest/gtest.h>
#include <ClientHelper.h>
#include "Settings.h"
/*
class ClientTester : public ::testing::Test
{

   ClientTester(){}

};*/


TEST(SettingTests, defaultParameterMustBeCorrectSet)
{
   EXPECT_EQ(3425, Setting::Instance().getTCPPort());
   EXPECT_EQ(3426, Setting::Instance().getUDPPort());
   EXPECT_EQ(Protocol::TCP, Setting::Instance().getProtocol());
}

TEST(SettingTests, ParametersToBeSetMustBeSetCorrectly)
{
   Setting::Instance().setProtocol(Protocol::UDP);
   Setting::Instance().setTCPPort(555);
   Setting::Instance().setUDPPort(556);

   EXPECT_EQ(555, Setting::Instance().getTCPPort());
   EXPECT_EQ(556, Setting::Instance().getUDPPort());
   EXPECT_EQ(Protocol::UDP, Setting::Instance().getProtocol());
}

TEST(ParserTests, ewr)
{
   constexpr int argc{4};
   char *argv[argc];
   argv[1] = "--protocol=TCP";
   argv[2] = "--tcp_port=1111";
   argv[3] = "--udp_port=1112";

   parseArgs(argc, argv);

   EXPECT_EQ(1111, Setting::Instance().getTCPPort());
   EXPECT_EQ(1112, Setting::Instance().getUDPPort());
   EXPECT_EQ(Protocol::TCP, Setting::Instance().getProtocol());
}

