//
// Created by danyal on 16.06.18.
//

#ifndef SERVER_HELPER_H
#define SERVER_HELPER_H

#include <regex>
#include <string>
#include <list>

template <typename T = unsigned, template <typename, typename...> class CONT = std::list>
decltype(auto) filterNumber(const std::string &str) {
    CONT<T> ret;
    std::regex r{R"((\d))"};
    for(std::sregex_iterator pos(std::cbegin(str), std::cend(str), r); pos != std::sregex_iterator{}; ++pos)
    {
        ret.push_back(std::stoi(pos->str(1)));
    }

    return ret;
}



#endif //SERVER_HELPER_H
