#include <netinet/in.h>
#include <iostream>
#include <UDPServer.h>
#include <thread>
#include "TCPServer.h"
#include "Helper.h"
#include "Statistic.h"


/**/

void commonHandler()
{}
void tcpConnection(int port) {
    TCPServer socketWrapper{port};

    while (true) {
        auto dataSocket = socketWrapper.accept();
        auto r = dataSocket->recv();
        std::cout << "TCP incoming message: " << r << std::endl;

        try {
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
                std::cout << res << std::endl;
            }
            dataSocket->send(r);
        }
        catch (const std::exception &ex) {
            dataSocket->send("Error");
            std::cerr << ex.what();
        }
    }
}

void UDPConnection(int port) {
    UDPServer socketWrapper{port};

    while (true) {
        auto dataSocket = socketWrapper.recv();
        auto r = dataSocket.getMessage();
        std::cout << "UDP incoming message: " << r << std::endl;

        try {
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
                std::cout << res << std::endl;
            }
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
    std::thread udp_thread(UDPConnection, 3426);

    if (tcp_thread.joinable())
        tcp_thread.join();
    if (udp_thread.joinable())
        udp_thread.join();

    return 0;
}
