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