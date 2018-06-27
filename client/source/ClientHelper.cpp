//
// Created by danyal on 19.06.18.
//

#include "ClientHelper.h"

namespace client {

void parseArgs(int argc, char *argv[]) {
    for (int i = 1; i < argc; i++) {
        parseLine(argv[i]);
    }
}

std::string_view getValue(std::string_view line) {
    std::string separator{"="};
    auto pos = line.find(separator);
    return line.substr(pos + separator.size(), line.size() - pos);
}

void parseLine(std::string_view line) {
    if (line.find("--tcp_port=") != std::string::npos) {
        Setting::Instance().setTCPPort(static_cast<short>(std::stoi(std::string{getValue(line)})));
    } else if (line.find("--udp_port=") != std::string::npos) {
        Setting::Instance().setUDPPort(static_cast<short>(std::stoi(std::string{getValue(line)})));
    } else if (line.find("--protocol=") != std::string::npos) {
        Setting::Instance().setProtocol(network::stringToProtocol(getValue(line)));
    }
}
}