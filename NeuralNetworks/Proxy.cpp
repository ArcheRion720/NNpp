#include "Proxy.h"

Proxy::Proxy(double* _data, size_t _limit) : data(_data), limit(_limit)
{}

double& Proxy::operator[](size_t index)
{
    if (index < 0 || index > limit)
        throw std::out_of_range("Accessed index in proxy was out of range");

    return data[index];
}
