#include <netinet/in.h>
#include <iostream>
#include <UDPServer.h>
#include <thread>
#include "TCPServer.h"
#include "Helper.h"
#include "Statistic.h"
#include "SyncOut.h"

void commonHandler(const std::string r) {
    Statistic stats;
    auto numbers = filterNumber(r);
    if (!numbers.empty()) {
        stats.add(numbers);
        std::string res;
        res += "Max: " + std::to_string(stats.getMax()) + "\n"
               + " Min: " + std::to_string(stats.getMin()) + "\n"
               + " Sum: " + std::to_string(stats.getSum()) + "\n";

        res += "Sort: \n";
        for (auto &&it : stats.getSort()) {
            res += std::to_string(it) + ",";
        }
        res.pop_back();
        SyncOut{} << res << std::endl;
    }
}

void tcpConnection(int port) {
    TCPServer tcp_server{port};

    if (!tcp_server.isInit())
        return;

    SyncOut{} << "TCP server is start" << std::endl;

    while (true) {
        auto dataSocket = tcp_server.accept();
        try {
            auto r = dataSocket.recv();

            commonHandler(r);
            dataSocket.send(r);
        }
        catch (const std::exception &ex) {
            dataSocket.send("Error");
            std::cerr << ex.what();
        }
    }
}

void udpConnection(int port) {

    UDPServer udp_server{port};

    if (!udp_server.isInit())
        return;

    SyncOut{} << "UDP server is start" << std::endl;

    while (true) {
        auto dataSocket = udp_server.recv();
        auto r = dataSocket.getMessage();

        try {
            commonHandler(r);
            dataSocket.send(r);
        }
        catch (const std::exception &ex) {
            dataSocket.send("Error");
            std::cerr << ex.what();
        }
    }
}


int main() {

    std::thread tcp_thread(tcpConnection, 3425);
    std::thread udp_thread(udpConnection, 3426);

    if (tcp_thread.joinable())
        tcp_thread.join();
    if (udp_thread.joinable())
        udp_thread.join();

    return 0;
}
