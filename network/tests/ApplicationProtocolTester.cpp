//
// Created by danyal on 22.06.18.
//

#include <gtest/gtest.h>
#include "ApplicationProtocol.h"

class ApplicationProtocolTester : public ::testing::Test
{

};


TEST(APtests, t1)
{
    std::string msg{"data"};
    std::string expect_packet{"00004data"};
    ApplicationProtocolMessage ap{msg};

    EXPECT_EQ(expect_packet, ap.getPacket());
    EXPECT_EQ(msg, ap.getData());
    EXPECT_EQ(msg.size(), ap.getSize());
}

