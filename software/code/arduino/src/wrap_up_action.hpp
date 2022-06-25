#ifndef WRAP_UP_ACTION_HPP
#define WRAP_UP_ACTION_HPP

#include "wrap_up_action_interface.hpp"

class WrapUpAction : public WrapUpActionInterface
{
    public:
    WrapUpAction();

    void WrapUp() override;

    virtual ~WrapUpAction();

    private:
    struct impl;
    impl* pImpl;
};

#endif