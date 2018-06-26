//
// Created by danyal on 26.06.18.
//

#include <thread>
#include "gtest/gtest.h"
#include "Client.h"
#include "TCPServer.h"
#include "TCPClient.h"

namespace network {


std::string random_string(size_t length) {
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

void tcpConnection(int port) {
    network::TCPServer tcp_server{port};

    if (!tcp_server.isInit()) {
        std::cerr << "TCP server can not be created" << std::endl;
        return;
    }

    try {

        auto session = tcp_server.accept();
        try {
            auto r = session.recv();
            session.send(r);
        }
        catch (const std::runtime_error &ex) {
            session.send(std::string("Error:") + ex.what());
        }
    }
    catch (const std::runtime_error &ex) {
        std::cerr << ex.what() << std::endl;
    }

}

class NetworkTester : public ::testing::Test {
protected:
    const int port;

    std::unique_ptr<Client> _client;
public:

    NetworkTester() : port{3425}/*, _server{port}*/ {
    }

    void SetUp() override {}


    void checker(const std::string &msg) {
        std::thread t(tcpConnection, port);
        std::this_thread::sleep_for(std::chrono::seconds(1));
        _client = std::make_unique<TCPClient>(port);
        _client->send(msg);
        auto recv_msg = _client->recv();/*, _server{port}*/

        if (t.joinable())
            t.join();
        EXPECT_EQ(msg, recv_msg);
    }
};


TEST_F(NetworkTester, IfPassOnlyCharacterShouldWork) {
    auto msg = "qwerty";
    checker(msg);
}

TEST_F(NetworkTester, ShouldWorkIfMessageSmallSize) {
    auto msg = random_string(8);
    checker(msg);
}

TEST_F(NetworkTester, ShouldWorkIfMessageMediumSize) {
    auto msg = random_string(1000);
    checker(msg);
}

TEST_F(NetworkTester, ShouldWorkIfMessagBigSize) {
    auto msg = random_string(10000);
    checker(msg);
}

TEST_F(NetworkTester, ShouldWorkIfMessageVeryBigSize) {
    auto msg = random_string(65536);
    checker(msg);
}

/*
TEST_F(NetworkTester, ShouldThrowExceptionIfMessagOverSizeSize) {
    auto msg = random_string(65537);
    _client->send(msg);

}
*/


}

