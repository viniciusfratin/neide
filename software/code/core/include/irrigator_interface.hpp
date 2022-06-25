#ifndef IRRIGATOR_INTERFACE_HPP
#define IRRIGATOR_INTERFACE_HPP

#include <cstdint>

class IrrigatorInterface
{
    public:
    virtual void Irrigate(int32_t irrigation_time_seconds) = 0;
};

#endif