//
// Created by danyal on 27.06.18.
//

#ifndef PROTEITESTTASK_NETWORKERROR_H
#define PROTEITESTTASK_NETWORKERROR_H

#include<stdexcept>

namespace network {

class NetworkError : public std::runtime_error
{
    std::string _what_message;
public:
    NetworkError(const std::string&);
    virtual const char* what() const noexcept override;
};
}
#endif //PROTEITESTTASK_NETWORKERROR_H
