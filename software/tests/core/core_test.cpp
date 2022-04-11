#include "gtest/gtest.h"

extern "C"
{
#include "core_states.h"
#include "core.h"
#include "idle_state.h"
#include "woke_state.h"
}

Bool stub_should_wake_up_true()
{
	return TRUE;
}

Bool stub_should_wake_up_false()
{
	return FALSE;
}

TEST(CoreTest, ShouldBeIdleStateAfterInitialization)
{
	/* Given */
    IdleState idle_state;
    WokeState woke_state;
    
    idle_state = IdleState_Construct(stub_should_wake_up_true, &woke_state);
    woke_state = WokeState_Construct();

	SystemCore system_core = SystemCore_Construct(
        IdleState_GetHandleCoreState(idle_state)
    );

	/* When */
	CoreState current_state = SystemCore_GetCurrentState(system_core);

	/* Then */
	EXPECT_EQ(current_state, CORE_STATE_IDLE);


    WokeState_Destruct(&woke_state);
    IdleState_Destruct(&idle_state);
	SystemCore_Destruct(&system_core);
}

TEST(CoreTest, ShouldBeNotValidAfterDestruction)
{
	/* Given */
	IdleState idle_state;
    WokeState woke_state;
    
    idle_state = IdleState_Construct(stub_should_wake_up_true, &woke_state);
    woke_state = WokeState_Construct();

	SystemCore system_core = SystemCore_Construct(
        IdleState_GetHandleCoreState(idle_state)
    );

	/* When */
    WokeState_Destruct(&woke_state);
    IdleState_Destruct(&idle_state);
	SystemCore_Destruct(&system_core);

	/* Then */
	EXPECT_EQ(system_core, SYSTEM_CORE_INVALID_INSTANCE);
}

TEST(CoreTest, ShouldBeValidAfterConstruction)
{
	/* Given, when */
	IdleState idle_state;
    WokeState woke_state;
    
    idle_state = IdleState_Construct(stub_should_wake_up_true, &woke_state);
    woke_state = WokeState_Construct();

	SystemCore system_core = SystemCore_Construct(
        IdleState_GetHandleCoreState(idle_state)
    );

	/* Then */
	EXPECT_NE(system_core, SYSTEM_CORE_INVALID_INSTANCE);


    WokeState_Destruct(&woke_state);
    IdleState_Destruct(&idle_state);
	SystemCore_Destruct(&system_core);
}

TEST(CoreTest, ShouldBeWokeStateWhenIdleStateAndAdvancingCycleAndWakeUpCallbackIsTrue)
{
	/* Given */
	IdleState idle_state;
    WokeState woke_state;
    
    idle_state = IdleState_Construct(stub_should_wake_up_true, &woke_state);
    woke_state = WokeState_Construct();

	SystemCore system_core = SystemCore_Construct(
        IdleState_GetHandleCoreState(idle_state)
    );

	/* When */
	SystemCore_AdvanceCycle(system_core);

	/* Then */
	EXPECT_EQ(SystemCore_GetCurrentState(system_core), CORE_STATE_WOKE);


    WokeState_Destruct(&woke_state);
    IdleState_Destruct(&idle_state);
	SystemCore_Destruct(&system_core);
}

TEST(CoreTest, ShouldBeIdleStateWhenIdleStateAndAdvancingCycleAndWakeUpCallbackIsFalse)
{
	/* Given */
	IdleState idle_state;
    WokeState woke_state;
    
    idle_state = IdleState_Construct(stub_should_wake_up_false, &woke_state);
    woke_state = WokeState_Construct();

	SystemCore system_core = SystemCore_Construct(
        IdleState_GetHandleCoreState(idle_state)
    );

	/* When */
	SystemCore_AdvanceCycle(system_core);

	/* Then */
	EXPECT_EQ(SystemCore_GetCurrentState(system_core), CORE_STATE_IDLE);


    WokeState_Destruct(&woke_state);
    IdleState_Destruct(&idle_state);
	SystemCore_Destruct(&system_core);
}
