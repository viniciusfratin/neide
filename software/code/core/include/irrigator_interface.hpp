#ifndef IRRIGATOR_INTERFACE_HPP
#define IRRIGATOR_INTERFACE_HPP


class IrrigatorInterface
{
    public:
    virtual void Irrigate(long irrigation_time_seconds) = 0;
};

#endif