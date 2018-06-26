//
// Created by danyal on 26.06.18.
//

#include <thread>
#include <condition_variable>
#include <atomic>
#include <functional>
#include <UDPServer.h>
#include <UDPClient.h>
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


class NetworkTester : public ::testing::Test {
protected:
    int port;
    std::function<void(int)> _server_handler;

    std::unique_ptr<Client> _client;
    std::thread _thread;

public:
    void SetUp() override {
        _thread = std::thread(_server_handler, port);
    }

    void TearDown() override {
        if (_thread.joinable())
            _thread.join();
    }


    virtual void checker(const std::string &msg) = 0;
};

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


class TcpTester : public NetworkTester {
public:

    TcpTester() {
        port = 3425;
        _server_handler = tcpConnection;
    }

    virtual void checker(const std::string &msg) {

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        _client = std::make_unique<TCPClient>(port);

        _client->send(msg);
        auto recv_msg = _client->recv();

        EXPECT_EQ(msg, recv_msg);
    }

};


TEST_F(TcpTester, IfPassOnlyCharacterShouldWork) {
    auto msg = "qwerty";
    checker(msg);
}

TEST_F(TcpTester, ShouldWorkIfMessageSmallSize) {
    auto msg = random_string(8);
    checker(msg);
}

TEST_F(TcpTester, ShouldWorkIfMessageMediumSize) {
    auto msg = random_string(1000);
    checker(msg);
}

TEST_F(TcpTester, ShouldWorkIfMessagBigSize) {
    auto msg = random_string(10000);
    checker(msg);
}

TEST_F(TcpTester, ShouldWorkIfMessageVeryBigSize) {
    auto msg = random_string(65536);
    checker(msg);
}


TEST_F(TcpTester, ShouldThrowExceptionIfMessagOverSizeSize) {
    auto msg = random_string(65537);
    ASSERT_ANY_THROW(checker(msg));
    _client->send("placeholder");
    _client->recv();
}

void udpConnection(int port) {

    network::UDPServer udp_server{port};

    if (!udp_server.isInit())
        return;

    auto dataSocket = udp_server.recv();
    auto r = dataSocket.getMessage();

    try {
        dataSocket.send(r);
    }
    catch (const std::exception &ex) {
        dataSocket.send("Error");
        std::cerr << ex.what();
    }
}

class UdpTester : public NetworkTester {
public:

    UdpTester() {
        port = 3426;
        _server_handler = udpConnection;
    }


    virtual void checker(const std::string &msg) {

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        _client = std::make_unique<UDPClient>(port);

        _client->send(msg);
        auto recv_msg = _client->recv();

        EXPECT_EQ(msg, recv_msg);
    }
};


TEST_F(UdpTester, IfPassOnlyCharacterShouldWork) {
    auto msg = "qwerty";
    checker(msg);
}

TEST_F(UdpTester, ShouldWorkIfMessageSmallSize) {
    auto msg = random_string(8);
    checker(msg);
}

TEST_F(UdpTester, ShouldWorkIfMessageMediumSize) {
    auto msg = random_string(1000);
    checker(msg);
}

TEST_F(UdpTester, ShouldWorkIfMessagBigSize) {
    auto msg = random_string(10000);
    checker(msg);
}

TEST_F(UdpTester, ShouldWorkIfMessageVeryBigSize) {
    auto msg = random_string(65536);
    checker(msg);
}


TEST_F(UdpTester, ShouldThrowExceptionIfMessagOverSizeSize) {
    auto msg = random_string(65537);
    ASSERT_ANY_THROW(checker(msg));
    _client->send("placeholder");
    _client->recv();
}


}

