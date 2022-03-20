#include <gtest/gtest.h>

extern "C"
{
#include "core.h"
}

TEST(CoreTest, DummyCore) {
  int core_result = core();
  
  EXPECT_EQ(core_result, 123);
}