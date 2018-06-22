//
// Created by danyal on 20.06.18.
//


#include <gtest/gtest.h>

int main(int argc, char **argv)
{
   ::testing::InitGoogleTest(&argc, argv);
   ::testing::GTEST_FLAG(filter) = "ClientUDPTester.ShouldWorkIfMessageVeryBigSize";
   return RUN_ALL_TESTS();
}