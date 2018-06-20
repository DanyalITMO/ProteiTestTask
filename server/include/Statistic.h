//
// Created by danyal on 16.06.18.
//

#ifndef SERVER_STATISTIC_H
#define SERVER_STATISTIC_H

#include <set>
#include <map>
#include <numeric>

template <typename ValueType = unsigned>
class Statistic {
    std::multiset<ValueType, std::greater<ValueType>> _numbers;

public:
    template <template <typename , typename...> class CONT>
    void add(const CONT<ValueType>& arg)
    {
        //TODO fix it
        for(auto&& it : arg)
        {
            _numbers.insert(it);
        }
//        std::copy(std::begin(arg), std::end(arg), std::end(_numbers));
    }
/*getMin optional version
 * */
    decltype(auto) getOptionalMin() const noexcept
    {
        std::optional<typename decltype(_numbers)::value_type> ret;
        if(_numbers.empty())return ret;

        ret = *std::cbegin(_numbers);
        return ret;
    }

    decltype(auto) getMin() const
    {
        if(_numbers.empty()) throw std::runtime_error{"Static has not data"};
        return *std::cbegin(_numbers);
    }

    decltype(auto) getOptionalMax() const noexcept
    {
        std::optional<typename decltype(_numbers)::value_type> ret;
        if(_numbers.empty())return ret;

        ret = *std::prev(std::cend(_numbers));
        return ret;
    }

    decltype(auto) getMax() const
    {
        if(_numbers.empty()) throw std::runtime_error{"Static has not data"};
        return *std::prev(std::cend(_numbers));
    }

    decltype(auto) getOptionalSum() const noexcept
    {
        //TODO add type_traits
        std::optional<std::size_t> ret;
        if(_numbers.empty())return ret;

        ret = std::accumulate(std::cbegin(_numbers), std::cend(_numbers), typename decltype(_numbers)::value_type{});
        return ret;
    }

    decltype(auto) getSum() const
    {
        if(_numbers.empty()) throw std::runtime_error{"Static has not data"};
        return std::accumulate(std::cbegin(_numbers), std::cend(_numbers), typename decltype(_numbers)::value_type{});
    }

    const std::multiset<ValueType, std::greater<ValueType>>& getSort() const
    {
        return _numbers;
    }

};


#endif //SERVER_STATISTIC_H
