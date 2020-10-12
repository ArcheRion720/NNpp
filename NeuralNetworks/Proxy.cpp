#include "Proxy.h"

Proxy::Proxy(double* _data, int _limit) : data(_data), limit(_limit)
{
}

double& Proxy::operator[](int index)
{
    if (index < 0 || index > limit)
        throw std::out_of_range("Accessed index in proxy was out of range");

    return data[index];
}
