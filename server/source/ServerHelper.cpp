//
// Created by danyal on 16.06.18.
//

#include "ServerHelper.h"
#include "Setting.h"

namespace server {

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
    }
}

}