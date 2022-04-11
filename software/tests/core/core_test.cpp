#include "gtest/gtest.h"

extern "C"
{
#include "core_states.h"
#include "core.h"
#include "idle_state.h"
#include "woke_state.h"
}

extern "C"
{
#include "stubs.hpp"
}

class CoreWithWakeUpTrue : public ::testing::Test
{
    private:
        IdleState idle_state;
        WokeState woke_state;

    protected:
        SystemCore system_core;
        
        void SetUp() override
        {
            idle_state = IdleState_Construct(stub_should_wake_up_true, &woke_state);
            woke_state = WokeState_Construct();

            system_core = SystemCore_Construct(
                IdleState_GetHandleCoreState(idle_state)
            );
        }

        void TearDown() override
        {
            WokeState_Destruct(&woke_state);
            IdleState_Destruct(&idle_state);
            SystemCore_Destruct(&system_core);
        }
};

class CoreWithWakeUpFalse : public ::testing::Test
{
    private:
        IdleState idle_state;
        WokeState woke_state;

    protected:
        SystemCore system_core;
        
        void SetUp() override
        {
            idle_state = IdleState_Construct(stub_should_wake_up_false, &woke_state);
            woke_state = WokeState_Construct();

            system_core = SystemCore_Construct(
                IdleState_GetHandleCoreState(idle_state)
            );
        }

        void TearDown() override
        {
            WokeState_Destruct(&woke_state);
            IdleState_Destruct(&idle_state);
            SystemCore_Destruct(&system_core);
        }
};

TEST_F(CoreWithWakeUpTrue, ShouldBeIdleStateAfterInitialization)
{
	/* Given fixture */
	/* When */
	CoreState current_state = SystemCore_GetCurrentState(system_core);

	/* Then */
	EXPECT_EQ(current_state, CORE_STATE_IDLE);
}

TEST_F(CoreWithWakeUpTrue, ShouldBeWokeStateWhenIdleStateAndAdvancingCycleAndWakeUpCallbackIsTrue)
{
	/* Given fixture */
	/* When */
	SystemCore_AdvanceCycle(system_core);

	/* Then */
	EXPECT_EQ(SystemCore_GetCurrentState(system_core), CORE_STATE_WOKE);
}

TEST_F(CoreWithWakeUpFalse, ShouldBeIdleStateWhenIdleStateAndAdvancingCycleAndWakeUpCallbackIsFalse)
{
	/* Given fixture */
	/* When */
	SystemCore_AdvanceCycle(system_core);

	/* Then */
	EXPECT_EQ(SystemCore_GetCurrentState(system_core), CORE_STATE_IDLE);
}
