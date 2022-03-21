#include "gtest/gtest.h"

extern "C"
{
#include "core.h"
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
  SystemCore system_core = SystemCore_Construct(stub_should_wake_up_true);
  
  /* When */
  CoreState current_state = SystemCore_GetCurrentState(system_core);

  /* Then */
  EXPECT_EQ(current_state, CORE_STATE_IDLE);


  SystemCore_Destruct(&system_core);
}

TEST(CoreTest, ShouldBeNotValidAfterDestruction)
{
  /* Given */
  SystemCore system_core = SystemCore_Construct(stub_should_wake_up_true);
  
  /* When */
  SystemCore_Destruct(&system_core);

  /* Then */
  EXPECT_EQ(system_core, SYSTEM_CORE_INVALID_INSTANCE);
}

TEST(CoreTest, ShouldBeValidAfterConstruction)
{
  /* Given, when */
  SystemCore system_core = SystemCore_Construct(stub_should_wake_up_true);
  
  /* Then */
  EXPECT_NE(system_core, SYSTEM_CORE_INVALID_INSTANCE);


  SystemCore_Destruct(&system_core);
}

TEST(CoreTest, ShouldBeWokeStateWhenIdleStateAndAdvancingCycleAndWakeUpCallbackIsTrue)
{
  /* Given */
  SystemCore system_core = SystemCore_Construct(stub_should_wake_up_true);

  /* When */
  SystemCore_AdvanceCycle(system_core);

  /* Then */
  EXPECT_EQ(SystemCore_GetCurrentState(system_core), CORE_STATE_WOKE);


  SystemCore_Destruct(&system_core);
}

TEST(CoreTest, ShouldBeIdleStateWhenIdleStateAndAdvancingCycleAndWakeUpCallbackIsFalse)
{
  /* Given */
  SystemCore system_core = SystemCore_Construct(stub_should_wake_up_false);

  /* When */
  SystemCore_AdvanceCycle(system_core);

  /* Then */
  EXPECT_EQ(SystemCore_GetCurrentState(system_core), CORE_STATE_IDLE);


  SystemCore_Destruct(&system_core);
}
