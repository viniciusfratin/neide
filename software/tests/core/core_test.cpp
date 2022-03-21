#include <gtest/gtest.h>

extern "C"
{
#include "core.h"
}

TEST(CoreTest, ShouldBeIdleStateAfterInitialization)
{
  /* Given */
  SystemCore system_core = SystemCore_Construct();
  
  /* When */
  CoreState current_state = SystemCore_GetCurrentState(system_core);

  /* Then */
  EXPECT_EQ(current_state, CORE_STATE_IDLE);


  SystemCore_Destruct(&system_core);
}

TEST(CoreTest, ShouldBeNotValidAfterDestruction)
{
  /* Given */
  SystemCore system_core = SystemCore_Construct();
  
  /* When */
  SystemCore_Destruct(&system_core);

  /* Then */
  EXPECT_EQ(system_core, SYSTEM_CORE_INVALID_INSTANCE);
}

TEST(CoreTest, ShouldBeValidAfterConstruction)
{
  /* Given, when */
  SystemCore system_core = SystemCore_Construct();
  
  /* Then */
  EXPECT_NE(system_core, SYSTEM_CORE_INVALID_INSTANCE);


  SystemCore_Destruct(&system_core);
}
