#include <netinet/in.h>
#include <iostream>
#include <UDPServer.h>
#include <thread>
#include <Setting.h>
#include "TCPServer.h"
#include "Helper.h"
#include "Statistic.h"
#include "SyncOut.h"

namespace server {

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
        network::TCPServer tcp_server{port};

        if (!tcp_server.isInit())
            return;

        SyncOut{} << "The TCP server is running on the port "<<Setting::Instance().getTCPPort() << std::endl;

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
/*
    void udpConnection(int port) {

        network::UDPServer udp_server{port};

        if (!udp_server.isInit())
            return;

        SyncOut{} << "The UDP server is running on the port " <<Setting::Instance().getUDPPort()<< std::endl;

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
    }*/

}

int main(int argc, char* argv[]) {
    using namespace server;

    parseArgs(argc, argv);

    std::thread tcp_thread(tcpConnection, Setting::Instance().getTCPPort());
//    std::thread udp_thread(udpConnection, Setting::Instance().getUDPPort());

    if (tcp_thread.joinable())
        tcp_thread.join();
//    if (udp_thread.joinable())
//        udp_thread.join();

    return 0;
}

