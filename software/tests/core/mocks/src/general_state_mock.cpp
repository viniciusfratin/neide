#include "general_state_mock.hpp"

GeneralStateMock::GeneralStateMock(CoreState core_state) :
core_state(core_state)
{

}

GeneralStateMock::~GeneralStateMock()
{
    
}

CoreStateInterface* GeneralStateMock::ExecuteState()
{
    return this;
}

CoreState GeneralStateMock::GetCoreState()
{
    return this->core_state;
}
