//
// Created by danyal on 22.06.18.
//

#ifndef PROTEITESTTASK_SETTING_H
#define PROTEITESTTASK_SETTING_H

namespace server {
class Setting {

public:
    static Setting &Instance();

    short getUDPPort() const noexcept;

    short getTCPPort() const noexcept;

    void setUDPPort(short) noexcept;

    void setTCPPort(short) noexcept;

private:
    short _server_port_udp{3426};
    short _server_port_tcp{3425};

    Setting() = default;

    ~Setting() = default;
};
}

#endif //PROTEITESTTASK_SETTING_H
