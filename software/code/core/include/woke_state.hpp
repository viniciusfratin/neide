#ifndef WOKE_STATE_HPP
#define WOKE_STATE_HPP

#include "core_state_interface.hpp"

class WokeState : public CoreStateInterface
{
    public:
    WokeState();

    void SetTransitions(
        CoreStateInterface* soil_humidity_check_state_interface_ptr
    );
    
    CoreStateInterface* ExecuteState() override;
    CoreState GetCoreState() override;

    virtual ~WokeState();

    private:
    struct impl;
    impl* pImpl;
};


#endif