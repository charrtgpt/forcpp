#ifndef EASYFIND_HPP
#define EASYFIND_HPP

#include <algorith>
#include <stdexcept>

template <typename T>
typename T::iterator easyfind(T &container, int value)
{
    typename T::iterator it;

    it = std::find(container.begin(), container.end(), value);
    if (it ==container.end())
        trow std::runtime_error("Value not found");

    return it;
}


#endif