#ifndef GENERAL_STATE_MOCK_HPP
#define GENERAL_STATE_MOCK_HPP

#include "core_state_interface.hpp"

class GeneralStateMock : public CoreStateInterface
{
    public:
    GeneralStateMock(CoreState core_state);
    virtual ~GeneralStateMock();

    CoreStateInterface* ExecuteState() override;
    CoreState GetCoreState() override;

    private:
    const CoreState core_state;
};

#endif