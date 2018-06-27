//
// Created by danyal on 27.06.18.
//

#include "NetworkError.h"
namespace network {

NetworkError::NetworkError(const std::string& message): std::runtime_error(message), _what_message(message)
{}
const char* NetworkError::what() const noexcept
{
    return _what_message.c_str();
}

}
