#include "gtest/gtest.h"

extern "C"
{
#include "core_states.h"
#include "core.h"
#include "idle_state.h"
#include "woke_state.h"
#include "soil_humidity_check_state.h"
}

#include "stubs_cpp.hpp"
#include "mocks_cpp.hpp"

class CoreInitialIdleWithWakeUpTrue : public ::testing::Test
{
    private:
        IdleState idle_state;
        GeneralStateMock woke_state_mock;
        CoreStateInterface idle_state_interface;
        CoreStateInterface woke_state_mock_interface;

    protected:
        SystemCore system_core;
        
        void SetUp() override
        {
            idle_state = IdleState_Construct(stub_should_wake_up_true, &woke_state_mock_interface);
            woke_state_mock = GeneralStateMock_Construct(CORE_STATE_WOKE);

            idle_state_interface = IdleState_GetCoreStateInterface(idle_state);
            woke_state_mock_interface = GeneralStateMock_GetCoreStateInterface(woke_state_mock);

            system_core = SystemCore_Construct(
                idle_state_interface
            );
        }

        void TearDown() override
        {
            GeneralStateMock_Destruct(&woke_state_mock);
            IdleState_Destruct(&idle_state);
            SystemCore_Destruct(&system_core);
        }
};

class CoreInitialIdleWithWakeUpFalse : public ::testing::Test
{
    private:
        IdleState idle_state;
        GeneralStateMock woke_state_mock;
        CoreStateInterface idle_state_interface;
        CoreStateInterface woke_state_mock_interface;

    protected:
        SystemCore system_core;
        
        void SetUp() override
        {
            idle_state = IdleState_Construct(stub_should_wake_up_false, &woke_state_mock_interface);
            woke_state_mock = GeneralStateMock_Construct(CORE_STATE_WOKE);

            idle_state_interface = IdleState_GetCoreStateInterface(idle_state);
            woke_state_mock_interface = GeneralStateMock_GetCoreStateInterface(woke_state_mock);

            system_core = SystemCore_Construct(
                idle_state_interface
            );
        }

        void TearDown() override
        {
            GeneralStateMock_Destruct(&woke_state_mock);
            IdleState_Destruct(&idle_state);
            SystemCore_Destruct(&system_core);
        }
};

class CoreInitialWoke : public ::testing::Test
{
    private:
        WokeState woke_state;
        GeneralStateMock soil_humidity_check_state_mock;
        CoreStateInterface woke_state_interface;
        CoreStateInterface soil_humidity_check_state_mock_interface;

    protected:
        SystemCore system_core;
        
        void SetUp() override
        {
            woke_state = WokeState_Construct(&soil_humidity_check_state_mock_interface);
            soil_humidity_check_state_mock = GeneralStateMock_Construct(CORE_STATE_SOIL_HUMIDITY_CHECK);

            woke_state_interface = WokeState_GetCoreStateInterface(woke_state);
            soil_humidity_check_state_mock_interface = GeneralStateMock_GetCoreStateInterface(soil_humidity_check_state_mock);

            system_core = SystemCore_Construct(
                woke_state_interface
            );
        }

        void TearDown() override
        {
            GeneralStateMock_Destruct(&soil_humidity_check_state_mock);
            WokeState_Destruct(&woke_state);
            SystemCore_Destruct(&system_core);
        }
};

TEST_F(CoreInitialIdleWithWakeUpTrue, ShouldBeIdleStateAfterInitialization)
{
	/* Given fixture */
	/* When */
	CoreState current_state = SystemCore_GetCurrentState(system_core);

	/* Then */
	EXPECT_EQ(current_state, CORE_STATE_IDLE);
}

TEST_F(CoreInitialIdleWithWakeUpTrue, ShouldBeWokeStateWhenIdleStateAndAdvancingCycleAndWakeUpCallbackIsTrue)
{
	/* Given fixture */
	/* When */
	SystemCore_AdvanceCycle(system_core);

	/* Then */
	EXPECT_EQ(SystemCore_GetCurrentState(system_core), CORE_STATE_WOKE);
}

TEST_F(CoreInitialIdleWithWakeUpFalse, ShouldBeIdleStateWhenIdleStateAndAdvancingCycleAndWakeUpCallbackIsFalse)
{
	/* Given fixture */
	/* When */
	SystemCore_AdvanceCycle(system_core);

	/* Then */
	EXPECT_EQ(SystemCore_GetCurrentState(system_core), CORE_STATE_IDLE);
}

TEST_F(CoreInitialWoke, ShouldBeSoilHumidityCheckStateWhenWokeStateAndAdvancingCycle)
{
	/* Given fixture */
	/* When */
	SystemCore_AdvanceCycle(system_core);

	/* Then */
	EXPECT_EQ(SystemCore_GetCurrentState(system_core), CORE_STATE_SOIL_HUMIDITY_CHECK);
}
